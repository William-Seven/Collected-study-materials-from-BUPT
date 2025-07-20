.text
main:
ADDIU $r2,$r0,A
ADDIU $r3,$r0,B
loop:
LW $r1,0($r2)
ADD $r1,$r1,$r3
SW $r1,0($r2)
LW $r5,0($r1)
ADDI $r5,$r5,10  
ADDI $r2,$r2,4  
SUB $r4,$r3,$r2
BGTZ $r4,loop
SLL $r0,$r0,0
TEQ $r0,$r0
SLL $r0,$r0,0
SLL $r0,$r0,0
.data
A: .word 0, 4, 8
B: .word 2, 1, 0
