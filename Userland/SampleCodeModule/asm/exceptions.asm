GLOBAL zeroDiv
GLOBAL opCode

section .text

zeroDiv:
	mov rcx, 0
	div rcx
	ret

opCode:
	ud2
	ret