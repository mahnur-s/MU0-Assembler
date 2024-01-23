#include "assembler.h"

int main()
{
//----------------------------------------------
    //DO NOT CHANGE THIS PART
    FILE *fin;
    // FILE *fout;
    char line[LINE_SIZE] ={};
    char input[MAX_INSTRUCTION_SIZE][LINE_SIZE] = {};
    char output[MAX_INSTRUCTION_SIZE][LINE_SIZE] = {};
    int limit = 0;
    
    char file_name[1024]={};
    
    memset(file_name, 0x00, sizeof(file_name));
    
    printf("input file name: ");
    scanf("%s", file_name);

    fin = fopen(file_name, "r");
    memset(line, 0x00, sizeof(line));

    while(fgets(line, LINE_SIZE, fin) != NULL){
        strcpy(input[limit], line);
        limit++;
        memset(line, 0x00, sizeof(line));

    }
    fclose(fin);


    assemble(input, output, limit);
    
    
    

    for(int i = 0; i < limit; i++){
        if(strlen(output[i])!=0 || *(output[i]) == '\n'){
            printf("%s\n", output[i]);
        }
    }
    
    
    
	return 0;
    //-----------------------------------------------
}