// function.s
    sub r13, r13, #60  //space for a[11],largest,size,count
    mov r0, #1
    str r0, [r13,#0] // a[0] = 1
    mov r0, #3
    str r0, [r13,#4] // a[1] = 3
    mov r0, #50
    str r0, [r13,#8] // a[2] = 50
    mov r0, #6
    str r0, [r13,#12] // a[3] = 6
    mov r0, #3
    str r0, [r13,#16] // a[4] = 3
    mov r0, #3
    str r0, [r13,#20] // a[5] = 3
    mov r0, #6
    str r0, [r13,#24] // a[6] = 6
    mov r0, #8
    str r0, [r13,#28] // a[7] = 8
    mov r0, #9
    str r0, [r13,#32] // a[8] = 9
    mov r0, #10
    str r0, [r13,#36] // a[9] = 10
    mov r0, #0
    str r0, [r13,#40] // a[10] = 0
    mov r0, #0
    str r0, [r13,#44] // x = 0
    str r14, [r13,#48]// save LR on Stack 
    mov r0, r13       // put address of a into r0
    mov r1, #11       // size of a = 11 into r1
    bl count
    
count:                  //count # of v in a 
    sub r13, r13, #24   // space for: count, i, r4, r5, lr
    str r4, [r13, #0]   // put r4 on stack
    str r5, [r13,#4]    // PUT r5 on stack
    str r14, [r13, #8]  // put LR on stack
    ldr r4, #0          
    str r4, [r13,#12]   // c = 0
    ldr r4, #0          
    str r4, [r13,#16]   // i = 0
    ldr r4, #3
    str r4, [r13,#20]   // v = 3
loop:                 //While loop
    ldr r4, [r13,#16]
    cmp r4, r1
    bge endloop 
endloop:


    