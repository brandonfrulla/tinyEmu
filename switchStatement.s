// switchstatement.s
// emu $ r d 400
// emu $ m 400 1 
// emu $ m 404 2
// emu $ m 408 3
main:
    mov r0, #1       //
    mov r2, #2       //
    mov r3, #3       //
    str r0, [r13,#0] // a = 1
    str r1, [r13,#4] // b = 2
    str r2, [r13,#8] // c = 3
    cmp r0, #1       // compare a to 1
    beq case1           //
    cmp r0, #2       // compare a to 2
    beq case2           //
    cmp r0, #3       // compare a to 3
    beq case3           //
    cmp r0, #4       // compare a to 4
    beq case4           //          
    cmp r0, #5       // compare a to 5
    beq case5           //      
    cmp r0, #6       // compare a to 6
    beq case6           //
    cmp r0, #7       // compare a to 7
    beq case7           //
    b caseDefault       //
case1:                  //
    add r0, r1, r2      // adding b & c, storing in a
    str r0, [r13,#0]    //    
    b endif             //
case2:                  //
    sub r0, r1, r2      // subtracting c from b, storing in a
    str r0, [r13,#0]        //
    b endif                 //
case3:                      //
    mul r0, r1, r2      // multiplying b and c, storing in a
    str r0, [r13,#0]        //
    b endif                 //
case4:                          //
    div r0, r1, r2      // dividing b and c, storing in a
    str r0, [r13,#0]        //
    b endif         //
case5:                  //
    and r0, r1, r2      // comparing b && c, storing in a
    str r0, [r13,#0]    //
    b endif             //
case6:                      //
    orr r0, r1, r2      // comparing b || c, storing in a
    str r0, [r13,#0]        //
    b endif                 //
case7:                      //
    eor r0, r1, r2      // comparing b ^ c, storing in a
    str r0, [r13,#0]        //
    b endif                 //
caseDefault:                //
    mov r0, #0          // make a = 0
    str r0, [r13,#0]        //
endif:                      //
    //blank 