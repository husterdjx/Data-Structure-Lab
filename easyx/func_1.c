#include<stdio.h>
#include<stdlib.h>
#include "ui.h"

void InitHeader(Polynomial list) {
	/*初始化头结点*/
	list->Next = NULL;
	list->Previous = NULL;
	list->Coefficient = 0;
	list->Exponent = -100;
}

void InitNode(PtrToNode node) {
	/*初始化结点Node*/
	node->Previous = NULL;
	node->Next = NULL;
}

int Poly_is_empty(Polynomial list) {
	/*判断多项式链表是否为空，传入参数为链表头结点指针，若为空返回true，否则返回false*/
	if (list->Next == NULL) return true;
	else return false;
}

void Delete_List_Zero(Polynomial list) {
	/*删除链表中系数为0的结点，传入参数为多项式头结点指针list*/
	PtrToNode now = list->Next;
	PtrToNode next;
	while (now != NULL) {
		next = now->Next;
		if (!now->Coefficient) {
			if(now->Next!=NULL) now->Next->Previous = now->Previous;
			now->Previous->Next = now->Next;
			free(now);
		}
		now = next;
	}
}

void NodeAdd(Polynomial list, PtrToNode elem) {
	/*向list多项式链表中添加结点elem，输入参数为多项式头结点指针list和多项式结点指针elem*/
	PtrToNode i = list;
	while (elem->Exponent > i->Exponent&&i->Next!=NULL) {//找到插入位置
		i = i->Next;
	}
	if (i->Exponent == elem->Exponent) {//若已经存在同指数项则复用
		i->Coefficient += elem->Coefficient;
		free(elem);
	}
	else if(elem->Exponent<i->Exponent){//正常插入位置
		elem->Next = i;
		elem->Previous = i->Previous;
		i->Previous->Next = elem;
		i->Previous = elem;
	}
	else {//找到末尾
		i->Next = elem;
		elem->Previous = i;
		elem->Next = NULL;
	}
	//printf("add: %fx^%f\n", elem->Coefficient, elem->Exponent);
}
void parse(Polynomial list, double buffer[],int n) {
	/*解析数组buffer中的系数与指数对到list多项式链表中，n为系数与指数总数。传入参数为多项式头结点指针list，系数指数数组buffer，系数指数个数n*/
	double coefficient;
	double exponent;
	PtrToNode ptr;
	for (int i = 0; i < n; i+=2) {
		coefficient = buffer[i];
		exponent = buffer[i + 1];
		if( (ptr = (PtrToNode)malloc(sizeof(struct Node))) == NULL) panic("OOM when parse!"),exit(1); //OOM情况
		InitNode(ptr);//初始化结点
		ptr->Coefficient = coefficient, ptr->Exponent = exponent;//赋值
		NodeAdd(list, ptr);//添加到链表中
	}
}

/*int parse(Polynomial list, char* buffer) {
	int coefficient = 0;
	int exponent = 0;

	int x_flag = 0;
	int neg_flag = 0;
	int point_flag = 0;
	int exp_flag = 0;

	char* c=buffer;
	while (*(c++) != '\0') {
		if (*c == 'x') {
			x_flag = 1;
			if (coefficient == 0) {
				coefficient = 1;
			}
			else if(neg_flag){
				coefficient = (-coefficient);
			}
			continue;
		}
		if (*c == '-') {
			neg_flag = 1;
			continue;
		}
		if (*c == '^') {
			exp_flag = 1;
			continue;
		}
		if (*c == '.') {
			point_flag = 1;
			continue;
		}

		if (*c >= '0'&&*c <= '9'&& !x_flag) {
			coefficient *= 10;
			coefficient += (*c) - '0';
		}
		else if (*c >= '0'&&*c <= '9' && exp_flag) {
			exponent *= 10;
			exponent += (*c) - '0';
		}
		else if (*c == '+' || *c == '-') {
			struct Node elem = { -coefficient,exponent,NULL,NULL };
			coefficient = 0, exponent = 0, flag = 0;
			NodeAdd(list, &elem);
		}
		else {
			continue;
		}
	}
	return 0;
}*/

void func_polynomial_ShowList(Polynomial list) {
	/*按指数升序输出list多项式链表到stdout，传入参数为多项式头结点指针list*/
	Delete_List_Zero(list);
	if (list->Next == NULL) {//链表为空
		printf("0");
	}
	else {
		PtrToNode i = list->Next;
		int n=0;
		while (i != NULL) {
			n++;
			i = i->Next;
		}
		printf("%d",n);
		i = list->Next;
		while (i != NULL) {
			if (i->Coefficient - ((int)i->Coefficient) == 0) printf(",%.0f", i->Coefficient);
			else printf(",%.1f", i->Coefficient);
			if (i->Exponent - ((int)i->Exponent) == 0) printf(",%.0f", i->Exponent);
			else printf(",%.1f", i->Exponent);
			i = i->Next;
		}
		printf("\n");
	}
}

void func_polynomial_ShowListinReverse(Polynomial list) {
	/*按指数降序输出list多项式链表到stdout，传入参数为多项式头结点指针list*/
	Delete_List_Zero(list);
	if (list->Next == NULL) {//链表为空
		printf("0");
	}
	else {
		PtrToNode i = list,end;
		while (i->Next != NULL) {
			i = i->Next;
		}
		end = i;
		printf("(");
		while (i != list) {//进行输出，注意特殊情况处理
			if (i->Coefficient > 0 && i!=end) printf("+");
			if (i->Exponent == 0) printf("%g", i->Coefficient);//常数项输出
			else if (i->Coefficient == 1 && i->Exponent != 1 ) printf("x^%.0f", i->Exponent);//系数为1
			else if (i->Coefficient == -1 && i->Exponent != 1) printf("-x^%.0f", i->Exponent);//系数为-1
			else if (i->Coefficient == 1 && i->Exponent == 1) printf("x");//系指数为1
			else if (i->Coefficient == -1 && i->Exponent == 1) printf("-x");//系数为-1，指数为1
			else if ((i->Coefficient) - (int)(i->Coefficient) == 0 && i->Exponent != 1) printf("%.0fx^%.0f", i->Coefficient, i->Exponent);//系指数均为整数
			else if ((i->Coefficient) - (int)(i->Coefficient) == 0 && i->Exponent == 1) printf("%.0fx", i->Coefficient);//系数为整数，指数为1
			else printf("%.1fx^%.0f", i->Coefficient, i->Exponent);//系数为小数，指数不为特殊情况
			i = i->Previous;
		}
		printf(")");
	}
}

Polynomial InitPoly(double buffer[], int n) {
	/*从输入的buffer数组构造多项式链表，传入参数为系数指数数组buffer，系数指数数目n*/
	Polynomial list = (Polynomial)malloc(sizeof(struct Node));
	InitHeader(list);

	parse(list, buffer, n);

	return list;
}

void func_polynomial(Polynomial list1, Polynomial list2, int x) {
	/*将list1和list2两个多项式链表相加，覆盖list1。传入参数为多项式头结点指针list1和list2*/
	printf("相加后结果为：\n");
	func_polynomial_ShowListinReverse(list1);//自然输出
	if (x == ADD) printf("+");
	else printf("-");
	func_polynomial_ShowListinReverse(list2);

	if(x==SUB) func(polynomial, neglist, list2);
	PtrToNode now = list2->Next;
	PtrToNode next;
	while (now != NULL) {
		next = now->Next;
		NodeAdd(list1, now);
		now = next;
	}
	printf("=");
	func_polynomial_ShowListinReverse(list1);//自然输出
	printf("\n");
	func_polynomial_ShowList(list1);//整数输出
	system("pause");
}


void func_init_window_polynomial_first(void) {
	//输入第一个多项式的输出显示
	system("cls");
	system("title 一元稀疏多项式");
	printf("******************************\nWelcome to this func!\n******************************\n\n请输入需要计算的第一个一元稀疏多项式：\n请输入多项式的项数:");
	return ;
}

void func_init_window_polynomial_second(void) {
	//输入第二个多项式的输出显示
	printf("\n请输入需要计算的第二个一元稀疏多项式：\n");
	printf("请输入多项式的项数:");
	return;
}

int func_polynomial_choose_addorsub(void) {
	/*判断是加法还是减法运算*/
	printf("\n");
	printf("请输入是加法还是减法：");
	char choose;
	while(choose = getchar()) {
		if (choose == '+') return ADD;
		if (choose == '-') return SUB;
		panic("Illgeal input!"); 
	}
	return ADD;
}

void func_polynomial_neglist(Polynomial list) {
	/*实现链表系数负置，传入参数为多项式头结点指针list*/
	PtrToNode i = list->Next;
	while (i != NULL) {
		i->Coefficient = (-i->Coefficient);
		i = i->Next;
	}
}
