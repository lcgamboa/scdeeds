
//#include <def1.h>
//#include <file.c>

#asm
	ORG 00038h
	JMP int_7
	ORG 0100h
#endasm

int_7()
{
#asm
	push PSW
	in 00
	out 00
	pop PSW
	ei	
#endasm	
}	

unsigned char _a=0x12;
unsigned int  _b=0x1234;

main()
{

 _a=4;

// _x=22;

 _b =6;
#asm
	EI	
#endasm


  while(1)
  {

  }

}
