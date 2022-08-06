// 사지방 마감시간이라 그냥 커밋합니다... 풀이가 이거보다 훨씬 더 깔끔해질 수 있음
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include <limits.h>

using namespace std;

int N; int bracketLastInd;
int ret = INT_MIN;
string calcOrigin[20];
string calc[20];
bool bracket[10]; // 시작괄호의 존재여부. 문자열이 처음으로 만나는 수의 위치: index*2

int calcShort(int n1, int n2, string opr)
{
    if (opr == "+") return n1 + n2;
    else if (opr == "-") return n1 - n2;
    else if (opr == "*") return n1 * n2;
    else return -1; //error
}

int calcCurr()
{
    vector<string> calc;
    for (const string s : calcOrigin)
    {
        calc.push_back(s);
    }
    
    // 괄호 먼저 연산
    for (int i=0;i<=bracketLastInd;i++)
    {
        if (bracket[i] && calc[i*2] != "#") 
        {
            int tmp = calcShort(stoi(calc[i*2]), stoi(calc[i*2+2]), calc[i*2+1]);
            calc[i*2] = to_string(tmp);
            calc[i*2+1] = "#";
            calc[i*2+2] = "#";
        }
    }
    
    // 전체연산
    vector<string> st; // stack
    for (int j=N-1;j>=0;j--) // 뒤에서부터
    {
        if (calc[j] != "#")
        {
            st.push_back(calc[j]);
        }
    }
    
    while (st.size() >= 3)
    {
        int n1 = stoi(st.back());
        st.pop_back();
        string opr = st.back();
        st.pop_back();
        int n2 = stoi(st.back());
        st.pop_back();
        
        int tmp = calcShort(n1, n2, opr);
        string s = to_string(tmp);
        st.push_back(s);
    }
    string tmpret = st.back();
    int r = stoi(tmpret);
    return r;
}

void solve(int start)
{
    if (start >= bracketLastInd) // 기저
    {
        int tmp = calcCurr();
        ret = max(ret, tmp);
        return;
    }
    // 모든 경우의 수 탐색
    solve(start+1);// 미설치 경우의 수
    bracket[start] = true;
    solve(start+2);// 설치 경우의 수
    bracket[start] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    // 입력
    cin >> N;
    bracketLastInd = N/2;
    string calcStr;
    cin >> calcStr;
    for (int i=0;i<N;i++)
    {
        calcOrigin[i] = calcStr[i]; //0~9이므로 1글자
    }

    // solve
    solve(0);
    cout << ret << '\n';
    return 0;
}
