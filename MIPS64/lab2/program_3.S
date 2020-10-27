                    #
                    #   La Greca Salvatore Gabriele
                    #   Polito - s281589
                    #

    .data
a:      .byte       1, 2, 3, 4, 5, 7, 8, 1, 2, 3, 4, 5, 7, 8, 1, 2, 3, 4, 5, 7, 8, 1, 2, 3, 4, 5, 7, 8, 1, 2

b:      .byte       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1

res:     .space      0x1e                       # 30 bytes of storage

    .text

main:
        daddui      r1, r0, 0x1e                # r1 <-- 14                 # number of items in r1        
        daddu       r2, r0, r0                  # r2 <-- 0                  # used as index
        j           check

loop:
        lb          r3, a(r2)                   # r3 <-- a[r2]
        lb          r4, b(r2)                   # r4 <-- b[r2]
        daddu       r6, r0, r0                  # r6 <-- 0                  # used to store res

is_odd:
        andi        r5, r4, 0x1                 # r5 <-- r4 and 1           # i need to check if the lsb is eq to 1 to know if it is odd
        bnez        r5, add_odd                 # if r5 != 0, add to res         

continue:
        dsll        r3, r3, 0x1                 # r3 <-- r3 << 1            # mul r3 by 2
        dsrl        r4, r4, 0x1                 # r4 <-- r4 >> 1            # div r4 by 2
        bnez        r4, is_odd                  # if r4 != 0, do it again

        sb          r6, res(r2)                 # r6 --> res[r2]
        daddui      r2, r2, 0x1                 # r2 <-- r2 + 1

check:
        bne         r2, r1, loop                # loop if index != number of items
        j           end_loop

add_odd:
        dadd        r6, r6, r3                  # r6 <-- r6 + r3            # res += a[i]
        j           continue

end_loop:
        halt
