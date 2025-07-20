.text
main:
ADDIU $r8,$r0,num
LW $r1, 0($r8)
BGEZAL $r1,func
SLL $r0,$r0,0
SW $r2, 60($r0)
TEQ $r0,$r0
SLL $r0,$r0,0
func:
ADD $r2,$r1,$r0
ADDI $r6,$r0,8
loop:
ADDI $r1,$r1,-1
ADDI $r3,$r0,25
LW  $r4, 60($r6)
BEQ $r1,$r0,ret
SLL $r0,$r0,0
MUL $r2,$r1,$r2
BEQ $r0,$r0,loop
SLL $r0,$r0,0
ret:
JR $r31
SLL $r0,$r0,0
.data
num: .word 5
