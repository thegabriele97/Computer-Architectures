
        .data

        .text

        nop
        nop
        nop
        daddi           r6, r0, 0x7fff
        bnez            r6, lab

lab:
        halt