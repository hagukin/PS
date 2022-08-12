#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>

/*
6
10 20 10 30 15 50

10
0

10 20
0 1

10 20
0 1 0

10 20 30
0 1 0 2

10 15 30
0 1 0 2 1

10 15 30 50
0 1 0 2 1 3

3 2 1 0 -> 50 30 20 10
*/

using namespace std;
int N;
int origin[1000001][2]; // 수, 인덱스 순서
vector<int> v;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    v.push_back(INT_MIN);

    int num;
    for (int i=0;i<N;i++) 
    {
        cin >> num;
        origin[i][0] = num;
        if (num > v.back())
        {
            v.push_back(num);
            origin[i][1] = v.size() - 1;
        }
        else
        {
            int index = lower_bound(v.begin(), v.end(), num) - v.begin();
            v[index] = num;
            origin[i][1] = index;
        }
    }
    
    int lisLen = v.size()-1;
    cout << lisLen << '\n';
    for (int i=N-1;i>=0;i--)
    {
        if (origin[i][1] == lisLen) // -1은 맨 앞에 INT_MIN, 나머지 -1은 인덱스가 갯수-1이어서
        {
            v[lisLen] = origin[i][0];
            --lisLen;
        }
    }
    for (int i=1;i<v.size();i++)
    {
        cout << v[i] << " ";
    }
    return 0;
}
