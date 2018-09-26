GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu

GLOBAL _irq00Handler
GLOBAL _irq01Handler

GLOBAL _exception0Handler
GLOBAL _exception1Handler

GLOBAL _systemCallHandler

EXTERN systemCallDispatcher
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN load_idt
EXTERN nextProcess

GLOBAL _changeProcess
GLOBAL _yieldProcess
GLOBAL _yield_interrupt

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push fs
	push gs
%endmacro

%macro popState 0
	pop gs
	pop fs
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	mov rdi, rsp
	call nextProcess

	mov rsp, rax

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandler 1
	pushState
	push rsp

	mov rdi, %1 ; pasaje de parametro nro de excepcion
	mov rsi, rsp ; pasaje de registros como estan pusheados

	call exceptionDispatcher

	pop rsp
	popState

	mov qword [rsp], 0x400000 ;Despues de la excepcion que vuelva a el modulo que esta en 0x400000 que es SampleCodeModule
	iretq
%endmacro

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret


_changeProcess:
	mov rsp, rdi
	popState
	iretq

	_yieldProcess:
	int 70h
	ret

	_yield_interrupt:
		pushState

		mov rdi, rsp
		call nextProcess

		mov rsp, rax
		popState

		iretq

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

;Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid Code Exception
_exception1Handler:
	exceptionHandler 6

;System Calls
_systemCallHandler:
    pushState

    call systemCallDispatcher

	mov [aux], rax
	popState
    mov rax, [aux]

	iretq

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1
