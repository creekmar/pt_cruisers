//
// demo_curses.c is derived from an example found in
// http://heather.cs.ucdavis.edu/~matloff/UnixAndC/CLanguage/Curses.pdf [2018]
//
// @author: CS @ RIT.EDU

#include <curses.h>
#include <stdio.h>

// To build: gcc -std=c99 -ggdb -Wall -Wextra demo_curses.c -o demo -lcurses
// you can use -lcurses or -lncurses
//

static int nrows;                  ///< set by curses' getmaxyx macro

static int ncols;                  ///< set by curses' getmaxyx macro

static WINDOW * wnd = NULL;        ///< saves window reference (unused)

/// main gets window, initializes curses, and handles user input until 'q'.

int main( void ) {

    wnd = initscr();               // initialize curses window
    cbreak();                      // set no waiting for Enter key
    noecho();                      // set no echoing of user input
    getmaxyx( stdscr,nrows,ncols); // ncurses call to find size of window
    clear();                       // clear screen and send cursor to (0,0)

    mvprintw( 20, 20, "Hello ncurses!! Press a letter or press 'q' to exit.");
    refresh();                     // implement all changes since last refresh

    int r = 1;
    int c = 10;
    while (1)  {
        int d = getch();           // get input from keyboard
        if ( d == 'q' ) break;     // quit?
        // draw the character
        // printw("%c", d);        // prints char at the current location
        mvprintw( r++, c++, "%c", d); // move and print
        refresh();                 // implement all changes since last refresh
    }

    endwin();                      // restore original window and leave curses
}
