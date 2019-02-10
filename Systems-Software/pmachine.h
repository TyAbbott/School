//Includes necessary header files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

//Declare maximum values for inputs/code.
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 250
#define MAX_LEX_LEVELS 3


//Declaring a struct that will hold the separate fields for a line of code
//utilizing format: OP R L M.
//OP - Operation Code, R - Register, L - Lexicographical Level
//M - Operation Data (depends on specific Operation)
struct instruction{
    int OP, R, L, M;};

//Declare + Initialize the Program Counter, Instruction Register,
//Base Pointer, and Stack Pointer to their initial values.
int pc, sp = 0;
int bp = 1;

//Initialize the stack.
int stack[MAX_STACK_HEIGHT] = {0};

//Declare CPU Registers
int r[8] = {0};

//Declare Halt flag. Initialize to zero (do not halt).
int halt = 0;

//Declare input and output files
FILE *input;
FILE *output;

void print(int cnt);
void fetch();
int execute();
int base(int L, int base);
void printStack( int flag);

//Initialize our array of code. This will hold all the code we execute for the program.
struct instruction code[MAX_CODE_LENGTH];

//Declare the instruction register.
struct instruction ir;

    //Main function
    int pmachine(int flag){


        //Open input and output files
        input =   fopen("pmachineinput.txt", "r");
        output =   fopen("pmachineoutput.txt", "w");

        //If the file isn't there or could not open properly, end the program.
        if(input == NULL){
            printf("File could not open. Program halted.\n");
            return 0;
        }

        //Keep track of number of instructions the input file.
        int cnt = 0;

        //Read in the lines from the input file.
        while(!feof(input))
        {   
			fscanf(input, "%d", &code[cnt].OP);
            fscanf(input, "%d", &code[cnt].R);
            fscanf(input, "%d", &code[cnt].L);
            fscanf(input, "%d", &code[cnt].M);
            cnt++;
        }

    //Call our initial printing function
    print(cnt);

    cnt = 0;

    //Print the column headers for the stack tracing
    if(flag)
	{
		printf("\n\nExecution of Program:\n");
		printf("\nInitial Values\t\t\t\tpc\tbp\tsp\n");
    }

    fprintf(output, "\n\nExecution of Program:\n");
    fprintf(output, "\nInitial Values\t\t\t\tpc\tbp\tsp\n");
	
	int stop = 0;
	int times = 0;
    //Fetch - Execute Cycle. Runs until the halt flag is set to stop the loop.
    while(halt == 0){

        //Start the fetch part of the fetch-execute cycle.
        fetch();

        //Start the execution process of the cycle
        stop = execute();
		if(stop == 1)
			halt = 1;

        if(flag){
        printf("%d\t%d\t%d\t", ir.R, ir.L, ir.M);
        printf("%d\t%d\t%d\t", pc, bp, sp);
        }
        fprintf(output, "%d\t%d\t%d\t", ir.R, ir.L, ir.M);
        fprintf(output, "%d\t%d\t%d\t", pc, bp, sp);
        printStack(flag);

        if(( (pc==0) && (bp==0) && (sp==0) ))
            halt = 1;

		times++;
		if(times > 50)
			halt = 1;

    }

    //Close files.
    fclose(input);
    fclose(output);

    //End main function.
    return 1;
    }

    //Pre: Print takes in the number of instructions in the code array.
    //Post: The OP codes (operation code) of all instructions will be
    //  interpreted and the input code as a whole will be printed out to the
    //  output file designated for the entire program.
    void print(int cnt){

        int i;

        fprintf(output, "Interpreted Assembly Language\n");
        fprintf(output, "\nLine\tOP\tR\tL\tM");

        for(i=0; i<cnt; i++){

            int op = code[i].OP;

            //Interpret the operation.
            switch(op)
			{
            case 1: fprintf(output, "\n%d\t", i); fprintf(output, "lit\t"); break;
            case 2: fprintf(output, "\n%d\t", i); fprintf(output, "rtn\t"); break;
            case 3: fprintf(output, "\n%d\t", i); fprintf(output, "lod\t"); break;
            case 4: fprintf(output, "\n%d\t", i); fprintf(output, "sto\t"); break;
            case 5: fprintf(output, "\n%d\t", i); fprintf(output, "cal\t"); break;
            case 6: fprintf(output, "\n%d\t", i); fprintf(output, "inc\t"); break;
            case 7: fprintf(output, "\n%d\t", i); fprintf(output, "jmp\t"); break;
            case 8: fprintf(output, "\n%d\t", i); fprintf(output, "jpc\t"); break;
            case 9: fprintf(output, "\n%d\t", i); fprintf(output, "sio\t"); break;
            case 10:fprintf(output, "\n%d\t", i); fprintf(output, "sio\t"); break;
            case 11:fprintf(output, "\n%d\t", i); fprintf(output, "sio\t"); break;
            case 12:fprintf(output, "\n%d\t", i); fprintf(output, "neg\t"); break;
            case 13:fprintf(output, "\n%d\t", i); fprintf(output, "add\t"); break;
            case 14:fprintf(output, "\n%d\t", i); fprintf(output, "sub\t"); break;
            case 15:fprintf(output, "\n%d\t", i); fprintf(output, "mul\t"); break;
            case 16:fprintf(output, "\n%d\t", i); fprintf(output, "div\t"); break;
            case 17:fprintf(output, "\n%d\t", i); fprintf(output, "odd\t"); break;
            case 18:fprintf(output, "\n%d\t", i); fprintf(output, "mod\t"); break;
            case 19:fprintf(output, "\n%d\t", i); fprintf(output, "eql\t"); break;
            case 20:fprintf(output, "\n%d\t", i); fprintf(output, "neq\t"); break;
            case 21:fprintf(output, "\n%d\t", i); fprintf(output, "lss\t"); break;
            case 22:fprintf(output, "\n%d\t", i); fprintf(output, "leq\t"); break;
            case 23:fprintf(output, "\n%d\t", i); fprintf(output, "gtr\t"); break;
            case 24:fprintf(output, "\n%d\t", i); fprintf(output, "geq\t"); break;
            default: return;
            }

            //Print the three other fields: R, L, M.
            fprintf(output, "%d\t", code[i].R);
            fprintf(output, "%d\t", code[i].L);
            fprintf(output, "%d\t", code[i].M);
        }
        return;
    }

    //Fetch retrieves the instruction to be executed, then
    void fetch(){

        //Fetch current instruction
        ir = code[pc];

        //Print the program counter before it's incremented.
        fprintf(output, "%d\t", pc);

        //Increment the Program Counter before we start execution.
        //Program Counter points to the NEXT instruction.
        pc++;

        //Return to main function.
        return;

    }

    int execute(){

        switch(ir.OP){
        //LIT
        case 1:
            fprintf(output, "lit\t");
            r[ir.R] = ir.M;
            break;

        //RTN
        case 2:
            fprintf(output, "rtn\t");
            sp = bp -1;
            bp = stack[sp+3];
            pc = stack[sp+4];
            break;

        //LOD
        case 3:
            fprintf(output, "lod\t");
            r[ir.R] = stack[base(ir.L, bp) + ir.M];
            break;

        //STO
        case 4:
            fprintf(output, "sto\t");
            stack[ base(ir.L, bp) + ir.M] = r[ir.R];
            break;

        //CAL
        case 5:
            fprintf(output, "cal\t");
            stack[sp+1] = 0;
            stack[sp+2] = base(ir.L, bp);
            stack[sp+3] = bp;
            stack[sp+4] = pc;
            bp = sp+1;
            pc = ir.M;
            break;

        //INC
        case 6:
            fprintf(output, "inc\t");
            sp = sp + ir.M;
            break;

        //JMP
        case 7:
            fprintf(output, "jmp\t");
            pc = ir.M;
            break;

        //JPC
        case 8:
            fprintf(output, "jpc\t");
            if(r[ir.R]==0)
                pc = ir.M;
            break;

        //SIO - write register to screen
        case 9:
            fprintf(output, "sio\t");
            printf("\nR[%d] = %d\n", ir.R, r[ir.R]);
            break;

        //SIO - read in value from screen to register.
        case 10:
            fprintf(output, "sio\t");
            printf("\nPlease type in the number you wish to store in the register. Press enter when finished.\n");
            scanf("%d", &r[ir.R]);
            break;

        //SIO - set halt flag to 1.
        case 11:
            fprintf(output, "sio\t");
            halt = 1;
            break;

        //NEG
        case 12:
            fprintf(output, "neg\t");
            r[ir.R] = 0 - r[ir.L];
            break;

        //ADD
        case 13:
            fprintf(output, "add\t");
            r[ir.R] = r[ir.L] + r[ir.M];
            break;

        //SUB
        case 14:
            fprintf(output, "sub\t");
            r[ir.R] = r[ir.L] - r[ir.M];
            break;

        //MUL
        case 15:
            fprintf(output, "mul\t");
            r[ir.R] = r[ir.L] * r[ir.M];
            break;

        //DIV
        case 16:
            fprintf(output, "div\t");
            r[ir.R] = ((r[ir.L])/(r[ir.M]));
            break;

        //ODD
        case 17:
            fprintf(output, "odd\t");
            r[ir.R] = r[ir.R]%2;
            break;

        //MOD
        case 18:
            fprintf(output, "mod\t");
            r[ir.R] = (r[ir.L])%(r[ir.M]);
            break;

        //EQL
        case 19:
            fprintf(output, "eql\t");
            if(r[ir.L]==r[ir.M])
                r[ir.R]=1;
            else
                r[ir.R]=0;
            break;

        //NEQ
        case 20:
            fprintf(output, "neq\t");
            if(r[ir.L]!=r[ir.M])
                r[ir.R]=1;
            else
                r[ir.R]=0;
            break;

        //LSS
        case 21:
            fprintf(output, "lss\t");
            if(r[ir.L]<r[ir.M])
                r[ir.R]=1;
            else
                r[ir.R]=0;
            break;

        //LEQ
        case 22:
            fprintf(output, "leq\t");
            if(r[ir.L]<=r[ir.M])
                r[ir.R]=1;
            else
                r[ir.R]=0;
            break;

        //GTR
        case 23:
            fprintf(output, "gtr\t");
            if(r[ir.L]>r[ir.M])
                r[ir.R]=1;
            else
                r[ir.R]=0;
            break;

        //GEQ
        case 24:
            fprintf(output, "geq\t");
            if(r[ir.L]>=r[ir.M])
                r[ir.R]=1;
            else
                r[ir.R]=0;
            break;


        default:
            fprintf(output, "err\t");
            return 1;

        }
    return 0;

    }

    int base(int L, int base){

        int b1; //Find base L levels down

        b1 = base;

        while(L>0){
            b1 = stack[b1 + 1];
            L--;
        }

        return b1;
}


    void printStack(int flag){
        if(bp==0){
            return;
        }
		if(sp>20)
			sp = 20;
        else{
            int i;
            for(i=1; i<=sp; i++){
                if(flag)
                    printf("%d\t", stack[i]);
                fprintf(output, "%d\t", stack[i]);
            }
            if(flag)
              printf("\n");
            fprintf(output, "\n");
            return;

        }
    }