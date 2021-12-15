
section.data
msg : db "Hello, this is my string", 0
fmtstr : db "%s", 10, 0
fmtuint : db "%d", 10, 0
fmtuintin : db "%d", 0
fmtfloatin : db "%f", 0
float1 : dd     0.0

section.bss

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
float1: resd 1
float2: resd 1
float3: resd 1
float4: resd 1
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

section.text

extern printf
extern scanf
global main
main :
push rbp; Push base pointer onto stack to save it


; num var1 = 3*4 => Optimized
mov eax, 12
mov [var1], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var1]
xor rax, rax
call printf

; num var2 = 12 / 6 => Optimized
mov eax, 2
mov [var2], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var2]
xor rax, rax
call printf

; num var3 = 12/6 => Optimized
mov eax, 2
mov [var3], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var3]
xor rax, rax
call printf

; num var4 = 5 + 4 * 3 => Optimized
mov eax, 17
mov [var4], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var4]
xor rax, rax
call printf

; num var5 = 12 + 34 * 45 => Optimized
mov eax, 1542
mov [var5], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var5]
xor rax, rax
call printf

; num var6 = (4 / 5) => Optimized
mov eax, 0
mov [var6], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var6]
xor rax, rax
call printf

; num var7 = 2 * 2 + 5 * 5 => Optimized
mov eax, 29
mov [var7], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var7]
xor rax, rax
call printf

; num var8 = 42 => Optimized
mov eax, 42
mov [var8], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var8]
xor rax, rax
call printf

; num var9 = (42) => Optimized
mov eax, 42
mov [var9], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var9]
xor rax, rax
call printf

; num var10 = ((42)) => Optimized
mov eax, 42
mov [var10], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var10]
xor rax, rax
call printf

; num var11 = ( ( 42 ) ) => Optimized
mov eax, 42
mov [var11], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var11]
xor rax, rax
call printf

; num var12 = 1234*5678 => Optimized
mov eax, 7006652
mov [var12], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var12]
xor rax, rax
call printf

; num var13 = ((12-8)-3) => Optimized
mov eax, 1
mov [var13], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var13]
xor rax, rax
call printf

; num var14 = (5*(8/4)) => Optimized
mov eax, 10
mov [var14], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var14]
xor rax, rax
call printf

; num var15 = (1+2) * 3 => Optimized
mov eax, 9
mov [var15], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var15]
xor rax, rax
call printf

; num var16 = (((2+3)*4)+(7+(8/2))) => Optimized
mov eax, 31
mov [var16], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var16]
xor rax, rax
call printf

; num var17 = (((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3*3*3*3)+1)/2)) => Optimized
mov eax, 1337
mov [var17], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var17]
xor rax, rax
call printf

; num var18 = -42 => Optimized
mov eax, -42
mov [var18], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var18]
xor rax, rax
call printf

; num var19 = (-42) => Optimized
mov eax, -42
mov [var19], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var19]
xor rax, rax
call printf

; num var21 = (-42 ) => Optimized
mov eax, -42
mov [var21], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var21]
xor rax, rax
call printf

; num var23 = 2-3 => Optimized
mov eax, -1
mov [var23], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var23]
xor rax, rax
call printf

; num var24 = 2 - 3 => Optimized
mov eax, -1
mov [var24], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var24]
xor rax, rax
call printf

; num var34 = -2 - (-3)
mov eax, -2
mov ebx, -3
sub eax, ebx
mov [var34], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var34]
xor rax, rax
call printf

; num var35 = -2 - (-3 - (4))
mov eax, -2
mov ebx, -3
mov ebx, [4]
sub eax, ebx
sub eax, ebx
mov [var35], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var35]
xor rax, rax
call printf

; num var36 = -2 - (-3 - (4))
mov eax, -2
mov ebx, -3
mov ebx, [4]
sub eax, ebx
sub eax, ebx
mov [var36], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var36]
xor rax, rax
call printf

; num var39 = -2 - (-2 - (-2 - 2))
mov eax, -2
mov ebx, -2
mov ebx, -2
mov ebx, [2]
sub eax, ebx
sub eax, ebx
sub eax, ebx
mov [var39], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var39]
xor rax, rax
call printf

; num var41 = 3^3 => Optimized
mov eax, 27
mov [var41], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var41]
xor rax, rax
call printf

; num var42 = 4 ^ 4 => Optimized
mov eax, 256
mov [var42], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var42]
xor rax, rax
call printf

; num var43 = 3^3^3 => Optimized
mov eax, 19683
mov [var43], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var43]
xor rax, rax
call printf

; num var44 = 3^(3^3) => Optimized
mov eax, 2030534528
mov [var44], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var44]
xor rax, rax
call printf

; num var45 = 5 + 4 * 3 ^ 2 => Optimized
mov eax, 149
mov [var45], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var45]
xor rax, rax
call printf

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

; num issue1 = 5 => Optimized
mov eax, 5
mov [issue1], eax

; num issue2 = 3 + 4 => Optimized
mov eax, 7
mov [issue2], eax

; num orig = 4 + 2 => Optimized
mov eax, 6
mov [orig], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [orig]
xor rax, rax
call printf

; num copy = orig => Optimized
mov eax, 6
mov [copy], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [copy]
xor rax, rax
call printf

; num var49 = var1 + var2 => Optimized
mov eax, 14
mov [var49], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var49]
xor rax, rax
call printf

; num var50 = var1 - var2 => Optimized
mov eax, 10
mov [var50], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var50]
xor rax, rax
call printf

; num var51 = var2 - var1 => Optimized
mov eax, -10
mov [var51], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var51]
xor rax, rax
call printf

; num var52 = var1 * var1 => Optimized
mov eax, 144
mov [var52], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var52]
xor rax, rax
call printf

; num var53 = (var3 + var4) * (var5 + var3) => Optimized
mov eax, 29336
mov [var53], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [var53]
xor rax, rax
call printf


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

; num user1 = 0 => Optimized
mov eax, 0
mov [user1], eax


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
mov rsi,  "Enter a number: "
mov rdi, fmtstr
mov rax, 0
call printf

; num user2 = 0 => Optimized
mov eax, 0
mov [user2], eax


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
mov rsi,  "Enter a number: "
mov rdi, fmtstr
mov rax, 0
call printf

; num user3 = 0 => Optimized
mov eax, 0
mov [user3], eax


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
mov rsi,  "Enter a number: "
mov rdi, fmtstr
mov rax, 0
call printf

; num user4 = 0 => Optimized
mov eax, 0
mov [user4], eax


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
mov eax, user1
mov ebx, user2
add eax, ebx
mov [userResult1], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult1]
xor rax, rax
call printf

; num userResult2 = user3 - user4
mov eax, user3
mov ebx, user4
sub eax, ebx
mov [userResult2], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult2]
xor rax, rax
call printf

; num userResult3 = user1 * user2
mov eax, user1
mov ebx, user2
mul eax, ebx
mov [userResult3], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult3]
xor rax, rax
call printf

; num userResult4 = user3 / user4
mov eax, user3
mov ebx, user4
div eax, ebx
mov [userResult4], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult4]
xor rax, rax
call printf


j addend
add:

push eax
push ebx

; num result = a + b
mov eax, a
mov ebx, b
add eax, ebx
mov [result], eax

pop ebx
pop eax

mov eax, [result]
ret 
addend: 



j multend
mult:

push eax
push ebx

; num result = a * b
mov eax, a
mov ebx, b
mul eax, ebx
mov [result], eax

pop ebx
pop eax

mov eax, [result]
ret 
multend: 


mov ebx, 2
mov ebx,  3
call add
; num result1 = add(2, 3)
mov [result1], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result1]
xor rax, rax
call printf

; num a = 2 => Optimized
mov eax, 2
mov [a], eax

; num b = 3 => Optimized
mov eax, 3
mov [b], eax

mov ebx, a
mov ebx,  b
call add
; num result2 = add(a, b)
mov [result2], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result2]
xor rax, rax
call printf

mov ebx, a
mov ebx,  b
call mult
; num result3 = mult(a, b)
mov [result3], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result3]
xor rax, rax
call printf

mov ebx, a
mov ebx, a
call mult
; num result4 = mult(a,a)
mov [result4], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result4]
xor rax, rax
call printf

mov ebx, b
mov ebx, b
call mult
; num result5 = mult(b,b)
mov [result5], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result5]
xor rax, rax
call printf

mov ebx, a
mov ebx,  b
call add
mov ebx, a
mov ebx,  b
call mult
; num result7 = add(a, b) - mult(a, b)
sub eax, ebx
mov [result7], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result7]
xor rax, rax
call printf

mov ebx, a
mov ebx, a
call add
mov ebx, a
mov ebx, b
call mult
mov ebx, b
mov ebx, b
call mult
; num result8 = add(a,a) + mult(a,b) * mult(b,b)
mul eax, ebx
add eax, ebx
mov [result8], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [result8]
xor rax, rax
call printf

mov ebx, add(a
mov ebx, b
call add

; print a string
mov rsi,  "Result of adding first and second user inputs: "
mov rdi, fmtstr
mov rax, 0
call printf

mov ebx, user1
mov ebx,  user2
call add
; num userResult5 = add(user1, user2)
mov [userResult5], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult5]
xor rax, rax
call printf


; print a string
mov rsi,  "Result of multiplying third and fourth user inputs: "
mov rdi, fmtstr
mov rax, 0
call printf

mov ebx, user3
mov ebx,  user4
call mult
; num userResult6 = mult(user3, user4)
mov [userResult6], eax


; print integer back out
lea rdi, [fmtuint]
mov rsi, [userResult6]
xor rax, rax
call printf


j computeApproxSphereVolumeend
computeApproxSphereVolume:

push eax
push ebx

; num result = radius ^ 3 * 4 * 31416 / 10000 / 3
mov eax, radius
mov ebx, [3]

xor edi, edi
mov     eax, 1
mov     edx, r9
exp_start{ immediateName }:
cmp edi, edx
jz exp_done{ immediateName }
imul eax, r8
inc edi
jmp exp_start{ immediateName }
exp_done{ immediateName }:
mov ebx, [4]
mul eax, ebx
mov ebx, [31416]
mul eax, ebx
mov ebx, [10000]
div eax, ebx
mov ebx, [3]
div eax, ebx
mov [result], eax

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

; num userRadius = 0 => Optimized
mov eax, 0
mov [userRadius], eax


; read an integer
lea rdi, [fmtuintin]
lea rsi, [userRadius]
mov rax, 0
call scanf

mov ebx, userRadius)
mov ebx, 
call computeApproxSphereVolume
; num volume = computeApproxSphereVolume(userRadius)
mov [volume], eax


; print a string
mov rsi,  "The volume is: "
mov rdi, fmtstr
mov rax, 0
call printf


; print integer back out
lea rdi, [fmtuint]
mov rsi, [volume]
xor rax, rax
call printf


; print a string
mov rsi,  "Congratulations on the great semester!"
mov rdi, fmtstr
mov rax, 0
call printf
