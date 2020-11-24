 //FunctionsAssem.s       
        mov r0, #1          //
	    str	r0, [r13,#0]    //
		mov	r0, #3          //
		str	r0, [r13,#4]    //
		mov	r0, #50         //
		str	r0, [r13,#8]    //
		mov	r0, #6          //
		str	r0, [r13,#12]   //
		mov	r0, #3          //
		str	r0, [r13,#16]   //
		mov	r0, #3          //
		str	r0, [r13,#20]   //
		mov	r0, #6          //
		str	r0, [r13,#24]   //
		mov	r0, #8          //
		str	r0, [r13,#28]   //
		mov	r0, #9          //
		str	r0, [r13,#32]   //
		mov	r0, #10         //
		str r0, [r13,#36]   //
		mov	r0, #0          //
		str	r0, [r13,#40]   //
		mov	r0, #0          //
		str	r0, [r13,#44]   //
		str	r14, [r13,#48]  //
		mov	r1, #11         //
		mov	r2, #0          //
		ldr	r0,[r13,r2]     //
		bl	count           //
		str	r5, [r13,#44]   //
		mov	r2, #0          //
		ldr	r0, [r13,r2]    //
		bl	largest         //  
		str	r3, [r13,#44]   //
		mov	r2, #0          //
		ldr	r0, [r13,r2]    //
		bl	size            //  
		str	r1, [r13,#44]   //
		b	ending          //
count:	                    //
        mov	r4, #0          //
		mov	r6, #0          //
		mov	r5, #3          //
loop:		                //
        cmp	r6, r1          //
		bge	endcount        //
		cmp	r0, r5          //
		bne	else            //  
		add	r4, r4 , #1     //
else:	                    //
        add	r6, r6, #1      //
		add	r2, r2, #4      //
		ldr	r0, [r13,r2]    //
		b loop              //
endcount:	                //
        mov	r15, r14        //
largest:	                //
        mov	r1, #10         //
		ldr	r3, [r13,r2]    //
		ldr	r4, [r13,r2]    //
		add	r1, r1, #30     //
		mov	r5, r1          //
largeloop:	                //
        cmp	r2, r5          //  
		bge	endlarge        //
		cmp	r4, r3          //
		ble	lelse           //
		mov	r3, r4          //
lelse:	                    //
        add	r2, r2, #4      //
		ldr	r4, [r13, r2]   //
		b largeloop         //
endlarge:	                //
        mov	r15, r14        //
size:		                //
        mov	r1, #0          //
		mov	r3, #0          //
sizeloop:	                //
        cmp	r3, r0          //
        beq	endsize         //
		add	r1, r1, #1      //
		add	r2, r2, #4      //
		ldr	r0, [r13,r2]    //
		b sizeloop          //
endsize:	                //
        mov	r15, r14        //
ending:                     //