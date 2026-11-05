#!/usr/bin/env bash
# Проходит все тесты указателей: строгая сборка + запуск под ASan/UBSan.
# Вывод: сколько файлов/проверок прошли, где упали. Выход: 0 — всё чисто.
set -u
cd "$(dirname "$0")"

CC=gcc
FLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2'
SAN='-g -fsanitize=address,undefined -fno-omit-frame-pointer'

total=0
failed=0

for f in 0*.c; do
    total=$((total + 1))
    bin="/tmp/ptrtest_${f%.c}"
    echo "=== $f ==="
    if ! $CC $FLAGS $SAN "$f" -o "$bin" 2> /tmp/ptrtest_cc.err; then
        echo "СБОРКА УПАЛА:"
        cat /tmp/ptrtest_cc.err
        failed=$((failed + 1))
        continue
    fi
    out=$("$bin" 2> /tmp/ptrtest_run.err)
    rc=$?
    echo "$out"
    if [ "$rc" -ne 0 ]; then
        [ -s /tmp/ptrtest_run.err ] && sed 's/^/  sanitizer: /' /tmp/ptrtest_run.err
        failed=$((failed + 1))
    fi
    rm -f "$bin"
done

echo
if [ "$failed" -eq 0 ]; then
    echo "ВСЁ ЧИСТО: $total/$total файлов, все проверки OK."
    exit 0
else
    echo "ОТКАЗ: $failed из $total файлов упали — смотри строки FAIL/СБОРКА выше."
    exit 1
fi
