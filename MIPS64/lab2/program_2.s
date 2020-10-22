                    #
                    #   La Greca Salvatore Gabriele
                    #   Polito - s281589
                    #

    .data
v1:     .double     0.0, 0.1, 0.2, 0.3
        .double     0.4, 0.5, 0.6, 0.7
        .double     0.8, 0.9, 1.0, 1.1
        .double     1.2, 1.3, 1.4, 1.5
        .double     1.6, 1.7, 1.8, 1.9
        .double     2.0, 2.1, 2.2, 2.3
        .double     2.4

v2:     .double     0.0, 0.1, 0.2, 0.3
        .double     0.4, 0.5, 0.6, 0.7
        .double     0.8, 0.9, 1.0, 1.1
        .double     1.2, 1.3, 1.4, 1.5
        .double     1.6, 1.7, 1.8, 1.9
        .double     2.0, 2.1, 2.2, 2.3
        .double     2.4

v4:     .double     0.0, 0.1, 0.2, 0.3
        .double     0.4, 0.5, 0.6, 0.7
        .double     0.8, 0.9, 1.0, 1.1
        .double     1.2, 1.3, 1.4, 1.5
        .double     1.6, 1.7, 1.8, 1.9
        .double     2.0, 2.1, 2.2, 2.3
        .double     2.4

v3:     .space      0xC8                                # 200 bytes (25 double * 8 byte each double)
v5:     .space      0xC8                                # same

    .text

main:
        daddui      r6, r0, 0x19                        # r6 <-- 25             # total of cycles to do
        daddu       r7, r0, r0                          # r7 <-- 0              # used as index for matrixes (looped as array)
        
        dsll        r6, r6, 0x3                         # r6 <-- r6 << 3        # multiplying r6 by 8 in this way r7 will reach it correctly
        j           check

loop:
        l.d         f1, v1(r7)                          # f1 <-- v1[r7]
        l.d         f2, v2(r7)                          # f2 <-- v2[r7]
        l.d         f4, v4(r7)                          # f4 <-- v4[r7]

        mul.d       f3, f1, f2                          # f3 <-- f1 * f2
        mul.d       f5, f3, f4                          # f5 <-- f3 * f4

        s.d         f3, v3(r7)                          # f3 --> v3[r7]
        s.d         f5, v5(r7)                          # f5 --> v5[r7]

        daddui      r7, r7, 0x8                         # r7 <-- r7 + 8         # going at the next float numbers

check:
        bne         r7, r6, loop                        # loop if r7 != r6

then:
        halt