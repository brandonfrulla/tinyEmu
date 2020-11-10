// switch.s
// emu $ r 13 400
// emu $ m 400 1  
// emu $ m 404 2  
// emu $ m 408 3  
    ldr r0, [r13,#0]    //a = 1
    ldr r1, [r13,#4]    //b = 2
    ldr r2, [r13,#8]    //c = 3
    cmp r0, #1          //compare a to 1
    beq Case1           //Branch if a = 1
    cmp r0, #2          //compare a to 2
    beq Case2           //Branch if a = 2
    cmp r0, #3          //compare a to 3
    beq Case3           //Branch if a = 3
    cmp r0, #4          //compare a to 4
    beq Case4           //Branch if a = 4
    cmp r0, #5          //compare a to 5
    beq Case5           //Branch if a = 5
    cmp r0, #6          //compare a to 6
    beq Case6           //Branch if a = 6
    cmp r0, #7          //compare a to 7
    beq Case7           //Branch if a = 7
    b CaseDef           //Branch to default
Case1:                   // a = 1
        add r0, r1, r2   // add b + c 
        str r0, [r13,#0]
        b endif          //
Case2:                   // a = 2
        sub r0, r1, r2   // subtract b + c
        str r0, [r13,#0]
        b endif          //
Case3:                   // a = 3
        mul r0, r1, r2   // multiply b and c
        str r0, [r13,#0]
        b endif          //
Case4:                   // a = 4
        mul r0, r1, r2   // divide b and c
        str r0, [r13,#0]
        b endif          //
Case5:                   // a = 5
        and r0, r1, r2   // and b and c
        str r0, [r13,#0]
        b endif          //
Case6:                   // a = 6
        orr r0, r1, r2   //or b and c
        str r0, [r13,#0]
        b endif          //
Case7:                   // a = 7
        eor r0, r1, r2   //xor b and c
        str r0, [r13,#0]
        b endif          //
CaseDef:                 // Default
        mov r0, #0       // put a somewhere
        str r0, [r13,#0]
endif:                   //Endpoint of program