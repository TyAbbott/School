/** Parser/Code Generator for PL/0 Programming Language written in c
	Ty Abbott
	Fall 2017
	Systems Software - COP 3402 - UCF


	For constants, you must store kind, name and value.
	For variables, you must store kind, name, L and M.
	For procedures, you must store kind, name, L and M.
	
	Input:  parsercodgeninput.txt
	Output: pmachineinput.txt


-------------------------------------------------------------------
	ERROR MESSAGES FOR THE PL/O PARSER
	1.	Use = instead of :=.
	2.	= must be followed by a number.
	3.	Identifier must be followed by :=.
	4.	const, var, procedure must be followed by identifier.
	5.	Semicolon or comma missing.
	6.	Incorrect symbol after procedure declaration.
	7.	Statement expected.
	8.	Incorrect symbol after statement part in block.
	9.	Period expected.
	10.	Semicolon between statements missing.
	11.	Undeclared identifier.
	12.	Assignment to constant or procedure is not allowed.
	13.	Assignment operator expected.
	14.	call must be followed by an identifier.
	15.	Call of a constant or variable is meaningless.
	16.	then	 expected.
	17.	Semicolon or } expected.
	18.	do expected.
	19.	Incorrect symbol following statement.
	20.	Relational operator expected.
	21.	Expression must not contain a procedure identifier.
	22.	Right parenthesis missing.
	23.	The preceding factor cannot begin with this symbol.
	24.	An expression cannot begin with this symbol.
	25.	This number is too large.
	26. End symbol expected after begin sequence.
--------------------------------------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOL_TABLE_SIZE 100
#define MAX_CODE_SIZE 200

// Struct for the symbol table
typedef struct  
    { 
		int kind; 		// const = 1, var = 2, proc = 3
		char name[10];	// name up to 11 chars
		int val; 		// number (ASCII value) 
		int level; 		// L level (always 0 for now)
		int addr; 		// M address/modifier
    } symbol; 

// making our symbol table
symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];


// 	Token struct
typedef struct
	{
		char type[3];    // Type of token as determined by token_type
		char value[12];  // value of the token (identifier or num value)
	} token;
	
typedef struct
	{
		int op; // opcode
		int r;  // register
		int l;  // lexicographical level
		int m;  // modifier/address
	} code_struct;

// making all of the pointers, data structures, and pointers

code_struct codearray[MAX_CODE_SIZE]; 	// code array
int cx = 0;								// code index
int reg_ptr;							// register pointer (8 total registers)
int sp;									// stack pointer
int level;								// max lexicographical level
int curr_lex_level;						// current lexicographical level
token current_token;					// current token being analyzed
int symbol_cnt;							// keeps track of symbols in symbol table
FILE *PCGinput;							// File pointer to token input
char buffer[3];							// Used to store converted value of itoa function



// Method declarations

int get_token(); 									// gets the next token
void add_to_symbol_table(int, char[], int, int);	// adds symbols into symbol table
void emit(int, int, int, int);						// generates PL/0 code
void error(int);									// prints out error message and stops operation

// Methods defined in the grammer

void program();
void block();
void statement();
void condition();
int rel_op();
void expression();
void term();
void factor();

void parsercodgen(int flag)
{
	int i;
	int x = 0;
	symbol_cnt = 0;
	reg_ptr = 0;
	cx = 0;
	sp = 1;
	level = curr_lex_level = 1;
	
	// open our input file
	PCGinput = fopen("parsercodgeninput.txt", "r");
	
	
	// initialize our code array
	for(i=0; i<MAX_CODE_SIZE; i++)
	{
		codearray[i].op = 0;
		codearray[i].r = 0;
		codearray[i].l = 0;
		codearray[i].m = 0;
	}
	
	program();
	
	printf("\nProgram compiled! It is syntactically correct!\n");
	
	FILE *fout = fopen("pmachineinput.txt", "w");
	
	while(!(codearray[x].op == 0 && codearray[x].r == 0 && codearray[x].l == 0 && codearray[x].m == 0))
	{
		if(flag)
			 printf("%d %d %d %d\n", codearray[x].op, codearray[x].r, codearray[x].l, codearray[x].m );
		
		fprintf(fout, "%d %d %d %d\n", codearray[x].op, codearray[x].r, codearray[x].l, codearray[x].m );
		x++;
	}
	
	fclose(PCGinput);
	fclose(fout);
	
	return;
}

// token will just be symbol[dx].  our program will just keep incrementing dx at every get
void program()
{
    get_token();
	block();
	
	// if no period after block, send error
	if(strcmp(current_token.type, "19") != 0)
		error(9);
	
	emit(11,0,0,3);
}

void block()
{
	char name[12];
	int value;
	int procedure_spot;
	sp = 3;
	int space = 4;
	int procx; 
	
	int jump_address = cx;
	
	
	// emit jump 
	emit(7,0,0,0);
	
	
	// Declaring constants
	if(strcmp(current_token.type, "28") == 0)
	{
		do
		{
			get_token();
			
			// Not an identifier symbol
			if(strcmp(current_token.type, "2") != 0)
				error(4);
			
			strcpy(name, current_token.value);
			get_token();
			
			// Not an equal symbol
			if(strcmp(current_token.type, "9") != 0)
				error(3);
			
			get_token();
			
			// Not a number symbol
			if(strcmp(current_token.type, "3") != 0)
				error(2);
			
			// takes the current value and adds it to symbol in the symbol table
			value = atoi(current_token.value);
			add_to_symbol_table(1,name,value,0);
			get_token();
			
			// Checks while comma symbol
		} while(strcmp(current_token.type, "17") == 0);
		
		// No semicolon after declaring, error
		if(strcmp(current_token.type, "18") != 0)
			error(5);
                      
		get_token();
	}
      

	// Declaring variables
	if(strcmp(current_token.type, "29") == 0)       
	{
		do
		{
			get_token();
			
			// Looking for ident symbol
			if(strcmp(current_token.type, "2") != 0)
				error(4);

			// adds variable to symbol table
			strcpy(name, current_token.value);
			add_to_symbol_table(2,name,0,sp);
			symbol_table[symbol_cnt - 1].level = level;
			
			space++;
			sp++;
			
			get_token();
			// checks while comma symbol
		}while(strcmp(current_token.type, "17") == 0);
		
		// checks for semicolon
		if(strcmp(current_token.type, "18") != 0) 
			error(5);
		
		get_token();
    }
	
	// procedure
	while(strcmp(current_token.type, "30") == 0)
	{
		get_token();
		
		// must be an identifier after procedure
		if(strcmp(current_token.type, "2") != 0)
			error(4);
		
		// copies current name into symbol table
		strcpy(name, current_token.value);
		add_to_symbol_table(3,name,0,0);
		
		// sets the level and address to the previous symbols
		procx = symbol_cnt - 1;
		symbol_table[procx].level = level;
		symbol_table[procx].addr = jump_address + 1;
		
		get_token();
		
		// Check for semicolon
		if(strcmp(current_token.type, "18") != 0) 
			error(17);
		
		get_token();
		level++;
		
		block();
		
		
		// Check for semicolon
		if(strcmp(current_token.type, "18") != 0) 
			error(17);
		
		get_token();
	}
	
	codearray[jump_address].m = cx;
	emit(6,0,0,space);
	
	// Got through without errors, go to statement
	statement();
	
	curr_lex_level--;
}	

void statement()
{
	int i;			  // index
	int declared = 0; // 0 means identifier is not declared, 1 means it is declared
	int ident_index;  // saves the index for indentifiers
	
	
	// checks for identifier
	if(strcmp(current_token.type, "2") == 0)
	{
		// check if it's in the symbol table
		for(i=symbol_cnt-1; i>=0; i--)
		{
			if(strcmp(current_token.value, symbol_table[i].name) == 0)
			{
				if(symbol_table[i].kind == 1)
					error(12);
				else if(symbol_table[i].kind == 2)
				{
					declared = 1;
					ident_index = i;
				}
			}
		}
		
		// undeclared identifier
		//if(!declared)
			//error(11);
		
		get_token();
		
		if(strcmp(current_token.type, "20") != 0)
			error(3);
		
		get_token();
		expression();
		
		emit(4, reg_ptr-1, curr_lex_level-symbol_table[ident_index].level, symbol_table[ident_index].addr - 1);
		reg_ptr--;
	}
	
	// call symbol
	else if(strcmp(current_token.type, "27") == 0)
	{
		int declared = 0;
		get_token();
		
		// identifier expected
		if(strcmp(current_token.type, "2") != 0)
			error(14);
		
		for(i=symbol_cnt - 1; i>=0; i--)
		{
			if(strcmp(current_token.value, symbol_table[i].name) == 0)
			{
				declared = 1;
				ident_index = i;
			}
		}
		
		if(!declared)
			error(11);
		
		if(symbol_table[ident_index].kind == 3)
			emit(5,0,level,symbol_table[ident_index].addr);
		
		else
			error(14);
		
		get_token();
	}
	
	// begin
	else if(strcmp(current_token.type, "21") == 0)
	{
		get_token();
		statement();
		
		while(strcmp(current_token.type,"18") == 0)
		{
			get_token();
			statement();
		}
		
		// checks for end symbol
		if(strcmp(current_token.type, "22") != 0)
			error(26);
		
		get_token();
	}
	
	// if condition
	else if(strcmp(current_token.type, "23") == 0)
	{
		get_token();
		condition();
		
		
		// then condition
		if(strcmp(current_token.type, "24") != 0)
			error(16);
		
		get_token();
		
		// starts code generation
		
		int ctemp = cx;
		emit(8,reg_ptr-1,0,0);
		statement();
		
		get_token();
		
		//else condition
		if(strcmp(current_token.type, "33") == 0)
		{
			int ctemp2 = cx;
			emit(7,0,0,0);
			
			codearray[ctemp].m = cx;
			get_token();
			
			statement();
			
			codearray[ctemp2].m = cx;
			reg_ptr--;
		}
		
		else
		{
			codearray[ctemp].m = cx;
			reg_ptr--;
		}
	}
	
	
	// while and do
	else if(strcmp(current_token.type,"25") == 0)
	{
		int cx1 = cx;
		
		get_token();
		condition();
		
		int cx2 = cx;
		
		emit(8,reg_ptr - 1,0,0);
		
		if(strcmp(current_token.type, "26") != 0)
			error(18);
		
		get_token();
		statement();
		
		emit(7,0,0,cx1);
		codearray[cx2].m = cx;
		reg_ptr--;
	}
}	

void condition()
{
	// odd symbol
	if(strcmp(current_token.type, "8") == 0)
	{
		get_token();
		expression();
		emit(17, reg_ptr-1, reg_ptr-1, 0);
	}
	
	// rel op
	else
	{
		expression();
		int op = rel_op();
		
		if(!op)
			error(20);
		
		get_token();
		expression();
		
		emit(op, reg_ptr-2, reg_ptr-2, reg_ptr-1);
		reg_ptr--;
	}
}

void expression()
{
	char add_op[3];
	
	// + or - symbol
	if(strcmp(current_token.type, "4") == 0 || strcmp(current_token.type, "5") == 0)
	{
		strcpy(add_op, current_token.type);
		get_token();
		term();
		
		if(strcmp(add_op, "5") == 0)
			emit(12, reg_ptr - 1, reg_ptr - 1, 0);
	}
	
	else
		term();
	
	// checking for + and -
	while(strcmp(current_token.type, "4") == 0 || strcmp(current_token.type, "5") == 0)
	{
		strcpy(add_op, current_token.type);
		get_token();
		term();
		
		// plus
		if(strcmp(add_op, "4") == 0)
		{
			emit(13, reg_ptr-2, reg_ptr-2, reg_ptr-1);
			reg_ptr--;
		}
		
		// minus
		else
		{
			emit(14, reg_ptr-2, reg_ptr-2, reg_ptr-1);
			reg_ptr--;
		}
	}
}

void term()
{
	char mulop[3];
	
	factor();
	// multiply or division (* or /)
	while(strcmp(current_token.type, "6") == 0 || strcmp(current_token.type, "7") == 0)
	{
		strcpy(mulop,current_token.type);
		get_token();
		factor();
		
		if(strcmp(mulop, "6") == 0)
		{
			emit(15, reg_ptr-2, reg_ptr-2, reg_ptr-1);
			reg_ptr--;
		}
		
		else
		{
			emit(16, reg_ptr-2, reg_ptr-2, reg_ptr-1);
			reg_ptr--;
		}
	}
}

void factor()
{
	int i;
	int declared = 0;
	int ident_index = 0;
	
	// identifier
	if(strcmp(current_token.type, "2") == 0)
	{
		// check symbol table
		for(i=symbol_cnt-1; i>=0; i--)
		{
			if(strcmp(current_token.value, symbol_table[i].name) == 0)
			{
				declared = 1;
				ident_index = i;
			}
		}
		
		// undeclared, throws error
		//if(!declared)
			//error(11);
		
		if(symbol_table[ident_index].kind == 2)
			emit(3, reg_ptr, curr_lex_level - symbol_table[ident_index].level, symbol_table[ident_index].addr - 1);
		
		else if(symbol_table[ident_index].kind == 1)
			emit(1,reg_ptr,0,symbol_table[ident_index].val);
		
		reg_ptr++;
		get_token();
	}
	
	// number symbol
	else if(strcmp(current_token.type, "3") == 0)
	{
		emit(1, reg_ptr, 0, atoi(current_token.value));
		reg_ptr++;
		
		get_token();
	}
	
	// left parenthesis
	else if(strcmp(current_token.type, "15") == 0)
	{
		get_token();
		expression();
	
		// right parenthesis
		if(strcmp(current_token.type, "16") != 0)
			error(22);
		
		get_token();
	}
	
	else
		error(23);
	
}

int get_token()
{
	if(fscanf(PCGinput, "%s", current_token.type) != EOF)
	{
		if(strcmp(current_token.type, "2") == 0 || strcmp(current_token.type, "3") == 0)
			fscanf(PCGinput, "%s", current_token.value);
		
		else
			current_token.value[0] = '\0';
		
		return 1;
	}
	
	else
	{
		// all out of tokens
		current_token.type[0] = '\0';
		current_token.value[0] = '\0';
		return 0;
	}
}


void error(int x)
{
	printf("\nError number %d, ",x);
	
  switch(x)
  {

  case 1:
    printf("Use = instead of :=\n");
    break;
  case 2:
    printf("= must be followed by a number\n");
    break;
  case 3:
    printf("Identifier must be followed by =\n");
    break;
  case 4:
    printf("Const, int, procedure must be followed by identifier\n");
    break;
  case 5:
    printf("Semicolon or comma missing\n");
    break;
  case 6:
    printf("Incorrect symbol after procedure declaration\n");
    break;
  case 7:
    printf("Statement expected\n");
    break;
  case 8:
    printf("Incorrect symbol after statement part in block\n");
    break;
  case 9:
    printf("Period expected\n");
    break;
  case 10:
    printf("Semicolon between statements missing\n");
    break;
  case 11:
    printf("Undeclared identifier\n");
    break;
  case 12:
    printf("Assignment to constant or procedure is not allowed\n");
    break;
  case 13:
    printf("Assignment operator expected\n");
    break;
  case 14:
    printf("Call must be followed by an identifier\n");
    break;
  case 15:
    printf("Call of a constant or variable is meaningless\n");
    break;
  case 16:
    printf("Then expected\n");
    break;
  case 17:
    printf("Semicolon or } expected\n");
    break;
  case 18:
    printf("Do expected\n");
    break;
  case 19:
    printf("Incorrect symbol following statement\n");
    break;
  case 20:
    printf("Relational operator expected\n");
    break;
  case 21:
    printf("Expression must not contain a procedure identifier\n");
    break;
  case 22:
    printf("Right parenthesis missing\n");
    break;
  case 23:
    printf("The preceding factor cannot begin with this symbol\n");
    break;
  case 24:
    printf("Expression cannot begin with this symbol\n");
    break;
  case 25:
    printf("Number is too large\n");
    break;
  case 26:
	printf("End symbol expected after begin sequence.");
	break;
  }
	
	fclose(PCGinput);
	exit(0);
}

void emit(int op, int r, int l, int m)
{
	codearray[cx].op = op;
	codearray[cx].r = r;
	codearray[cx].l = l;
	codearray[cx].m = m;
	cx++;
}

void add_to_symbol_table(int k, char name[], int val, int addr)
{
	symbol_table[symbol_cnt].kind = k;
	strcpy(symbol_table[symbol_cnt].name, name);
	symbol_table[symbol_cnt].val = val;
	symbol_table[symbol_cnt].addr = addr;
	
	symbol_cnt++;
}

int rel_op()
{
	// equal
  if(strcmp(current_token.type,"9") == 0)
    return 19;
    
	//not equal
  else if(strcmp(current_token.type,"10") == 0 )
    return 20;
    
	//less than
  else if(strcmp( current_token.type,"11") == 0 )
    return 21;
    
	//less than or equal
  else if(strcmp( current_token.type,"12") == 0 )
    return 22;
    
	//greater than
  else if(strcmp( current_token.type,"13") == 0)
    return 23;
    
	//greater than or equal
  else if(strcmp( current_token.type,"14") == 0)
    return 24;

  else
    return 0;
}

