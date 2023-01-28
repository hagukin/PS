#include <iostream>
#include <vector>
#include <string>
using namespace std;
string s;
int ret = 0;

struct Bracket
{
    char c;
    int idx;
};

vector<Bracket> st;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> s;
    
    for (int i=0;i<s.size();++i)
    {
        if (s[i] == '(')
        {
            Bracket b = {'(',i};
            st.push_back(b);
        }
        else
        {
            if (!st.empty() && st.back().c == '(') st.pop_back();
            else
            {
                Bracket b = {')',i};
                st.push_back(b);
            }
        }
    }
    
    // 스택을 보고 해결 가능한 문제인지 판단
    if (st.size() != 2) ret = 0;
    else if (st[0].c == ')' && st[1].c == '(') ret = 0; // )(자꼴 -> 해결불가
    else
    {
        if (st[0].c == '(') // l<r인 경우
        {
            int minIdx = st[1].idx;
            for (int i=minIdx;i<s.size();++i)
            {
                if (s[i] == '(') ret++;
            }
        }
        else
        {
            int maxIdx = st[0].idx;
            for (int i=0;i<=maxIdx;++i)
            {
                if (s[i] == ')') ret++;
            }
        }
    }
    cout << ret << '\n';
    return 0;
}
