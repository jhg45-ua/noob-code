.data
    vector_words: .space 40   # tamaño del vector
    msg_1: .asciiz "Introduce: "
.text
    la $a0, msg_1
    li $v0, 4
    syscall

    li $t0, 12
    sw $t0, vector_words

    li $v0, 10
    syscall
