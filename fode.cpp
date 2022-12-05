// A normal IO example code
#include <bits/stdc++.h>
using namespace std;
#include <vector.hpp>

bool    check(string n)
{
    vector<int> ko;
    int j = n.length();

    for (int i = 0; i < n.length(); i++)
    {
        

    }
    return (1);
}

bool    is_it(string    n)
{
    int j = n.length();
    for (int i = 0; i < j; i++)
    {
     if (n[i] != n[j - 1 - i]) {
        return 0;
        }
    }
    return 1;
}
int main()
{
    string n;
    cin >> n;
    
    if (check(n))
    {
        cout << "YES";
        return 0;
    }
    if (is_it(n))
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
