#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "assembler.h"

#define MAX_INSTRUCTION_SIZE 128
#define LINE_SIZE 90
#define MAX_LABEL_SIZE 90

#define LABEL_C ':'
#define NUM_LITERAL_C '#'
#define CHAR_LITERAL_C '$'

/*
    Implement the mu0 assembler
    input : 2D array contain MAXINUM 1024 insturction and labels
    output : 2D array of Machine language as hex (000f, 1009, ....)
    mu0 instructions
    (LDA, STO, ADD SUB, JMP, JGE, JNE, STP)
    
    
*/
static char *opcode_str[8] = {
    "LDA", "STO", "ADD", "SUB", "JMP", "JGE", "JNE", "STP"
};
int countvalid(int i, char input[][LINE_SIZE]) {
    int counter = 0;
    for (int z = i-1; z >= 0; z--) {
        char *linecheck = input[z];
        if (!(input[z][0] == '$' || (isspace(linecheck[0])) || input[z][0] == ':')) {
            counter++;
        }
    }
    return counter;
}
void assemble(char input[][LINE_SIZE], char output[][LINE_SIZE], int len){
    //---------------
    //your code here
    
    char labelarr[MAX_LABEL_SIZE][len];
    int labelline[len];
    int address = 0;
    int num_labels = 0;
    int index2 = 0;

    for (int i = 0; i < len; i++) {
        char *line = input[i];
        if ((strncmp(line, "STP", 3) == 0) || (line[0] == '#') || (isspace(line[0])) || (line[0] == '$')) {
            continue;
        } else {
            if (input[i][0] == ':') {
                int val = countvalid(i, input);
                labelline[index2] = val;
                index2++;
                strncpy(labelarr[num_labels], &line[1], MAX_LABEL_SIZE - 1);
                num_labels++;
            }
        }
    }

    for (int i = 0; i < len; i++) {
        char *line = input[i];
        if (input[i][0] == '#') {
            char hexnum[MAX_LABEL_SIZE];
            int val = atoi(input[i] + 1);
            sprintf(hexnum, "%04x", val);
            strcpy(output[address], hexnum);
            address++;
        } else if (input[i][0] == '$') {
            char ascii_char = input[i][1];
            char hexnum[4];
            sprintf(hexnum, "%04x", ascii_char);
            strcpy(output[address], hexnum);
            address++;
        } else if ((input[i][0] == ':') || isspace(line[0])) {
            continue;
        } else {
            for (int j = 0; j < 8; j++) {
                if (strstr(line, opcode_str[j]) != NULL) {
                    char *colon_pos = strchr(line, ':');
                    char *substring = NULL;
                    if (colon_pos != NULL) {
                        substring = colon_pos + 1;
                        for (int k = 0; k < num_labels; k++) {
                            if (strcmp(labelarr[k], substring) == 0) {
                                int neededindex = j;
                                char formatted_string[5];
                                int line_number = labelline[k];
                                sprintf(formatted_string, "%x%03x", neededindex, line_number);
                                strcpy(output[address], formatted_string);
                                address++;
                            }
                        }
                    } else if (strlen(line)) {
                        int neededindex = j;
                        char formatted_string[5];
                        int line_number = 0;
                        sscanf(line + 3, "%x", &line_number);
                        sprintf(formatted_string, "%x%03x", neededindex, line_number);
                        strcpy(output[address], formatted_string);
                        address++;
                    }
                }
            }
        }
    }
}