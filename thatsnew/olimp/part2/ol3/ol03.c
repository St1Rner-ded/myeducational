#include <stdio.h>

int main (void) {
    unsigned short round = 0, square = 0, figure = 0;
    char string[1001];
    char last_char;
    printf ("Enter sequence of various brackets, number of open and closed brackets must be same: ");
    scanf ("%s", string);
    unsigned i = 0;
    while (string[i] != '\0') {
        switch (string[i]){
            case '(':
                round++;
                last_char = string[i];
                break;
            case ')':
                if (last_char == '(' || (round != 0 && square == 0 && figure == 0)) {
                    round--;
                    last_char = string[i];
                    break;
                }
                else {
                    printf ("Your sequence is wrong.\n");
                    return 0;
                }
            case '[':
                square++;
                last_char = string[i];
                break;
            case ']':
                if (last_char == '[' || (square != 0 && round == 0))
        }
    }
    return 0;
}