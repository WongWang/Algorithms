#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "Calendar.h"

void gotoxy(int x, int y)//���庯�����ƶ������(x, y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

int get_date(int* year, int* month, int* day)//��ȡ���ڣ���ָ����ʽ����ȡ������Ϣд��Calendar.c�е�year, month��day������
{
	if (scanf("%d-%d-%d", year, month, day) != 3)//����Ƿ���"��-��-��"����ʽ�ɹ���ȡ������������ȡδ�ɹ�����ӡͼ��
	{
		printf("Date must be entered in form like 2020-01-01");
		return 1;//���ڸ�ʽ����ȷreturn 1
	}
	if (*year < MIN_YEAR || *year > MAX_YEAR)//��������Ƿ񳬳���Χ������������ӡͼ��
	{
		//print_image();
		return 1;//��ݳ���ָ����Χreturn 1
	}
	return 0;//���ڷ���Ҫ��return 0
}

void print_line(void)//��ӡһ����ΪLINE_LENGTH����
{
	for (int i = 0; i < LINE_LENGTH; i++)
		printf("-");
	printf("\n");
}

void print_header(int year)//��ӡ������ͷ
{
	print_line();
	gotoxy((LINE_LENGTH - strlen("Calendar of Year yyyy")) / 2, 2);//�ڵ�2�о��д�ӡ
	printf("Calendar of Year %d\n", year);
}

int day_cal(int year, int month)//����ÿ�µ�һ��Ϊ���ڼ������ؽ��Ϊ0-6��
{
	int adjust1, adjust2, adjust3, day;

	if (month < 3)//A magical algorithm
	{
		adjust1 = year - 1;
		adjust2 = month + 13;
	}
	else
	{
		adjust1 = year;
		adjust2 = month + 1;
	}
	adjust3 = 1461 * adjust1 / 4 + 153 * adjust2 / 5 + 1;
	day = (adjust3 - 621049) % 7;

	return day;
}

void calendar(int year, int group)//��ӡһ�飨�����£������е����ֲ��֣�groupΪ��������0��3
{
	bool leap_year;
	const int Day[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//һ��ÿ��������

	if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)//�����Ƿ�Ϊ����
		leap_year = true;
	else
		leap_year = false;

	for (int position = 0; position < 3; position++)//ѭ�����Σ��ֱ��ӡ����������
	{
		int day;
		day = day_cal(year, (position + 1) + group * 3);//���㼴����ӡ���µ�һ��Ϊ���ڼ�
		for (int j = 0; j < day; j++)//���������������ӡ���µ�һ���λ��
			printf("    ");
		printf("   1");//��ӡ��1��
		for (int j = 2, line = 0; j <= Day[position + group * 3] + (group == 0 && position == 1 && leap_year); j++)//��ӡ����º����������ѭ�������������������
		{
			day++;//ÿ��ӡһ��day��+1
			if (day == 7)//��ÿ�δ�ӡ��������������ӡ����ʱ
			{
				day = 0;//����dayΪ0�����ص�����
				line++;//����line+1��ͳ���Ѿ���ӡ�˼���
				switch (position % 3)//���У��ƶ��������һ�п�ͷ
				{
				case 0:
					gotoxy(0, 7 + line + 10 * group);
					break;
				case 1:
					gotoxy(31, 7 + line + 10 * group);
					break;
				case 2:
					gotoxy(62, 7 + line + 10 * group);
					break;
				}
			}
			printf("%4d", j);//��ӡ4�ַ���ȵ�����
		}
		gotoxy((position + 1) * 31, 7 + 10 * group);//һ���´�ӡ��ɣ�������ƶ����¸��µ�һ�п�ͷ
	}
}

void print_form1(int year)//��ӡ����ǰ����Ŀ�ܲ��֣�1-6�£�
{
	int adjust = ((LINE_LENGTH / 3) - (strlen("Jan"))) / 2;//���㽫�·���������Ҫ���ٸ��ո񣬽������ֵ��adjust
	for (int group = 0; group < 2; group++)//ѭ�����Σ��ֱ��ӡ����Ŀ��
	{
		print_line();
		printf("\n");
		print_line();
		printf(" Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat\n");//��ӡһ����������������
		gotoxy(adjust, 4 + group * 10);//�ص�����ճ����У���adjust���У�׼����ӡ�·���
		switch (group)//��ӡ�������·�����
		{
		case 0: 
			printf("Jan");
			gotoxy(((LINE_LENGTH / 3) + 1) + adjust, 4 + group * 10);
			printf("Feb");
			gotoxy(((LINE_LENGTH / 3) + 1) * 2 + adjust, 4 + group * 10);
			printf("Mar");
			break;
		case 1: 
			printf("Apr");
			gotoxy(((LINE_LENGTH / 3) + 1) + adjust, 4 + group * 10);
			printf("May");
			gotoxy(((LINE_LENGTH / 3) + 1) * 2 + adjust, 4 + group * 10);
			printf("Jun");
			break;
		}
		gotoxy(0, 13 + group * 11);//�ƶ�����һ�鿪ͷ
	}
}

void print_form2(int year)//ͬ�ϣ���δ�ӡ������Ŀ�ܣ�7-12�£�
{
	int adjust = ((LINE_LENGTH / 3) - (strlen("Jan"))) / 2;
	for (int group = 2; group < 4; group++)
	{
		print_line();
		printf("\n");
		print_line();
		printf(" Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat\n");
		gotoxy(adjust, 4 + group * 10);
		switch (group)//��ӡ�·�����
		{
		case 2:
			printf("Jul");
			gotoxy(((LINE_LENGTH / 3) + 1) + adjust, 4 + group * 10);
			printf("Aug");
			gotoxy(((LINE_LENGTH / 3) + 1) * 2 + adjust, 4 + group * 10);
			printf("Sep");
			break;
		case 3:
			printf("Oct");
			gotoxy(((LINE_LENGTH / 3) + 1) + adjust, 4 + group * 10);
			printf("Nov");
			gotoxy(((LINE_LENGTH / 3) + 1) * 2 + adjust, 4 + group * 10);
			printf("Dec");
			break;
		}
		gotoxy(0, 33);
	}
}

void quote_the_day(int year, int month, int day)//����������������Ǻ�
{
	int first_day, x, y, x_adjust, y_adjust;
	first_day = day_cal(year, month);//�����������ڶ�Ӧ���µ�һ�������ڼ�

	x = ((month - 1) % 3) * (LINE_LENGTH / 3) + 1;//����������·ݵ�һ�п�ͷ������
	y = 7 + ((month - 1) / 3) * 10;//����������·ݵ�һ�п�ͷ������
	x_adjust = (((day + first_day) - 1) % 7) * 4;//���������µ�һ�п�ͷ���������ƶ����������������Ҫ���ַ���
	y_adjust = (((day + first_day) - 1) / 7);//���������µ�һ�п�ͷ���������ƶ����������������Ҫ�ƶ����ַ���
	if ((month - 1) % 3 == 1 || (month - 1) % 3 == 2)//ÿ�е�һ������һ���ո�ͷ�������������������ո�ͷ�������������ǵڶ��е��·ݣ��������������ƶ�һ���ַ�
		x_adjust++;
	if ((month - 1) % 3 == 2)//�����������ǵ����е��·ݣ����������������ƶ�һ���ַ�
		x_adjust++;
	gotoxy(x + x_adjust, y + y_adjust);//�ƶ��������������
	printf("*");
	gotoxy(x + x_adjust + 3, y + y_adjust);//�ƶ������������Ҳ�
	printf("*");
}