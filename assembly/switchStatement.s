// switchstatement.s
// emu $ r d 400
// emu $ m 400 1 
// emu $ m 404 2
// emu $ m 408 3
main:
    ldr r0, [r13, #0] // a = 1
    ldr r1, [r13, #4] // b = 2
    ldr r2, [r13, #8] // c = 3
    
    cmp r0, 0x1       // compare a to 1
    beq case1
    cmp r0, 0x2       // compare a to 2
    beq case2
    cmp r0, 0x3       // compare a to 3
    beq case3
    cmp r0, 0x4       // compare a to 4
    beq case4
    cmp r0, 0x5       // compare a to 5
    beq case5
    cmp r0, 0x6       // compare a to 6
    beq case6
    cmp r0, 0x7       // compare a to 7
    beq case7
    b caseDefault

case1:
    add r0, r1, r2      // adding b & c, storing in a
    str r0, [r13, #0]
    endif    
case2:
    sub r0, r1, r2      // subtracting c from b, storing in a
    str r0, [r13, #0]
    endif
case3:
    mul r0, r1, r2      // multiplying b and c, storing in a
    str r0, [r13, #0]
    endif
case4:
    div r0, r1, r2      // dividing b and c, storing in a
    str r0, [r13, #0]
    endif
case5:
    and r0, r1, r2      // comparing b && c, storing in a
    str r0, [r13, #0]  
    endif
case6:
    orr r0, r1, r2      // comparing b || c, storing in a
    str r0, [r13, #0]
    endif
case7:
    eor r0, r1, r2      // comparing b ^ c, storing in a
    str r0, [r13, #0]
    endif
caseDefault:
    mov r0, #0          // make a = 0
    str r0, [r13, #0]
endif:
    //blank af