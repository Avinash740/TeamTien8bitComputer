; Start of test
start: ...
...

; End of test

	ldi r0, $good_exit
	jmp r0
error_exits:
	
error_regs:
	ldi r0, #0x2
	hlt

error_add:
	ldi r0, #0x2
	hlt

error_sub:
	ldi R0, #0x4
	hlt
...

	.org 0x1000
good_exit:
	ldi r0,#-1
	hlt



