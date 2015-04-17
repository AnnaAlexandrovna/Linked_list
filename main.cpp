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
      cout << " \t\t\t Меню:"<<endl;
    head = tail = NULL;  
      for(;;)
      {
        switch(menu_select()) {
          case 1: input();
            break;
          case 2: del(&head);
            break;
          case 3: list(); 
            break;
          case 4: search();
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
cout << "Введите 0 для выхода из формы ввода:"<<endl;
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
   
    cout << "Введите название книги:"<<endl;
    cin >> i->title;

    cout << "Введите автора книги:";
    cin >> i->author;

    cout << "Введите год:"<<endl;
    cin>>a;
    i->year = a;

    if(i->year == 0) break;

    cout << "Введите количество книг:"<<endl;
    cin>>a;
    i->amount=a;

    store(i, &head, &tail);
  }
}

void store(struct book *i, struct book **head, struct book **tail)
{
    struct book *old, *p;

    p = *head;

    if(!*tail)
    { 
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
      { 
        old->next = i;
        i->next = p;
        return;
      }
      i->next = p; 
      *head = i;
      return;
    }
  }
  (*tail)->next = i; /
  i->next = NULL;
  *tail = i;
}

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
          t=t->next; 
      }
      t->next=i->next; 
      delete i;
  }
  else if (i==*head)
  {
      *head=(*head)->next; 
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

void list()
{
  struct book *i;
  i = head;
  while(i) {
    display(i);
    i = i->next; 
  }
 cout <<"\n\n";
}

void display(struct book *i)
{
    cout << "\n Код УДК: " << i->number;
    cout << "\n Название книги: " << i->title;
    cout << "\n Автор: " << i->author;
    cout << "\n Год издания: " << i->year;
    cout << "\n Количество книг: " << i->amount;

   cout << "\n";
}

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
