﻿# Stack-Based-Equation-Validator
 
## Overview
This project is a C program for validating and converting mathematical equations using a stack-based approach. The program reads equations from a file, checks their validity, converts infix equations to prefix format, evaluates valid equations, and writes invalid equations to an output file.


## Features
* Read Equations from File: Read mathematical equations from an input file.
* Validate Equations: Check the validity of equations for correct bracket pairing and operator placement.
* Convert Infix to Prefix: Convert valid infix equations to prefix notation.
* Evaluate Prefix Expressions: Evaluate the converted prefix expressions.
* Print Invalid Equations: Print invalid equations to the console.
* Write Invalid Equations to File: Save invalid equations to an output file.

## Files

### main.c: Contains the main logic of the program.
### Input_file.txt: Contains the input equations.
### Output_file.txt: The output file where invalid equations are saved.


## Code Structure 
## Data Structures 
`CharStack`: A structure representing a stack of characters, used for processing equations.
## Functions

### Stack Operations:

* `CharStack* Make_Stack()`: Creates a new stack.
* `void push(CharStack* cs, char c)`: Pushes a character onto the stack.
* `char Top(CharStack* cs)`: Returns the top character of the stack.
* `void Pop(CharStack* cs)`: Pops the top character from the stack.
* `CharStack* ReverseStack(CharStack* cs)`: Reverses the stack.
* `CharStack* Clone(CharStack* cs)`: Clones the stack.

### File Operations:

* `int getNumberOfEquationsInFile()`: Gets the number of equations in the input file.
* `void ReadFromFile(CharStack* cs[])`: Reads equations from the input file and stores them in stacks.
* `void WriteOnFile(FILE* ofile, CharStack* cs[])`: Writes invalid equations to the output file.

### Validation and Conversion:

* `int ValidityOfEquations(CharStack* cs)`: Checks bracket pairing in the equation.
* `int ValidityOfEquations1(CharStack* cs)`: Checks operator placement in the equation.
* `int Validity(CharStack* cs)`: Combines both validity checks.
* `CharStack* InfixToPrefix(CharStack* cs)`: Converts infix notation to prefix notation.
* `int EvaluteValidEqu(CharStack* cs)`: Evaluates a prefix expression.
### Utility Functions:

* `int ConvertToInt(char c)`: Converts a character to an integer.
* `int Priority(char c)`: Returns the priority of an operator.
* `int MathOP(int x, int y, char c)`: Performs a mathematical operation.
* `int BelongTo0_9(char c)`: Checks if a character is a digit.
* `int BelongToOperation(char c)`: Checks if a character is an operator.
* `int BelongToOpenBrackets(char c)`: Checks if a character is an opening bracket.
* `int BelongToCloseBrackets(char c)`: Checks if a character is a closing bracket.
* `int Find(CharStack* cs, char c)`: Finds and removes a character from the stack.


### Usage Example
* Place your equations in Input_file.txt.
* Run the compiled program.
* Choose the desired operations from the menu.
* View the results on the console or in Output_file.txt.
