#include <graphics.h>
#include<iostream>
#include<conio.h>
using namespace std;

extern "C" {
#include "ui.h"
}

double buffer[MAX];

void SetWindowStyle() {
	/*初始化窗口*/
	system("title 数据结构实验");
	system("color f0");
	system("mode con cols=60 lines=20");
}

void Welcome() {
	/*显示Welcome界面*/
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
	/*显示菜单栏目*/
	/*返回选择的菜单表数字*/
	char option = 0;

	system("cls");
	cout << "***************菜单***************" << endl;
	cout << "1. 一元稀疏多项式" << endl;
	cout << "2. 一元稀疏多项式（字符串处理）" << endl;
	cout << "3. Updating..." << endl;
	cout << endl;

	while (1) {
		cout << "请输入需要查询的功能：";
		option = _getch();

		if (option == ESC) {	//输入ESC直接退出
			cout << endl << "have a nice day!" << endl;
			Sleep(1);
			exit(0);
		}
		else if (option == '1') {	//输入1则向main函数返回对应序号
			cout << '1';
			return 1;
		}
		else if (option == '2') {	//输入2则向main函数返回对应序号
			cout << '2';
			return 2;
		}
		else {	//输入非ESC和已实现的序号则panic
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
				func_init_window(polynomial,first);//显示输入第一个多项式的输入准备
				//输入第一个多项式
				int i = 0;
				while (cin.peek() != '\n') {
					cin >> buffer[i++];
				}
				while (getchar() != '\n');
				Polynomial list1 = InitPoly(buffer,i);//利用输入写入链表
				func(polynomial, ShowListinReverse, list1);//自然书写显示多项式

				func_init_window(polynomial, second);//显示输入第二个多项式的输入准备
				i = 0;

				//输入第二个多项式
				while (cin.peek() != '\n') {
					cin >> buffer[i++];
				}
				while (getchar() != '\n');
				Polynomial list2 = InitPoly(buffer, i);
				func(polynomial,ShowListinReverse,list2);

				int x;
				if (func(polynomial,choose_addorsub) == 0) {//接受信号，判断加减法
					x = SUB;
				}
				else x = ADD;

				func_polynomial(list1, list2, x);//执行相加功能

				while (getchar() != '\n');//清除缓冲区额外换行符

				break;
			}
			case 2: {
				func_init_window(polynomial, first);
				float coefficient = 0;
				int exponent = 0;
				int n, i = 0;
				scanf_s("%d", &n);
				//printf("n:%d\n", n);
				while (n--) {//读入字符串
					scanf_s("%fx^%d", &coefficient, &exponent);
					buffer[i] = coefficient;
					buffer[i + 1] = exponent;
					coefficient = 0, exponent = 0;
					i+=2;
				}

				while (getchar() != '\n');
				Polynomial list1 = InitPoly(buffer, i);//利用输入写入链表
				func(polynomial, ShowListinReverse, list1);//自然书写显示多项式

				func_init_window(polynomial, second);//显示输入第二个多项式的输入准备
				i = 0;

				//输入第二个多项式
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
				if (func(polynomial, choose_addorsub) == 0) {//接受信号，判断加减法
					func(polynomial, neglist, list2);
					x = SUB;
				}
				else x = ADD;
				func_polynomial(list1, list2, x);//执行相加功能

				while (getchar() != '\n');//清除缓冲区额外换行符
				break;
			}
			default: {
				break;
			}
		}
	}
	return 0;
}