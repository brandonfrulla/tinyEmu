// ifelse.s
// emu $ r 13 400
// emu $ m 400 a
// emu $ m 404 14 
// emu $ m 408 0
        mov r0, #10      //
        mov r1, #20      //
        mov r2, #0       //
        str r0, [r13,#0] // a = 10
        str r1, [r13,#4] // b = 20
        str r2, [r13,#8] // c = 0
        ldr r0, [r13,#0] //
        ldr r1, [r13,#4] //
        ldr r2, [r13,#8] //
        cmp r0, r1       // a < b
        bge else         //
        str r0, [r13,#8] // c = a
        b endif          //
else:                    //
        str r1, [r13,#8] // c = b
endif:                   // END of program
