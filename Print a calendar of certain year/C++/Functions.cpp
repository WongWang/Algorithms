#include <iostream>
#include <iomanip>
#include <windows.h>
#include "Date.h"
#include "Calendar.h"

using std::cout;
using std::endl;
using std::setw;

void gotoxy(short x, short y)//定义函数：移动光标至(x, y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void print_line(void)//打印一条长为LINE_LENGTH的线
{
	for (int i = 0; i < LINE_LENGTH; i++)
		cout << '-';
	cout << endl;
}

void print_header(int year)//打印日历开头
{
	print_line();
	gotoxy((LINE_LENGTH - strlen("Calendar of Year yyyy")) / 2, 2);//在第2行居中打印
	cout << "Calendar of Year " << year << endl;
}

void print_form(int year)//打印日历前两组的框架部分（1-6月）
{
	int adjust = ((LINE_LENGTH / 3) - (strlen("Jan"))) / 2;//计算将月份名居中需要多少个空格，将结果赋值给adjust
	for (int group = 0; group < 4; group++)//循环两次，分别打印两组的框架
	{
		print_line();
		cout << endl;
		print_line();
		cout << " Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat    Sun Mon Tue Wed Thu Fri Sat" << endl;//打印一组中三个月星期名
		gotoxy(adjust, 4 + group * 10);//回到上面空出的行，按adjust居中，准备打印月份名
		switch (group)//打印三个月月份名称
		{
		case 0: 
			cout << "Jan";
			gotoxy(((LINE_LENGTH / 3) + 1) + adjust, 4 + group * 10);
			cout << "Feb";
			gotoxy(((LINE_LENGTH / 3) + 1) * 2 + adjust, 4 + group * 10);
			cout << "Mar";
			break;
		case 1: 
			cout << "Apr";
			gotoxy(((LINE_LENGTH / 3) + 1) + adjust, 4 + group * 10);
			cout << "May";
			gotoxy(((LINE_LENGTH / 3) + 1) * 2 + adjust, 4 + group * 10);
			cout << "Jun";
			break;
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
		gotoxy(0, 13 + group * 10);//移动到下一组开头
	}
}

void print_calendar(unsigned year)
{
    Date count;
    count.year = year;
    count.month = 1;
    count.day = 1;

    gotoxy(0, 7);
    int week = count.week();
    int line = 0;
    int row_position = (count.month-1) / 3;
    int column_position = (count.month - 1) % 3;
    int row_coordination = 7 + (row_position * 10);
    int column_coordination = column_position * 31;
    while (count.year == year)
    {
        for (int i = 0; i != week; ++i)
            cout << "    ";
        cout << "   1";
        ++count;
        ++week;
        while (count.day != 1)
        {
            if (week == 7)
            {
                week = 0;
                ++line;
                gotoxy(column_coordination, row_coordination + line);
            }
            cout << setw(4) << count.day;
            ++count;
            ++week;
        }
        row_position = (count.month-1) / 3;
        column_position = (count.month - 1) % 3;
        row_coordination = 7 + (row_position * 10);
        column_coordination = column_position * 31;
        gotoxy(column_coordination, row_coordination);
        line = 0;
        if (week == 7)
            week = 0;
    }  
}

void quote_the_day(Date day_input)
{
    int row_position = (day_input.month-1) / 3;
    int column_position = (day_input.month - 1) % 3;
    int row_coordination = 7 + (row_position * 10);
    int column_coordination = column_position * 31;
    int row_adjust = (((day_input.day + day_input.week()) - 1) / 7);//计算从这个月第一行开头将横坐标移动到输入日期左侧需要移动的字符数
    int column_adjust = (((day_input.day + day_input.week()) - 1) % 7) * 4;//计算从这个月第一行开头将横坐标移动到输入日期左侧需要的字符数
	gotoxy(column_coordination + column_adjust + 1, row_coordination + row_adjust);//移动到输入日期左侧
	cout << '*';
	gotoxy(column_coordination + column_adjust + 3 + 1, row_coordination + row_adjust);//移动到输入日期右侧
	cout << '*';
    gotoxy(0, 43);
}