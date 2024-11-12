// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(RESTART)
    @SCREEN
    D=A //allows manipulation of screen varaible
    @0
    M=D	//sets start value pf screen at ROM[0]

(KBDCHECK)//checks if key is being pressed
    @KBD
    D=M //memory of keyboard
    @BLACK
    D;JGT //if keyboard value is greater than zero jump to fill
    @WHITE
    D;JEQ //i fkeyboard valus is 0 then go to white
    @KBDCHECK
    0;JMP

(BLACK)
    @i
    M=-1 //twos complimetn will fill with a bunch of ones
    @LOOP
    0;JMP

(WHITE)
    @i
    M=0	//make screen white
    @LOOP
    0;JMP

(LOOP) //pixel incrementer
    @i 
    D=M //is pixel black or white
    @0
    A=M	//next screen pixel
    M=D	//fill pixel
    @0
    D=M+1 //goto next pixel
    @KBD
    D=A-D //keyboard-screen=A
    @0
    M=M+1 //go to next pixel
    A=M
    @CHANGE
    D;JGT //end loop if A=0 becauee whole screen is black
    @RESTART
    0;JMP



