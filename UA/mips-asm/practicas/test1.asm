.text 0x00400000
    li $s2, 6
    
    BucleWhile: #slt $t0, $s2, $s1
                blt $s2, $s1, SalirBucle
                addi $s1, $s1,1
                j BucleWhile

    SalirBucle: addi $v0, $0, 10		# System call 10 - Exit
                syscall				    # execute