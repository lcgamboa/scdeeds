const char  crt[]=";       Run time start off for Small C.\n"
"\tORG 0000h\n"
"\tjmp\tstart\n"
"\tORG 003Ch\n"
"start:\n"
"        lxi     sp, 0FFFFh       ; load stack pointer\n"
"        call    mem_init         ; call memory initialization\n"
"        call    main             ; call main program\n"
"crtend: jmp     crtend\n";
