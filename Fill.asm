// fill.asm
// Continuously checks keyboard input.
// If any key is pressed, fill the screen black.
// If no key is pressed, clear the screen white.

(START)
    @KBD
    D=M
    @BLACK
    D;JNE      
    @WHITE
    0;JMP      


(BLACK)
    @SCREEN
    D=A
    @addr
    M=D        

(BLACK_LOOP)
    @KBD
    D=M
    @WHITE
    D;JEQ      
    @addr
    A=M
    M=-1       
    @addr
    M=M+1
    D=M
    @KBD
    D=D-A     
    @BLACK_LOOP
    D;JLT      

    @START
    0;JMP      



(WHITE)
    @SCREEN
    D=A
    @addr
    M=D        

(WHITE_LOOP)
    @KBD
    D=M
    @BLACK
    D;JNE    

    @addr
    A=M
    M=0       
    @addr
    M=M+1
    D=M
    @KBD
    D=D-A
    @WHITE_LOOP
    D;JLT

    @START
    0;JMP
