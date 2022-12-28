#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "seqbot_helpers.h"
#define LINE_BUFFER_SIZE 256

/* Return the melting temperature of sequence, or -1 if the sequence is invalid.
 * The melting temperature formula is given in the handout.
 * An invalid sequence is a sequence of length 0, or a sequence that contains
 * characters other than 'A', 'C', 'G', 'T'.
 */
int calculate_melting_temperature(char *sequence, int sequence_length)
{

     if (sequence_length == 0){
        return -1;
    }
    int n_A = 0;
    int n_T = 0;
    int n_G = 0;
    int n_C = 0;
    int i;
    for (i = 0; i < sequence_length; i++){
        char temp = sequence[i];
        if (temp == 'A'){
            n_A += 1;
        }
        else if (temp == 'T'){
            n_T += 1;
        }
        else if (temp == 'C'){
            n_C += 1;
        }
        else if (temp == 'G'){
            n_G += 1;
        }
       else{
            return -1;
       }
    }
    return (n_A + n_T)*2 + (n_C + n_G)*4;
    return -1;
}

/* Prints the instructions to make a molecule from sequence.
 * If an invalid character is found in sequence print
 * "INVALID SEQUENCE" and return immediately
 */
void print_instructions(char *sequence, int sequence_length)
{
    // TODO: complete this function
    printf("%s", "START\n");
    if (sequence_length > 0){
        int n_A = 0;
        int n_C = 0;
        int n_G = 0;
        int n_T = 0;
        char temp = sequence[0];
        int count = 1;
        int i;
        for (i = 1; i < sequence_length; i++){
            if (temp == sequence[i]){
                count += 1;
            }
            else if (temp != sequence[i]){
                printf("WRITE %c %d\n", temp, count);
                 if (temp == 'A'){
       		     n_A += count;
 		  }
 	         else if (temp == 'T'){
          	     n_T += count;
       		  }
       		 else if (temp == 'C'){
          	     n_C += count;
       		  }
   		 else if (temp == 'G'){
           	     n_G += count;
        	  }
                 else{
                     printf("INVALID SEQUENCE");
                     return;
                  }
                 count = 1;
                 temp = sequence[i];
            }
        }
        printf("WRITE %c %d\n", temp, count);
        printf("SET_TEMPERATURE %d\n", calculate_melting_temperature(sequence, sequence_length));
        printf("END\n");
    }
}


/* Print to standard output all of the sequences of length k.
 * The format of the output is "<length> <sequence> 0" to 
 * correspond to the input format required by generate_molecules_from_file()
 * 
 * Reminder: you are not allowed to use string functions in these files.
 */
void permutation(char *arr, char *option, int k, int level){
    if (level == k){
        printf("%d ", k);
        for (int i = 0; i < k; i ++){
                printf("%c", arr[i]);
        }
        printf(" 0\n");
        return;
    }
    for (int i = 0; i < 4; i++){
        arr[level] = option[i];
        permutation(arr, option, k, level + 1);
    }
}

void generate_all_molecules(int k)
{
    // TODO: complete this function
    char arr[k];
    char option[4] = {'A', 'C', 'G', 'T'};
    permutation(arr, option, k, 0);
}


/* Print the instructions for each of the sequences found in filename according
 * to the mode provided.
 * filename contains one sequence per line, and the format of each line is
 * "<length> <sequence> <mode>" where 
 *     - <length> is the number of characters in the sequence 
 *     - <sequence> is the array of DNA characters
 *     - <mode> is either 0, 1, 2, or 3 indicating how the <sequence> should 
 *              be modified before printing the instrutions. The modes have the 
 *              following meanings:
 *         - 0  - print instructions for sequence (unmodified)
 *         - 1  - print instructions for the the complement of sequence
 *         - 2  - print instructions for the reverse of sequence
 *         - 3  - print instructions for sequence where it is complemented 
 *                and reversed.
 * 
 * Error checking: If any of the following error conditions occur, the function
 * immediately prints "INVALID SEQUENCE" to standard output and exits the 
 * program with a exit code of 1.
 *  - length does not match the number of characters in sequence
 *  - length is not a positive number
 *  - sequence contains at least one invalid character
 *  - mode is not a number between 0 and 3 inclusive
 * 
 * You do not need to verify that length or mode are actually integer numbers,
 * only that they are in the correct range. It is recommended that you use a 
 * fscanf to read the numbers and fgetc to read the sequence characters.
 */
void generate_molecules_from_file(char* filename)
{
    FILE* file = fopen(filename, "r");

    char seq[LINE_BUFFER_SIZE];
    int seq_length = -1;
    int mode = -1;

    int r = fscanf(file, "%d %s %d", &seq_length, seq, &mode);
    int i = 0;

    int start, end, temp;

    while (r != EOF)
    {
        while (seq[i] != '\0') {
            if ((seq_length <= 0) || (seq[i] != 'A' && seq[i] != 'G' && seq[i] != 'T' && seq[i] != 'C')) {
                printf("INVALID SEQUENCE");
                return;
            }

            i++;
        }

        if (i != seq_length) {
            printf("INVALID SEQUENCE");
            return;
        }

        if (mode < 0 || mode>3) {

            return;
        }

        i = 0;
        switch (mode) {
        case 0:
            print_instructions(seq, seq_length);
            break;
        case 1:
            while (seq[i] != '\0') {

                switch (seq[i]) {
                case 'A':
                    seq[i] = 'T';
                    break;
                case 'G':
                    seq[i] = 'C';
                    break;
                case 'T':
                    seq[i] = 'A';
                    break;
                case 'C':
                    seq[i] = 'G';
                    break;
                }

                i++;
            }
            print_instructions(seq, seq_length);
            break;
        case 2:
            start = 0;
            end = seq_length-1;
            while (start < end)
            {
                temp = seq[start];
                seq[start] = seq[end];
                seq[end] = temp;
                start++;
                end--;
            }

            print_instructions(seq, seq_length);
            break;
        case 3:
            while (seq[i] != '\0') {

                switch (seq[i]) {
                case 'A':
                    seq[i] = 'T';
                    break;
                case 'G':
                    seq[i] = 'C';
                    break;
                case 'T':
                    seq[i] = 'A';
                    break;
                case 'C':
                    seq[i] = 'G';
                    break;
                }

                i++;
            }

            start = 0;
            end = seq_length - 1;
            while (start < end)
            {
                temp = seq[start];
                seq[start] = seq[end];
                seq[end] = temp;
                start++;
                end--;
            }

            print_instructions(seq, seq_length);
            break;
        default:
            printf("INVALID SEQUENCE");
            return;
        }

        r = fscanf(file, "%d %s %d", &seq_length, seq, &mode);
    }

    fclose(file);
}


