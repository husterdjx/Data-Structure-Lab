#include <graphics.h>
#include<iostream>
#include<conio.h>
using namespace std;

extern "C" {
#include "ui.h"
}

double buffer[MAX];

void SetWindowStyle() {
	/*��ʼ������*/
	system("title ���ݽṹʵ��");
	system("color f0");
	system("mode con cols=60 lines=20");
}

void Welcome() {
	/*��ʾWelcome����*/
	initgraph(640, 480, EW_SHOWCONSOLE);

	IMAGE bg;
	loadimage(&bg, _T("./Hustseals.png"));
	putimage(150, 50, &bg);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	settextstyle(&f);
	char wel_1[] = "WELCOME TO HERE!";
	char wel_2[] = "--by husterdjx";
	outtextxy(230, 350, wel_1);
	outtextxy(390, 370, wel_2);
	Sleep(2000);
	cleardevice();
	closegraph();
}

int ShowMenu() {
	/*��ʾ�˵���Ŀ*/
	/*����ѡ��Ĳ˵�������*/
	char option = 0;

	system("cls");
	cout << "***************�˵�***************" << endl;
	cout << "1. һԪϡ�����ʽ" << endl;
	cout << "2. һԪϡ�����ʽ���ַ�������" << endl;
	cout << "3. Updating..." << endl;
	cout << endl;

	while (1) {
		cout << "��������Ҫ��ѯ�Ĺ��ܣ�";
		option = _getch();

		if (option == ESC) {	//����ESCֱ���˳�
			cout << endl << "have a nice day!" << endl;
			Sleep(1);
			exit(0);
		}
		else if (option == '1') {	//����1����main�������ض�Ӧ���
			cout << '1';
			return 1;
		}
		else if (option == '2') {	//����2����main�������ض�Ӧ���
			cout << '2';
			return 2;
		}
		else {	//�����ESC����ʵ�ֵ������panic
			cout << option<<endl;
			panic("illegal input!");
		}
	}
}
int main()
{
	//init windows
	SetWindowStyle();
	// welcome
	Welcome();

	bool flag_out = 0;
	while (true) {
		switch (ShowMenu()) {
			case 1: {
				func_init_window(polynomial,first);//��ʾ�����һ������ʽ������׼��
				//�����һ������ʽ
				int i = 0;
				while (cin.peek() != '\n') {
					cin >> buffer[i++];
				}
				while (getchar() != '\n');
				Polynomial list1 = InitPoly(buffer,i);//��������д������
				func(polynomial, ShowListinReverse, list1);//��Ȼ��д��ʾ����ʽ

				func_init_window(polynomial, second);//��ʾ����ڶ�������ʽ������׼��
				i = 0;

				//����ڶ�������ʽ
				while (cin.peek() != '\n') {
					cin >> buffer[i++];
				}
				while (getchar() != '\n');
				Polynomial list2 = InitPoly(buffer, i);
				func(polynomial,ShowListinReverse,list2);

				int x;
				if (func(polynomial,choose_addorsub) == 0) {//�����źţ��жϼӼ���
					x = SUB;
				}
				else x = ADD;

				func_polynomial(list1, list2, x);//ִ����ӹ���

				while (getchar() != '\n');//������������⻻�з�

				break;
			}
			case 2: {
				func_init_window(polynomial, first);
				float coefficient = 0;
				int exponent = 0;
				int n, i = 0;
				scanf_s("%d", &n);
				//printf("n:%d\n", n);
				while (n--) {//�����ַ���
					scanf_s("%fx^%d", &coefficient, &exponent);
					buffer[i] = coefficient;
					buffer[i + 1] = exponent;
					coefficient = 0, exponent = 0;
					i+=2;
				}

				while (getchar() != '\n');
				Polynomial list1 = InitPoly(buffer, i);//��������д������
				func(polynomial, ShowListinReverse, list1);//��Ȼ��д��ʾ����ʽ

				func_init_window(polynomial, second);//��ʾ����ڶ�������ʽ������׼��
				i = 0;

				//����ڶ�������ʽ
				scanf_s("%d", &n);
				//printf("n:%d\n", n);
				while (n--) {
					scanf_s("%fx^%d", &coefficient, &exponent);
					buffer[i] = coefficient;
					buffer[i + 1] = exponent;
					i+=2;
				}
				while (getchar() != '\n');
				Polynomial list2 = InitPoly(buffer, i);
				func(polynomial, ShowListinReverse, list2);
				
				int x;
				if (func(polynomial, choose_addorsub) == 0) {//�����źţ��жϼӼ���
					func(polynomial, neglist, list2);
					x = SUB;
				}
				else x = ADD;
				func_polynomial(list1, list2, x);//ִ����ӹ���

				while (getchar() != '\n');//������������⻻�з�
				break;
			}
			default: {
				break;
			}
		}
	}
	return 0;
}