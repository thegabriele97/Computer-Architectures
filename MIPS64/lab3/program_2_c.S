

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
        dadd        r9, r0, r0          # r9 <-- 0              # used as index
        daddui      r10, r0, 0x8
        daddui      r11, r0, 0x10  

        dsll        r8, r8, 0x3         # r8 <-- r8 << 3        # multiply r8 by 8 because index increments by 8 at each loop

loop:                                   # loop unrolling
        l.d         f1, v1(r9)          # f1 <-- v1[r9]
        l.d         f2, v2(r9)          # f2 <-- v2[r9]
        l.d         f3, v3(r9)          # f3 <-- v3[r9]
        
        sub.d       f5, f1, f2          # f5 <-- f1 - f2
        l.d         f8, v1(r10)         # f1 <-- v1[r9]
        l.d         f9, v2(r10)         # f2 <-- v2[r9]
        l.d         f4, v4(r9)          # f4 <-- v4[r9]
        mul.d       f5, f5, f3          # f5 <-- f5 * f3
        
        sub.d       f11, f8, f9         # f5 <-- f1 - f2
        l.d         f10, v3(r10)        # f3 <-- v3[r9]
        l.d         f1, v1(r11)         # f1 <-- v1[r9]         # FROM THE THIRD SEGMENT
        l.d         f15, v2(r11)        # f2 <-- v2[r9]         # FROM THE THIRD SEGMENT
        mul.d       f11, f11, f10       # f5 <-- f5 * f3        # FROM THE THIRD SEGMENT
        l.d         f12, v4(r10)        # f4 <-- v4[r9]
        s.d         f5, v5(r9)          # f5 --> v5[r9]
        
        mul.d       f6, f5, f3          # f6 <-- f5 * f3
        l.d         f3, v3(r11)         # f3 <-- v3[r9]         # FROM THE THIRD SEGMENT
        l.d         f16, v4(r11)        # f4 <-- v4[r9]         # FROM THE THIRD SEGMENT
        sub.d       f5, f1, f15         # f5 <-- f1 - f2        # FROM THE THIRD SEGMENT
        s.d         f11, v5(r10)        # f5 --> v5[r9]       
        mul.d       f13, f11, f10       # f6 <-- f5 * f3
        add.d       f7, f6, f4          # f7 <-- f6 + f4
        mul.d       f5, f5, f3          # f5 <-- f5 * f3        # FROM THE THIRD SEGMENT
        s.d         f6, v6(r9)          # f6 --> v6[r9]         # FROM THE FIRST SEGMENT


        mul.d       f7, f7, f2          # f7 <-- f7 * f2
        mul.d       f6, f5, f3          # f6 <-- f5 * f3        # FROM THE THIRD SEGMENT
        s.d         f5, v5(r11)         # f5 --> v5[r9]         # FROM THE THIRD SEGMENT

        add.d       f14, f13, f12       # f7 <-- f6 + f4
        s.d         f7, v7(r9)          # f7 --> v7[r9]

        daddui      r9, r9, 0x18        # r9 <-- r9 + 8         # computing next index
        add.d       f17, f6, f16         # f7 <-- f6 + f4
       
                
        s.d         f13, v6(r10)        # f6 --> v6[r9]
        mul.d       f14, f14, f9        # f7 <-- f7 * f2
        s.d         f6, v6(r11)         # f6 --> v6[r9]

        mul.d       f17, f17, f15         # f7 <-- f7 * f2
        s.d         f14, v7(r10)        # f7 --> v7[r9]

        daddui      r10, r10, 0x18      # r9 <-- r9 + 8         # computing next index
        #################################################################################################
        
                
        s.d         f17, v7(r11)         # f7 --> v7[r9]

check:
        bne         r9, r8, loop        # if r9 != r8, loop
        daddui      r11, r11, 0x18      # r9 <-- r9 + 8     # computing next index

then:
        halt