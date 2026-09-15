/* ============================================================
   M2-T2 · Флаги и упаковка полей в одно число
   Куда сдать: solutions/M2/M2-T2.c
   ============================================================ */
/*  Компиляция:  gcc -std=c11 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined M2-T2.c -o t -lm && ./t
    Ожидание:    ALL TESTS PASSED
    МЕНЯЙ ТОЛЬКО код между маркерами SOLUTION START / SOLUTION END. */
/*  ЗАДАЧА 1 — работа с отдельным битом (это ровно то, что ты будешь делать
   с регистрами микроконтроллера):
       uint32_t flag_set(uint32_t f, unsigned bit);     установить бит
       uint32_t flag_clear(uint32_t f, unsigned bit);   сбросить бит
       uint32_t flag_toggle(uint32_t f, unsigned bit);  инвертировать бит
       int      flag_test(uint32_t f, unsigned bit);    вернуть 0 или 1
   Если bit > 31 — вернуть flags БЕЗ ИЗМЕНЕНИЙ (для flag_test вернуть 0).
   Сдвиг на величину >= ширины типа — неопределённое поведение, это надо защитить.

   ЗАДАЧА 2 — упаковка даты в uint32_t (экономим память, как в реальных протоколах):
       биты  0..4   (5 бит)  — день   1..31
       биты  5..8   (4 бита) — месяц  1..12
       биты  9..31  (23 бита)— год    0..8388607
       uint32_t pack_date(unsigned day, unsigned month, unsigned year);
       void     unpack_date(uint32_t packed, unsigned *day, unsigned *month, unsigned *year);
   pack_date должна обнулять биты, не влезшие в поле (день > 31, месяц > 15 —
   не должно «поехать» в соседнее поле). Используй маску.

   ВОПРОСЫ ДЛЯ ОТЧЁТА (в solutions/notes/M2.md):
    1) Почему `flags & (1 << bit)` неправильно, а `flags & (1u << bit)` правильно?
    2) Чем побитовое поле `struct { unsigned day : 5; }` хуже ручной упаковки
       через сдвиги? (подсказка: переносимость и порядок битов)
    3) Что такое маска и зачем нужна операция `& 0x1F` в pack_date?                       */
#include <stdint.h>
#include <stdio.h>

uint32_t flag_set(uint32_t flags, unsigned bit) {
    /* >>> SOLUTION START (меняй только здесь) */
    if (bit > 31) return flags;
    flags |= (1u << bit);
    return flags;
    /* >>> SOLUTION END */
}

uint32_t flag_clear(uint32_t flags, unsigned bit) {
    /* >>> SOLUTION2 START (меняй только здесь) */
    if (bit > 31) return flags;
    flags &= ~(1u << bit);
    return flags;
    /* >>> SOLUTION2 END */
}

uint32_t flag_toggle(uint32_t flags, unsigned bit) {
    /* >>> SOLUTION3 START (меняй только здесь) */
    if (bit > 31) return flags;
    flags ^= (1u << bit);
    return flags;
    /* >>> SOLUTION3 END */
}

int flag_test(uint32_t flags, unsigned bit) {
    /* >>> SOLUTION4 START (меняй только здесь) */
    if (bit > 31) return 0;
    if (flags & (1u << bit)) return 1;
    return 0;
    /* >>> SOLUTION4 END */
}

uint32_t pack_date(unsigned day, unsigned month, unsigned year) {
    /* >>> SOLUTION5 START (меняй только здесь) */
    day &= 0x0000001Fu;
    month = (month & 0x0000000Fu) << 5u;
    year = (year & 0x007FFFFFu) << 9u;
    uint32_t date = day + month + year;
    return date;
    /* >>> SOLUTION5 END */
}

void unpack_date(uint32_t packed, unsigned *day, unsigned *month, unsigned *year) {
    /* >>> SOLUTION6 START (меняй только здесь) */
    /* TODO: твой код */
    (void)packed; (void)day; (void)month; (void)year;
    /* >>> SOLUTION6 END */
}

/* -------------------- тесты: НЕ редактируй -------------------- */
static int g_fail = 0;
static void chk_u32(uint32_t got, uint32_t want, const char *what) {
    if (got != want) { printf("FAIL %-28s got 0x%08X, want 0x%08X\n", what, got, want); ++g_fail; }
}
static void chk_int(int got, int want, const char *what) {
    if (got != want) { printf("FAIL %-28s got %d, want %d\n", what, got, want); ++g_fail; }
}
int main(void) {
    chk_u32(flag_set(0x00u, 0),  0x00000001u, "set(0, bit 0)");
    chk_u32(flag_set(0x00u, 31), 0x80000000u, "set(0, bit 31)");
    chk_u32(flag_set(0xFFu, 4),  0x000000FFu, "set(0xFF, bit 4) уже установлен");
    chk_u32(flag_clear(0xFFu, 0), 0x000000FEu, "clear(0xFF, bit 0)");
    chk_u32(flag_clear(0xFFu, 7), 0x0000007Fu, "clear(0xFF, bit 7)");
    chk_u32(flag_toggle(0x0Fu, 0), 0x0000000Eu, "toggle(0x0F, bit 0)");
    chk_u32(flag_toggle(0x0Fu, 4), 0x0000001Fu, "toggle(0x0F, bit 4)");
    chk_int(flag_test(0x0Au, 1), 1, "test(0x0A, bit 1)");
    chk_int(flag_test(0x0Au, 0), 0, "test(0x0A, bit 0)");
    chk_int(flag_test(0x80000000u, 31), 1, "test(0x80000000, bit 31)");

    /* защита от сдвига на >= 32: значение не должно меняться */
    chk_u32(flag_set(0x1234u, 32),   0x00001234u, "set(bit 32) — без изменений");
    chk_u32(flag_set(0x1234u, 100),  0x00001234u, "set(bit 100) — без изменений");
    chk_u32(flag_clear(0x1234u, 64), 0x00001234u, "clear(bit 64) — без изменений");
    chk_int(flag_test(0xFFFFFFFFu, 32), 0, "test(bit 32) — 0");

    /* упаковка даты */
    chk_u32(pack_date(1, 1, 0), 0x00000001u | (1u << 5), "pack(1 янв 0)");
    struct { unsigned d, m, y; uint32_t want; } cs[] = {
        {15,  7, 2026, (15u) | (7u << 5) | (2026u << 9)},
        {31, 12, 8388607u, 31u | (12u << 5) | (8388607u << 9)},
        { 1,  1, 1, (1u) | (1u << 5) | (1u << 9)}
    };
    for (size_t i = 0; i < sizeof cs / sizeof cs[0]; ++i) {
        const uint32_t got = pack_date(cs[i].d, cs[i].m, cs[i].y);
        chk_u32(got, cs[i].want, "pack_date");
        unsigned d = 999, m = 999, y = 999;
        unpack_date(got, &d, &m, &y);
        if (d != cs[i].d || m != cs[i].m || y != cs[i].y) {
            printf("FAIL unpack_date: got %u.%u.%u, want %u.%u.%u\n",
                   d, m, y, cs[i].d, cs[i].m, cs[i].y);
            ++g_fail;
        }
    }
    /* переполнение поля не должно «поехать» в соседа */
    { unsigned d = 0, m = 0, y = 0;
      unpack_date(pack_date(0xFFu, 0xFFu, 0xFFFFFFFFu), &d, &m, &y);
      chk_u32(d, 31u, "день обрезан до 5 бит");
      chk_u32(m, 15u, "месяц обрезан до 4 бит");
      chk_u32(y, 0x7FFFFFu, "год обрезан до 23 бит"); }

    /* round-trip по всем дням и месяцам */
    for (unsigned d = 1; d <= 31; ++d)
        for (unsigned m = 1; m <= 12; ++m) {
            unsigned rd = 0, rm = 0, ry = 0;
            unpack_date(pack_date(d, m, 1999), &rd, &rm, &ry);
            if (rd != d || rm != m || ry != 1999) { printf("FAIL round-trip %u.%u\n", d, m); ++g_fail; }
        }

    if (g_fail == 0) puts("ALL TESTS PASSED");
    else printf("%d test(s) FAILED\n", g_fail);
    return g_fail != 0;
}
