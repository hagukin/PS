#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<pair<int,int>> st;
vector<int> ret;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        pair<int,int> p;
        cin >> p.first;
        p.second = i;
        
        while (!st.empty() && st.back().first < p.first) 
        {
            st.pop_back(); // worst case: push N번, pop N번 -> O(N)
        }
        if (st.empty())
        {
            ret.push_back(0);
            st.push_back(p);
        }
        else
        {
            ret.push_back(st.back().second);
            st.push_back(p);
        }
        
    }
    for (int i : ret) cout << i << ' ';
    cout << '\n';
    return 0;
}
