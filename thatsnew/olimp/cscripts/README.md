# cscripts — генераторы входов для задач olimp

Самодельные стенды: генерируют входные данные в `*.txt` (файлы в `.gitignore`),
которые подаются задачам через `< файл.txt` или пайп. Часть учебного трека.

| Генератор | Что пишет | Для каких задач |
|---|---|---|
| `rand_num.c` | COUNT случайных чисел | числовые part1: 01_even_odd, 02_digit_sum, 03_max_of_three, 09–12, 16 |
| `eq_num.c` | COUNT одинаковых чисел | вырожденный случай: 06_array_sum, 07_array_max, part2/01_array_median |
| `arr_rand_num.c` | массив из COUNT случайных чисел | массивные: 06_array_sum, 07_array_max, 17/18, part2/01_array_median (100000 — верх лимита) |
| `eq_symbols.c` | строки из повторяющихся символов | строковые part1: 04_reverse_string, 05_vowel_count, 08_palindrome, 13/14/20 |
| `bracket_seq_right.c` | заведомо правильная скобочная последовательность (1000) | part2/03_bracket_check |
| `bracket_seq_wrong.c` | заведомо неправильная скобочная последовательность (1000) | part2/03_bracket_check |
| `big_number.c` | предельный вход: 10⁹ и 10¹⁸ | part2/05_quick_power |
| `segments_gen.c` | N случайных отрезков (старт + длина) | part3/03_max_noncrosses |
| `labyr_gen.c` | случайный лабиринт с гарантированным путём S→E | part3/02_labyrinth_shortest_route |
