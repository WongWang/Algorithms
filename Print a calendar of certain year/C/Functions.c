#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "Calendar.h"

void gotoxy(int x, int y)//定义函数：移动光标至(x, y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

int get_date(int* year, int* month, int* day)//读取日期，以指针形式将读取到的信息写入Calendar.c中的year, month和day变量中
{
	if (scanf("%d-%d-%d", year, month, day) != 3)//检测是否以"年-月-日"的形式成功读取三个数，若读取未成功，打印图案
	{
		printf("Date must be entered in form like 2020-01-01");
		return 1;//日期格式不正确return 1
	}
	if (*year < MIN_YEAR || *year > MAX_YEAR)//检测日期是否超出范围，若超出，打印图案
	{
		//print_image();
		return 1;//年份超出指定范围return 1
	}
	return 0;//日期符合要求return 0
}

void print_line(void)//打印一条长为LINE_LENGTH的线
{
	for (int i = 0; i < LINE_LENGTH; i++)
		printf("-");
	printf("\n");
}

void print_header(int year)//打印日历开头
{
	print_line();
	gotoxy((LINE_LENGTH - strlen("Calendar of Year yyyy")) / 2, 2);//在第2行居中打印
	printf("Calendar of Year %d\n", year);
}

int day_cal(int year, int month)//计算每月第一天为星期几（返回结果为0-6）
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

void calendar(int year, int group)//打印一组（三个月）日历中的数字部分，group为行数，从0到3
{
	bool leap_year;
	const int Day[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//一年每个月天数

	if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)//计算是否为闰年
		leap_year = true;
	else
		leap_year = false;

	for (int position = 0; position < 3; position++)//循环三次，分别打印三个月日历
	{
		int day;
		day = day_cal(year, (position + 1) + group * 3);//计算即将打印的月第一天为星期几
		for (int j = 0; j < day; j++)//将光标移至即将打印的月第一天的位置
			printf("    ");
		printf("   1");//打印第1天
		for (int j = 2, line = 0; j <= Day[position + group * 3] + (group == 0 && position == 1 && leap_year); j++)//打印这个月后面的天数，循环次数等于这个月天数
		{
			day++;//每打印一天day就+1
			if (day == 7)//当每次打印完周六，即将打印周日时
			{
				day = 0;//重置day为0，即回到周日
				line++;//行数line+1，统计已经打印了几行
				switch (position % 3)//换行，移动光标至下一行开头
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
			printf("%4d", j);//打印4字符宽度的日期
		}
		gotoxy((position + 1) * 31, 7 + 10 * group);//一个月打印完成，将光标移动到下个月第一行开头
	}
}

void print_form1(int year)//打印日历前两组的框架部分（1-6月）
{
	int adjust = ((LINE_LENGTH / 3) - (strlen("Jan"))) / 2;//计算将月份名居中需要多少个空格，将结果赋值给adjust
	for (int group = 0; group < 2; group++)//循环两次，分别打印两组的框架
	{
		print_line();
		printf("\n");
		print_line();
		printf(" Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat\n");//打印一组中三个月星期名
		gotoxy(adjust, 4 + group * 10);//回到上面空出的行，按adjust居中，准备打印月份名
		switch (group)//打印三个月月份名称
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
		gotoxy(0, 13 + group * 11);//移动到下一组开头
	}
}

void print_form2(int year)//同上，这次打印后两组的框架（7-12月）
{
	int adjust = ((LINE_LENGTH / 3) - (strlen("Jan"))) / 2;
	for (int group = 2; group < 4; group++)
	{
		print_line();
		printf("\n");
		print_line();
		printf(" Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat\n");
		gotoxy(adjust, 4 + group * 10);
		switch (group)//打印月份名称
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

void quote_the_day(int year, int month, int day)//在输入日期两侧加星号
{
	int first_day, x, y, x_adjust, y_adjust;
	first_day = day_cal(year, month);//计算输入日期对应的月第一天是星期几

	x = ((month - 1) % 3) * (LINE_LENGTH / 3) + 1;//计算输入的月份第一行开头横坐标
	y = 7 + ((month - 1) / 3) * 10;//计算输入的月份第一行开头纵坐标
	x_adjust = (((day + first_day) - 1) % 7) * 4;//计算从这个月第一行开头将横坐标移动到输入日期左侧需要的字符数
	y_adjust = (((day + first_day) - 1) / 7);//计算从这个月第一行开头将横坐标移动到输入日期左侧需要移动的字符数
	if ((month - 1) % 3 == 1 || (month - 1) % 3 == 2)//每行第一个月以一个空格开头，而后两个月以两个空格开头，如果输入的月是第二列的月份，将横坐标向右移动一个字符
		x_adjust++;
	if ((month - 1) % 3 == 2)//如果输入的月是第三列的月份，将横坐标再向右移动一个字符
		x_adjust++;
	gotoxy(x + x_adjust, y + y_adjust);//移动到输入日期左侧
	printf("*");
	gotoxy(x + x_adjust + 3, y + y_adjust);//移动到输入日期右侧
	printf("*");
}