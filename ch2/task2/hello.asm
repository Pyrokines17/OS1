global _start          
 
section .data   
message: db "Hello, world!",10  
 
section .text           
_start:                 
    mov rax, 1          
    mov rdi, 1          
    mov rsi, message    
    mov rdx, 13         
    syscall             
 
    mov rdi, rax
    mov rax, 60
    syscall
