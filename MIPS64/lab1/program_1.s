                    ;
                    ;   La Greca Salvatore Gabriele
                    ;   Polito - s281589
                    ;

        .data
a:      .word16     -801, 660, 113, 94, -78, 537, 464, 729 
        .word16     -521, -368, -18, -405, -270, -805, -800, -515
        .word16     498, -475, 292, -972, 267, 696, -289, 164
        .word16     934, 846, 900, 391, 510, 932

b:      .word16     30, 627, -730, -516, -752, -320, -216, -170
        .word16     609, 427, -631, 428, -439, 25, -882, 814
        .word16     364, 556, -240, -42, 594, -125, -275, -663
        .word16    -245, 700, 767, -991, 646, -253

c:      .space      0x3c                        ; 30 array cells, each of 16 bits so 60 bytes
max:    .space      0x1                         ; 2 byte of space
min:    .space      0x1                         ; 2 byte of space

        .text
main:
        daddi       r1, r0, 0x1e                ; r1 <-- const              ; numbers of values 
        dadd        r2, r0, r0                  ; r2 <-- 0                  ; indexer
        
        daddi       r6, r0, 0x8000              ; r6 <-- -32768             ; storing the highest value in r6 to check for the max
        daddi       r7, r0, 0x7fff              ; r7 <-- +32767             ; storing the lowest value in r7 to check for the mins
        dsll        r1, r1, 0x1                 ; r1 <-- r1 << 1            ; r1 = r1*2 because i check r2 that grows up by 2 bytes at a time and compare it with r1

        j           loop                        ; -                         ; branch to loop to check if the loop can be started

sum:    
        lh          r3, a(r2)                   ; r3 <-- a[r2]
        lh          r4, b(r2)                   ; r4 <-- b[r2]

        dadd        r5, r3, r4                  ; r5 <-- r3 + r4            ; storing the result in r5
        dsll        r5, r5, 0x2                 ; r5 <-- r5 << 2            ; multiply by 4

        slt         r3, r5, r7                  ; r3 <-- r5 < r7 ? 1 : 0    ; checking for the minimum value
        slt         r4, r6, r5                  ; r4 <-- r6 < r5 ? 1 : 0    ; I looking for r5 > r6 for the maximum value

        beqz        r3, no_min                  ; -                         ; if r3 = 0, branch because its not the min
        daddu       r7, r0, r5                  ; r7 <-- r5                 ; saving the new minimum value

no_min:
        beqz        r4, no_max                  ; -                         ; if r4 = 0, branch because its not the max
        daddu       r6, r0, r5                  ; r6 <-- r5                 ; saving the new maximum value

no_max:
        sh          r5, c(r2)                   ; r5 --> c[r2]              ; storing the result in memory 
        daddui      r2, r2, 0x2                 ; r2 <-- r2 + 2

loop:                
        bne         r2, r1, sum                 ; if (r2 != r1): branch     ; checking the end of the loop

out_lo:
        sh          r7, min(r0)                 ; r7 --> min[r0]            ; storing the minimum value in memory
        sh          r6, max(r0)                 ; r6 --> max[r0]            ; storing the maximum value in memory
        
        halt