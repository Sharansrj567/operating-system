.section .text
.global zfunction
.type zfunction, @function
.LC0:
.string "\nlong zfunction(long param)\n"
.text

zfunction:
    // saving the value of the base pointer
    push %ebp  
    movl %esp, %ebp

    # printing to verify
    push $ .LC0
    call kprintf

    # loading parameter into eax register
    mov 0x4(%esp), %eax


    # clearing the 20th to 27th bits
    movl 8(%ebp), %eax
    and $0xfffff00f, %eax

    # left shifting
    sall $8, %eax

    # filling right bits
    orl $0xff, %eax
    leave

    # returning
    ret

    .size zfunction, .-zfunction