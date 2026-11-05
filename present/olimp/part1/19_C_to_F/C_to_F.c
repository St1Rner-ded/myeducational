//Дана температура C в градусах Цельсия. Переведите её в градусы Фаренгейта по формуле F = C × 9/5 + 32.
//-273 <= C <= 1000

#include <stdio.h>

#define MIN_T -273
#define MAX_T 1000

int main (void) {
    int celcius = 0;
    if (scanf ("%d", &celcius) != 1 || celcius < MIN_T || celcius > MAX_T) {
        return 1;
    }
    printf ("%d", celcius * 9/5 + 32);
    return 0;
}