// ifelse.s
// emu $ r d 400
// emu $ m 400 a
// emu $ m 404 14 
// emu $ m 408 0
        ldr r0, [r13,#0]  // r0 = a 
        ldr r1, [r13,#4]  // r1 = b
        ldr r2, [r13,#8]  // r2 = c
        cmp r0, r1        // compare a and b 
        bge else          // branch to else >=
        str r0, [r13,#8]  // C = a
        b endif           // branch endif
else:                     // else
        str r1, [r13,#8]  // update c 
endif:                    // end