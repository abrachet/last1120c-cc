.extern main
.global _start

// obviously there is very little runtime in this 'version' of C
// so there is not much to do except call main

_start:
    // ignore command line arguments for now
    mov x0, 0
    mov x1, 0
    bl main
    mov x8, 0x900001
    SVC 0
