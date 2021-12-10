
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
issue1: resd 1
issue2: resd 1
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
: resd 1
: resd 1
: resd 1
a: resd 1
b: resd 1
: resd 1
userRadius: resd 1

section.text

extern printf
extern scanf
global main
main :
push rbp; Push base pointer onto stack to save it
