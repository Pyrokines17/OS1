global _start          
 
section .data   
message: db "Hello, world!",10  
 
section .text           
_start:                 
    mov eax, 4
    mov ebx, 1
    mov ecx, message
    mov edx, 13
    int 80h

    mov eax, 1 
    mov ebx, 0 
    int 80h