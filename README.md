# HCS1
A simple VM created in C, modelled after the HCS12 microcontroller assembly code. I created this following @felixangell's "Virtual machine in C" guide, as an introduction for myself into lower level programming, and to enhance my C skills. 

The VM holds a stack of size 256, that is managed using a stack pointer, defined within the registers space of the program. There are a total of 6 memory registers, labelled A-F, as well as a program counter register, counting which instruction the VM is at.

#Instruction Set
The HCS1, as I like to call it, supports 11 instructions:

  #HLT:
      Ends the program.
  
  #PSH:
      Pushes a number onto the stack.
      
  #POP:
      Pops a number from the stack (does not return it though).
      
  #ADD:
      Adds the last two stack elements, stores the sum in register B, and pushes the sum to the stack.
  
  #STR:
      Stores a register with a value; first input is the register, second input is the value.
  
  #ADDR:
      Adds the values at two registers together, and stores that sum in the first register specified.
  
  #ITOB:
      Converts an integer to binary.
  
  #MOV:
      Moves the value of one register to the other specified register (e.g MOV A B moves the value of A to B). 
  
  #EXG:
      Exchanges the values between two registers.
  
  #BAND:
      Bitwise AND operation of two registers; This is similar to to the BCLR command in the HCS12 microcontroller.
  
  #BOR:
      Bitwise OR operation of two registers; This is similar to to the BSET command in the HCS12 microcontroller.
      
  These instructions are not called in the .hcs file by their syntax names, but their number in the enum defined in main.c For example, HLT is not actually called to stop the program, but 0 is called.
