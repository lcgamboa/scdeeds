
unsigned int  i=0;

main()
{
  while(1)
  {
     for(i=0;i<10;i++);
 #asm
	PUSH PSW
	MVI A, 00h
	OUT 00h
	OUT 01h
	OUT 02h
	OUT 03h
	POP PSW
#endasm
     for(i=0;i<10;i++);
 #asm
	PUSH PSW
	MVI A, 0FFh
	OUT 00h
	OUT 01h
	OUT 02h
	OUT 03h
	POP PSW
#endasm
   }
}
