	AREA |.text|, CODE, READONLY
	EXPORT syscall
syscall
	PUSH {R4-R7}
	MOV R7, R0;	push syscall num to R7(dont be covered by kernel mode)
	MOV R0, R1
	MOV R1, R2
	MOV R2, R3
	ADD R6, SP, #0x10
	LDM R6, {R3-R5}	;调用syscall的时候,其他几个参数通过堆栈传递.
	;BKPT 0XAB
	SVC 0
	POP {R4-R7}
	BX  LR
	
	END