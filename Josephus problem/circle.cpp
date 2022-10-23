#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    cout << "please input the total of numbers." << endl;
    int n;
    cin >> n;
    vector<int> number;
    for (int i = 0; i != n; ++i)
    {
        number.push_back(i + 1);
    }
    auto b = number.begin();
    int count = 1;
    while (number.size() != 1)
    {
        if (count == 3)
        {
            count = 1;
            b = number.erase(b);
            auto e = number.end();
            if(b == e)
                b = number.begin();
        }
        else
        {
            ++b;
            auto e = number.end();
            if(b == e)
                b = number.begin();
            ++count;
        }
    }

    cout << *b << " is left" << endl;

    return 0;
}