#include <stddef.h>
#include <string.h>
#include "utils.h"
int count_lines(char *string){
    int lines = 0;
    char *ptr = string;
    while(*ptr != '\0'){
        if(*ptr == '\n'){
            lines++;
        }
        ptr++;
    }
    return lines;
}
char** process_input(char* buffer, int line_count){
    char **strings = NULL;
    int i=0;
    strings = (char**)malloc(line_count);
    // Tokenize on newline and store in string array
    strings[0] = strtok(buffer, "\n");
    for(i=1;i<line_count;i++){
       strings[i] = strtok(NULL,"\n");
    }
    return strings;
}
