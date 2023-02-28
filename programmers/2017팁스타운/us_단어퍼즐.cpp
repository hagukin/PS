/*
접근 자체가 잘못된 시간초과나는 TopDown DP 풀이.
싹 지우고 처음부터 다시 풀어보자
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;
constexpr int INF = 987654321;

unordered_set<string> myStrs;
char memo[20002][20002] = {0,};

int getAns(string& originStr, int si, int cnt)
{
    if (memo[si][cnt] != 0) return memo[si][cnt];
    
    string cStr = originStr.substr(si,cnt);
    if (myStrs.find(cStr) != myStrs.end()) return memo[si][cnt] = 1;
    
    int funcRet = INF;
    for (int i=1;i<cnt;++i)
    {
        int tmp1 = getAns(originStr, si, i);
        int tmp2 = getAns(originStr, si+i, cnt-i);
        
        if (tmp1 < 0 || tmp2 < 0) continue; // 경우의 수 삭제
        funcRet = min(funcRet, tmp1+tmp2);
    }
    if (funcRet >= INF) funcRet = -1;
    return memo[si][cnt] = funcRet; // memo에 -1도 기록될 수 있음
}

int solution(vector<string> strs, string t)
{
    int answer = 0;
    for (int i=0;i<strs.size();++i)
    {
        myStrs.insert(strs[i]);
    }
    answer = getAns(t, 0, t.length());
    if (answer < 0) answer = -1;
    cout << answer << '\n';
    return answer;
}
