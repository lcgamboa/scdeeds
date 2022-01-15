

# SCDEEDS

This program is a simple C source coder editor (scdeeds) to use [scc8080](https://github.com/ncb85/SmallC-85) small c compiler with [DeedsMcE](https://www.digitalelectronicsdeeds.com/downloads.html) 8080 assembly simulator.


The scdeed is a frontend that uses other command-line open source programs in backend:

 - The [scc8080](https://github.com/ncb85/SmallC-85) program is the small c compiler, the generated assembly code is to be loaded into RAM. 
 - The sc2deeds program translates the assembly code to be compatible with [DeedsMcE](https://www.digitalelectronicsdeeds.com/downloads.html) and loaded into ROM. 
 - The [8085asm](https://github.com/lcgamboa/8085asm) program is used to test otherwise there is no error in the assembly program before loading it into McE.



![SCDEEDS](screenshot.png?raw=true "SCDEEDS")

