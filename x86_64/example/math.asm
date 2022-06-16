global fun_add_a_b__word
fun_add_a_b__word:
    push rbp                                                                                                    
    mov rbp, rsp                                                                                                
    sub rsp, 2

    mov rax, 0h                                                                                                 
    mov rax, [rbp + 8]                                                                                      
    add rax, qword [rbp + 16]                                                                                     
    mov word [rsp-2], ax

    mov rsp, rbp                                                                                                
    pop rbp                                                                                                     
    ret 16

global fun_mul_a_b__word
fun_mul_a_b__word:
    push rbp
    mov rbp, rsp
    sub rsp, 2

    xor rax, rax
    xor rbx, rbx
    mov rax, QWORD [rbp + 16]
    mov rbx, QWORD [rbp + 24]
    imul eax, ebx
    mov word [rsp-2], ax

    mov rsp, rbp
    pop rbp
    ret 16
