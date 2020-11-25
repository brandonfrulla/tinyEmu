// sumloop.s
// emu $ r d 400
// emu $ m 400 0
// emu $ m 404 a
// emu $ m 408 1
    mov r0, #0         //
    mov r1, #10        //
    mov r2, #1         //
    str r0, [r13,#0]   // sum = 0
    str r1, [r13,#4]   // n = 10
    str r2, [r13,#8]   // i = 1
addloop:               // 
    add r0, r0, #1     // add 1 to sum
    str r0, [r13,#0]   // update sum
    add r2, r2, #1     // add 1 to i
    str r2, [r13,#8]   // update i
    cmp r2, r1         // compare i and n
    blt addloop        // continue loop until i >= n
    str r0, [r13,#0]   // store final value 