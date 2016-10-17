; CreateThreadEx

IFDEF RAX
; 64bit

EXTERNDEF sciCreateThreadEx:DWORD

.DATA
.CODE
 
HcCreateThreadEx PROC 
	mov r10, rcx
	mov eax, sciCreateThreadEx
	syscall
	ret
HcCreateThreadEx ENDP 

ELSE
; 32bit

EXTERNDEF C sciCreateThreadEx:DWORD

.586              
.MODEL FLAT, C   
.STACK         
.DATA
.CODE
 
ASSUME FS:NOTHING	
 
HcCreateThreadEx PROC 
	mov eax, sciCreateThreadEx
	mov ecx, fs:[0c0h]
	test ecx, ecx
	jne _wow64
	lea edx, [esp + 4]
	INT 02eh
	ret
	_wow64:
	xor ecx, ecx
	lea edx, [esp + 4h]
	call dword ptr fs:[0c0h]
	ret
HcCreateThreadEx ENDP 

ENDIF

END