; 10 integers addition
;---------------------------
.data
values: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ;64-bit integers
result: .space 8
.text
MAIN: daddui R1,R0,10 ;R1 <-- 10
dadd R2,R0,R0 ;R2 <-- 0 POINTER REG
dadd R3,R0,R0 ;R3 <-- 0 RESULT REG

LOOP: ld R4,values(R2) ;GET A VALUE IN R4
dadd R3,R3,R4 ;R3 <-- R3 + R4
daddi R2,R2,8 ;R2 <-- R2 + 8 POINTER INCREMENT
daddi R1,R1,-1 ;R1 <-- R1 - 1 DECREMENT COUNTER
bnez R1,LOOP
sd R3,result(R0) ;Result in MEM
halt ;the end