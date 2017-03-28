#include "curses.h"
#include "tui.h"

void tui_start(const char** strings, const int line_count, char* selection, int selection_max){
    int selected_index = 1; // 1 indexed selection from the list
    int i = 0;
    bool run = TRUE;
    char key_press = '\0';
    initscr();                                     // start the curses mode
    noecho(); // echo();                           // Show characters written to screen
    raw(); //cbreak();                             // Control chracters are not sent to the program?
    keypad(stdscr, TRUE);                      // Do capture function and escape keys
    //getmaxyx(stdscr, screen_rows, screen_columns); // get the number of rows and columns
    for(i=0;i<line_count;i++){
        mvprintw(i+1, 1, "%s\n", strings[i]);
    }
    mvprintw(i+1, 1, "%d %d", line_count, selection_max);
    while(run){
       mvchgat(selected_index, 1, -1, A_STANDOUT, 1, NULL); // Set highlighted row
       box(stdscr, 0, 0);// Create bordered window
       refresh();
       key_press = getch();
       switch(key_press){
         case 'j':  // Move down without moving off screen
           if(selected_index < line_count){ 
               mvchgat(selected_index, 1, -1, A_NORMAL, 1, NULL); // Unset highlighted row
               selected_index++;
           }
           break;
       case 'k':
           if(selected_index > 1){ // Move up without moving off screen
               mvchgat(selected_index, 1, -1, A_NORMAL, 1, NULL); // Unset highlighted row
               selected_index--;
           }
           break;
       case KEY_ENTER:// Make selection
       case '\n':
       case '\r':
           strncpy(selection, strings[selected_index-1], selection_max);
           run = FALSE;
           break;
        case 'q': // Quit
        case 'Q':
           run = FALSE;
           break;
        case 'c': // Copy to clipboard
        case 'C':
            //clipboard_copy();
            //run = FALSE;
            break;
        default:
           break;
       }
    }
    clear(); // Clean up screen
    refresh(); // write clean screen
    endwin(); // end ncurses
}
