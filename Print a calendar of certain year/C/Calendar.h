#pragma once

#define MAX_YEAR 3000
#define MIN_YEAR 1000
#define LINE_LENGTH 90

void gotoxy(int x, int y);
int get_date(int* year, int* month, int* day);
void print_line(void);
void print_header(int year);
int day_cal(int year, int month);
void calendar(int year, int group);
void print_form1(int year);
void print_form2(int year);
void quote_the_day(int year, int month, int day);