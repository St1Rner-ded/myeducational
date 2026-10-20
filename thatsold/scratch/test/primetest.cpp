#include <cstdint>
#include <cstdio>

int main() {
    unsigned n=0x00000000;
    printf("vvedite chislo\n");
    scanf ("%x", &n);
    int c = 0;
    while (n) {
        c++;
        n &= (n - 1);
    }
    printf("iterations (popcount): %d\n", c);
    return 0;
}