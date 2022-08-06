#include <iostream>
#include <cstring>
#include <string>
using namespace std;

constexpr int DIVN = 1000000;
int memo[5001]; // memo[i] = s[i,s.length() - 1]로 만들 수 있는 모든 암호의 갯수.
string s;

void wrongInput()
{
    cout << 0 << '\n'; return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(memo, 0, sizeof(memo));
    cin >> s;
    
    if (s.empty()) {wrongInput(); return 0;}; // 빈 암호문
    
    int ei = s.length()-1;
    if (s[ei]!='0') memo[ei] = 1;
    for (int i=ei-1; i>=0; i--)
    {
        if (s[i+1] == '0' && s[i] == '0') {wrongInput(); return 0;}
        if (s[i]!='0' && s[i+1]!='0') // x xxxx꼴
        {
            memo[i] += memo[i+1];
            memo[i] %= DIVN;
        }
        
        if (ei-i==1 && stoi(s.substr(i,2)) <= 26 && s[i]!='0') // xx꼴 (2개)
        {
            memo[i] += 1;
            memo[i] %= DIVN;
        }
        else if (i+2 <= ei && s[i+2]!=0 && stoi(s.substr(i,2)) <= 26 && s[i]!='0') // xx xxx꼴
        {
            memo[i] += memo[i+2];
            memo[i] %= DIVN;
        }
        
    }
    cout << memo[0] << '\n';
    return 0;
}

/*
top down 방식으로 구하면 2^5000 => 불가능
2 5114
	2 5 114
		2 5 11 4 O
		2 5 1 14
			2 5 1 1 4 O
			2 5 1 14 O
25 114
	25 1 14
		25 1 14 O
		25 1 1 4 O
	25 11 4 O

bottom up으로 풀이!
4 -> 1
14 -> 1 + 1 = 2
114 -> 2 + 1 = 3
5114 -> 3
25114 -> 3 + 3 = 6
*/
