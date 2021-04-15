segment .data		; data section
	fmt : db "%d",10,0
	fmt2 : db "%d ---> %d",10,0
	fmt3: db "",10,0				
	fmt4 : db "%d",0
	fmt5 : db " ---> %d",10,0

	kule1: dd 1
	kule2: dd 2
	kule3: dd 3
	parametre: db 0


segment .text		; code section
	extern printf
	global factorial_iterative
	global factorial_recursive
	global fibonacci_iterative
	global fibonacci_recursive
	global hanoi_recursive
	global hanoi_iterative



takedown_stackframe:
	push	eax
	push    dword eax
        push    dword fmt	
	call    printf		
        add     esp, 12		; pop stack 3 push times 4 bytes
        mov     esp, ebp	; takedown stack frame
        pop     ebp		; same as "leave" op
	mov	eax,0		;  normal, no error, return value
	ret		


hanoi_iterative_print2:
	push 	eax
	push 	fmt5
	call 	printf
	add	esp,8
	call	from
	ret
hanoi_iterative_print1:
	push 	eax
	push 	fmt4
	call 	printf
	add	esp,8
	call	too
	ret


hanoi_iterative:


	push	ebp
	mov	ebp,esp
	mov	ecx, [ebp+8]	; put a from store into register
	mov	eax,1
	mov 	ebx,2
	L8:
		mul ebx
	loop L8
	
	mov 	edi,eax		;max=ebx
	mov	ebx,1

	L9:
		from:		
			cmp	ebx,edi
			jz 	L10
		
			mov 	eax,ebx
			sub 	ebx,1
			and	eax,ebx
			add	ebx,1
			mov	esi,ebx
		
			mov	ebx,3
			xor	edx,edx			
			div	ebx
			mov	eax,edx
			mov	ebx,esi
			add 	eax,1
	
			mov	edx,[ebp+12]		
			cmp	edx,1		
			jz	hanoi_iterative_print1
	
		too:
			mov	eax,ebx
			sub 	ebx,1
			or	eax,ebx
			add	ebx,1
			add	eax,1
			mov	esi,ebx
		
			mov	ebx,3
			xor	edx,edx			
			div	ebx
			mov	eax,edx
			mov	ebx,esi
			add 	eax,1
			add	ebx,1
			mov	edx,[ebp+12]		
			cmp	edx,1		
			jz	hanoi_iterative_print2
	

	loop L9

	

	L10:	
		mov	edx,[ebp+12]		
		cmp	edx,1
		jz	hanoi_print_space		
		mov     esp, ebp	; takedown stack frame
		pop     ebp		; same as "leave" op
		mov	eax,0		;  normal, no error, return value
		ret			; return



hanoi_print_space:
 	push    dword fmt3	; address of ctrl string
        call    printf		; Call C function
        add     esp, 4		; pop stack 3 push times 4 bytes
        mov     esp, ebp	; takedown stack frame
        pop     ebp		; same as "leave" op
	mov	eax,0		;  normal, no error, return value
	ret			; return
				
hanoi_rec_do:
	
	push	ebp
	mov	ebp,esp	
	
	mov 	edx,[esp+8];kule2
	mov 	ecx,[esp+12];kule3
	mov 	ebx,[esp+16];kule1
	mov	eax,[esp+20];value
	
	cmp 	eax,0
	jz	L7
	
	sub	eax,1
	push	eax
	push 	ebx
	push 	edx
	push 	ecx
	
	call	hanoi_rec_do
	pop	ecx
	pop	edx
	pop 	ebx
	pop 	eax
	
	pusha	
	push    ecx		; value of variable a
	push	ebx		; value of a+2	 
        push    dword fmt2	; address of ctrl string       	
	cmp	edi,0
	jz	hanoi_not_print	
	call 	printf
	hanoi_not_print	: 	
		add 	esp,12
	popa
			
	push	eax
	push 	edx
	push 	ecx
	push 	ebx

	call	hanoi_rec_do
	pop	ebx
	pop 	ecx
	pop	edx
	pop	eax
	
		
L7:
	mov     esp, ebp	; takedown stack frame
        pop     ebp		; same as "leave" op
	ret

hanoi_recursive:
	
	push	ebp
	mov	ebp,esp
	mov	edi,[ebp+12]
	push 	dword [ebp+8]
	push 	dword [kule1]
	push 	dword [kule3]
	push 	dword [kule2]	
	
	call 	hanoi_rec_do	
	add 	esp,16
	cmp	edi,1
	jz	hanoi_print_space
        mov     esp, ebp	; takedown stack frame
        pop     ebp		; same as "leave" op
	mov	eax,0		;  normal, no error, return value
	ret			; return
			


L2:
		cmp 	edi,1
		jz	print
		ret			; return

fibonacci_iterative:
	push	ebp
	mov	ebp,esp
	mov	eax, [ebp+8]	; put a from store into register
	mov	edi,[ebp+12]
	mov 	ebx,0
	mov 	edx,1
	mov 	ecx,eax
	dec 	ecx
	cmp 	ecx,0
	jz 	L2
	cmp 	ecx,-1
	jz 	L2
	
	L1:
		add 	ebx,edx
		mov 	eax,ebx
		mov 	ebx,edx
		mov 	edx,eax	
	loop L1
	
	cmp	edi,1
	jz	print
	mov     esp, ebp	; takedown stack frame
        pop     ebp		; same as "leave" op	
	ret
	
	
	

L4:	
		cmp	edi,1
		jz	print
		ret
   
fibonacci_rec_do:
	
	cmp 	ecx,0
	jz 	L3
	dec 	ecx
	add	ebx,edx
	mov	eax,ebx
	mov	ebx,edx
	mov	edx,eax
	call 	fibonacci_rec_do
	
	L3:
		ret
	
ret

fibonacci_recursive:
	push	ebp
	mov	ebp,esp
	mov	eax, [ebp+8]	; put a from store into register
	mov	edi,[ebp+12]
	mov 	ebx,0	
	mov 	edx,1
	mov 	ecx,eax
	dec 	ecx
	cmp 	ecx,0
	jz 	L4
	cmp 	ecx,-1
	jz 	L4

	call fibonacci_rec_do
	cmp	edi,1
	jz	print
	mov     esp, ebp	; takedown stack frame
        pop     ebp		; same as "leave" op	
	ret
	
	
        
	
fac_rec_do:				;faktoriyel recursive function
	cmp 	ebx,1
	jz 	L5
	dec 	ebx
	mul 	ebx
	call fac_rec_do
	
	L5:
		ret	
ret


factorial_recursive:
	push	ebp
	mov	ebp,esp
	mov	eax, [ebp+8]
	mov	edi,[ebp+12]
	mov 	ebx, eax
	call 	fac_rec_do
	
	cmp 	edi,1
	jz	print
  	mov     esp, ebp		; takedown stack frame
      pop     ebp		; same as "leave" op	
	
	ret
	

factorial_iterative:
	push	ebp
	mov	ebp,esp
	mov 	eax,[ebp+8]	;take the parameter
	mov	edi,[ebp+12]
	mov 	ebx,eax
	
	sub 	ebx,2
	mov 	ecx,ebx
	mov 	ebx,eax
	L6:
		dec ebx
		mul ebx
	loop L6
	
	cmp 	edi,1
	jz	print
  	mov     esp, ebp	; takedown stack frame
      pop     ebp		; same as "leave" op	
	ret

print:	
		call 	takedown_stackframe
		ret

