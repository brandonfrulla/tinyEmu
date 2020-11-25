 //FunctionsAssem.s    
        mov r0, #1          //
	    str	r0, [r13,#0]    // a[0] = 1
		mov	r0, #3          //
		str	r0, [r13,#4]    // a[1] = 3
		mov	r0, #50         //
		str	r0, [r13,#8]    // a[2] = 50
		mov	r0, #6          //
		str	r0, [r13,#12]   // a[3] = 6
		mov	r0, #3          //
		str	r0, [r13,#16]   // a[4] = 3
		mov	r0, #3          //
		str	r0, [r13,#20]   // a[5] = 3
		mov	r0, #6          //
		str	r0, [r13,#24]   // a[6] = 6 
		mov	r0, #8          //
		str	r0, [r13,#28]   // a[7] = 8 
		mov	r0, #9          //
		str	r0, [r13,#32]   // a[8] = 9
		mov	r0, #10         //
		str r0, [r13,#36]   // a[9] = 10
		mov	r0, #0          //
		str	r0, [r13,#40]   // a[10] = 0
		mov	r0, #0          //
		str	r0, [r13,#44]   // x = 0
		str	r14, [r13,#48]  // Store Load Register
		mov	r1, #11         // Size = 11
		mov	r2, #0          // Array Offset = 0
		ldr	r0, [r13,r2]    //  
		bl	count           //
		str	r5, [r13,#44]   // Set X to count
		mov	r2, #0          // Reset Offset
		ldr	r0, [r13,r2]    // 
		bl	largest         //
		str	r3, [r13,#44]   // Set X to largest
		mov	r2, #0          // Reset Offset
		ldr	r0, [r13,r2]    //
		bl	size            //
		str	r1, [r13,#44]   // Set X to size
		b	ending          // Branch to end
count:	                    //
        mov	r4, #0          // C = 0
		mov	r6, #0          // I = 0
		mov	r5, #3          // V = 3
loop:		                //
        cmp	r6, r1          // i < s 
		bge	endcount        //
		cmp	r0, r5          // *a == v
		bne	else            //  
		add	r4, r4 , #1     // c ++
else:	                    //
        add	r6, r6, #1      // i++
		add	r2, r2, #4      // Offset += 4
		ldr	r0, [r13,r2]    //
		b loop              //
endcount:	                //
        mov	r15, r14        // Move Load Register to PC
largest:	                //
        mov	r1, #10         // S = 10
		ldr	r3, [r13,r2]    // L = a[r2]
		ldr	r4, [r13,r2]    // p = a[r2]
		add	r1, r1, #30     // 
		mov	r5, r1          //
largeloop:	                //
        cmp	r2, r5          // p < a+s  
		bge	endlarge        //
		cmp	r4, r3          // p > l
		ble	lelse           //
		mov	r3, r4          // l = p
lelse:	                    //
        add	r2, r2, #4      // Offset += 4 
		ldr	r4, [r13, r2]   // 
		b largeloop         //
endlarge:	                //
        mov	r15, r14        // Move Load Register to PC
size:		                // 
        mov	r1, #0          // I = 0
		mov	r3, #0          // L = a[0]
sizeloop:	                //
        cmp	r3, r0          // a[i] != 0
        beq	endsize         //
		add	r1, r1, #1      // i++
		add	r2, r2, #4      // offset += 4
		ldr	r0, [r13,r2]    //  
		b sizeloop          //
endsize:	                //
        mov	r15, r14        // Move Load Register to PC
ending:                     // END of program