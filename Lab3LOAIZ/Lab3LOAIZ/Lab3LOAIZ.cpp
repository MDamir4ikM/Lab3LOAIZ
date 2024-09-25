#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include <iostream>

using namespace std;

struct node
{
	char inf[256];  // полезная информация
	int priority;
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента

struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int prior = 0;
	if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: ");   // вводим данные
	scanf("%s", s);
	printf("Введите приоритет: ");
	scanf("%d", &prior);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);
	p->priority = prior;
	p->next = NULL;
	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL || head->priority < p->priority)
	{
		p->next = head;
		head = p;
	}
	else
	{
		for (struct node* i = head; i != NULL; i = i->next)
		{
			if (i->next)
			{
				if (i->next->priority < p->priority)
				{
					p->next = i->next;
					i->next = p;
					break;
				}
			}
			else
			{
				i->next = p;
				last = p;
				break;
			}
		}
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, приоритет - %d\n", struc->inf, struc->priority);
		struc = struc->next;
	}
	return;
}

/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev = NULL;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}


}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Сколько элементов Вы желаете ввести: ";
	int count = 0;
	cin >> count;
	
	for (int i = 0; i < count; i++)
	{
		spstore();
	}

	cout << "Хотите увидеть Вашу мини-базу данных:\n1 - Да\n2 - нет\nОтвет: ";
	int otvet;
	cin >> otvet;

	if (otvet == 1)
	{
		review();
	}
	else
	{
		cout << "Жаль((";
	}

	cout << "Сколько элементов Вы хотите удалить: ";
	int count_del = 0;
	cin >> count_del;
	for (int i = 0; i < count_del; i++)
	{
		if (count_del > count)
		{
			cout << "Слишком многом хотите удалить";
		}
		else
		{
			cout << "Введите название элемента, который хотите удалить: ";
			char name[255];
			cin >> name;
			del(name);
		}
	}

	if (otvet == 1)
	{
		review();
	}
	else
	{
		cout << "Жаль((";
	}

	return 0;
}