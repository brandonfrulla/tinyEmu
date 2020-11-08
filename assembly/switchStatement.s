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
    cmp r0, 0x2
    beq case2
    cmp r0, 0x3
    beq case3
    cmp r0, 0x4
    beq case4
    cmp r0, 0x5
    beq case5
    cmp r0, 0x6
    beq case6
    cmp r0, 0x7
    beq case7
    b caseDefault
case1:
    
case2:

case3:

case4:

case5:

case6:

case7:

caseDefault:
