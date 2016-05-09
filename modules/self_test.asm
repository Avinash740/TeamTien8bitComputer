// ******* Found online *************
// This is a test of a VESPA processor.
//
// Testing hardware with software running on that same questionable 
// hardware is not trivial, so we will start out by being somewhat
// skeptical that things actually work, and we will get more
// sophisticated as we build confidence.    
// 
//------------------------------------------------------------------------
// USER REQUIREMENTS
//------------------------------------------------------------------------
// 
//   When a HALT instruction is encountered...... 
//     the user must somehow 
//      - output the current values of Registers 1, 2, 3, and 5, and 
//      - output the program counter 
//	
//------------------------------------------------------------------------
// OUTPUT SUMMARY
//------------------------------------------------------------------------
//
//  PC (Program Counter) 
//     < 0x0800 - initial sanity checks failed
//     > 0x0800 - sanity tests passed
//       - see registers 1, 2, 3, and 5 for test results
//
//  Registers 1, 2, 3, and 5
//    test result details - IF - the initial sanity tests passed
//
//  Register 0 
//    an easy way to watch the progress thru this test program 
//
//------------------------------------------------------------------------
// OUTPUT DETAILS
//------------------------------------------------------------------------
//      
//  The value of the program counter will tell which of the HLT
//  instructions was executed.  
//    - The first HALT instructions appear in the intial sanity checks.
//      A HALT with a program counter less than 0x0800 indicates
//      that there was a HALT during initial sanity checking.
//        HALT address
//               < 0100  - initial branch tests failed
//         0100 -> 0200  - setting the -equal- condition code testing failed
//         0200 -> 0300  - load-immediate and -equal- condition code testing failed
//         0300 -> 0400  - load-immediate, compare, or, and -equal- cc testing failed
//         0400 -> 0500  - using registers 0 thru 7
//    - If the HALT is at a program counter value greater than 
//      0x0800, then the initial sanity checks passed.
//
//  If the initial sanity checks are passed, then Registers 1, 2, and 3  
//  will be used as indicators showing which tests are successfully 
//  executed in some general categories.  The registers are used as
//  -bit-masks- with a bit turned on for each test category successfully executed.
//  This technique allows the values in these registers to simultaneously
//    indicate which tests passed,
//    indicate which tests failed.
//  At least during processor development and debug the indication of 
//  which tests did -not- pass will be exceedingly useful.  Note that there
//  is not a bit for each and every test.  Instead, each bit represents a
//  -small- group of similar tests.
//
//   Reg 1 - Category 1 - basic register useage, memory access, and condition code
//   Reg 2 - Category 2 - alu operations
//   Reg 3 - Category 3 - more complex operations, data hazards
//
//  (in the following list the value under the -label- column is the assembler
//   label at the start of this test section - possibly handy if you want to
//   quickly locate the implementation for a particular test.)   
//		
//   The tests are performed in the same order as the bits are listed here.  This
//   is done because if there are multiple failures the first failure is probably
//   the more interesting.  This is because subsequent failures can be the result
//   of innocently using a function previously found to be incorrect.
//
//     Register 1 - bit mask values          -binary-           -hex-    -label-
//       verify-register-access        0..0100000000000000     x0..4000    RA0
//       load-immediate-positive       0..0010000000000000     x0..2000    LI0
//       load/store                    0..0001000000000000     x0..1000    LS0
//       load-immediate-negative       0..0000100000000000     x0..0800    LI10 
//       more load-immediate           0..0000010000000000     x0..0400    LI15
//       -N- condition code            0..0000001000000000     x0..0200    CN0
//       -Z- condition code            0..0000000100000000     x0..0100    CZ0
//       -V- condition code            0..0000000010000000     x0..0080    CV0
//       -C- condition code            0..0000000001000000     x0..0040    CC0
//     Register 2 - bit mask values
//       compare register              0..0100000000000000     x0..4000    CP0
//       compare immediate             0..0010000000000000     x0..2000    CP14
//       add register                  0..0001000000000000     x0..1000    AD0
//       add immediate                 0..0000100000000000     x0..0800    AD11
//       subtract register             0..0000010000000000     x0..0400    SU0
//       subtract immediate            0..0000001000000000     x0..0200    SU11
//       and register                  0..0000000100000000     x0..0100    AN0
//       and immediate                 0..0000000010000000     x0..0080    AN7
//       or register                   0..0000000001000000     x0..0040    OR0
//       or immediate                  0..0000000000100000     x0..0020    OR7
//       not                           0..0000000000010000     x0..0010    NT0
//     Register 3 - bit mask values
//       BGE and BLT tests             0..0100000000000000     x0..4000    CX0
//       BGT and BLE tests             0..0010000000000000     x0..2000    CX10
//       ALU pass-thru tests           0..0001000000000000     x0..1000    PT0
//       load-indexed                  0..0000100000000000     x0..0800    LX0
//       store-indexed                 0..0000010000000000     x0..0400    SX0
//       branch - next instruction     0..0000001000000000     x0..0200    BC0
//       branch - negative offset      0..0000000100000000     x0..0100    BC10
//       jump                          0..0000000010000000     x0..0080    JP0
//       jump-and-link                 0..0000000001000000     x0..0040    JL0
//       hazard recently modified reg  0..0000000000100000     x0..0020    DH0
//       hazard recently modified reg  0..0000000000010000     x0..0010    DH5
//       hazard recently modified reg  0..0000000000001000     x0..0008    DH10
//       hazard recently loaded reg    0..0000000000000100     x0..0004    DH20
//       really risky tests            0..0000000000000010     x0..0002    RR0 
//
//
//  Register 5 is a simple count of the tests passed.
//
//  Register 0 is loaded with the bit-mask value for each test - when that
//    test is completed.  This happens if the test is successful or not.
//    So watching the value of Reg 0 let-s you keep track of the last
//    test which was completed.        
//
//------------------------------------------------------------------------
// OUTPUT AFTER PERFECT EXECUTION
//------------------------------------------------------------------------
//      
// If -all- tests have been passed, then, when we halt...
//   the PC will be greater than 0x0800
//   Register 1 will contain  00007FC0 
//   Register 2 will contain  00007FF0
//   Register 3 will contain  00007FFE
//   Register 5 will contain  0000006E  (110 - decimal)
//
// Approximately 1100 (decimal) instructions will be executed. 
//
// Note - it is not considered good form to simply set the VESPA 
//        registers to these values and terminate without actually
//        doing much of anything.  Initially that might look 
//        exceedingly successful, but....    
//
//------------------------------------------------------------------------
// Let-s begin
//------------------------------------------------------------------------
// The first thing we are going to do is test that we can BRANCH forward
// correctly.  (We will worry about branch back, or with a negative
// offset later.)  (We will also worry about setting and testing the
// condition code later.)  
// If we cannot branch, then it is going to be pretty hard to alter our
// instruction sequence based on the results of any testing.
//
// If this branch testing should FAIL, we will HALT with a program 
// counter which is less than 100 (hex). 
//
       NOP                  ; do nothing be sure we can increment the PC 
       BRA   B11            ; branch (always) - be sure we compute a br addr 
//                  Note that -branch-delay- processing means that somewhere,
//                  somehow some -nop- instructions are being inserted after a branch.
//                  We put one here to be -very- sure since we are not very trusting yet.  
       NOP                  ; nop just to be sure we do not have branch delay problems
       HLT                  ; if we did not branch we should just stop here
       HLT                  ; it should not be possible to get here, but...
       HLT                  ; it should not be possible to get here, but...
B11:   BRA   B12            ; let-s try another branch
//                  This branch target B11 is surrounded by HLT instructions
//                  so if the branch address was computed incorrectly we 
//                  are probably going to hit one of the HLT instructions.  
       NOP                  ; nop just to be sure we do not have branch delay problems
       HLT                  ; again - should not get here
       HLT                  ; or here
       HLT                  ; or here
       NOP                  ; or here 
B12:   NOP                  ; but we should have gotten here
       NOP                  ; just insert a filler
       NOP                  ; and another filler
//                  Now let-s be sure we do not have some problem with branch-delay
//                  processing.  
       BRA   B13            ; branch again
       HLT                  ; if the next instruction is executed we halt
       HLT                  ; should not be able to get here
       HLT                  ; or here
B13:   BRA   B20            ; finally let-s go on to the next tests
//
// Well, it seems that we can branch forward. (At least some)
// And, the next instruction after a branch is -not- being executed. 
//  
//------------------------------------------------------------------------
// Now, let-s see about some setting and testing of the -equal- condition code 
//------------------------------------------------------------------------
// We are going to worry first about -equal- or -zero- setting and testing
// of the condition code.  After all, if we want to know if the result of 
// a test was successful we need to check to see if the result was equal
// to an expected value.  
       .ORG   0x100         ; set the instruction address
//                  Note - we are setting the location - to group HALT
//                  addresses for this early testing
// If this initial testing of setting and testing the -equal- condition code
// should FAIL, we will HALT with a program counter in the 0x1xx range.
//
// The goal of this testing is to check that we can -probably- set and test
// the -equal- or -zero- bit of the condition code. 
//
// Of course this implicitly tests some ALU operations also because you have
// to use the ALU to set the condition code bits.
//
// We will be using register zero for these tests to minimize any difficulty
// in correctly computing the address of a register in the register array 
// 
B20:   NOP                  ; well, here we are after branch testing
       LDI    R0,#0         ; phooey - trapped
// verilog requires a reg be -set- before it can be used - oh well
       NOP
       NOP
       SUB   R0,R0,R0       ; subtracting something from itself should be zero
//                  Note - this did not require any loading of the register
//                  to set an initial value
       BEQ   B21            ; we really should take this branch
       HLT                  ; if we are here then either setting the -equal-
//                            condition code or BEQ is not working so well
B21:   NOP                  ; good - it looks like BEQ worked
//                  If that is true - and we really set and tested the condition 
//                  code - then a BNE should not be taken
       BNE   B22            ; we should -not- take this branch
       BRA   B23            ; which means we should get here
B22:   HLT                  ; setting or testing the -equal- condition code
//                            failed if we have gotten here
B23:   NOP                  ; it -seems- we were successful     
//                  It seems that we set, and tested, the -equal- condition code bit
       BRA   B30            ; move on to the next tests
       HLT                  ; should not be able to get here 
// 
// It appears that we can test and set the -equal- condition code bit. 
// Of course it is possible that the condition code bit is just always
// being set to an -ON- value.
//    
//------------------------------------------------------------------------
// Now, let-s test Load-Immediate actually putting a known value in a register.
// At the same time we can continue testing the -equal- condition code bit.   
//------------------------------------------------------------------------
// We are going to attempt the LOAD IMMEDIATE instruction - using register 0.
       .ORG   0x200         ; set the instruction address
// If this initial testing of LOAD IMMEDIATE should fail, then we will HALT
// with a program counter in the 0x2xx range.
//
// The goal of this testing is to check that we can -probably- load a value
// into a register - and we are going to try to be sure that the -equal- 
// condition code bit is not just always set on.  
// 
B30:   NOP                  ; well, here we are after condition code testing
//                  We should be able to assume register zero still contains
//                  the value zero.  
       ADD   R0,R0,R0       ; adding zero to zero should be, well, zero
       BEQ   B31            ; and we should take this branch 
       HLT                  ; stop here if we had condition code troubles
B31:   LDI   R0,#1          ; ok - let-s try to load -1- into register 0
//                  If we have succeeded, then if we add the register to itself
//                  we should have a non-zero result, and the -equal- condition code
//                  bit should now be -OFF-.  We are starting to live dangerously.
       ADD   R0,R0,R0       ; we should have 2 in reg 0, and not an -equal- cond code
       BEQ   B32            ; we should therefore -not- take this branch
//                  If we got here things are going pretty well.  We have loaded 
//                  -something- in R0, -and- determined that it is non-zero, -and-
//                  we have verified that the -equal- condition code bit is not
//                  being set on all the time.
       BRA   B40            ; branch to next section if this worked        
B32:   HLT                  ; we did not set, or test the condition code correctly
       HLT                  ; should not be able to get here 
//
// Well, it seems that we really can set and test the -equal- cond code.
// Also load-immediate will put something non-zero in a register. 
// 
//------------------------------------------------------------------------
// Now, let-s try just a tiny bit more before just going wild 
//------------------------------------------------------------------------
// We are going to attempt the LOAD IMMEDIATE instruction - using register
// one - and - then we will attempt a COMPARE and OR. 
       .ORG   0x300         ; set the instruction address
// If this testing should fail we HALT with a PC in the 0x03xx range.
//
// The goal of this testing is to check that we can use registers other 
// than zero, and we can do some arithmetic operations.
// 
B40:   NOP                  ; well, here we are after and initial load-immediate
//                  Building on our previous successes we are going to assume
//                  that register zero contains -2-.  And now we will try to load
//                  another value in another register, and do a couple comparisons
//                  and subtractions.  
       LDI   R1,#1          ; let-s try to put a -1- into register 1
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       SUB   R0,R0,R1       ; try to subtract R1 from R0 - result should be 1
       BNE   B41            ; we should take this branch           
       HLT                  ; problem if we get here
B41:   NOP                  ; nop to avoid any data hazards
       SUB   R0,R0,R1       ; try to subtract R1 from R0 - result should be zero
       BNE   B42            ; so this time we should -not- take this branch   
       BEQ   B43            ; and then we should take this branch
       HLT                  ; if we got here we did not take -any- branch - very wrong
B42:   HLT                  ; if we got here we took a BNE that we should not have taken
       HLT                  ; it should be impossible to get here
B43:   NOP                  ; and if we got here we did it correctly - and R0 contains zero
       OR    R0,R0,R1       ; let-s try an -or- operation - result should be 1
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       ADD   R0,R0,R0       ; and then add the result to itself - result should be 2
       BNE   B45            ; we should branch because the result should be -2-
       HLT                  ; halt if something (probably the -or-) did not work
B45:   NOP                  ; nop to avoid any data hazards
       LDI   R1,#2          ; let-s try to put a -2- into register 1
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       CMP   R1,R1          ; and now let-s try a cmp - result should be equal
       BEQ   B46            ; and we should take this branch
       HLT                  ; halt if the compare failed - or did not set the cond code        
B46:   NOP                  ; nop to avoid any data hazards
       BRA   B50            ; let-s go start doing some serious testing  
//
// Well, it seems that we really can do some basic functions.
// Now let-s be reasonably sure we can use at least registers 0 thru 7
//
//------------------------------------------------------------------------
// Now, let-s try addressing all the registers 0 thru 7 
//------------------------------------------------------------------------
       .ORG   0x400         ; set the instruction address
// If this initial testing of the registers zero thru seven
// should fail, then we will HALT with a program counter in the 0x4xx range.
// 
B50:   NOP                  ; well, here we are with some basic stuff working
       LDI   R0,#1          ; load R0 with 1 
       LDI   R1,#2          ; load R1 with 2 
       LDI   R3,#3          ; load R3 with 3
       NOP                  ; nop to avoid any data hazards
       ADD   R2,R0,R1       ; load R2 with 3
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       CMP   R2,R3          ; hopefully verify we loaded regs 0 thru 3
       BEQ   B51            ; should branch
       HLT                  ; halt if we cannot use the regs
B51:   LDI   R4,#4          ; load R4 with 4
       LDI   R5,#5          ; load R5 with 5
       LDI   R7,#9          ; load R7 with 9
       NOP                  ; nop to avoid any data hazards
       ADD   R6,R4,R5       ; load R6 with 9
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       CMP   R6,R7          ; hopefully verify we loaded regs 4 thru 7
       BEQ   B52            ; should branch
       HLT                  ; halt if we cannot use the regs
//                  It seems we can use regs 0 thru 7 -but- not being a
//                  very trusting soul we should probably check that some
//                  wierd problem has not made it so when we address reg 4 
//                  we really get reg 0, reg 5 is really reg 1, etc.  
B52:   LDI   R0,#17         ; load R0 with 17
       LDI   R4,#2          ; load R4 with 2 (should 0 and 4 be the same this is a problem)
       LDI   R2,#3          ; load R2 with 3 
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       ADD   R6,R0,R4       ; load R6 with 19     
       LDI   R7,#19         ; load R7 with 19 
       LDI   R3,#4          ; trash R7 should R3 and R7 be somehow the same
       NOP                  ; nop to avoid any data hazards
       NOP                  ; nop to avoid any data hazards
       CMP   R6,R7          ; compare R6 and R7
       BEQ   B60            ; should branch
       HLT                  ; halt if we cannot use the regs
//
// Well, it seems that we can do some basic operations.
// We have verified a -very- limited set of.....
//   branch, load-immediate, add, subtract, or, compare.
// And we seem to be able to use at least regs 0 thru 7.
// At least we seem to have the functions working that we want to 
// use to -keep-score- for the remaining tests.
//
//------------------------------------------------------------------------
// So let-s begin
//------------------------------------------------------------------------
//
// First let-s declare some data areas that we are going to be
// using later.
//
       .ORG   0x600         ; set the instruction address
WP1:   .word  0x1           ; a plus one in memory
WP2:   .word  0x2           ; a plus two in memory
WP4:   .word  0x4           ; a plus four in memory
W22P:  .word  0x001FFFFF    ; largest 22-bit positive number 2,097,151
WPM:   .word  0x7FFFFFFF    ; largest positive number
WMM:   .word  0x80000000    ; largest negative number
W22M:  .word  0xFFE00000    ; largest 22-bit negative number 2,097,152
WM2:   .word  0xFFFFFFFE    ; a minus two in memory
WM1:   .word  0xFFFFFFFF    ; a minus one in memory
W17P:  .word  0x0000FFFC    ; a 17-bit positive value
WP1X:  .word  0x1           ; another plus one in memory
       .ORG   0x640         ; set the instruction address
WX1:   .word  0x0
WX2:   .word  0x0
WX3:   .word  0x0  
//  
// And next we are going to drop some code here at a fixed known address
// that we are going to use for -jump- targets much later
//  target for first jump test
       .org   0x700         ; set the instruction address
       ADD    R10,R10,#1    ; increment an indicator
       BRA    JP1           ; and go back
// target for second jump test - we are really trying for 0720 by using
// 0710 + offset 0010.  But if the offset is not used properly we might hit 0710
       .org   0x710         ; set the instruction address
       ADD    R10,R10,#16   ; increment an indicator
       BRA    JP4           ; and go back
       .org   0x720         ; set the instruction address
       ADD    R10,R10,#2    ; increment an indicator
       BRA    JP4           ; and go back
// target for third jump test - we are really trying for 0730 by using
// 0740 - offset 0010.  But if the offset is not used properly we might hit 0740
       .org   0x730         ; set the instruction address
       ADD    R10,R10,#4    ; increment an indicator
       BRA    JP7           ; and go back
       .org   0x740         ; set the instruction address
       ADD    R10,R10,#16    ; increment an indicator
       BRA    JP7           ; and go back
// target for fourth jump test - we are really trying for 0750 by using
// -10 + offset 0760.  But if the offset is not used properly we might hit 0760
       .org   0x750         ; set the instruction address
       ADD    R10,R10,#8    ; increment an indicator
       BRA    JP10          ; and go back
       .org   0x760         ; set the instruction address
       ADD    R10,R10,#16   ; increment an indicator
       BRA    JP10          ; and go back
//  target for first jump and link test
       .org   0x780         ; set the instruction address
       ADD    R10,R10,#1    ; increment an indicator
       BRA    JL1           ; and go back
//  target for second jump and link test
       .org   0x790         ; set the instruction address
JL4:   LDI    R9,#0x07B0    ; set up jump target address
       LDI    R8,#0         ; clear link register
       NOP
       NOP
       JMPL   R8,R9         ; jump and link - to address 0x07B0 
       .org   0x7B0         ; set the instruction address
       BRA    JL5           ; and go back
//
//------------------------------------------------------------------------
// Now, let-s start some serious testing. 
//------------------------------------------------------------------------
// First - we initialize the registers we are going to use to keep
// track of just how well things are working
//
// And a couple of -notation- things.....
//      - from here on we are not going to put a comment saying why
//        nop-s are inserted - it should be obvious and understood
//      - code and comments shifted 2 positions to the right are
//        -score-keeping- code only and are not -really- part of 
//        the code which is actually performing some test 
//------------------------------------------------------------------------
       .ORG   0x800         ; set the instruction address
B60:   NOP                  ; well, here we are after the sanity checks
       SUB   R1,R1,R1       ; clear indicator register
       SUB   R2,R2,R2       ; clear indicator register
       SUB   R3,R3,R3       ; clear indicator register
       SUB   R5,R5,R5       ; scorekeeping register - nothing passed yet
       LDI   R6,#1          ; scorekeeping incrementing value 
//------------------------------------------------------------------------
// Verify all registers can be used
//
// reference registers 8, 9, 10, and 11
// reference registers 12, 13, 14, and 15
// reference registers 16, 17, 18, and 19
// reference registers 20, 21, 22, and 23
// reference registers 24, 25, 26, and 27
// reference registers 28, 29, 30, and 31
//
//   success flag - REG 1 - 00004000   
//------------------------------------------------------------------------
 RA0:    SUB   R7,R7,R7       ; clear local score
// reference registers 8, 9, 10, and 11
       LDI   R8,#1          ; load R8 with 1 
       LDI   R9,#2          ; load R9 with 2 
       LDI   R11,#3         ; load R11 with 3
       NOP         
       ADD   R10,R8,R9      ; load R10 with 3
       NOP               
       NOP              
       CMP   R10,R11        ; hopefully verify we loaded regs 8 thru 11
       BEQ   RA1            ; should branch
       BRA   RA2           
RA1:     ADD   R7,R7,R6       ; increment score  
// reference registers 12, 13, 14, and 15
RA2:   LDI   R12,#4         ; load R12 with 4
       LDI   R13,#5         ; load R13 with 5
       LDI   R15,#9         ; load R15 with 9
       NOP              
       ADD   R14,R12,R13    ; load R14 with 9
       NOP               
       NOP                
       CMP   R14,R15        ; hopefully verify we loaded regs 12 thru 15
       BEQ   RA3            ; should branch
       BRA   RA4
RA3:     ADD   R7,R7,R6       ; increment score
// reference registers 16, 17, 18, and 19
RA4:   LDI   R16,#10        ; load R16 with 10
       LDI   R17,#11        ; load R17 with 11
       LDI   R19,#21        ; load R19 with 21
       NOP               
       ADD   R18,R16,R17    ; load R18 with 21
       NOP                 
       NOP                
       CMP   R18,R19        ; hopefully verify we loaded regs 16 thru 19 
       BEQ   RA5            ; should branch
       BRA   RA6
RA5:     ADD   R7,R7,R6       ; increment score
// reference registers 20, 21, 22, and 23
RA6:   LDI   R20,#10        ; load R20 with 10
       LDI   R21,#11        ; load R21 with 11
       LDI   R23,#21        ; load R23 with 21
       NOP               
       ADD   R22,R20,R21    ; load R22 with 21
       NOP            
       NOP               
       CMP   R22,R23        ; hopefully verify we loaded regs 20 thru 23 
       BEQ   RA7            ; should branch
       BRA   RA8
RA7:     ADD   R7,R7,R6       ; increment score
// reference registers 24, 25, 26, and 27
RA8:   LDI   R24,#12        ; load R24 with 12
       LDI   R25,#13        ; load R25 with 13
       LDI   R27,#25        ; load R27 with 25
       NOP                
       ADD   R26,R24,R25    ; load R26 with 25
       NOP               
       NOP                 
       CMP   R26,R27        ; hopefully verify we loaded regs 24 thru 27 
       BEQ   RA9            ; should branch
       BRA   RA10
RA9:     ADD   R7,R7,R6       ; increment score
// reference registers 28, 29, 30, and 31
RA10:  LDI   R28,#14        ; load R28 with 14
       LDI   R29,#15        ; load R29 with 15
       LDI   R31,#29        ; load R31 with 29
       NOP                
       ADD   R30,R28,R29    ; load R30 with 29
       NOP               
       NOP            
       CMP   R30,R31        ; hopefully verify we loaded regs 28 thru 31 
       BEQ   RA11           ; should branch
       BRA   RA12
RA11:    ADD   R7,R7,R6       ; increment score
RA12:    LDI   R4,#6          ; number of groups of 4 registers tested
         LDI   R0,#0x4000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   LI0            ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Load Immediate tests - positive numbers
//  
// load-immediate - zero
// load-immediate - positive number
// load-immediate - max positive number
//
//   success flag - REG 1 - 00002000   
//------------------------------------------------------------------------
LI0:     SUB   R7,R7,R7 
// load-immediate - zero
       LDI   R8,#0          ; hopefully load (immediate) zero
       SUB   R9,R9,R9
       NOP             
       NOP               
       ADD   R8,R8,R9       ; use add to set condition code based on reg 8
       BEQ   LI1            ; branch if successful
       BRA   LI2
LI1:     ADD   R7,R7,R6       ; increment score
// load-immediate - positive number
LI2:   LDI   R8,#2          ; hopefully load (immediate) positive number                    
       NOP              
       NOP              
       ADD   R8,R8,R9       ; use add to set condition code based on reg 8
       BNE   LI3            ; branch if successful
       BRA   LI4
LI3:     ADD   R7,R7,R6       ; increment score
// load-immediate - max positive number
LI4:   LDI   R8,#2097151    ; hopefully load max immediate pos num (3FFFFF)
       NOP                
       NOP                 
       ADD   R8,R8,R9       ; use add to set condition code based on reg 8
       BNE   LI5            ; branch if successful
       BRA   LI6
LI5:     ADD   R7,R7,R6       ; increment score
LI6:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x2000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   L01            ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Constants set-up
//   Ok, Load-immediate of a positive value either works, or we know about
//   the failure.  We are going to use LDI to load up a few values into
//   some registers to hopefully save just a bit of time and effort as
//   we go along here.
//
// Reg 12 - 2
// Reg 13 - 3
// Reg 14 - 4
// Reg 15 - 5
// Reg 16 - 6  
//------------------------------------------------------------------------
L01:   LDI   R12,#2         ; load a -2- in reg 12
       LDI   R13,#3         ; load a -3- in reg 13
       LDI   R14,#4         ; load a -4- in reg 14
       LDI   R15,#5         ; load a -5- in reg 15
       LDI   R16,#6         ; load a -6- in reg 16  
       SUB   R20,R20,R20    ; clear indicator register
//------------------------------------------------------------------------
// Load / Store -or- Memory Access tests
//   We start out loading the same value from two different places in 
//   memory.  If our memory addressing is messed up these two loads will
//   -probably- not result in loading the same value.
//   Note - we do -not- test the maximum address allowed by load/store.
//   This is because we do not know the implemented size of the memory when
//   we run this test so......
//
// load - positive number
// load - negative number
// store
//   
//   success flag - REG 1 - 00001000   
//------------------------------------------------------------------------
LS0:     SUB   R7,R7,R7 
// load - positive number
       LD    R8,WP1X        ; hopefully load one from memory
       LD    R9,WP1         ; hopefully load one from memory
       NOP                
       NOP                 
       SUB   R9,R8,R9       ; subtract - should give zero
       BEQ   LS2            ; branch if successful
       BRA   LS3
LS2:     ADD   R7,R7,R6       ; increment score
LS3:   ADD   R8,R8,R8       ; should give us two
       LD    R9,WP2         ; hopefully load a two from memory 
       NOP               
       NOP                
       SUB   R9,R8,R9       ; subtract - should give zero
       BEQ   LS4            ; branch if successful
       BRA   LS5
LS4:     ADD   R7,R7,R6       ; increment score
// load - negative number
LS5:   LD    R9,WM2         ; hopefully load a minus two from memory 
       NOP               
       NOP                
       ADD   R9,R8,R9       ; add - should give zero
       BEQ   LS6            ; branch if successful
       BRA   LS7
LS6:     ADD   R7,R7,R6       ; increment score
// store
LS7:   ST    WX2,R8         ; hopefully store two in memory
       SUB   R9,R9,R9       ; clear R9 just to be sure
       NOP               
       NOP              
       LD    R9,WX2         ; now load the value back from memory
       NOP                 
       NOP                
       SUB   R9,R9,R8       ; and subtract - should be zero again 
       BEQ   LS8            ; branch if successful
       BRA   LS9
LS8:     ADD   R7,R7,R6       ; increment score
LS9:     LDI   R4,#4          ; number of tests
         LDI   R0,#0x1000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   LI10           ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Load Immediate tests - negative numbers
//   Note that we have not checked out -compare- using negative values
//   yet so we probably do not want to use -compare- to check that we
//   have loaded a negative value
//
// load immediate - negative number
// load immediate - largest negative number
//     
//   success flag - REG 1 - 00000800   
//------------------------------------------------------------------------
LI10:    SUB   R7,R7,R7 
// load immediate - negative number
       LDI   R8,#-1         ; hopefully load (immediate) minus one
       LD    R9,WP1         ; load positive one 
       NOP              
       NOP                 
       ADD   R10,R8,R9      ; use add which sets the cond code to compare the values
       BEQ   LI11           ; branch if successful
       BRA   LI12             
LI11:    ADD   R7,R7,R6       ; increment score
// load immediate - largest negative number
LI12:  NOP
//     LDI   R8,#-2097152   ; hopefully load largest immediate negative num
       // assembler will not allow this value - so we do it the hard way
       // After changing the assembler the opcode for LDI is 11 and not 10
       // so had to change the line.
       // .word 0x52200000

	.word 0x5A200000
       LD    R9,W22M        ; load largest immediate negative num from memroy
       SUB   R9,R9,R8       ; subtract - result should be zero
       BEQ   LI13           ; branch if successful
       BRA   LI14             
LI13:    ADD   R7,R7,R6       ; increment score
LI14:    LDI   R4,#2          ; number of tests
         LDI   R0,#0x0800     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   LI15           ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Load Immediate tests 
//   It is possible that load-immed is loading everything shifted by a 
//   bit or two.  So far our testing would not have detected that very well
//
// load immediate - verify the positive value loaded
// load immediate - verify the negative value loaded
//      
//   success flag - REG 1 - 00000400   
//------------------------------------------------------------------------
LI15:     SUB   R7,R7,R7 
// load immediate - verify the positive value loaded
       LDI   R8,#1          ; hopefully load (immediate) -one- into a register
       LD    R9,WP1         ; load -one- into a register from memory
       NOP                 
       NOP                 
       CMP   R8,R9          ; compare one and one
       BEQ   LI16           ; branch if successful
       BRA   LI17 
LI16:    ADD   R7,R7,R6       ; increment score
// load immediate - verify the negative value loaded
LI17:  LDI   R8,#-1         ; hopefully load (immediate) -minus-one- into a register
       LD    R9,WM1         ; load -minus-one- into a register from memory
       NOP                 
       NOP                
       CMP   R8,R9          ; compare minus-one and minus-one
       BEQ   LI18           ; branch if successful
       BRA   LI19
LI18:    ADD   R7,R7,R6       ; increment score
LI19:    LDI   R4,#2          ; number of tests                
         LDI   R0,#0x0400     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CN0            ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag      
//------------------------------------------------------------------------
// Condition code tests for the -N- bit
//   It would seem valid to argue that if an operation sets the -N- bit 
//   correctly, then the -operation- causing the bit to be set does not
//   matter so it is not necessary to test more than one instruction.  
//   However, Murphy's Law indicates that testing only one operation
//   is probably not a good idea. 
//
// set the -N- bit with a subtract
// clear the -N- bit with a subtract
// set the -N- bit with an add
// clear the -N- bit with an add
//   
//   success flag - REG 1 - 00000200   
//------------------------------------------------------------------------
CN0:     SUB   R7,R7,R7 
// set the -N- bit with a subtract
       LDI   R8,#1          ; load reg 8 with 1
       SUB   R9,R9,R9       ; load reg 9 with 0   
       NOP                
       NOP               
       SUB   R9,R9,R8       ; load reg 9 with minus 1 - hopefully set N bit
       BMI   CN1            ; branch if successful
       BRA   CN2
CN1:     ADD   R7,R7,R6       ; increment score
// clear the -N- bit with a subtract
CN2:   LDI   R8,#1          ; load reg 8 with 1 
       NOP                
       NOP               
       SUB   R9,R12,R8      ; load reg 9 with 1 - hopefully clear N (or set not-N) 
       BPL   CN3            ; branch if successful 
       BRA   CN4 
CN3:     ADD   R7,R7,R6       ; increment score
// set the -N- bit with an add
CN4:   LDI   R8,#-1         ; load reg 8 with minus 1 
       LDI   R9,#-2         ; load reg 9 with minus 2
       NOP                
       NOP               
       ADD   R9,R9,R8       ; load reg 9 with 1 - hopefully set N  
       BMI   CN5            ; branch if successful 
       BRA   CN6 
CN5:     ADD   R7,R7,R6       ; increment score
// clear the -N- bit with an add
CN6:   LDI   R8,#1          ; load reg 8 with 1
       NOP                
       NOP               
       ADD   R9,R12,R8      ; load reg 9 with 3 - hopefully clear N (or set not-N)
       BPL   CN7            ; branch if successful
       BRA   CN8
CN7:     ADD   R7,R7,R6       ; increment score
CN8:     LDI   R4,#4          ; number of tests
         LDI   R0,#0x0200     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CZ0            ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Condition code tests for the -Z- bit
//
// subtract giving zero - setting the -Z- bit
// subtract with a negative result - clearing the -Z- bit
// add giving a positive result - clearing -Z- bit
// add giving zero - setting the -Z- bit
//   
//   success flag - REG 1 - 00000100   
//------------------------------------------------------------------------
CZ0:     SUB   R7,R7,R7 
// subtract giving zero and setting the -Z- bit
       SUB   R9,R9,R9       ; load reg 9 with 0   - hopefully set Z bit
       BEQ   CZ1            ; branch if successful
       BRA   CZ2
CZ1:     ADD   R7,R7,R6       ; increment score
// subtract with a negative result - clearing the -Z- bit
CZ2:   LDI   R8,#1          ; load reg 8 with 1
       NOP
       NOP
       SUB   R9,R9,R8       ; subtract - giving a neg result and hopefully clearing the Z bit
       BNE   CZ3            ; branch if successful
       BRA   CZ4
CZ3:     ADD   R7,R7,R6       ; increment score 
// add giving a positive result and clearing -Z- bit
CZ4:   SUB   R9,R9,R9       ; clear reg 9
       NOP
       NOP
       ADD   R9,R9,R6       ; add - giving a pos result and hopefully clearing the Z bit  
       BNE   CZ5            ; branch if successful
       BRA   CZ6
CZ5:     ADD   R7,R7,R6       ; increment score 
// add giving zero and setting the -Z- bit
CZ6:   LDI   R9,#1          ; load reg 9 with 1
       LD    R8,WM1         ; load reg 8 with minus 1
       NOP
       NOP
       ADD   R9,R9,R8       ; add - giving zero result and hopefully setting Z bit 
       BEQ   CZ7            ; branch if successful
       BRA   CZ8
CZ7:     ADD   R7,R7,R6       ; increment score
CZ8:     LDI   R4,#4          ; number of tests
         LDI   R0,#0x0100     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CV0            ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Condition code tests for the -V- bit
//
// add to the biggest pos number causing an overflow and setting the V bit
// add not causing an overflow and clearing the V bit
// add to the biggest neg number causing an overflow and setting the V bit
// add not causing an overflow and clearing the V bit
// subtract from the biggest neg num causing an overflow and setting the V bit
// subtract not causing an overflow and clearing the V bit
//
//   success flag - REG 1 - 00000080   
//------------------------------------------------------------------------
CV0:     SUB   R7,R7,R7 
// add to the biggest pos number causing an overflow and setting the V bit
       LD    R8,WPM         ; load reg 8 with biggest positive number
       LDI   R9,#1          ; load reg 9 with one
       NOP                 
       NOP              
       ADD   R10,R8,R9      ; add and hopefully set V bit
       BVS   CV1            ; branch if successful
       BRA   CV2
CV1:     ADD   R7,R7,R6       ; increment score
// add not causing an overflow and clearing the V bit
CV2:   SUB   R8,R8,R12      ; subtract two
       NOP                
       NOP                
       ADD   R10,R8,R9      ; add and hopefully clear V bit (or set not-V)
       BVC   CV3            ; branch if successful
       BRA   CV4
CV3:     ADD   R7,R7,R6       ; increment score
// add to the biggest neg number causing an overflow and setting the V bit
CV4:   LD    R8,WMM         ; load reg 8 with biggest negative number
       LDI   R9,#-1         ; load reg 9 with minus one
       NOP                
       NOP                 
       ADD   R10,R8,R9      ; add and hopefully set V bit
       BVS   CV5            ; branch if successful
       BRA   CV6
CV5:     ADD   R7,R7,R6       ; increment score
// add not causing an overflow and clearing the V bit
CV6:   ADD   R8,R8,R12      ; add 2 to biggest neg number
       NOP                
       NOP                  
       ADD   R10,R8,R9      ; add and hopefully clear V bit (or set not-V)
       BVC   CV7            ; branch if successful
       BRA   CV8
CV7:     ADD   R7,R7,R6       ; increment score
// subtract from the biggest neg num causing an overflow and setting the V bit
CV8:   LD    R8,WMM         ; load reg 8 with biggest negative number
       LDI   R9,#1          ; load reg 9 with one
       NOP                
       NOP                 
       SUB   R10,R8,R9      ; subtract and hopefully set V bit
       BVS   CV9            ; branch if successful
       BRA   CV10
CV9:     ADD   R7,R7,R6       ; increment score
// subtract not causing an overflow and clearing the V bit
CV10:  ADD   R8,R8,R12      ; add 2 to biggest neg number
       NOP                
       NOP                  
       SUB   R10,R8,R9      ; subtract and hopefully clear V bit (or set not-V)
       BVC   CV11           ; branch if successful
       BRA   CV12
CV11:    ADD   R7,R7,R6       ; increment score
CV12:    LDI   R4,#6          ; number of tests
         LDI   R0,#0x0080     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CC0            ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Condition code tests for the -C- bit
//
// add causing a carry and setting the C bit      
// add not causing a carry and clearing the C bit      
//
//   success flag - REG 1 - 00000040   
//------------------------------------------------------------------------
CC0:     SUB   R7,R7,R7 
// add causing a carry/overflow and setting the C bit      
       LD    R8,WM1         ; load all ones into reg 8 
       LDI   R9,#1          ; load one into reg 9
       NOP                 
       NOP                 
       ADD   R10,R8,R9      ; add and hopefully set C bit
       BCS   CC1            ; branch if successful
       BRA   CC2
CC1:     ADD   R7,R7,R6       ; increment score
// add not causing a carry/overflow and clearing the C bit      
CC2:   SUB   R8,R8,R12      ; subtract two
       NOP                
       NOP               
       ADD   R10,R8,R9      ; add and hopefully clear C bit (or set not-C)
       BCC   CC3            ; branch if successful
       BRA   CC4
CC3:     ADD   R7,R7,R6       ; increment score
CC4:     LDI   R4,#2          ; number of tests
         LDI   R0,#0x0040     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CP0            ; if not skip setting the indicator bit
         OR    R1,R1,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - COMPARE - reg-reg 
//   We have already been using compare, but we have not necessarily tested
//   it as completely as we might have.  
//   We  should maybe verify that no register is changed by a compare, and
//   we should probably verify that a not-equal result is possible - which 
//   would not be the case if say the first register was just being 
//   compared with itself. 
// 
// compare two identical positive numbers in two different registers
// verify compare did not change source registers
// compare two identical negative numbers in two different registers
// verify compare did not change source registers
// compare two different positive numbers in two different registers
// compare a register to itself
//
//   success flag - REG 2 - 00004000   
//------------------------------------------------------------------------
CP0:     SUB   R7,R7,R7 
// compare two identical positive numbers in two different registers
       LDI   R9,#2          ; load (immed) reg 9 with 2
       NOP                
       NOP                
       CMP   R12,R9         ; compare and hopefully the two are equal
       BEQ   CP1            ; branch if successful - we assume this works
       BRA   CP2
CP1:     ADD   R7,R7,R6       ; increment score
// verify compare did not change source registers
CP2:   ADD   R10,R12,R9     ; add to set reg 10 - should be 4 if regs 12 and 9 are still 2
       NOP                 
       NOP               
       SUB   R10,R10,R14    ; subtract - should be zero if compare left regs 8 and 9 unchanged
       BEQ   CP3            ; branch if successful 
       BRA   CP4
CP3:     ADD   R7,R7,R6       ; increment score
// compare two identical negative numbers in two different registers
CP4:   LD    R8,WM1         ; load reg 8 with minus 1
       LD    R9,WM1         ; load reg 9 with minus 1
       NOP               
       NOP                
       CMP   R8,R9          ; compare and hopefully the two are equal
       BEQ   CP5            ; branch if successful 
       BRA   CP6
CP5:     ADD   R7,R7,R6       ; increment score
// verify compare did not change source registers
CP6:   ADD   R10,R8,R9      ; load reg 10 - should be minus 2 if regs 8 and 9 are still -1 
       NOP                
       NOP                 
       ADD   R10,R10,R12    ; add - should be zero if compare left regs 8 and 9 unchanged  
       BEQ   CP7            ; branch if successful 
       BRA   CP8
CP7:     ADD   R7,R7,R6       ; increment score
// compare two different positive numbers in two different registers
CP8:   CMP   R12,R14        ; compare and hopefully the values are unequal
       BNE   CP9            ; branch if successful      
       BRA   CP10
CP9:     ADD   R7,R7,R6       ; increment score
// compare a register to itself
CP10:  CMP   R12,R12        ; compare reg with itself - hopefully are equal
       BEQ   CP11           ; branch if successful      
       BRA   CP12
CP11:    ADD   R7,R7,R6       ; increment score
CP12:    LDI   R4,#6          ; number of tests
         LDI   R0,#0x4000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CP14           ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - COMPARE - reg-immed 
//
// compare a register with an identical positive immediate value
// compare a register with an identical negative immediate value
// compare a register with a different positive immediate value
//
//   success flag - REG 2 - 00002000   
//------------------------------------------------------------------------
CP14:    SUB   R7,R7,R7 
// compare a register with an identical positive immediate value
       CMP   R12,#2         ; hopefully compare with an immediate 2
       BEQ   CP15           ; branch if successful 
       BRA   CP16
CP15:    ADD   R7,R7,R6       ; increment score
// compare a register witn an identical negative immediate value
CP16:  LDI   R8,#-1         ; load reg 8 - with minus 1
       NOP                 
       NOP               
       CMP   R8,#-1         ; hopefully compare with an immediate minus 1
       BEQ   CP17           ; branch if successful 
       BRA   CP18
CP17:    ADD   R7,R7,R6       ; increment score
// compare a register with a different positive immediate value
CP18:  CMP   R12,#3         ; compare with 3
       BNE   CP19           ; branch if successful      
       BRA   CP20
CP19:    ADD   R7,R7,R6       ; increment score
CP20:    LDI   R4,#3          ; number of tests
         LDI   R0,#0x2000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   AD0            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - ADD - reg-reg
//
// add positive numbers
// add a positive and a negative number
// add negative numbers
// add using the same reg for both source operands
// add using the same reg for all operands
// 
//   success flag - REG 2 - 00001000   
//------------------------------------------------------------------------
AD0:     SUB   R7,R7,R7 
// add positive numbers
       LDI   R9,#2          ; load reg 9 with 2
       NOP                
       NOP                  
       ADD   R10,R12,R9     ; hopefully add positive numbers 
       NOP                 
       NOP                
       CMP   R10,#4         ; compare result with 4
       BEQ   AD1            ; branch if successful 
       BRA   AD2
AD1:     ADD   R7,R7,R6       ; increment score
// add a positive and a negative number
AD2:   LDI   R9,#-2         ; load reg 9 with minus 2
       NOP                
       NOP                 
       ADD   R10,R12,R9     ; hopefully add pos and neg number giving zero 
       NOP                 
       NOP                
       CMP   R10,#0         ; compare result with 0
       BEQ   AD3            ; branch if successful 
       BRA   AD4
AD3:     ADD   R7,R7,R6       ; increment score
// add negative numbers
AD4:   LDI   R8,#-2         ; load reg 8 with minus 2 
       NOP                
       NOP                  
       ADD   R10,R8,R9      ; hopefully add negative numbers 
       NOP                 
       NOP                
       CMP   R10,#-4        ; compare result with minus 4
       BEQ   AD5            ; branch if successful 
       BRA   AD6
AD5:     ADD   R7,R7,R6       ; increment score
// add using the same reg for both source operands
AD6:   ADD   R10,R12,R12    ; add with both source operands the same reg
       NOP
       NOP
       CMP   R10,#4         ; compare result with 4
       BEQ   AD7
       BRA   AD8
AD7:     ADD   R7,R7,R6       ; increment score
// add using the same reg for all operands
AD8:   LDI   R8,#2          ; load reg 8 with 2
       NOP
       NOP
       ADD   R8,R8,R8
       NOP
       NOP
       CMP   R8,#4          ; compare result with 4
       BEQ   AD9
       BRA   AD10  
AD9:     ADD   R7,R7,R6       ; increment score
AD10:    LDI   R4,#5          ; number of tests
         LDI   R0,#0x1000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   AD11           ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - ADD - reg-immed
//   At this point it seems logical to assert that ALU operations with
//   immediate data values have been tested, so this is not necessary.
//   Logically that seems valid.  But Murphy again says to ignore this
//   at your peril.  Clearly it is not absolutely required that one 
//   successful use of an immediate value implies all will work.      
//
// add a positive immediate value
// add a negative immediate value
//
//   success flag - REG 2 - 00000800   
//------------------------------------------------------------------------
AD11:    SUB   R7,R7,R7 
// add a positive immediate value
       ADD   R10,R12,#2     ; hopefully add a positive immediate value  
       NOP                 
       NOP                
       CMP   R10,#4         ; compare result with 4
       BEQ   AD12           ; branch if successful 
       BRA   AD13
AD12:    ADD   R7,R7,R6      ; increment score
// add a negative immediate value
AD13:  ADD   R10,R13,#-2    ; hopefully add a negative immediate value 
       NOP                 
       NOP                
       CMP   R10,#1         ; compare result with 1
       BEQ   AD14           ; branch if successful 
       BRA   AD15
AD14:    ADD   R7,R7,R6       ; increment score
AD15:    LDI   R4,#2          ; number of tests
         LDI   R0,#0x0800     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   SU0            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - SUBTRACT - reg-reg
//
// subtract positive numbers
// subtract a positive and a negative number
// subtract negative numbers
// subtract using the same reg for both source operands
// subtract using the same reg for all operands
//
//   success flag - REG 2 - 00000400   
//------------------------------------------------------------------------
SU0:     SUB   R7,R7,R7 
// subtract positive numbers
       SUB   R10,R14,R12    ; hopefully subtract positive numbers 
       NOP                 
       NOP                
       CMP   R10,#2         ; compare result with 2
       BEQ   SU1            ; branch if successful 
       BRA   SU2
SU1:     ADD   R7,R7,R6       ; increment score
// subtract a positive and a negative number
SU2:   LDI   R9,#-2         ; load reg 9 with minus 2
       NOP                
       NOP                 
       SUB   R10,R14,R9     ; hopefully subtract a pos and a neg number  
       NOP                 
       NOP                
       CMP   R10,#6         ; compare result with 6
       BEQ   SU3            ; branch if successful 
       BRA   SU4
SU3:     ADD   R7,R7,R6       ; increment score
// subtract negative numbers
SU4:   LDI   R8,#-4         ; load reg 8 with minus 4 
       NOP                
       NOP                  
       SUB   R10,R8,R9      ; hopefully subtract negative numbers 
       NOP                 
       NOP                
       CMP   R10,#-2        ; compare result with minus 2
       BEQ   SU5            ; branch if successful 
       BRA   SU6
SU5:     ADD   R7,R7,R6       ; increment score
// subtract using the same reg for both source operands
SU6:   SUB   R10,R14,R14
       BEQ   SU7
       BRA   SU8 
SU7:     ADD   R7,R7,R6       ; increment score
// subtract using the same reg for all operands
SU8:   SUB   R8,R8,R8
       BEQ   SU9
       BRA   SU10
SU9:     ADD   R7,R7,R6       ; increment score
SU10:    LDI   R4,#5          ; number of tests
         LDI   R0,#0x0400     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   SU11           ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - SUBTRACT - reg-immed
//
// subtract a positive immediate value
// subtract a negative immediate value
//
//   success flag - REG 2 - 00000200   
//------------------------------------------------------------------------
SU11:    SUB   R7,R7,R7 
// subtract a positive immediate value
       SUB   R10,R12,#1     ; hopefully subtract a pos immediate value  
       NOP                 
       NOP                
       CMP   R10,#1         ; compare result with 1
       BEQ   SU12           ; branch if successful 
       BRA   SU13
SU12:    ADD   R7,R7,R6       ; increment score
// subtract a negative immediate value
SU13:  SUB   R10,R12,#-2    ; hopefully subtract a neg immediate value 
       NOP                 
       NOP                
       CMP   R10,#4         ; compare result with 4
       BEQ   SU14           ; branch if successful 
       BRA   SU15
SU14:    ADD   R7,R7,R6       ; increment score
SU15:    LDI   R4,#2          ; number of tests
         LDI   R0,#0x0200     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   AN0            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// At this point we are making a simplifying assumption.  The preceeding 
// tests have tested the ability to fetch and store the proper operands 
// for the ALU operations.  No longer will we test things like using the
// same register for both source operands.  
//------------------------------------------------------------------------
// ALU - AND - reg-reg 
//
// and resulting in zero
// and resulting in non-zero
// verify and does not set the condition code 
// 
//   success flag - REG 2 - 00000100   
//------------------------------------------------------------------------
AN0:     SUB   R7,R7,R7 
// and resulting in zero
       AND   R10,R14,R12    ; hopefully and resulting in zero 
       NOP                 
       NOP   
       CMP   R10,#0         ; compare results with zero             
       BEQ   AN1            ; branch if successful 
       BRA   AN2
AN1:     ADD   R7,R7,R6       ; increment score
// and resulting in non-zero
AN2:   AND   R10,R14,R16    ; hopefully and resulting in non-zero 
       NOP                 
       NOP   
       CMP   R10,#4         ; compare results with 4             
       BEQ   AN3            ; branch if successful 
       BRA   AN4
AN3:     ADD   R7,R7,R6       ; increment score
// verify and does not set the condition code 
AN4:   CMP   R14,#6         ; set a not-equal contition
       AND   R10,R12,R14    ; and - result is zero, but cond code should not be set
       NOP
       NOP 
       BNE   AN5            ; branch if successful - cond code not set
       BRA   AN6
AN5:     ADD   R7,R7,R6       ; increment score
AN6:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x0100     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   AN7            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - AND - reg-immed 
//
// and immediate using a positive immediate value
// and immediate using a negative immediate value
// 
//   success flag - REG 2 - 00000080   
//------------------------------------------------------------------------
AN7:     SUB   R7,R7,R7 
// and immediate using a positive immediate value
       AND   R10,R14,#2     ; hopefully and resulting in zero 
       NOP                 
       NOP   
       CMP   R10,#0         ; compare results with zero             
       BEQ   AN8            ; branch if successful 
       BRA   AN9
AN8:     ADD   R7,R7,R6       ; increment score
// and immediate using a negative immediate value
AN9:   LDI   R9,#-1         ; load reg 9 with minus 1
       NOP                
       NOP                  
       AND   R10,R9,#-1     ; hopefully and resulting in zero 
       NOP                 
       NOP   
       CMP   R10,#-1        ; compare results with minus 1             
       BEQ   AN10           ; branch if successful 
       BRA   AN11
AN10:    ADD   R7,R7,R6       ; increment score
AN11:    LDI   R4,#2          ; number of tests
         LDI   R0,#0x0080     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   OR0            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - OR - reg-reg
//
// or with overlapping bits
// or with all bits exclusive to one operand
// verify or does not set the condition code 
// 
//   success flag - REG 2 - 00000040   
//------------------------------------------------------------------------
OR0:     SUB   R7,R7,R7 
// or with overlapping bits
       OR    R10,R14,R16    ; or with some bits common to both operands
       NOP
       NOP
       CMP   R10,R16        ; compare result with 6 
       BEQ   OR1            ; branch if successful
       BRA   OR2
OR1:     ADD   R7,R7,R6       ; increment score
// or with all bits exclusive to one operand
OR2:   OR    R10,R12,R14    ; or with bits exclusive
       NOP
       NOP
       CMP   R10,R16        ; compare result with 6
       BEQ   OR3            ; branch if successful
       BRA   OR4  
OR3:     ADD   R7,R7,R6       ; increment score
// verify or does not set the condition code
OR4:   CMP   R10,R10        ; compare - setting -equal- result 
       OR    R10,R12,R14    ; or giving a non-zero result
       NOP
       BEQ   OR5            ; -z- cond code should still be set
       BRA   OR6
OR5:     ADD   R7,R7,R6       ; increment score
OR6:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x0040     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   OR7            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - OR - reg-immed 
//
// or immediate using a positive immediate value
// or immediate using a negative immediate value
//
//   success flag - REG 2 - 00000020   
//------------------------------------------------------------------------
OR7:     SUB   R7,R7,R7
// or immediate using a positive immediate value
       OR    R10,R14,#2     ; or 4 and an immediate 2
       NOP
       NOP
       CMP   R10,R16        ; compare result with 6
       BEQ   OR8            ; branch if successful
       BRA   OR9    
OR8:     ADD   R7,R7,R6       ; increment score
// or immediate using a negative immediate value
OR9:   OR    R10,R12,#-4    ; or 2 and an immediate minus 4
       NOP
       NOP
       CMP   R10,#-2        ; compare results with minus 2
       BEQ   OR10           ; branch if successful
       BRA   OR11 
OR10:    ADD   R7,R7,R6       ; increment score
OR11:    LDI   R4,#2          ; number of tests
         LDI   R0,#0x0020     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   NT0            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU - NOT  
//
// not resulting in no bits left on
// not resulting in some bits left
// verify not does not change the condition code
//
//   success flag - REG 2 - 00000010   
//------------------------------------------------------------------------
NT0:     SUB   R7,R7,R7
// not resulting in no bits left on
       LDI   R8,#-1         ; load a minus 1 - FFFFFFFF
       NOP
       NOP
       NOT   R10,R8         ; not a minus 1 - should result in zero
       NOP
       NOP
       CMP   R10,#0         ; compare result with zero
       BEQ   NT1            ; branch if successful
       BRA   NT2     
NT1:     ADD   R7,R7,R6       ; increment score
// not resulting in some bits left
NT2:   NOT   R10,R12        ; not a plus 2 - should result in minus 3
       NOP
       NOP
       CMP   R10,#-3        ; compare result with minus 3
       BEQ   NT3            ; branch if successful
       BRA   NT4
NT3:     ADD   R7,R7,R6       ; increment score
// verify not does not change the condition code
NT4:   CMP   R10,R10        ; compare - setting -equal- result 
       NOT   R10,R12        ; not resulting in a non-zero result
       BEQ   NT5            ; branch if cond code still unchanged
       BRA   NT6
NT5:     ADD   R7,R7,R6       ; increment score
NT6:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x0010     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CX0            ; if not skip setting the indicator bit
         OR    R2,R2,R0       ; set test passed flag  
//------------------------------------------------------------------------
// BGE and BLT Condition code tests 
//
// test BGE and BLT with N^V 
// test BGE and BLT with ^N^V   
// test BGE and BLT with ^NV   
// test BGE and BLT with NV   
//  
//   success flag - REG 3 - 00004000   
//------------------------------------------------------------------------
CX0:     SUB   R7,R7,R7
// test BGE and BLT with N^V 
       LDI   R8,#0          ; clear reg 8
       LD    R9,WM1         ; load reg 9 with minus 1
       NOP
       NOP  
       ADD   R9,R9,R8       ; add zero - but this will set cond code N and ^V  
       BGE   CX2            ; should -not- branch if successful
       BLT   CX1            ; branch if successful
       BRA   CX2 
CX1:     ADD   R7,R7,R6       ; increment score
// test BGE and BLT with ^N^V   
CX2:   ADD   R9,R8,R8       ; add giving zero - set cond code ^N and ^V
       BLT   CX4            ; should -not- branch if successful
       BGE   CX3            ; branch if successful
       BRA   CX4
CX3:     ADD   R7,R7,R6       ; increment score
// test BGE and BLT with ^NV
CX4:   LD    R8,WMM         ; load max negative number
       NOP
       NOP
       ADD   R9,R8,R8       ; add two max neg numbers - giving zero - set cond code ^N and V
       BGE   CX6            ; should -not- branch if successful
       BLT   CX5            ; branch if successful
       BRA   CX6           
CX5:     ADD   R7,R7,R6       ; increment score
// test BGE and BLT with NV   
CX6:   LD    R8,WPM         ; load max positive number
       NOP
       NOP
       ADD   R9,R8,R8       ; add giving neg result - set cond code N and V
       BLT   CX8            ; should -not- branch if successful
       BGE   CX7            ; branch if successful
       BRA   CX8
CX7:     ADD   R7,R7,R6       ; increment score
CX8:     LDI   R4,#4          ; number of tests
         LDI   R0,#0x4000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   CX10           ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
//------------------------------------------------------------------------
// BGT and BLE Condition code tests 
//
//   (test BGT and BLE with ZN^V -but- Z and N are mutually exclusive) 
// test BGT and BLE with Z^N^V   
// test BGT and BLE with Z^NV   
//   (test BGT and BLE with ZNV  -but- Z and N are mutually exclusive)   
// test BGT and BLE with ^ZN^V 
// test BGT and BLE with ^Z^N^V   
// test BGT and BLE with ^Z^NV    
// test BGT and BLE with ^ZNV   
//  
//   success flag - REG 3 - 00002000   
//------------------------------------------------------------------------
CX10:    SUB   R7,R7,R7
// test BGT and BLE with Z^N^V   
       LDI   R8,#0          ; clear reg 8
       NOP
       NOP
       ADD   R9,R8,R8       ; add giving zero - set cond code Z, ^N and ^V
       BGT   CX12           ; should -not- branch if successful
       BLE   CX11           ; branch if successful
       BRA   CX12
CX11:    ADD   R7,R7,R6       ; increment score
// test BGT and BLE with Z^NV   
CX12:  LD    R8,WMM         ; load max negative number
       NOP
       NOP
       ADD   R9,R8,R8       ; add two max neg numbers - giving zero - set cond code Z, ^N and V
       BGT   CX14           ; should -not- branch if successful
       BLE   CX13           ; branch if successful
       BRA   CX14           
CX13:    ADD   R7,R7,R6       ; increment score
// test BGT and BLE with ^ZN^V 
CX14:  LDI   R8,#0          ; clear reg 8
       LD    R9,WM1         ; load reg 9 with minus 1
       NOP
       NOP  
       ADD   R9,R9,R8       ; add zero - but this will set cond code ^Z, N and ^V  
       BGT   CX16           ; should -not- branch if successful
       BLE   CX15           ; branch if successful
       BRA   CX16 
CX15:    ADD   R7,R7,R6       ; increment score
// test BGT and BLE with ^Z^N^V   
CX16:  LDI   R8,#1          ; load reg 8 with 1
       NOP
       NOP  
       ADD   R9,R8,R8       ; add giving 2 - set cond code ^Z, ^N and ^V
       BLE   CX18           ; should -not- branch if successful
       BGT   CX17           ; branch if successful
       BRA   CX18
CX17:    ADD   R7,R7,R6       ; increment score
// test BGT and BLE with ^Z^NV    
CX18:  LDI   R8,#-2         ; load reg 8 with minus 2
       LD    R9,WMM         ; load reg 9 with max neg number 
       NOP
       NOP  
       ADD   R9,R8,R8       ; add giving 2 - set cond code ^Z, ^N and V
       BGT   CX20           ; should -not- branch if successful
       BLE   CX19           ; branch if successful
       BRA   CX20 
CX19:    ADD   R7,R7,R6       ; increment score
// test BGT and BLE with ^ZNV   
CX20:  LDI   R8,#2          ; load reg 8 with 2
       LD    R9,WPM         ; load reg 9 with max pos number 
       NOP
       NOP  
       ADD   R9,R8,R8       ; add giving 2 - set cond code ^Z, N and V
       BLE   CX22           ; should -not- branch if successful
       BGT   CX21           ; branch if successful
       BRA   CX22
CX21:    ADD   R7,R7,R6       ; increment score
CX22:    LDI   R4,#6          ; number of tests
         LDI   R0,#0x2000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   PT0            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
//------------------------------------------------------------------------
// ALU pass-thru tests
//   Some operations pass data thru the ALU, and may even use the ALU
//   for some operation, yet the condition code is -not- supposed to
//   be altered by these operations. 
//
// load immediate - verify cond code unchanged
// load - verify cond code unchanged
// do logical op - verify cond code unchanged
//  
//   success flag - REG 3 - 00001000   
//------------------------------------------------------------------------
PT0:     SUB   R7,R7,R7
// load immediate - verify cond code unchanged
       SUB   R8,R8,R8       ; set reg 8 to zero - and set -Z- cond code
       NOP
       NOP
       LDI   R8,#1          ; load reg 8 - should leave cond code unchanged
       NOP
       NOP
       BEQ   PT1            ; branch if successful
       BRA   PT2
PT1:     ADD   R7,R7,R6       ; increment score
// load - verify cond code unchanged
PT2:   SUB   R8,R8,#2       ; set reg 8 to minus 1 - and set -N- cond code
       NOP
       NOP
       LD    R8,WPM         ; load max pos number - should leave cc unchanged
       NOP
       NOP
       BMI   PT3            ; branch if successful
       BRA   PT4 
PT3:     ADD   R7,R7,R6       ; increment score
// do logical op - verify cond code unchanged
PT4:   SUB   R8,R8,R8       ; set reg 8 to zero - and set -Z- cond code
       LDI   R9,#1          ; load reg 9 with 1
       NOP
       NOP
       OR    R8,R8,R9       ; or - set reg 8 to 1 - leave cond code unchanged
       BEQ   PT5            ; branch if successful
       BRA   PT6 
PT5:     ADD   R7,R7,R6       ; increment score
PT6:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x1000     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   LX0            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Load Indexed
//   The last of these tests is an attempt to verify the use of the 17-bit
//   immediate address.  If the offset value is something like
//   0 1xxx xxxx xxxx xxxx then using this as a 16-bit value would result
//   in a negative value.  However, if this is treated as a 17-bit value
//   then it is a positive offset. 
//   WARNING - if this offset is treated as a 16-bit number - which means
//   it is going to be -negative- then we will address memory at some
//   negative address.  It might be difficult to predice what might 
//   happen if this is attempted.    
//
// load using an offset of zero
// load using a positive offset
// load using a negative offset
//  
//   success flag - REG 3 - 00000800  
//------------------------------------------------------------------------
LX0:     SUB   R7,R7,R7
// load using an offset of zero
       LDI   R8,#0x0604     ; load address of a pos 2 in memory
       NOP
       NOP
       LDX   R9,R8          ; load 2 from address 0604
       NOP
       NOP
       CMP   R9,#2          ; check for the expected value of 2
       BEQ   LX1            ; branch if successful
       BRA   LX2
LX1:     ADD   R7,R7,R6       ; increment score
// load using a positive offset
LX2:   LDX   R9,R8,#4       ; load with a positive offset value
       NOP
       NOP
       CMP   R9,#4          ; check for the expected value of 4
       BEQ   LX3            ; branch if successful
       BRA   LX4
LX3:     ADD   R7,R7,R6       ; increment score
// load using a negative offset
LX4:   LDX   R9,R8,#-4      ; load with a negative offset value
       NOP
       NOP
       CMP   R9,#1          ; check for the expected value of 1
       BEQ   LX5            ; branch if successful
       BRA   LX6
LX5:     ADD   R7,R7,R6       ; increment score
LX6:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x0800     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   SX0            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
         ADD   R20,R20,R6     ; increment special indicator
//------------------------------------------------------------------------
// Store Indexed
//
// store using an offset of zero
// store using a positive offset
// store using a negative offset
//  
//   success flag - REG 3 - 00000400  
//------------------------------------------------------------------------
SX0:     SUB   R7,R7,R7
// store using an offset of zero
       LDI   R8,#0x0644     ; load address of a word in memory
       LDI   R9,#2          ; load a 2 into reg 9
       NOP
       NOP
       STX   R8,R9          ; store 2 in address 0644
       LD    R10,WX2
       NOP
       NOP
       CMP   R10,#2         ; check for the expected value of 2
       BEQ   SX1            ; branch if successful
       BRA   SX2
SX1:     ADD   R7,R7,R6       ; increment score
// store using a positive offset
SX2:   STX   R8,#4,R9       ; store 2 in address 0644 plus 4
       LD    R10,WX3
       NOP
       NOP
       CMP   R10,#2         ; check for the expected value of 2
       BEQ   SX3            ; branch if successful
       BRA   SX4
SX3:     ADD   R7,R7,R6       ; increment score
// store using a negative offset
SX4:   STX   R8,#-4,R9      ; store 2 in address 0644 minus 4
       LD    R10,WX1
       NOP
       NOP
       CMP   R10,#2         ; check for the expected value of 2
       BEQ   SX5            ; branch if successful
       BRA   SX6
SX5:     ADD   R7,R7,R6       ; increment score
SX6:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x0400     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   BC0            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Branch - next instruction
//   it is not easy to prove this works.  We can assert that it looks
//   very much like this worked ok.  If the branch to other positive
//   offsets is working ok, then we can probably deduce that we have
//   a pretty decent test for branch to next.  (We risk some data 
//   hazards, but since the code should not be reached anyway....)   
//
// branch to the very next instruction 
//
//   success flag - REG 3 - 00000200   
//------------------------------------------------------------------------
BC0:     SUB   R7,R7,R7
// branch to the very next instruction 
       LDI   R10,#0         ; clear a counter
       LDI   R11,#0    
       BRA   BC1            ; branch to a branch
       ADD   R10,R10,#10    ; increment counter - should not get here
       ADD   R10,R10,#20    ; increment counter - should not get here
       ADD   R10,R10,#40    ; increment counter - should not get here
BC1:   ADD   R10,R10,#1     ; increment counter to 1 - should branch to here
       BRA   BC2            ; branch to the very next instruction
BC2:   ADD   R11,R11,#2     ; increment counter to 2 - should branch to here
       BRA   BC3            ; branch onward 
       ADD   R10,R10,#10    ; increment counter - should not get here
       ADD   R10,R10,#20    ; increment counter - should not get here     
       ADD   R10,R10,#40    ; increment counter - should not get here
BC3:   CMP   R10,#1         ; check that we got to instruction BC1
       BNE   BC4            ; branch if there was a problem
       CMP   R11,#2         ; check that we got to instruction BC2
       BNE   BC4            ; branch if there was a problem    
         ADD   R7,R7,R6       ; increment score
BC4:     LDI   R4,#1          ; number of tests
         LDI   R0,#0x0200     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   BC10           ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Branch - negative offset  
//
// branch with a negative offset
//
//   success flag - REG 3 - 00000100   
//------------------------------------------------------------------------
BC10:    SUB   R7,R7,R7
// branch with a negative offset
       LDI   R9,#2          ; initialize loop indicator 
       LDI   R10,#0         ; clear an indicator register
       LDI   R11,#0         ; clear an indicator register
       BRA   BC12           ; branch ahead - skip some instructions
       ADD   R10,R10,R12    ; add 2 to indicator - should not get here
BC11:  ADD   R11,R11,R12    ; add 2 to indicator
       BRA   BC14           ; go check results
BC12:  SUB   R9,R9,#1       ; count times we got here (should be just one)
       BEQ   BC14           ; break out if we detect a loop here         
       BRA   BC11           ; branch with negative offset
BC14:  CMP   R9,#1          ; check for one time thru the code
       BNE   BC15           ; branch if a problem
       CMP   R10,#0         ; check that we did not go back too far
       BNE   BC15           ; branch if a problem
       CMP   R11,#2         ; check that we branched back far enough
       BNE   BC15           ; branch if a problem
         ADD   R7,R7,R6       ; increment score
BC15:    LDI   R4,#1          ; number of tests
         LDI   R0,#0x0100     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   JP0            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag         
//------------------------------------------------------------------------
// Jump Indirect  
//
// jump with a zero offset
// jump with a positive offset
// jump with a negative offset
//
//   success flag - REG 3 - 00000080   
//------------------------------------------------------------------------
JP0:     SUB   R7,R7,R7 
// jump with a zero offset
       LDI   R10,#0         ; clear an indicator register
       LDI   R9,#0x0700     ; load target instruction address - 0x0700
       JMP   R9             ; jump to target - 0x0700
       ADD   R10,R10,#16    ; we should never get here
JP1:   NOP
       NOP
       CMP   R10,#1         ; check that we reached our target 
       BEQ   JP2            ; branch if successful
       BRA   JP3
JP2:     ADD   R7,R7,R6       ; increment score
// jump with a positive offset
JP3:   LDI   R10,#0         ; clear an indicator register
       LDI   R9,#0x0710     ; load target area address - 0710
       JMP   R9,#0x0010     ; jump to target instruction - 0x0720
       ADD   R10,R10,#16    ; we should never get here
JP4:   NOP
       NOP
       CMP   R10,#2         ; check that we reached our target 
       BEQ   JP5            ; branch if successful
       BRA   JP6
JP5:     ADD   R7,R7,R6       ; increment score
// jump with a negative offset
JP6:   LDI   R10,#0         ; clear an indicator register
       LDI   R9,#0x0740     ; load target area addr plus some extra - 0x0740   
       JMP   R9,#-16        ; jump to target instruction - 0x0730
       ADD   R10,R10,#16    ; we should never get here
JP7:   NOP
       NOP
       CMP   R10,#4         ; check that we reached our target 
       BEQ   JP8            ; branch if successful
       BRA   JP9
JP8:     ADD   R7,R7,R6       ; increment score
JP9:     LDI   R4,#3          ; number of tests
         LDI   R0,#0x0080     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   JL0            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
         ADD   R20,R20,R6     ; increment special indicator
//------------------------------------------------------------------------
// Jump And Link
//
// verify jump does not alter reg 0 as a -link- register
// verify that the link register is set properly
//  
//   success flag - REG 3 - 00000040   
//------------------------------------------------------------------------
JL0:     SUB   R7,R7,R7 
// verify jump does not alter reg 0 as a -link- register
//   ok, you can argue this is a plain -jump- test, but it also involves -link-
//   and it did not seem helpful to fail the jump tests if this failed 
       LDI   R0,#0          ; clear an indicator register
       LDI   R10,#0         ; clear an indicator register
       LDI   R9,#0x0780     ; load target instruction address - 0x0780
       JMP   R9             ; jump to target - 0x0780
       ADD   R10,R10,#16    ; we should never get here
JL1:   NOP
       NOP
       CMP   R0,#0          ; verify reg 0 is unchanged 
       BEQ   JL2            ; branch if successful
       BRA   JL3
JL2:     ADD   R7,R7,R6       ; increment score
// verify that the link register is set properly
JL3:   NOP
       BRA   JL4            ; go to known address
JL5:   NOP                  ; this is the return point
       CMP   R8,#0x07A4     ; was the link address set correctly
       BEQ   JL6
       BRA   JL7
JL6:     ADD   R7,R7,R6       ; increment score
JL7:     LDI   R4,#2          ; number of tests
         LDI   R0,#0x0040     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   DH0            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
//------------------------------------------------------------------------
// Now we need to address -data- -hazards-.  This is certainly a test
// done because we explicitly know one internal design feature of the
// hardware under test.   Until now the testing has carefully avoided
// altering a register and then using it again -too-soon-.  Now we 
// will intentionally do exactly that.  This testing will be broken up
// into several pieces just so that the test reporting is not reduced
// to a case of all-or-nothing.
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// hazard recently altered registers 
//
// use a reg as source operand 2 the second instruction after the reg is set
// use a reg as source operand 1 the second instruction after the reg is set
//     
//   success flag - REG 3 - 00000020   
//------------------------------------------------------------------------
DH0:     SUB   R7,R7,R7 
// use a reg as source operand 2 the second instruction after the reg is set
       LDI   R8,#1          ; load reg with a known value
       NOP
       NOP
       LDI   R9,#10         ; load reg with a known value
       NOP
       ADD   R10,R8,R9      ; use value loaded 2 instructions ago
       NOP
       NOP
       CMP   R10,#11        ; was result of add as expected
       BEQ   DH1            ; branch if successful
       BRA   DH2  
DH1:     ADD   R7,R7,R6       ; increment score
// use a reg as source operand 1 the second instruction after the reg is set
DH2:   LDI   R9,#20         ; load reg with a known value
       NOP
       ADD   R10,R9,R8      ; use value loaded 2 instructions ago
       NOP
       NOP
       CMP   R10,#21        ; was result of add as expected
       BEQ   DH3            ; branch if successful
       BRA   DH4  
DH3:     ADD   R7,R7,R6       ; increment score
DH4:     LDI   R4,#2          ; number of tests
         LDI   R0,#0x0020     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   DH5            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag
//------------------------------------------------------------------------
// hazard recently altered registers 
//
// use a reg as source operand 2 immediately after the reg is set
// use a reg as source operand 1 immediately after the reg is set
//     
//   success flag - REG 3 - 00000010   
//------------------------------------------------------------------------
DH5:     SUB   R7,R7,R7 
// use a reg as source operand 2 immediately after the reg is set
       LDI   R9,#10         ; load reg with a known value
       ADD   R10,R8,R9      ; use value loaded 2 instructions ago
       NOP
       NOP
       CMP   R10,#11        ; was result of add as expected
       BEQ   DH6            ; branch if successful
       BRA   DH7  
DH6:     ADD   R7,R7,R6       ; increment score
// use a reg as source operand 1 immediately after the reg is set
DH7:   LDI   R9,#20         ; load reg with a known value
       ADD   R10,R9,R8      ; use value loaded 2 instructions ago
       NOP
       NOP
       CMP   R10,#21        ; was result of add as expected
       BEQ   DH8            ; branch if successful
       BRA   DH9  
DH8:     ADD   R7,R7,R6       ; increment score
DH9:     LDI   R4,#2          ; number of tests
         LDI   R0,#0x0010     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   DH10           ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag
//------------------------------------------------------------------------
// hazard recently altered registers 
//
// both operands of an instruction use the same recently altered source reg
// alter a reg with consecutive instructions and then use the reg as a
//   source operand
// alter a reg with consecutive instructions and then use the reg as 
//   both source operands
// two operands of an instruction use different, but both recently altered
//   regs as source operands  
//     
//   success flag - REG 3 - 00000008   
//------------------------------------------------------------------------
DH10:    SUB   R7,R7,R7 
// both operands of an instruction use the same recently altered source reg
       LDI   R9,#15         ; load reg with a known value
       ADD   R10,R9,R9      ; use value loaded 2 instructions ago
       NOP
       NOP
       CMP   R10,#30        ; was result of add as expected
       BEQ   DH11            ; branch if successful
       BRA   DH12  
DH11:    ADD   R7,R7,R6       ; increment score
// alter a reg with consecutive instructions and then use the reg as a
//   source operand
DH12:  LDI   R9,#25         ; load reg with a known value
       LDI   R9,#35         ; and load the reg again
       ADD   R10,R9,R8      ; use the correct value just loaded 
       NOP
       NOP
       CMP   R10,#36        ; was result of add as expected
       BEQ   DH13           ; branch if successful
       BRA   DH14  
DH13:    ADD   R7,R7,R6       ; increment score
// alter a reg with consecutive instructions and then use the reg as 
//   both source operands
DH14:  LDI   R9,#7          ; load reg with a known value
       LDI   R9,#15         ; and load the reg again
       ADD   R10,R9,R9      ; use the correct value just loaded 
       NOP
       NOP
       CMP   R10,#30        ; was result of add as expected
       BEQ   DH15           ; branch if successful
       BRA   DH16  
DH15:    ADD   R7,R7,R6       ; increment score
// two operands of an instruction use different, but both recently altered
//   regs as source operands  
DH16:  LDI   R8,#21         ; load reg with a known value
       LDI   R9,#31         ; and load the reg again
       ADD   R10,R8,R9      ; use the correct value just loaded 
       NOP
       NOP
       CMP   R10,#52        ; was result of add as expected
       BEQ   DH17           ; branch if successful
       BRA   DH18  
DH17:    ADD   R7,R7,R6       ; increment score
DH18:    LDI   R4,#4          ; number of tests
         LDI   R0,#0x0008     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   DH20           ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag
//------------------------------------------------------------------------
// hazard recently loaded registers 
//
// use a reg as a source operand the second instruction after the reg is loaded
// use a reg as a source operand immediately after the reg is loaded
// load a reg with consecutive instructions and then use the reg as a
//   source operand
// both operands of an instruction use the same recently loaded source reg
// two operands of an instruction use different, but both recently loaded
//   regs as source operands  
//     
//   success flag - REG 3 - 00000004   
//------------------------------------------------------------------------
DH20:    SUB   R7,R7,R7 
// use a reg as a source operand the second instruction after the reg is set
       LDI   R8,#1          ; load reg with a known value
       NOP
       NOP
       LD    R9,WP2         ; load reg with a known value
       NOP
       ADD   R10,R8,R9      ; use value loaded 2 instructions ago
       NOP
       NOP
       CMP   R10,#3         ; was result of add as expected
       BEQ   DH21           ; branch if successful
       BRA   DH22  
DH21:    ADD   R7,R7,R6       ; increment score
// use a reg as a source operand immediately after the reg is loaded
DH22:  LD    R9,WP4         ; load reg with a known value
       ADD   R10,R9,R8      ; use value just loaded 
       NOP
       NOP
       CMP   R10,#5         ; was result of add as expected
       BEQ   DH23           ; branch if successful
       BRA   DH24  
DH23:    ADD   R7,R7,R6       ; increment score
// load a reg with consecutive instructions and then use the reg as a
//   source operand
DH24:  LD    R9,WP1         ; load reg with a known value
       LD    R9,WP2         ; load reg with a known value
       ADD   R10,R8,R9      ; use value just loaded 
       NOP
       NOP
       CMP   R10,#3         ; was result of add as expected
       BEQ   DH25           ; branch if successful
       BRA   DH26  
DH25:    ADD   R7,R7,R6       ; increment score
// both operands of an instruction use the same recently loaded source reg
DH26:  LD    R9,WP1         ; load reg with a known value
       LD    R9,WP4         ; load reg with a known value
       ADD   R10,R9,R9      ; use value just loaded 
       NOP
       NOP
       CMP   R10,#8         ; was result of add as expected
       BEQ   DH27           ; branch if successful
       BRA   DH28  
DH27:    ADD   R7,R7,R6       ; increment score
// two operands of an instruction use different, but both recently loaded
//   regs as source operands  
DH28:  LD    R9,WP1         ; load reg with a known value
       LD    R8,WP2         ; load reg with a known value
       ADD   R10,R8,R9      ; use value just loaded 
       NOP
       NOP
       CMP   R10,#3         ; was result of add as expected
       BEQ   DH29           ; branch if successful
       BRA   DH30  
DH29:    ADD   R7,R7,R6       ; increment score
DH30:    LDI   R4,#5          ; number of tests
         LDI   R0,#0x0004     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   XXX            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag
//------------------------------------------------------------------------
// really risky tests
//   If things do not go really well, these tests have the potential to 
//   reference negative memory addresses, or even try to branch to 
//   negative memory addresses.  Therefore, these tests will -not- be 
//   attempted unless.....
//    - all previous load/store - indexed tests were successful
//    - all previous jump/jump-link tests were successful
//    - -most- all other tests were successful  
//
// ldx using a pos offset which has a non-zero next-most-significant bit
// jump when the register contains a negative value
//     
//   success flag - REG 3 - 00000002   
//------------------------------------------------------------------------
RR0:     SUB   R7,R7,R7
         CMP   R20,#2         ; were all -indexed- and -jump tests successful
         BNE   XXX            ; if not - skip these tests
         LDI   R8,#100
         NOP
         NOP
         SUB   R8,R5,R8       ; number of successful tests more than 100  
         BMI   XXX            ; branch if less than 100 tests successful         
// ldx using a pos offset which has a non-zero next-most-significant bit
//   this could be dangerous if the immediate value is interpreted as a 16-bit
//   value.  If this happens we have a -negative- offset and we will end 
//   up with a negative address
       LDI   R8,#0x0604     ; load address of a pos 2 in memory
       LD    R10,W17P       ; load 17-bit positive value (00FFFC)
       NOP
       NOP
       SUB   R8,R8,R10      ; subtract from address 0604 - giving neg addr
       NOP
       NOP
       LDX   R9,R8,#0x00FFFC ; load from 0604 ((0604-FFFC)+FFFC) 
       NOP
       NOP
       CMP   R9,#2          ; check for the expected value of 2
       BEQ   RR1            ; branch if successful
       BRA   XXX
RR1:     ADD   R7,R7,R6       ; increment score
// jump when the register contains a negative value
//   this could be dangerous if say the register is being used and the 
//   offset value ignored.  So..... we will only attempt this test if
//   all the previous jump tests were successful
       LDI   R10,#0         ; clear an indicator register
       LDI   R9,#-16        ; load jump target address of -16 or 0xFF..F0
       JMP   R9,#0x0760     ; jump to target instruction -0x0010 + 0x0760 (0x0750) 
       ADD   R10,R10,#16    ; we should never get here
JP10:  NOP
       NOP
       CMP   R10,#8         ; check that we reached our target 
       BEQ   RR3            ; branch if successful
       BRA   RR4
RR3:     ADD   R7,R7,R6       ; increment score
RR4:     LDI   R4,#2          ; number of tests
         LDI   R0,#0x0002     ; load successful completion bit flag
         ADD   R5,R5,R7       ; increment total score
         CMP   R7,R4          ; did all tests pass
         BNE   XXX            ; if not skip setting the indicator bit
         OR    R3,R3,R0       ; set test passed flag  
//------------------------------------------------------------------------
// It is hard to believe but it seems that we are done
//------------------------------------------------------------------------
XXX:   HLT                  ; wow - finished
//------------------------------------------------------------------------
//
// Check regs 1, 2, and 3 for status about which groups of tests passed and failed
// Check reg 5 for a count of the number of tests passed
//  
//------------------------------------------------------------------------

