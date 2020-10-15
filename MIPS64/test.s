
        .data
my_data: .word          1, 2, 3, 4, 5, 6, 7, 8, 9, 10
result: .space         8

        .text

main:    daddui        r1, r0, 0xA
         daddui        r2, r0, 0x0
         daddui        r3, r0, 0x0
         j             check

loop:    ld            r4, my_data(R3)
         dadd          r2, r2, r4
         daddi         r1, r1, 0xffff
         daddui        r3, r3, 0x8

check:   bnez          r1, loop

         sd            r2, result(R0)
         halt