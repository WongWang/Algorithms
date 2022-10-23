#include <iostream>
#include "Date.h"
#include "Calendar.h"

using std::cin;
using std::cout;
using std::endl;


int main()
{
    Date day_in_process;
    cin >> day_in_process;

    print_header(day_in_process.year);
    print_form(day_in_process.year);
    print_calendar(day_in_process.year);
    quote_the_day(day_in_process);
    print_line();
    
    cin.get();
    cin.get();
    
    return 0;
}