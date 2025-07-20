.text
main:
ADDI  $r2,$r0,1024
ADD   $r3,$r0,$r0
ADDI  $r4,$r0,8
loop:  
LW    $r1,0($r2)
ADDI  $r1,$r1,1
SW    $r1,0($r2)
ADDI  $r3,$r3,4
SUB   $r5,$r4,$r3
BGTZ  $r5,loop
ADD   $r7,$r0,$r6
TEQ   $r0,$r0



