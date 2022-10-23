#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "Calendar.h"

int main(void)
{
	int year, month, day;

	get_date(&year, &month, &day);
	print_header(year);
	print_form1(year);
	gotoxy(0, 7);
	calendar(year, 0);
	gotoxy(0, 17);
	calendar(year, 1);
	if (month <= 6)
		quote_the_day(year, month, day);
	gotoxy(0, 23);

	print_form2(year);
	gotoxy(0, 27);
	calendar(year, 2);
	gotoxy(0, 37);
	calendar(year, 3);
	if (month > 6)
		quote_the_day(year, month, day);
	gotoxy(0, 43);
	print_line();
	print_line();
	getchar();
	getchar();

	return 0;
}