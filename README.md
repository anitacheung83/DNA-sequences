# DNA-sequences

## Introduction
In this assignment you will use some of your newfound C skills including functions, loops and arrays on problems involving DNA sequences. DNA sequences can be represented as simple character arrays that contain only the characters A, C, G or T, so programs that work with DNA are often written in C. You won't need to know any biology to complete this assignment.

In this assignment you will be presented with some problems in your (pretend) job as a software developer at the fictional AGTCorp, the world's leading company for synthesizing DNA molecules. AGTCorp is developing their latest DNA synthesis machine, called SEQbot, and you've joined the project to help the team prepare for the launch.

Note that for this assignment you are working with arrays of characters, not strings. That means that these arrays will not necessarily have a null-termination character at the end, and you cannot use string operations on them. This is also why all of the operations require the length of the array to be specified. The only string operations appear in main which you will not be modifying.

It is important that your programs produce only the output specified in the handout, and exactly in the format specified.  You must not have any additional output.

## Task 1 - Melting DNA
DNA is a double-stranded molecule where each character on one strand binds to a complementary character on the other strand - A binds to T, C binds to G and vice-versa. These bonds can be broken to split a double-stranded molecule into two single strands by increasing temperature to melt the DNA. The melting temperature for a particular sequence of DNA is given by the formula:

'''
T = (n_A + n_T) * 2 + (n_C + n_G) * 4
'''
where n_A, n_C, n_G and n_T are the number of A,C,G and T characters in the DNA sequence. Your task is to write a function to calculate the melting temperature of a given DNA sequence. Your function must have the following signature:
'''
int calculate_melting_temperature(char *sequence, int sequence_length)
'''
## Task 2 - Building DNA
SEQbot is controlled by a simple text file that it reads from disk. The file contains a sequence of instructions that describes how SEQbot should create the DNA molecule. The commands that SEQbot accepts are START, END, SET_TEMPERATURE <t> and WRITE <char> <n>:

START tells SEQbot to begin creating a new DNA molecule
END tells SEQbot to finish the current molecule
SET_TEMPERATURE <t> tells SEQbot to set the temperature to the value <t>.
WRITE <char> <n> tells SEQbot to add n copies of <char> into the molecule. For example WRITE A 4 will append 4 copies of A to the current molecule.
A valid set of instructions to SEQbot has a single START command, then a series of WRITE commands, then a SET_TEMPERATURE command to melt the DNA molecule, followed by an END command. Important: SEQbot will jam if two consecutive WRITE commands contain the same character. The commands therefore must use run-length encoding to print a sequence of instructions that contain distinct characters for each consecutive WRITE (see the example below).

Your job is to create a function that takes in a DNA sequence as a character array, and print out the sequence of instructions needed to make the molecule. The function must have the signature:

void print_instructions(char *sequence, int sequence_length)
For example, given the input (AAGTTTTCGG, 10) your function should print:

START
WRITE A 2
WRITE G 1
WRITE T 4
WRITE C 1
WRITE G 2
SET_TEMPERATURE 28
END
This is a valid sequence of instructions as each WRITE command has a different character than the preceding WRITE. If the first WRITE A 2 instruction was replaced by two WRITE A 1 instructions the instruction sequence would not be valid as it would jam SEQbot.

## Task 3 - Testing SEQbot
After implementing print_instructions you want to test whether SEQbot is functioning correctly. To do this, you will write a function to create all possible sequences of A, C, G, T for a given length, k. For example, given k=3, your program should generate the sequences AAA, AAC, AAG, ..., TTG, TTT. The function will print each sequence to standard output in the format <length> <sequence> 0 There is one space between each of these fields. A user can then redirect the output of generate_all_molecules to a file to be read as input to generate_molecules_from_file as in Task 4.

Your function should have the signature:

void generate_all_molecules(int k)
For example, the first three lines of output for seqbot genall 3 is:

3 AAA 0
3 AAC 0
3 AAG 0
Task 4: Reading from files
As your final task on this project, you need to write a function that reads the sequences to generate from a text file. The text file contains one line for each sequence SEQbot should create. The format of each line is as follows:

<length> <sequence> <mode>
<length> is the number of characters in <sequence>. <mode> is an integer that controls what sequence should be output. When mode is 0, <sequence> should be output. When mode is 1 the complement <sequence> should be output by replacing A with T, C with G, G with C and T with A. When <mode> is 2 <sequence> should be reversed before output. Finally, when <mode> is 3 <sequence> should be both complemented and reversed.

For example when given an input file with these lines:

4 ACCT 0
4 ACCT 1
4 ACCT 2
4 ACCT 3
The output should be:

START
WRITE A 1
WRITE C 2
WRITE T 1
SET_TEMPERATURE 12
END
START
WRITE T 1
WRITE G 2
WRITE A 1
SET_TEMPERATURE 12
END
START
WRITE T 1
WRITE C 2
WRITE A 1
SET_TEMPERATURE 12
END
START
WRITE A 1
WRITE G 2
WRITE T 1
SET_TEMPERATURE 12
END
This example input and output is provided in the repository as example/task4_input.txt and example/task4_output.txt.

Your function should check whether <sequence> is a valid DNA sequence (it only contains the characters A, C, G, T). If the sequence is not valid you should print the message INVALID SEQUENCE (changed to be consistent with starter code) instead of printing the instructions. Your function should have the following signature:

void generate_molecules_from_file(char* filename)
How to complete the assignment
You can get the starter code from MarkUs either by downloading it to your machine through the browser, or telling MarkUs to commit the files to your repo.

The starter code contains three files, seqbot_helpers.h, seqbot_helpers.c and seqbot_main.c. The only file you will modify is seqbot_helper.c where you will complete the functions as described above. We have provided the function signatures for you. seqbot_helpers.h contains these function signatures and should not be modified. seqbot_main.c contains a main function that can be used to test your program.

Use the following compile line to compile your program:
'''
gcc -Wall -g -o seqbot seqbot_main.c seqbot_helpers.c
'''
Or you can use the provided a Makefile to compile seqbot.

See the usage message in main to learn how to run the sebot for testing. You are welcome to write (and commit) other test programs if you want to test cases that may not be as easy to test with the provided program.

Submission instructions
Commit and push the files needed to compile seqbot. Your repository must not contain any files that end in .o or the executable seqbot.

Check to make sure that your program compiles without warnings or errors, by cloning a new working copy in a different directory and compiling and testing the program.

This assignment will be auto-marked, so it is important to follow the instructions precisely.
