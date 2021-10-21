#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 256
int stack[STACK_SIZE];

typedef enum {
    HLT, //0
    PSH, //1
    POP, //2
    ADD, //3 
    STR, //4
    ADDR, //5
    ITOB, //6
    MOV, //7
    EXG, //8
    BAND, //9
    BOR //10
} InstructionSet;


typedef enum {
    STOP, A,B,C,D,E,F,PC,SP,
    NO_REGISTERS
} Registers;
static int registers[NO_REGISTERS];

int *instructions;
int ic = 0;
static bool running = true;
#define SP (registers[SP])
#define PC (registers[PC])
#define FETCH (instructions[PC])

unsigned int bint(unsigned int k){
    if(k==0) return 0;
    if(k==1) return 1;
    return (k % 2) + 10 * bint(k / 2);
}

void p_reg(){
    printf("Register values: \n");
    for(int i=0; i< NO_REGISTERS; i++){
        printf("%02d ", registers[i]);
        if((i+1)%8==0) { 
            printf("\n");
        }
    }
}

int eval(int instr){
    switch(instr){
        case HLT:
            running = false;
            printf("HLT\n");
            break;
        case PSH:
            SP = SP+1;
            PC = PC+1;
            stack[SP]= instructions[PC];
            break;
        case POP:
            printf("popped %d\n", stack[SP]);
            SP = SP-1;
            break;
        case ADD: //store last two stack elements to register B
            registers[A]= stack[SP];
            SP = SP-1;
            registers[B] = stack[SP];
            registers[B] = registers[B] + registers[A];
            stack[SP] = registers[B];
            printf("%d + %d is %d\n", registers[A], registers[B]-registers[A], registers[B]);
            break;
        case STR:
            PC = PC+1;
            int regID = instructions[PC];
            PC = PC+1;
            registers[regID] = instructions[PC];
            printf("Stored Register %d with %d\n", regID, registers[regID]);
            break;
        case ADDR:
            PC = PC+1;
            int reg1 = instructions[PC];
            PC = PC+1;
            int reg2 = instructions[PC];
            registers[reg1] = registers[reg1] + registers[reg2];
            printf("Added value at Register %d and value at register %d for a value of %d, stored in Register %d\n", reg1, reg2, registers[reg1], reg1);
            break;
        case ITOB: {
            PC = PC+1;
            int regval = registers[instructions[PC]];
            int bi = bint(regval);
            printf("Binary value of register is %04d\n", bi);
            break;
        }
        case MOV:
            registers[instructions[PC+2]]=registers[instructions[PC+1]];
            PC=PC+2;
            break;
        case EXG:
        {
            int temp = registers[instructions[PC+2]];
            registers[instructions[PC+2]]=registers[instructions[PC+1]];
            registers[instructions[PC+1]] = temp;
            PC = PC+2;
            break;
        }
        case BAND:
        {
            int res = registers[instructions[PC+1]]&registers[instructions[PC+2]];
            registers[instructions[PC+1]] = res;
            printf("Bitwise AND of register %d and %d is %04d\n", instructions[PC+1],instructions[PC+2], bint(res));
            PC=PC+2;
            break;
        }
        case BOR:
        {
            int res = registers[instructions[PC+1]]|registers[instructions[PC+2]];
            registers[instructions[PC+1]] = res;
            printf("Bitwise OR of register %d and %d is %04d\n", instructions[PC+1],instructions[PC+2], bint(res));
            PC=PC+2;
            break;
        }
    }
}


int main(int argc, char** argv){
    if(argc<=1){
        printf("missing file");
        return -1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("can't read file!");
        return -1;
    }

    instructions = malloc(sizeof(*instructions)*4);
    int num;
    int i=0;
    while(fscanf(file, "%d", &num) > 0){
        instructions[i] = num;
        i = i+1;
    }
    ic = i;
    fclose(file);
    SP = -1;


    while(running && PC<ic){
        eval(FETCH);
        PC = PC+1;
    }

    free(instructions);
    p_reg();
    return 0;
}