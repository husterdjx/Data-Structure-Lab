#include<string.h>
#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define func_init_window(x,y) concat(concat(func_init_window_,x)_,y)();
#define true 1
#define false 0
#define MAX 100
//LinkedList
typedef struct Node *PtrToNode;

struct Node {
	float Coefficient;
	float Exponent;
	PtrToNode Next;
	PtrToNode Previous;
};

typedef PtrToNode Polynomial;
//func
int func_polynomial(Polynomial, Polynomial);
void func_init_window_polynomial_first(void);
void func_init_window_polynomial_second(void);
Polynomial InitPoly(float[], int);

//ui.c
void panic(const char*);

#define ESC 27
