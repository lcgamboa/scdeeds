
#include<stdio.h>
#include<string.h>

#include "deeds.h"
#include "crt_asm.h"
#include "crun8080lib_asm.h"

//#define _DEV_

int main(int argc, char ** argv)
{
  FILE * fin;
  FILE * fout;
  char fname[1024];
  char fnameo[1024];
  char line[1024]; 	
  char buff[1024]; 	
  char temp[1024]; 	
  char label[256];

  char * ptr;
  char * end;

  unsigned int mc=0xFC00+(8*8);

  if(argc != 2)
  {
    printf("use: %s filename.s\n",argv[0]);
    return -1;
  }

  strcpy(fname,argv[1]);

  ptr=strrchr(fname,'.');
  strncpy(fnameo,fname,strlen(fname)-strlen(ptr));
  fnameo[strlen(fname)-strlen(ptr)]=0;
  strcat(fnameo,".asm");


  fin=fopen(fname,"r");
  
  fout=fopen(fnameo,"w");
	
  if(!fout)
  {
    printf("Error writting file (%s)\n",fnameo);
    return -1;
  }

  if(fin)
  {

#ifndef _DEV_
    fprintf(fout,"%s\n",crt);
#endif

//CODE	  
    while(fgets(line,1024,fin))
    {
       if(line[0]==';')
       {
	    fprintf(fout,line);
            continue;
       };	    
       if(strstr(line,".module"))continue;	
       if(strstr(line,".list"))continue;	
       if(strstr(line,".nlist"))continue;	
       if(strstr(line,".globl"))continue;	
       
       if(strstr(line,".area"))
       {
         if(strstr(line,"GENERATED_DATA"))
	 {
	   break;
	 } 
	 else
	 {
	   continue;
	 }
       }	       
       
       while((ptr=strstr(line,"#")))
       {
	 int len= strlen(line)-strlen(ptr);
         int res;

         strncpy(buff,line,len);
	 buff[len]=0;

	 strcpy(temp,ptr+1);
	 end=strtok(temp,"\n \t,");
	 res=strlen(end);
	 strncat(buff,ptr+1,res);
	 strcat(buff,"d");
	 strcat(buff,ptr+1+res);

	 strcpy(line,buff);
       }

       
       if((ptr=strstr(line,"$")))
       {
         ptr[0]='l';
       }	
	    
       fprintf(fout,line);	
    }
    fprintf(fout,"mem_init:\n");
//DATA	
    while(fgets(line,1024,fin))
    {
       if(line[0]==';')
       {
	    fprintf(fout,line);
            continue;
       };	    
       if(strstr(line,".globl"))continue;	
       if((ptr=strstr(line,":")))
       {
	       int len= strlen(line)-strlen(ptr);
	       strncpy(buff,line,len);
	       buff[len]=0;
	       	
	       strcpy(label,buff);
	       strcpy(line,buff);
       }	       
       while((ptr=strstr(line,"#")))
       {
	 int len= strlen(line)-strlen(ptr);
         int res;

         strncpy(buff,line,len);
	 buff[len]=0;

	 strcpy(temp,ptr+1);
	 end=strtok(temp,"\n \t,");
	 res=strlen(end);
	 strncat(buff,ptr+1,res);
	 strcat(buff,"d");
	 strcat(buff,ptr+1+res);

	 strcpy(line,buff);
       }
       if((ptr=strstr(line,".db")))
       {
	 if((end=strstr(line,",")))
	 {
	   strcpy(temp,ptr+3);
	   
	   if(label[0])
	   {
              sprintf(line,"	EQU %05Xh\n",mc);
	      sprintf(buff,"	LXI B,%s\n",label);
	      strcat(line,buff);
	      label[0]=0;
	   }
	   else
	   {
	     line[0]=0;
	   }		   
	   
	   end=strtok(temp,"\n \t,");
	   do{
	     sprintf(buff,"	MVI A,%s\n	STAX B\n	INX B\n",end);
	     strcat(line,buff);	
	     mc++;
	   }while((end=strtok(NULL,"\n \t,")));

	 }
	 else
	 {	 
	   strcpy(temp,ptr+4);      
           sprintf(line,"	EQU %05Xh\n",mc);
	   sprintf(buff,"	MVI A,%s	STA %s\n",temp,label);
	   strcat(line,buff);
	   mc++;
	 }
       }	
       if((ptr=strstr(line,".dw")))
       {
	 if((end=strstr(line,",")))
	 {
	   strcpy(temp,ptr+3);
	   
	   if(label[0])
	   {
              sprintf(line,"	EQU %05Xh\n",mc);
	      sprintf(buff,"	LXI B,%s\n",label);
	      strcat(line,buff);
	      label[0]=0;
	   }
	   else
	   {
	     line[0]=0;
	   }		   
	   
	   end=strtok(temp,"\n \t,");
	   do{
	     unsigned int value;	   
	     sscanf(end,"%u",&value);	   
	     sprintf(buff,"	MVI A,%ih\n	STAX B\n	INX B\n",value & 0x00FF);
	     strcat(line,buff);	
	     sprintf(buff,"	MVI A,%ih\n	STAX B\n	INX B\n",(value & 0xFF00)>>8);
	     strcat(line,buff);	
	     mc++;
	     mc++;
	   }while((end=strtok(NULL,"\n \t,")));

	 }
	 else
	 {	 
	   strcpy(temp,ptr+4);      
           sprintf(line,"	EQU %05Xh\n",mc);
	   sprintf(buff,"	LXI H,%s	SHLD %s\n",temp,label);
	   strcat(line,buff);
	   mc++;
	   mc++;
	 }
       }	
       fprintf(fout,line);	
    }
    fprintf(fout,"	ret\n");

    fclose(fin);

#ifndef _DEV_
    fprintf(fout,"%s\n",cruntime);
#endif
    fclose(fout);

#ifndef _DEV_
//Deeds MC8 file
    strcpy(fname,fnameo);
    ptr=strrchr(fname,'.');
    strncpy(fnameo,fname,strlen(fname)-strlen(ptr));
    fnameo[strlen(fname)-strlen(ptr)]=0;
    strcat(fnameo,".mc8");
  
    fin=fopen(fname,"r");
  
    fout=fopen(fnameo,"w");
	
    if(!fout)
    {
      printf("Error writting file (%s)\n",fnameo);
      return -1;
    }

    if(fin)
    {
      //deeds header
      fprintf(fout,"%s\n",deeds);
     
      while(fgets(line,1024,fin))
      {
         fprintf(fout,line);
      }
      fclose(fin);
      fclose(fout);
    }
    else
    {
      printf("Error open file (%s)\n",fname);
    }
#endif
  }
  else
  {
    printf("Error open file (%s)\n",fname);
  }

  return 0;
}


