/*sum.s
*/

.text

.global sum

sum:

mov r3,r0
add r3,r1
mov r0,r3
mov pc,lr	;#  lr即r14

.end
