// 06-out-params.c — как функция возвращает «большие» значения: int**, out-параметры, head-паттерн.
// Тема: параметр передаётся КОПИЕЙ. Чтобы поменять САМОТ указатель в вызывающем — int**.
// Сборка/запуск — в README.md этой папки.

#include <stdio.h>
#include <stdlib.h>

static int n_fail = 0;

static void check (int cond, const char *what) {
    if (!cond) {
        ++n_fail;
        printf ("FAIL: %s\n", what);
    }
}

// 1) int x — копия числа. Изменения копийии никак не влияют на оригинал.
void try_copy (int x) {
    x = 100;                                  // дописали в КОПИЮ
    printf ("(внутри try_copy: x = %d — копия, а не переменная вызывающего)\n", x);
}

// 2) int *p — копия адреса, но доступ к тому же самому числу. Меняет *x, не меняет указатель.
void try_dereference (int *x) { *x = 200; }

// 3) int **pp — копия адреса указателя. Меняет САМ указатель вызывающего.
void try_pointer_itself (int **pp) {
    static int storage = 777;   // чтобы указатель остался жив после выхода
    *pp = &storage;
}

// Паттерн head из linked_list.c: append без ** смог бы менять список, но не мог бы
// поменять head, если список пустой. ** — именно для этого.
typedef struct Cell {
    int value;
    struct Cell *next;
} Cell;

void cell_set_head (Cell **head, int value) {
    Cell *c = malloc (sizeof *c);
    if (c == NULL) {
        fprintf (stderr, "нет памяти\n");
        exit(1);
    }
    c->value = value;
    c->next = *head;     // старая голова становится второй
    *head = c;           // только теперь вызывающий увидит новую head
}

int main (void) {
    int a = 1;
    int *p = &a;

    try_copy (a);
    check (a == 1, "функция с int x получила копию: вызываемый a не тронут");

    try_dereference (&a);
    check (a == 200, "функция с int *x дописала 200 в ту самую ячейку a");

    int *q = &a;
    try_pointer_itself (&q);
    check (q != p, "передан адрес самого q: после вызова q смотрит в другое место, старый адрес q не сохранился");
    check (*q == 777, "*q = 777: по новому адресу живёт static int storage");
    check (p == &a && *p == 200, "старый указатель p не пострадал: каждая копия адреса живёт своей жизнью");

    // Теперь head-паттерн: сначала список пуст.
    Cell *head = NULL;
    // Ключевой случай: head == NULL. Умный append БЕЗ ** не умеет сказать вызывающему
    // «бери вот этот новый адрес» — параметр был копией NULL.
    cell_set_head (&head, 10);
    check (head != NULL && head->value == 10, "пустой список: **head записал новый адрес в head вызывающего");

    cell_set_head (&head, 20);
    check (head->value == 20 && head->next != NULL && head->next->value == 10,
           "после второй вставки: список 20 -> 10 -> NULL, head перекручен");

    // Очистка: освобождаем, ходя по копиям адресов, и обнуляем head.
    while (head != NULL) {
        Cell *cur = head;
        head = head->next;
        free (cur);
    }
    check (head == NULL, "после free всех ячеек head снова NULL — граблины с double-free сняты");

    if (n_fail == 0) {
        printf ("OK: все проверки (06). int — копия числа; int* — копия адреса (меняет объект); int** — меняет сам указатель.\n");
    } else {
        printf ("ОТКАЗ: не прошли %d проверок (06)\n", n_fail);
    }
    return n_fail == 0 ? 0: 1;
}
