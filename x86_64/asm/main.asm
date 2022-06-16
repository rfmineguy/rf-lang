section .data
    string:  db "Hello World", 0ah, 0h
        .len equ $-string

section .bss
 
section .text
global _start
_start:                                                                                                       
    push rbp                                                                                                    
    mov rbp, rsp                                                                                                
                                                                                                              
    mov rax, 1
    mov rdi, 1
    mov rsi, string
    mov rdx, string.len
    syscall

    mov rax, 60                                                                                                 
    mov rdi, 0                                                                                                  
    syscall                                                                                                     
    ret

;push str
;call print_str
print_str:
    push rbp
    mov rbp, rsp
    mov rdi, [rbp + 8]
    l1:
        cmp byte [rdi], 0h
        je .done
    .print_char:
        mov rcx, 0
        mov rcx, rdi
        mov edx, 1
        int 80h
        inc rdi
        jmp l1
    .done:

    mov rsp, rbp
    pop rbp
    ret 8

; push a                                                                                                        
; push b                                                                                                        
; call fun_add_a_b                                                                                              
fun_add_a_b:                                                                                                    
    push rbp                                                                                                    
    mov rbp, rsp                                                                                                
                                                                                                                
    mov rax, 0h                                                                                                 
    mov rax, QWORD [rbp + 8]                                                                                      
    add rax, QWORD [rbp + 16]                                                                                     
                                                                                                                
    mov rsp, rbp                                                                                                
    pop rbp                                                                                                     
    ret 8                                    
