
section.data
msg : db "Hello, this is my string", 0
fmtstr : db "%s", 10, 0
fmtuint : db "%d", 10, 0
fmtuintin : db "%d", 0
fmtfloatin : db "%f", 0
float1 : dd     0.0

section.bss

float1: resd 1
float2: resd 1
float3: resd 1
float4: resd 1

section.text

extern printf
extern scanf
global main
main :
push rbp; Push base pointer onto stack to save it


; ish float1 = 3.5 => Optimized
mov eax, 3
mov [float1], eax

; ish float2 = (3.5) => Optimized
mov eax, 3
mov [float2], eax

; ish float3 = ((3.55)) => Optimized
mov eax, 3
mov [float3], eax

; ish float4 = 3.14159+2.718218 => Optimized
mov eax, 5
mov [float4], eax


; print a string
mov rsi,  "This begins the user input section"
mov rdi, fmtstr
mov rax, 0
call printf


; print a string
mov rsi,  "Supply data and hit enter"
mov rdi, fmtstr
mov rax, 0
call printf


; print a string
mov rsi,  "Enter a number: "
mov rdi, fmtstr
mov rax, 0
call printf


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user1]
mov rax, 0
call scanf


; print a string
mov rsi,  "Enter a number: "
mov rdi, fmtstr
mov rax, 0
call printf


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user2]
mov rax, 0
call scanf


; print a string
mov rsi,  "Enter a number: "
mov rdi, fmtstr
mov rax, 0
call printf


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user3]
mov rax, 0
call scanf


; print a string
mov rsi,  "Enter a number: "
mov rdi, fmtstr
mov rax, 0
call printf


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user4]
mov rax, 0
call scanf


j addend
add:

push eax
push ebx

pop ebx
pop eax

mov eax, [result]
ret 
addend: 



j multend
mult:

push eax
push ebx

pop ebx
pop eax

mov eax, [result]
ret 
multend: 



; print a string
mov rsi,  "Result of adding first and second user inputs: "
mov rdi, fmtstr
mov rax, 0
call printf


; print a string
mov rsi,  "Result of multiplying third and fourth user inputs: "
mov rdi, fmtstr
mov rax, 0
call printf


j computeApproxSphereVolumeend
computeApproxSphereVolume:

push eax
push ebx

pop ebx
pop eax

mov eax, [result]
ret 
computeApproxSphereVolumeend: 



; print a string
mov rsi,  "Enter a radius: "
mov rdi, fmtstr
mov rax, 0
call printf


; read an integer
lea rdi, [fmtuintin]
lea rsi, [userRadius]
mov rax, 0
call scanf


; print a string
mov rsi,  "The volume is: "
mov rdi, fmtstr
mov rax, 0
call printf


; print a string
mov rsi,  "Congratulations on the great semester!"
mov rdi, fmtstr
mov rax, 0
call printf
