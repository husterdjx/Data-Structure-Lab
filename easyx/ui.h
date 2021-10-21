#include<string.h>
#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define func_init_window(x,y) concat(concat(func_init_window_,x)_,y)()
#define func(x,y,a) concat(func_,concat(x,concat(_,y)))(a)
#define true 1
#define false 0
#define MAX 100
#define ADD 1
#define SUB 0
#define ESC 27

//LinkedList
typedef struct Node *PtrToNode;

struct Node {
	double Coefficient;
	double Exponent;
	PtrToNode Next;
	PtrToNode Previous;
};

typedef PtrToNode Polynomial;

//func_1.c
void func_polynomial(Polynomial, Polynomial, int);
void func_init_window_polynomial_first(void);
void func_init_window_polynomial_second(void);
Polynomial InitPoly(double[], int);
void func_polynomial_ShowList(Polynomial list);
void func_polynomial_ShowListinReverse(Polynomial list);
int func_polynomial_choose_addorsub();
void func_polynomial_neglist(Polynomial);

//ui.c
void panic(const char*);

