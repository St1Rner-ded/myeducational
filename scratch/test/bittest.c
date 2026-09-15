#include <stdint.h>
#include <stdio.h>

uint32_t pack_date(unsigned day, unsigned month, unsigned year) {
    day &= 0x0000001Fu;
    printf (" %x\n", day);
    month = (month & 0x0000000Fu) << 5u;
    printf (" %x\n", month);
    year = (year & 0x007FFFFFu) << 9u;
    printf (" %x\n", year);
    uint32_t date = day + month + year;
    return date;
}

void unpack_date(uint32_t packed, unsigned *day, unsigned *month, unsigned *year) {
    /* >>> SOLUTION6 START (меняй только здесь) */
    /* TODO: твой код */
    (void)packed; (void)day; (void)month; (void)year;
    /* >>> SOLUTION6 END */
}

int main() {
    unsigned d = 0,
    m = 0,
    y = 0;
    printf ("enter date, just numbers, format: dd mm yyyy\n");
    scanf (" %u", &d); printf (" ur day: %x\n", d);
    scanf (" %u", &m); printf (" ur month: %x\n", m);
    scanf (" %u", &y); printf (" ur year: %x\n", y);
    printf (" ur date in HEX: %x\n", pack_date(d,m,y));
    printf("%zu, %zu\n", sizeof("A"), sizeof('A'));
    return 0;
}

