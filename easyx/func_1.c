#include<stdio.h>
#include<stdlib.h>
#include "ui.h"

void InitHeader(Polynomial list) {
	/*��ʼ��ͷ���*/
	list->Next = NULL;
	list->Previous = NULL;
	list->Coefficient = 0;
	list->Exponent = -100;
}

void InitNode(PtrToNode node) {
	/*��ʼ�����Node*/
	node->Previous = NULL;
	node->Next = NULL;
}

int Poly_is_empty(Polynomial list) {
	/*�ж϶���ʽ�����Ƿ�Ϊ�գ��������Ϊ����ͷ���ָ�룬��Ϊ�շ���true�����򷵻�false*/
	if (list->Next == NULL) return true;
	else return false;
}

void Delete_List_Zero(Polynomial list) {
	/*ɾ��������ϵ��Ϊ0�Ľ�㣬�������Ϊ����ʽͷ���ָ��list*/
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
	/*��list����ʽ��������ӽ��elem���������Ϊ����ʽͷ���ָ��list�Ͷ���ʽ���ָ��elem*/
	PtrToNode i = list;
	while (elem->Exponent > i->Exponent&&i->Next!=NULL) {//�ҵ�����λ��
		i = i->Next;
	}
	if (i->Exponent == elem->Exponent) {//���Ѿ�����ָͬ��������
		i->Coefficient += elem->Coefficient;
		free(elem);
	}
	else if(elem->Exponent<i->Exponent){//��������λ��
		elem->Next = i;
		elem->Previous = i->Previous;
		i->Previous->Next = elem;
		i->Previous = elem;
	}
	else {//�ҵ�ĩβ
		i->Next = elem;
		elem->Previous = i;
		elem->Next = NULL;
	}
	//printf("add: %fx^%f\n", elem->Coefficient, elem->Exponent);
}
void parse(Polynomial list, double buffer[],int n) {
	/*��������buffer�е�ϵ����ָ���Ե�list����ʽ�����У�nΪϵ����ָ���������������Ϊ����ʽͷ���ָ��list��ϵ��ָ������buffer��ϵ��ָ������n*/
	double coefficient;
	double exponent;
	PtrToNode ptr;
	for (int i = 0; i < n; i+=2) {
		coefficient = buffer[i];
		exponent = buffer[i + 1];
		if( (ptr = (PtrToNode)malloc(sizeof(struct Node))) == NULL) panic("OOM when parse!"),exit(1); //OOM���
		InitNode(ptr);//��ʼ�����
		ptr->Coefficient = coefficient, ptr->Exponent = exponent;//��ֵ
		NodeAdd(list, ptr);//��ӵ�������
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
	/*��ָ���������list����ʽ����stdout���������Ϊ����ʽͷ���ָ��list*/
	Delete_List_Zero(list);
	if (list->Next == NULL) {//����Ϊ��
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
	/*��ָ���������list����ʽ����stdout���������Ϊ����ʽͷ���ָ��list*/
	Delete_List_Zero(list);
	if (list->Next == NULL) {//����Ϊ��
		printf("0");
	}
	else {
		PtrToNode i = list,end;
		while (i->Next != NULL) {
			i = i->Next;
		}
		end = i;
		printf("(");
		while (i != list) {//���������ע�������������
			if (i->Coefficient > 0 && i!=end) printf("+");
			if (i->Exponent == 0) printf("%g", i->Coefficient);//���������
			else if (i->Coefficient == 1 && i->Exponent != 1 ) printf("x^%.0f", i->Exponent);//ϵ��Ϊ1
			else if (i->Coefficient == -1 && i->Exponent != 1) printf("-x^%.0f", i->Exponent);//ϵ��Ϊ-1
			else if (i->Coefficient == 1 && i->Exponent == 1) printf("x");//ϵָ��Ϊ1
			else if (i->Coefficient == -1 && i->Exponent == 1) printf("-x");//ϵ��Ϊ-1��ָ��Ϊ1
			else if ((i->Coefficient) - (int)(i->Coefficient) == 0 && i->Exponent != 1) printf("%.0fx^%.0f", i->Coefficient, i->Exponent);//ϵָ����Ϊ����
			else if ((i->Coefficient) - (int)(i->Coefficient) == 0 && i->Exponent == 1) printf("%.0fx", i->Coefficient);//ϵ��Ϊ������ָ��Ϊ1
			else printf("%.1fx^%.0f", i->Coefficient, i->Exponent);//ϵ��ΪС����ָ����Ϊ�������
			i = i->Previous;
		}
		printf(")");
	}
}

Polynomial InitPoly(double buffer[], int n) {
	/*�������buffer���鹹�����ʽ�����������Ϊϵ��ָ������buffer��ϵ��ָ����Ŀn*/
	Polynomial list = (Polynomial)malloc(sizeof(struct Node));
	InitHeader(list);

	parse(list, buffer, n);

	return list;
}

void func_polynomial(Polynomial list1, Polynomial list2, int x) {
	/*��list1��list2��������ʽ������ӣ�����list1���������Ϊ����ʽͷ���ָ��list1��list2*/
	printf("��Ӻ���Ϊ��\n");
	func_polynomial_ShowListinReverse(list1);//��Ȼ���
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
	func_polynomial_ShowListinReverse(list1);//��Ȼ���
	printf("\n");
	func_polynomial_ShowList(list1);//�������
	system("pause");
}


void func_init_window_polynomial_first(void) {
	//�����һ������ʽ�������ʾ
	system("cls");
	system("title һԪϡ�����ʽ");
	printf("******************************\nWelcome to this func!\n******************************\n\n��������Ҫ����ĵ�һ��һԪϡ�����ʽ��\n���������ʽ������:");
	return ;
}

void func_init_window_polynomial_second(void) {
	//����ڶ�������ʽ�������ʾ
	printf("\n��������Ҫ����ĵڶ���һԪϡ�����ʽ��\n");
	printf("���������ʽ������:");
	return;
}

int func_polynomial_choose_addorsub(void) {
	/*�ж��Ǽӷ����Ǽ�������*/
	printf("\n");
	printf("�������Ǽӷ����Ǽ�����");
	char choose;
	while(choose = getchar()) {
		if (choose == '+') return ADD;
		if (choose == '-') return SUB;
		panic("Illgeal input!"); 
	}
	return ADD;
}

void func_polynomial_neglist(Polynomial list) {
	/*ʵ������ϵ�����ã��������Ϊ����ʽͷ���ָ��list*/
	PtrToNode i = list->Next;
	while (i != NULL) {
		i->Coefficient = (-i->Coefficient);
		i = i->Next;
	}
}
