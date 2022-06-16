;push byte[]
;call fun_strlen_str__word
fun_strlen_str__word:
    push rbp
    mov rbp, rsp
    sub rsp, 2
    mov word [rsp - 2], 0
    mov rdi, qword [rbp + 16]

    while_:
        cmp byte [rdi], 0h
        je end_while_
        inc rdi
        inc word [rsp - 2]
        jmp while_
    end_while_:

    mov rax, 0
    mov ax, word [rsp - 2]

    mov rsp, rbp
    pop rbp
    ret 8

;push byte[]
;call fun_printString_void
fun_printString_str__void:
    push rbp
    mov rbp, rsp
    sub rsp, 2
    mov word [rsp-2], 0
    mov qword rdi, [rbp + 16]

    push rdi
    call fun_strlen_str__word

    mov rdx, rax                ;length of string
    mov rsi, [rbp + 16]
    mov rax, 1
    mov rdi, 1
    syscall

    mov rsp, rbp
    pop rbp
    ret 8
