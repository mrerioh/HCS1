# HCS1
A simple VM created in C, modelled after the HCS12 microcontroller assembly code. I created this following @felixangell's "Virtual machine in C" guide, as an introduction for myself into lower level programming, and to enhance my C skills. 

The VM holds a stack of size 256, that is managed using a stack pointer, defined within the registers space of the program. There are a total of 6 memory registers, labelled A-F, as well as a program counter register, counting which instruction the VM is at.

### Instruction Set
The HCS1, as I like to call it, supports 11 instructions:  
  <br />

  #### HLT
  Inherent mode. Ends the program.   
  <br />
  #### PSH
  Immediate mode. Pushes a number onto the stack.  
  <br />    
  #### POP
  Inherent mode. Pops a number from the stack (does not return it though).  
  <br />
  #### ADD
  Inherent mode. Adds the last two stack elements through POP, stores the sum in register B, and pushes the sum to the stack.  
  <br />
  #### STR
  Immediate mode. Stores a register with a value; first input is the register, second input is the value.  
  <br />
  #### ADDR
  Immediate mode. Adds the values at two registers together, and stores that sum in the first register specified.  
  <br />
  #### ITOB
  Direct mode. Converts an integer from the specified register to binary.  
  <br />
  #### MOV
  Immediate-direct mode. Moves the value of one register to the other specified register (e.g MOV A B moves the value of A to B).   
  <br />
  #### EXG
  Inherent mode, per the HCS12 instruction set. Exchanges the values between two registers.  
  <br />
  #### BAND
  Bitwise AND operation of two registers; This is similar to to the BCLR command in the HCS12 microcontroller.  
  <br />
  #### BOR
  Bitwise OR operation of two registers; This is similar to to the BSET command in the HCS12 microcontroller.  
      
  The opcodes in the .hcs file are not referred to by their syntax names, but their number in the enum defined in main.c for the instruction set. HLT has the opcode 0, and so on.
