#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <Windows.h>
#include <cstdlib>

struct node {
    char inf[256];  // полезная информация
    struct node* next; // указатель на следующий элемент 
    struct node* prev; // указатель на предыдущий элемент
};

struct node* head = NULL; // указатель на верхний элемент дека
struct node* tail = NULL; // указатель на нижний элемент дека

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");   // вводим данные
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;
    p->prev = NULL;

    return p;        // возвращаем указатель на созданный элемент
}

/* Добавление элемента в начало дека */
void push_front(void) {
    struct node* p = get_struct();
    if (p != NULL) {
        p->next = head; // следующий элемент нового узла — текущий верхний элемент
        p->prev = NULL; // предыдущий элемент у нового узла будет NULL
        if (head != NULL) {
            head->prev = p; // если дек не пуст, обновляем предыдущий указатель у старого верхнего элемента
        }
        head = p; // обновляем верхний элемент на добавленный узел
        if (tail == NULL) {
            tail = p; // если дек был пуст, обновляем и нижний элемент
        }
    }
}

/* Добавление элемента в конец дека */
void push_back(void) {
    struct node* p = get_struct();
    if (p != NULL) {
        p->next = NULL; // следующий элемент у нового узла будет NULL
        p->prev = tail; // предыдущим элементом нового узла будет текущий нижний элемент
        if (tail != NULL) {
            tail->next = p; // если дек не пуст, обновляем следующий указатель у старого нижнего элемента
        }
        tail = p; // обновляем нижний элемент на добавленный узел
        if (head == NULL) {
            head = p; // если дек был пуст, обновляем и верхний элемент
        }
    }
}

/* Извлечение элемента с начала дека */
void pop_front(void) {
    if (head == NULL) {
        printf("Дек пуст, невозможно извлечь элемент.\n");
        return;
    }
    struct node* temp = head; // сохраняем верхний элемент
    printf("Извлечён элемент с начала: %s\n", head->inf);
    head = head->next; // обновляем верхний элемент
    if (head != NULL) {
        head->prev = NULL; // обновляем предыдущий указатель у нового верхнего элемента
    }
    else {
        tail = NULL; // если дек стал пустым, обнуляем и нижний элемент
    }
    free(temp); // освобождаем память
}

/* Извлечение элемента с конца дека */
void pop_back(void) {
    if (tail == NULL) {
        printf("Дек пуст, невозможно извлечь элемент.\n");
        return;
    }
    struct node* temp = tail; // сохраняем нижний элемент
    printf("Извлечён элемент с конца: %s\n", tail->inf);
    tail = tail->prev; // обновляем нижний элемент
    if (tail != NULL) {
        tail->next = NULL; // обновляем следующий указатель у нового нижнего элемента
    }
    else {
        head = NULL; // если дек стал пустым, обнуляем и верхний элемент
    }
    free(temp); // освобождаем память
}

/* Просмотр содержимого дека. */
void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Дек пуст\n");
        return;
    }
    printf("Содержимое дека:\n");
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
        printf("\nВыберите действие:\n1 - Добавить элемент в начало дека\n2 - Добавить элемент в конец дека\n3 - Извлечь элемент из начала дека\n4 - Извлечь элемент из конца дека\n5 - Просмотреть дек\n6 - Выйти\nВаш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            push_front();
            break;
        case 2:
            push_back();
            break;
        case 3:
            pop_front();
            break;
        case 4:
            pop_back();
            break;
        case 5:
            review();
            break;
        case 6:
            return 0;
        default:
            printf("Неверный выбор, попробуйте снова.\n");
        }
    }

    return 0;
}