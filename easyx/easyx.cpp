#include <graphics.h>
#include<iostream>
#include<conio.h>
using namespace std;

extern "C" {
#include "ui.h"
}

float buffer[MAX];

void SetWindowStyle() {
	system("title ���ݽṹʵ��");
	system("color f0");
	system("mode con cols=60 lines=20");
}

void Welcome() {
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
	char option = 0;

	system("cls");
	cout << "***************�˵�***************" << endl;
	cout << "1. һԪϡ�����ʽ" << endl;
	cout << "2.Updateing" << endl;
	cout << endl;

	while (1) {
		cout << "��������Ҫ��ѯ�Ĺ��ܣ�";
		option = _getch();

		if (option == ESC) {	//����ESCֱ���˳�
			cout << "have a nice day!" << endl;
			exit(0);
		}
		else if (option == '1') {	//����1����main�������ض�Ӧ���
			return 1;
		}
		else {	//�����ESC����ʵ�ֵ������panic
			cout << option<<endl;
			panic("illegal input!");
		}
	}
}
int main()
{
	SetWindowStyle();
	// Welcome
	Welcome();

	bool flag_out = 0;
	while (true) {
		switch (ShowMenu()) {
			case 1: {
				func_init_window(polynomial,first);
				int i = 0;
				while (cin.peek() != '\n') {
					cin >> buffer[i++];
				}

				//system("pause");
				cin.ignore(MAX,'\n');
				Polynomial list1 = InitPoly(buffer,i);

				func_init_window(polynomial, second);
				i = 0;


				while (cin.peek() != '\n') {
					cin >> buffer[i++];
				}
				//system("pause");

				Polynomial list2 = InitPoly(buffer, i);

				func_polynomial(list1, list2);
				cin.ignore(MAX, '\n');

				break;
			}
			default: {
				break;
			}
		}
	}
	return 0;
}