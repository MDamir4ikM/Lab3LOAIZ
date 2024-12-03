#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <Windows.h>
#include <malloc.h>

char find_el[256];

struct node {
    char inf[256];  // полезная информация
    struct node* next; // ссылка на следующий элемент 
};

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");
    scanf("%s", s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p; // возвращаем указатель на созданный элемент
}

struct node* head = NULL; // указатель на первый элемент списка

/* Добавление элемента в очередь в алфавитном порядке */
void enqueue(void) {
    struct node* p = get_struct();
    if (p == NULL) return; // Если ввод пустой, выходим

    // Если очередь пуста или элемент меньше главы
    if (head == NULL || strcmp(p->inf, head->inf) < 0) {
        p->next = head; // вставляем перед головой
        head = p; // обновляем голову
    }
    else {
        struct node* current = head;
        while (current->next != NULL && strcmp(current->next->inf, p->inf) < 0) {
            current = current->next;
        }
        p->next = current->next;
        current->next = p;
    }
}

/* Извлечение элемента из очереди (из начала) */
void dequeue(void) {
    if (head == NULL) {
        printf("Очередь пуста, невозможно извлечь элемент.\n");
        return;
    }
    struct node* temp = head; // сохраняем голову
    printf("Извлечён элемент: %s\n", head->inf);
    head = head->next; // устанавливаем голову на следующий элемент
    free(temp); // освобождаем память
}

/* Просмотр содержимого очереди. */
void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    while (struc) {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    while (true) {
        printf("\nВыберите действие:\n1 - Добавить элемент в очередь\n2 - Извлечь элемент из очереди\n3 - Просмотреть очередь\n4 - Выйти\nВаш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            review();
            break;
        case 4:
            return 0;
        default:
            printf("Неверный выбор, попробуйте снова.\n");
        }
    }

    return 0;
}