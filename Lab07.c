/***************************************************************************
 * Lab07.c (barebones starter code version)
 *
 *   Created:
 *    Author: Sammy Mohamed
 * Processor: ATmega128A (on a ReadyAVR)
 *
 * Your comments go here...
 *
 * 
 *  use pointers to initialize, display, and update the 61 cell array.
 *self Notes: cp+i means go to cell i, *(cp+i)=look/change whats inside cell i, 
 **************************************************************************/

/* your #include file declaration(s) go here */
#include "UARTLibrary.h"
#include <string.h> //lets use memcpy

/* your #define declarations go here */
#define BaudRate 9600
#define DataBits 8
#define StopBits 1
#define NoParity 0

// prototype subroutine definitions
void initializeArray(unsigned char *cp);
void displayArray(unsigned char *cp);
void updateArray(unsigned char *cp);

int main(void)
{
    // create sopace for a 61-char array
    // holds for one full gen
    unsigned char cells[61];

    // make the starting pattern
    initializeArray(cells); //initializezed starting row


    // Initialize the UART
    // ProfNote:  Understand the UARTLibary.h before blindly running the next line!
    uart_init(BaudRate, DataBits, StopBits, NoParity); //lets board sends pattern to the putty


    // ProfNote:  Initial Testing Only!  Comment out after UART confirmed working!
    /*
    while (1) {
        uart_tx('H');uart_tx('e');uart_tx('l');uart_tx('l');uart_tx('o');uart_tx('\r');uart_tx('\n');
        uart_tx('W');uart_tx('o');uart_tx('r');uart_tx('l');uart_tx('d');uart_tx('!');uart_tx('\r');uart_tx('\n');
    }
    */


    /* your code goes here */

    // display and update the array 122 times
    for (int generation = 0; generation < 122; generation++)
    {
        // print the current generation first
        displayArray(cells);

        // then make the next generation
        updateArray(cells);
    }

}


/* your subroutines go here */


/* sets up the first generation */
void initializeArray(unsigned char *cp)
{
    // go through every cell
    for (int i = 0; i < 61; i++)
    {
        *(cp + i) = ' '; //*(cp+i)=look/change whats inside cell, all i to  white
    }

    // make the middle cell black since 30 is middle
    *(cp + 30) = '*';
}


/* prints one full gen */
void displayArray(unsigned char *cp)
{
    // ProfNote:  Look through your line using "uart_tx(<char>)" to print one character at a time.
    // At the end of the line, use "uart_tx('\r'); uart_tx('\n');" to print a new line to keep your
    // output aligned properly.

    // go through all 61 cells
    for (int i = 0; i < 61; i++)
    {
        // print each cell one at a time in putty
        uart_tx(*(cp + i));
    }

    // move to the next line
    uart_tx('\r');
    uart_tx('\n');
}


/* creates the next gen using Rule 26 */
void updateArray(unsigned char *cp)
{
    // temp place to buuild new row
    //  keeps  from changing the old one too early
    unsigned char next[61];

    // first and last cells always stay white
    next[0] = ' ';
    next[60] = ' ';

    // only update cells 1 through 59
    for (int i = 1; i < 60; i++)
    {
        // get the left, center, and right cells//
        unsigned char left = *(cp + i - 1);  //-1 to left of i 
        unsigned char center = *(cp + i);    //i
        unsigned char right = *(cp + i + 1); //+1 to right of i

        // start by putting the new cell is white
        next[i] = ' ';

        // Rule 26: black white white 100
        if (left == '*' && center == ' ' && right == ' ')
        {
            next[i] = '*';
        }

        // white, black, black 011
        else if (left == ' ' && center == '*' && right == '*')
        {
            next[i] = '*';
        }

        //  white, white, black 001
        else if (left == ' ' && center == ' ' && right == '*')
        {
            next[i] = '*';
        }
    }

    // copy the finished next generation back into the current generation
     
    memcpy(cp, next, 61);
}