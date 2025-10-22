.data
v1:     .byte 3, 2, 10
v2:     .half 12, 3, 12
v3:     .word 12, 2, 21

.text 0x00400000
    la $a0, v1
    lb $t0, 0($a0) # t0 = 0x03
    lb $t1, 1($a0) # t1 = 0x02
    lb $t2, 2($a0) # t2 = 0x0A

    add $t3, $t0, $t1
    add $t3, $t2, $t3

    sb $t3, 3($a0)
