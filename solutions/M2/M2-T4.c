/* ============================================================
   M2-T4 · Байты, порядок байтов, извлечение полей
   Куда сдать: solutions/M2/M2-T4.c
   ============================================================ */
/*  Компиляция:  gcc -std=c11 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined M2-T4.c -o t -lm && ./t
    Ожидание:    ALL TESTS PASSED
    МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END. */
/*  ЗАДАЧА:
      uint16_t swap_bytes16(uint16_t v);              0x1234 -> 0x3412
      uint32_t swap_bytes32(uint32_t v);              0xDEADBEEF -> 0xEFBEADDE
      uint32_t extract_byte(uint32_t v, unsigned i);  i-й байт, i=0 — младший
      int      is_little_endian(void);                1 или 0
      uint32_t set_byte(uint32_t v, unsigned i, unsigned byte);  заменить i-й байт

   Ограничения:
     - НЕ использовать union и приведение указателей в is_little_endian
       (это отдельный разговор, сделай через сдвиги или через uint16_t/uint8_t);
     - extract_byte и set_byte при i > 3 должны вести себя безопасно
       (extract -> 0, set -> v без изменений).

   ВОПРОСЫ ДЛЯ ОТЧЁТА (в solutions/notes/M2.md):
    1) Что такое little-endian и big-endian? Какой порядок на x86 и почему
       это важно при чтении бинарных файлов или сетевых пакетов?
    2) Зачем существуют htonl/htons/ntohl/ntohs?
    3) Почему чтение `*(uint8_t*)&some_uint32` формально является
       нарушением strict aliasing, а union — в C разрешено?
    4) Сколько байтов занимает struct { char a; int b; char c; } и почему
       не 6? Что такое выравнивание (alignment)?
    5) Порядок байтов нельзя определить через сдвиги: сдвиги работают со
       ЗНАЧЕНИЕМ, а не с памятью. Нужен доступ к байтам памяти — легальный
       способ сделать это в C — memcpy(). Про union и приведение указателей
       поговорим в разборе.                                                  */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint16_t swap_bytes16(uint16_t v) {
    /* >>> SOLUTION START (меняй только здесь) */
    /* TODO: твой код */
    (void)v;
    return 0;
    /* >>> SOLUTION END */
}

uint32_t swap_bytes32(uint32_t v) {
    /* >>> SOLUTION2 START (меняй только здесь) */
    /* TODO: твой код */
    (void)v;
    return 0;
    /* >>> SOLUTION2 END */
}

uint32_t extract_byte(uint32_t v, unsigned i) {
    /* >>> SOLUTION3 START (меняй только здесь) */
    /* TODO: твой код */
    (void)v; (void)i;
    return 0;
    /* >>> SOLUTION3 END */
}

uint32_t set_byte(uint32_t v, unsigned i, unsigned byte) {
    /* >>> SOLUTION4 START (меняй только здесь) */
    /* TODO: твой код */
    (void)v; (void)i; (void)byte;
    return 0;
    /* >>> SOLUTION4 END */
}

int is_little_endian(void) {
    /* >>> SOLUTION5 START (меняй только здесь) */
    /* TODO: твой код.
       Идея: возьми uint16_t со значением 1, скопируй его байты в unsigned char[2]
       через memcpy() и посмотри, какой байт оказался нулевым.                */
    return 0;
    /* >>> SOLUTION5 END */
}

/* -------------------- тесты: НЕ редактируй -------------------- */
static int g_fail = 0;
static void chk(uint32_t got, uint32_t want, const char *what) {
    if (got != want) { printf("FAIL %-26s got 0x%08X, want 0x%08X\n", what, got, want); ++g_fail; }
}
int main(void) {
    chk(swap_bytes16(0x1234), 0x3412, "swap16(0x1234)");
    chk(swap_bytes16(0x00FF), 0xFF00, "swap16(0x00FF)");
    chk(swap_bytes16(0x0000), 0x0000, "swap16(0)");
    chk(swap_bytes32(0xDEADBEEF), 0xEFBEADDE, "swap32(0xDEADBEEF)");
    chk(swap_bytes32(0x01020304), 0x04030201, "swap32(0x01020304)");
    chk(swap_bytes32(0), 0, "swap32(0)");
    chk(swap_bytes32(swap_bytes32(0xCAFEBABE)), 0xCAFEBABE, "swap32 дважды = исходное");

    chk(extract_byte(0xAABBCCDD, 0), 0xDD, "byte 0");
    chk(extract_byte(0xAABBCCDD, 1), 0xCC, "byte 1");
    chk(extract_byte(0xAABBCCDD, 2), 0xBB, "byte 2");
    chk(extract_byte(0xAABBCCDD, 3), 0xAA, "byte 3");
    chk(extract_byte(0xAABBCCDD, 4), 0,   "byte 4 — безопасно");
    chk(extract_byte(0xAABBCCDD, 100), 0, "byte 100 — безопасно");

    chk(set_byte(0xAABBCCDD, 0, 0x11), 0xAABBCC11, "set byte 0");
    chk(set_byte(0xAABBCCDD, 3, 0x11), 0x11BBCCDD, "set byte 3");
    chk(set_byte(0xAABBCCDD, 1, 0x1FF), 0xAABBFFDD, "set byte 1 (byte > 255 обрезается)");
    chk(set_byte(0xAABBCCDD, 4, 0x11), 0xAABBCCDD, "set byte 4 — без изменений");
    chk(set_byte(0x00000000, 2, 0xFF), 0x00FF0000, "set byte 2 с нуля");

    /* независимо проверяем порядок байтов через memcpy — и сверяем с твоим ответом */
    {
        const uint16_t probe = 0x0001u;
        unsigned char raw[2];
        memcpy(raw, &probe, sizeof raw);
        const int truth = (raw[0] == 0x01u) ? 1 : 0;
        const int le = is_little_endian();
        printf("INFO: is_little_endian() = %d (на этой машине должно быть %d)\n", le, truth);
        if (le != 0 && le != 1) { printf("FAIL is_little_endian вернул %d (нужно 0 или 1)\n", le); ++g_fail; }
        else if (le != truth)   { printf("FAIL is_little_endian: %d, а машина говорит %d\n", le, truth); ++g_fail; }
    }

    if (g_fail == 0) puts("ALL TESTS PASSED");
    else printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
