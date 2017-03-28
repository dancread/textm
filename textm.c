#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>  // Apparently required by pdcurses
#include <stdio.h>
#include "tui.h"
#include "utils.h"

#define INITIAL_BUFFER_SIZE 10000000
#define OUTPUT_BUFFER_SIZE 500000
void print_usage();
int main(int argc, char **argv) {
    int old_stdout;
    int line_count = 0; // Length of input by newline
    int bytes_read = 0; // Probably not needed
    char **strings = NULL; // Input strings from stdin
    char *input,*output,*full_command = NULL;
    input = (char*)malloc(INITIAL_BUFFER_SIZE);
    output = (char*)malloc(OUTPUT_BUFFER_SIZE);
    full_command = (char*)malloc(OUTPUT_BUFFER_SIZE);
    // Read stdin
    bytes_read = fread(input, 1, INITIAL_BUFFER_SIZE, stdin);
    // Terminate the string
    input[bytes_read] = '\0';
    // Count the number of newlines
    line_count = count_lines(input);
    strings = process_input(input, line_count);
    // Reset stdin to FILE_TYPE_CHAR for pdcurses
    freopen("CONIN$", "r", stdin);
    // Save old stdout
    old_stdout = _dup(1);
    // Reset stdout for pdcurses
    freopen("CONOUT$", "w", stdout);
    // Run TUI
    tui_start(strings, line_count, output, OUTPUT_BUFFER_SIZE);
    // Restore original stdout 
    _dup2( old_stdout, 1);
    // Execute system command on file
    if(argc > 1){
        sprintf(full_command,"%s %s",argv[1], full_command);
        system(full_command);
    }
    // Print result to stdout
    else{
        printf("%s",output);
    }
    free(input);
    free(output);
    free(full_command);
    exit(0);
}
// Win32 versions of getting and reassigning stdin
//ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, INITIAL_BUFFER_SIZE, &iBytesRead,NULL);
//SetStdHandle(STD_INPUT_HANDLE, CreateFileW(L"CONIN$", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL));
void print_usage(){
    printf("Usage: menut <command>");
}
