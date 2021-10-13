#include<stdio.h>
#include<stdlib.h>
#include "ui.h"

void InitHeader(Polynomial list) {
	list->Next = NULL;
	list->Previous = NULL;
	list->Coefficient = 0;
	list->Exponent = -100;
}

void InitNode(PtrToNode node) {
	node->Previous = NULL;
	node->Next = NULL;
}
int Poly_is_empty(Polynomial list) {
	if (list->Next == NULL) return true;
	else return false;
}

void Delete_List_Zero() {

}
void NodeAdd(Polynomial list, PtrToNode elem) {
	PtrToNode i = list;
	while (elem->Exponent > i->Exponent&&i->Next!=NULL) {
		i = i->Next;
	}
	if (i->Exponent == elem->Exponent) {
		i->Coefficient += elem->Coefficient;
		free(elem);
	}
	else if(elem->Exponent<i->Exponent){
		elem->Next = i;
		elem->Previous = i->Previous;
		i->Previous->Next = elem;
		i->Previous = elem;
	}
	else {
		i->Next = elem;
		elem->Previous = i;
		elem->Next = NULL;
	}
	//printf("add: %fx^%f\n", elem->Coefficient, elem->Exponent);
}
void parse(Polynomial list, float buffer[],int n) {
	//printf("parse:即将解析%d个数", n);
	float coefficient;
	float exponent;
	PtrToNode ptr;
	for (int i = 0; i < n; i+=2) {
		coefficient = buffer[i];
		exponent = buffer[i + 1];
		//printf("已解析：%fx^%f\n", coefficient, exponent);
		if( (ptr = (PtrToNode)malloc(sizeof(struct Node))) == NULL) panic("OOM when parse!"),exit(1);
		InitNode(ptr);
		ptr->Coefficient = coefficient, ptr->Exponent = exponent;
		NodeAdd(list, ptr);
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

void ShowList(Polynomial list) {
	if (list->Next == NULL) {
		printf("The list is empty!\n");
	}
	else {
		PtrToNode i = list->Next;
		printf("ShowList:\n");
		while (i != NULL) {
			printf("系数：%f，指数：%f\n", i->Coefficient, i->Exponent);
			i = i->Next;
		}
	}
}

Polynomial InitPoly(float buffer[], int n) {
	Polynomial list = (Polynomial)malloc(sizeof(struct Node));
	InitHeader(list);

	parse(list, buffer, n);

	ShowList(list);

	return list;
}
int func_polynomial(Polynomial list1, Polynomial list2) {
	PtrToNode now = list2->Next;
	PtrToNode next;
	while (now != NULL) {
		next = now->Next;
		NodeAdd(list1, now);
		now = next;
	}
	printf("相加后结果为：\n");
	ShowList(list1);
	system("pause");
	return 0;
}


void func_init_window_polynomial_first(void) {
	system("cls");
	system("title 一元稀疏多项式");
	printf("Welcome to this func!\n******************************\n请输入需要计算的第一个一元稀疏多项式：");
	return ;
}

void func_init_window_polynomial_second(void) {
	printf("请输入需要计算的第二个一元稀疏多项式：");
	return;
}