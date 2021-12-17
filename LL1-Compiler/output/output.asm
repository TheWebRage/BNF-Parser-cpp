
section .data
msg: db "Hello, this is my string", 0
fmtstr: db "%s", 10, 0
fmtuint: db "%d", 10, 0
fmtuintin: db "%d", 0
fmtfloatin: db "%f", 0

s1: db "This begins the user input section", 0
s10: db "The volume is: ", 0
s11: db "Congratulations on the great semester!", 0
s2: db "Supply data and hit enter", 0
s3: db "Enter a number: ", 0
s4: db "Enter a number: ", 0
s5: db "Enter a number: ", 0
s6: db "Enter a number: ", 0
s7: db "Result of adding first and second user inputs: ", 0
s8: db "Result of multiplying third and fourth user inputs: ", 0
s9: db "Enter a radius: ", 0


section .bss

var1: resd 1
var2: resd 1
var3: resd 1
var4: resd 1
var5: resd 1
var6: resd 1
var7: resd 1
var8: resd 1
var9: resd 1
var10: resd 1
var11: resd 1
var12: resd 1
var13: resd 1
var14: resd 1
var15: resd 1
var16: resd 1
var17: resd 1
var18: resd 1
var19: resd 1
var21: resd 1
var23: resd 1
var24: resd 1
var34: resd 1
var35: resd 1
var36: resd 1
var39: resd 1
var41: resd 1
var42: resd 1
var43: resd 1
var44: resd 1
var45: resd 1
issue1: resd 1
issue2: resd 1
error: resd 1
orig: resd 1
copy: resd 1
var49: resd 1
var50: resd 1
var51: resd 1
var52: resd 1
var53: resd 1
user1: resd 1
user2: resd 1
user3: resd 1
user4: resd 1
userResult1: resd 1
userResult2: resd 1
userResult3: resd 1
userResult4: resd 1
result1: resd 1
a: resd 1
b: resd 1
result2: resd 1
result3: resd 1
result4: resd 1
result5: resd 1
result7: resd 1
result8: resd 1
userResult5: resd 1
userResult6: resd 1
userRadius: resd 1
volume: resd 1

result: resd 1
radius: resd 1

section .text

extern printf
extern scanf
global main
main:
push rbp; Push base pointer onto stack to save it ; Needed for scanf


; num var1 = 3*4 => Optimized
mov rax, 12
mov [var1], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var1]
xor rax, rax
call printf

; num var2 = 12 / 6 => Optimized
mov rax, 2
mov [var2], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var2]
xor rax, rax
call printf

; num var3 = 12/6 => Optimized
mov rax, 2
mov [var3], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var3]
xor rax, rax
call printf

; num var4 = 5 + 4 * 3 => Optimized
mov rax, 17
mov [var4], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var4]
xor rax, rax
call printf

; num var5 = 12 + 34 * 45 => Optimized
mov rax, 1542
mov [var5], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var5]
xor rax, rax
call printf

; num var6 = (4 / 5) => Optimized
mov rax, 0
mov [var6], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var6]
xor rax, rax
call printf

; num var7 = 2 * 2 + 5 * 5 => Optimized
mov rax, 29
mov [var7], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var7]
xor rax, rax
call printf

; num var8 = 42 => Optimized
mov rax, 42
mov [var8], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var8]
xor rax, rax
call printf

; num var9 = (42) => Optimized
mov rax, 42
mov [var9], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var9]
xor rax, rax
call printf

; num var10 = ((42)) => Optimized
mov rax, 42
mov [var10], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var10]
xor rax, rax
call printf

; num var11 = ( ( 42 ) ) => Optimized
mov rax, 42
mov [var11], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var11]
xor rax, rax
call printf

; num var12 = 1234*5678 => Optimized
mov rax, 7006652
mov [var12], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var12]
xor rax, rax
call printf

; num var13 = ((12-8)-3) => Optimized
mov rax, 1
mov [var13], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var13]
xor rax, rax
call printf

; num var14 = (5*(8/4)) => Optimized
mov rax, 10
mov [var14], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var14]
xor rax, rax
call printf

; num var15 = (1+2) * 3 => Optimized
mov rax, 9
mov [var15], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var15]
xor rax, rax
call printf

; num var16 = (((2+3)*4)+(7+(8/2))) => Optimized
mov rax, 31
mov [var16], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var16]
xor rax, rax
call printf

; num var17 = (((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3*3*3*3)+1)/2)) => Optimized
mov rax, 1337
mov [var17], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var17]
xor rax, rax
call printf

; num var18 = -42 => Optimized
mov rax, -42
mov [var18], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var18]
xor rax, rax
call printf

; num var19 = (-42) => Optimized
mov rax, -42
mov [var19], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var19]
xor rax, rax
call printf

; num var21 = (-42 ) => Optimized
mov rax, -42
mov [var21], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var21]
xor rax, rax
call printf

; num var23 = 2-3 => Optimized
mov rax, -1
mov [var23], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var23]
xor rax, rax
call printf

; num var24 = 2 - 3 => Optimized
mov rax, -1
mov [var24], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var24]
xor rax, rax
call printf

; num var34 = -2 - (-3)
mov rax, -2
mov rbx, -3
sub rax, rbx
mov [var34], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var34]
xor rax, rax
call printf

; num var35 = -2 - (-3 - (4))
mov rax, -2
mov rbx, -3
mov rbx, 4
sub rax, rbx
sub rax, rbx
mov [var35], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var35]
xor rax, rax
call printf

; num var36 = -2 - (-3 - (4))
mov rax, -2
mov rbx, -3
mov rbx, 4
sub rax, rbx
sub rax, rbx
mov [var36], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var36]
xor rax, rax
call printf

; num var39 = -2 - (-2 - (-2 - 2))
mov rax, -2
mov rbx, -2
mov rbx, -2
mov rbx, 2
sub rax, rbx
sub rax, rbx
sub rax, rbx
mov [var39], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var39]
xor rax, rax
call printf

; num var41 = 3^3 => Optimized
mov rax, 27
mov [var41], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var41]
xor rax, rax
call printf

; num var42 = 4 ^ 4 => Optimized
mov rax, 256
mov [var42], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var42]
xor rax, rax
call printf

; num var43 = 3^3^3 => Optimized
mov rax, 19683
mov [var43], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var43]
xor rax, rax
call printf

; num var44 = 3^(3^3) => Optimized
mov rax, 2030534528
mov [var44], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var44]
xor rax, rax
call printf

; num var45 = 5 + 4 * 3 ^ 2 => Optimized
mov rax, 149
mov [var45], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var45]
xor rax, rax
call printf

; num issue1 = 5 => Optimized
mov rax, 5
mov [issue1], rax

; num issue2 = 3 + 4 => Optimized
mov rax, 7
mov [issue2], rax

; num orig = 4 + 2 => Optimized
mov rax, 6
mov [orig], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [orig]
xor rax, rax
call printf

; num copy = orig => Optimized
mov rax, 6
mov [copy], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [copy]
xor rax, rax
call printf

; num var49 = var1 + var2 => Optimized
mov rax, 14
mov [var49], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var49]
xor rax, rax
call printf

; num var50 = var1 - var2 => Optimized
mov rax, 10
mov [var50], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var50]
xor rax, rax
call printf

; num var51 = var2 - var1 => Optimized
mov rax, -10
mov [var51], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var51]
xor rax, rax
call printf

; num var52 = var1 * var1 => Optimized
mov rax, 144
mov [var52], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var52]
xor rax, rax
call printf

; num var53 = (var3 + var4) * (var5 + var3) => Optimized
mov rax, 29336
mov [var53], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var53]
xor rax, rax
call printf


; print a string
mov rsi, s1
mov rdi, fmtstr
mov rax, 0
call printf


; print a string
mov rsi, s2
mov rdi, fmtstr
mov rax, 0
call printf


; print a string
mov rsi, s3
mov rdi, fmtstr
mov rax, 0
call printf

; num user1 = 0 => Optimized
mov rax, 0
mov [user1], rax


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user1]
mov rax, 0
call scanf


; print integer back out
lea rdi, [fmtuint]
mov rsi, [user1]
xor rax, rax
call printf


; print a string
mov rsi, s4
mov rdi, fmtstr
mov rax, 0
call printf

; num user2 = 0 => Optimized
mov rax, 0
mov [user2], rax


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user2]
mov rax, 0
call scanf


; print integer back out
lea rdi, [fmtuint]
mov rsi, [user2]
xor rax, rax
call printf


; print a string
mov rsi, s5
mov rdi, fmtstr
mov rax, 0
call printf

; num user3 = 0 => Optimized
mov rax, 0
mov [user3], rax


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user3]
mov rax, 0
call scanf


; print integer back out
lea rdi, [fmtuint]
mov rsi, [user3]
xor rax, rax
call printf


; print a string
mov rsi, s6
mov rdi, fmtstr
mov rax, 0
call printf

; num user4 = 0 => Optimized
mov rax, 0
mov [user4], rax


; read an integer
lea rdi, [fmtuintin]
lea rsi, [user4]
mov rax, 0
call scanf


; print integer back out
lea rdi, [fmtuint]
mov rsi, [user4]
xor rax, rax
call printf

; num userResult1 = user1 + user2
mov rax, [user1]
mov rbx, [user2]
add rax, rbx
mov [userResult1], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult1]
xor rax, rax
call printf

; num userResult2 = user3 - user4
mov rax, [user3]
mov rbx, [user4]
sub rax, rbx
mov [userResult2], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult2]
xor rax, rax
call printf

; num userResult3 = user1 * user2
mov rax, [user1]
mov rbx, [user2]
imul rax, rbx
mov [userResult3], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult3]
xor rax, rax
call printf

; num userResult4 = user3 / user4
mov rax, [user3]
mov rbx, [user4]
xor rdx, rdx
div rbx
mov [userResult4], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult4]
xor rax, rax
call printf


jmp addend
add:

push rax
push rbx

; num result = a + b
mov rax, [a]
mov rbx, [b]
add rax, rbx
mov [result], rax

pop rbx
pop rax

mov rax, [result]
ret 
addend: 



jmp multend
mult:

push rax
push rbx

; num result = a * b
mov rax, [a]
mov rbx, [b]
imul rax, rbx
mov [result], rax

pop rbx
pop rax

mov rax, [result]
ret 
multend: 


mov rax, 2
mov [a], rax

mov rax, 3
mov [b], rax

call add
; num result1 = add(2, 3)
mov [result1], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result1]
xor rax, rax
call printf

; num a = 2 => Optimized
mov rax, 2
mov [a], rax

; num b = 3 => Optimized
mov rax, 3
mov [b], rax

mov rax, [a]
mov [a], rax

mov rax, [b]
mov [b], rax

call add
; num result2 = add(a, b)
mov [result2], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result2]
xor rax, rax
call printf

mov rax, [a]
mov [a], rax

mov rax, [b]
mov [b], rax

call mult
; num result3 = mult(a, b)
mov [result3], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result3]
xor rax, rax
call printf

mov rax, [a]
mov [a], rax

mov rax, [a]
mov [b], rax

call mult
; num result4 = mult(a,a)
mov [result4], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result4]
xor rax, rax
call printf

mov rax, [b]
mov [a], rax

mov rax, [b]
mov [b], rax

call mult
; num result5 = mult(b,b)
mov [result5], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result5]
xor rax, rax
call printf

mov rax, [a]
mov [a], rax

mov rax, [b]
mov [b], rax

call add
mov rax, [a]
mov [a], rax

mov rax, [b]
mov [b], rax

call mult
; num result7 = add(a, b) - mult(a, b)
sub rax, rbx
mov [result7], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result7]
xor rax, rax
call printf

mov rax, [a]
mov [a], rax

mov rax, [a]
mov [b], rax

call add
mov rax, [a]
mov [a], rax

mov rax, [b]
mov [b], rax

call mult
mov rax, [b]
mov [a], rax

mov rax, [b]
mov [b], rax

call mult
; num result8 = add(a,a) + mult(a,b) * mult(b,b)
imul rax, rbx
add rax, rbx
mov [result8], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result8]
xor rax, rax
call printf


; print a string
mov rsi, s7
mov rdi, fmtstr
mov rax, 0
call printf

mov rax, [user1]
mov [a], rax

mov rax, [user2]
mov [b], rax

call add
; num userResult5 = add(user1, user2)
mov [userResult5], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult5]
xor rax, rax
call printf


; print a string
mov rsi, s8
mov rdi, fmtstr
mov rax, 0
call printf

mov rax, [user3]
mov [a], rax

mov rax, [user4]
mov [b], rax

call mult
; num userResult6 = mult(user3, user4)
mov [userResult6], rax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult6]
xor rax, rax
call printf


jmp computeApproxSphereVolumeend
computeApproxSphereVolume:

push rax
push rbx

; num result = radius ^ 3 * 4 * 31416 / 10000 / 3
mov rax, [radius]
mov rbx, 3

mov r8, 1
xor rdi, rdi
exp_start98:
cmp rdi, rbx
jz exp_done98
imul r8, rax
inc rdi
jmp exp_start98
exp_done98:
mov rax, r8

mov rbx, 4
imul rax, rbx
mov rbx, 31416
imul rax, rbx
mov rbx, 10000
xor rdx, rdx
div rbx
mov rbx, 3
xor rdx, rdx
div rbx
mov [result], rax

pop rbx
pop rax

mov rax, [result]
ret 
computeApproxSphereVolumeend: 



; print a string
mov rsi, s9
mov rdi, fmtstr
mov rax, 0
call printf

; num userRadius = 0 => Optimized
mov rax, 0
mov [userRadius], rax


; read an integer
lea rdi, [fmtuintin]
lea rsi, [userRadius]
mov rax, 0
call scanf

mov rax, [userRadius]
mov [radius], rax

call computeApproxSphereVolume
; num volume = computeApproxSphereVolume(userRadius)
mov [volume], rax


; print a string
mov rsi, s10
mov rdi, fmtstr
mov rax, 0
call printf


; print integer back out
lea rdi, [fmtuint]
mov rsi, [volume]
xor rax, rax
call printf


; print a string
mov rsi, s11
mov rdi, fmtstr
mov rax, 0
call printf


mov rax, 60
xor rdi, rdi
syscall