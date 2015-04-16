#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

struct book {
    int number;
    char title[40];
    char author[20];
    int year;
    int amount;
    struct book *next;
};
struct book *head, *tail;

void input(), search(), list();
void del(struct book **);
void store(struct book *i, struct book **head, struct book **tail), display(struct book *);
int  menu_select(); struct book *find(char *s);

int main()
{setlocale (0, "Rus");
    head = tail = NULL;  /* инициализация указателей на начало и конец */
      for(;;)
      {
        switch(menu_select()) {
          case 1: input(); /* ввод адреса */
            break;
          case 2: del(&head); /* удаление адреса */
            break;
          case 3: list(); /* отображение списка */
            break;
          case 4: search(); /* поиск адреса */
            break;
          case 5: exit(0);
        }
      }
      return 0;
}

int  menu_select(void)
{
    int c;  char ch;

    cout << "1. Ввод информации о книге\n";
    cout << "2. Удаление книги\n";
    cout << "3. Отображение содержимого списка\n";
    cout << "4. Запрос о наличии книги в библиотеке\n";
    cout << "5. Выход\n";
    do
    {
        cout << "\nВаш выбор: ";
        cin >> ch;
        c = ch - '0';
    }
    while(c < 0 || c > 7);
    return c;
}

/* Ввод имени и адресов. */
void input()
{struct book *i;

  for(;;) {
    i = (struct book *)malloc(sizeof(struct book));
    if(!i) {
      cout << "\nНет свободной памяти";
      return;
    }
    int a;
    string k;

    cout << "Введите номер УДК:"<<endl;
    cin >> a;
    i->number= a;

    if(i->number == 0) break;
    /* завершить ввод */

    cout << "Введите название книги:"<<endl;
    cin >> i->title;

    cout << "Введите автора книги:";
    cin >> i->author;

    cout << "Введите год:"<<endl;
    cin>>a;
    i->year = a;

    if(i->year == 0) break;
    /* завершить ввод */

    cout << "Введите количество книг:"<<endl;
    cin>>a;
    i->amount=a;

    store(i, &head, &tail);
  }
}

/* Создание упорядоченного односвязного списка. */
void store(struct book *i, struct book **head, struct book **tail)
{
    struct book *old, *p;

    p = *head;

    if(!*tail)
    { /* первый элемент в списке */
        i->next = NULL;
        *tail = i;
        *head = i;
        return;
    }

    old = NULL;
    while(p) {
    if(p->year < i->year)
    {
      old = p;
      p = p->next;
    }
    else
    {
      if(old)
      { /* вставка в середину */
        old->next = i;
        i->next = p;
        return;
      }
      i->next = p; /* вставка в начало */
      *head = i;
      return;
    }
  }
  (*tail)->next = i; /* вставка в конец */
  i->next = NULL;
  *tail = i;
}

/* Удаление элемента из списка. */
void del(struct book **head)
{
    struct book *i;
    struct book *t=*head;

    char s[40];
    cout << "Введите  название книги ";
    cin >> s;
    i = find(s);

   if (i !=0 && i!=*head)
   {
      while (t->next!=i)
      {
          t=t->next;  /*ищем предыдущий элемент от удаляемого*/
      }
      t->next=i->next; /*предыдущий элемент теперь связан со следующим элементов после удаляемого*/
      delete i;
  }
  else if (i==*head)
  {
      *head=(*head)->next; //?????
      delete i;
  }
}

/*struct book *find(int years)
{
  struct book *i;

  i = head;
  while(i)
  {
    if( years == i->year)
    return i;
    i = i->next;
  }
 cout <<"Книга не найдена." << endl;
  return NULL;
}*/

struct book *find(char *s)
{
  struct book *i;
 cout << "\nВы ищете книгу с назваением: "<< s << endl;
  i = head;
  while(i)
  {
    if( strcmp(s,i->title) == 0)
    return i;
    i = i->next;
  }
 cout <<"Книга не найдена.\n\n" << endl;
  return NULL;
}

/* Отобразить на экране весь список. */
void list()
{
  struct book *i;
  i = head;
  while(i) {
    display(i);
    i = i->next;  /* перейти к следующему адресу */
  }
 cout <<"\n\n";
}

/* Данная функция выполняет собственно вывод на экран всех полей записи */
void display(struct book *i)
{
    cout << "\n Код УДК: " << i->number;
    cout << "\n Название книги: " << i->title;
    cout << "\n Автор: " << i->author;
    cout << "\n Год издания: " << i->year;
    cout << "\n Количество книг: " << i->amount;

   cout << "\n";
}

/* Поиск по наличаю книг в списке. */
void search()
{
  struct book *i;
/*  int y;
  cin >> y;
  i = find(y);*/
  char s[40];
  cout << "Введите  название книги ";
  cin >> s;
  i = find(s);
  if(i)
      if (i->amount > 0)
  display(i);
       else cout << "Нет книг в наличае\n";
}
