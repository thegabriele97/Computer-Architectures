

    .data

v1:     .double     0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0
        .double     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0
        .double     2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0
        
v2:     .double     0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0
        .double     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0
        .double     2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0
        
v3:     .double     0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0
        .double     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0
        .double     2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0
        
v4:     .double     0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0
        .double     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0
        .double     2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0
        
v5:     .space      0xf0                # 30 items * 8 byte
v6:     .space      0xf0                # 30 items * 8 byte
v7:     .space      0xf0                # 30 items * 8 byte

    .text

main:
        daddui      r8, r0, 0x1e        # r8 <-- 30
        dadd        r9, r0, r0          # r9 <-- 0          # used as index

        dsll        r8, r8, 0x3         # r8 <-- r8 << 3    # multiply r8 by 8 because index increments by 8 at each loop
        l.d         f1, v1(r9)          # f1 <-- v1[r9]

loop:
        l.d         f2, v2(r9)          # f2 <-- v2[r9]
        l.d         f3, v3(r9)          # f3 <-- v3[r9]
        
        sub.d       f5, f1, f2          # f5 <-- f1 - f2
        l.d         f4, v4(r9)          # f4 <-- v4[r9]
                
        mul.d       f5, f5, f3          # f5 <-- f5 * f3
        mul.d       f6, f5, f3          # f6 <-- f5 * f3
        add.d       f7, f6, f4          # f7 <-- f6 + f4
        mul.d       f7, f7, f2          # f7 <-- f7 * f2

        s.d         f5, v5(r9)          # f5 --> v5[r9]
        s.d         f6, v6(r9)          # f6 --> v6[r9]
        s.d         f7, v7(r9)          # f7 --> v7[r9]

        daddui      r9, r9, 0x8         # r9 <-- r9 + 8     # computing next index

check:
        bne         r9, r8, loop        # if r9 != r8, loop
        l.d         f1, v1(r9)          # f1 <-- v1[r9]

then:
        halt