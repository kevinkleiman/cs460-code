/*
 * demo.c
 *
 * Sample code to collect input from the user
 *
 * Sometimes, when you want both single-char input and longer text input,
 * using scanf and getc and such, one fetch may leave unconsumed characters
 * in stdin that confuses subsequent fetches.
 *
 * Trailing newlines also can cause trouble.
 *
 * Should these things cause you problems in pa1, this code may prove helpful.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "readline.h"

/*
 * testing out the readline code
 */
int main(int argc, char * argv[])
{
    const int lineLength = 50;           // maximum length of line
    char line[lineLength];               // buffer for reading lines

    // read input from stdin (e.g,. manual input on separate lines, piped/redirected file)
    while (!feof(stdin)) {
        printf("> ");
        if (readLine(line, lineLength)) {
            printf("|-> %s", line);
        }
    }

    return 0;
}
