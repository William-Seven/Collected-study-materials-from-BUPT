.text
main:
ADDIU  $r1,$r0,A
LW     $r2,0($r1)
ADD    $r4,$r0,$r2
SW     $r4,0($r1)
LW     $r6,4($r1)
ADD    $r8,$r6,$r1
MUL    $r12,$r10,$r1
ADD    $r16,$r12,$r1
ADD    $r18,$r16,$r1
SW     $r18,16($r1)
LW     $r20,8($r1)
MUL    $r22,$r20,$r14
MUL    $r24,$r26,$r14
TEQ $r0,$r0

.data
A: 
.word 4,6,8
