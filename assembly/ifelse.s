// ifelse.s
// emu $ r 13 400
// emu $ m 400 a
// emu $ m 404 14 
// emu $ m 408 0
        ldr r0, [r13,#0] //
        ldr r1, [r13,#4] // 
        ldr r2, [r13,#8] //
        cmp r0, r1       //
        bge else         //
        str r0, [r13,#8] //
        b endif          //
else:                    //
        str r1, [r13,#8] //
endif:                   //