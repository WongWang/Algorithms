#include <iostream>

using std::istream;
using std::cin;

struct Date
{
private:
	int week_count;
	const unsigned day_in_every_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//每月对应天数
	int leap_year_cal()//计算是否为闰年 -tested
	{
		int leap_year;
		if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)
			leap_year = 1;
		else
			leap_year = 0;
		return leap_year;
	}
	int day_cal()//计算每月第一天为星期几（返回结果为0-6）-tested
    {
        int adjust1, adjust2, adjust3, ans;

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
	    ans = (adjust3 - 621049) % 7;

	    return ans;
    }
public:
    //数据成员
    unsigned year;
    unsigned month;
    unsigned day;
	//运算符重载
	Date& operator++()
	{
		if (day != day_in_every_month[month - 1] + (month == 2 && leap_year_cal()))//如果递增日期之前日期没有到达该月最后一天
			++day;
		else
			if (month != 12)
			{
				++month;
				day = 1;
			}
			else
			{
				++year;
				month = 1;
				day = 1;
			}
		if (week_count != 7)
			++week_count;
		else
			week_count = 0;
			
		return *this;
	}
    //成员函数
    int week()
	{
		return day_cal();
	}
};

//运算符重载
inline istream &operator>>(istream &is, Date &item)
{
	is >> item.year;
	cin.ignore(1);
	is >> item.month;
	cin.ignore(1);
	is >> item.day;

	return is;
}