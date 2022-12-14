#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

pair<string,string>&& modString(string s)
{
    return make_pair<string,string>(s.substr(0,8),s.substr(9,8));
}

int timeToInt(string s)
{
    int ret = 0;
    ret += stoi(s.substr(0,2)) * 3600;
    ret += stoi(s.substr(3,2)) * 60;
    ret += stoi(s.substr(6,2));
    return ret;
}

string intToTime(int n)
{
    return "";
}

string solution(string play_time, string adv_time, vector<string> logs) 
{
    string answer = "";
    int watchCnt[360060];
    int te = timeToInt(play_time);
    int ta = timeToInt(adv_time);
    ll ansInt = 0;
    
    int t1, t2;
    string s1, s2;
    for (string& log : logs)
    {
        pair<string,string> s1s2 = modString(log);
        t1 = timeToInt(s1s2.first);
        t2 = timeToInt(s1s2.second);
        for (int i=t1;i<t2;++i) ++watchCnt[i]; // <=가 아니라 <t2임에 주의
    }
    
    // 슬라이딩 윈도우
    ll curr = 0;
    for (int i=0;i<=ta;++i)
    {
        curr += watchCnt[i];
    }
    
    for (int i=1;i<=te-ta;++i)
    {
        curr -= watchCnt[i-1];
        curr += watchCnt[i+ta];
        ansInt = max(ansInt, curr);
    }
    
    cout << ansInt << endl;
    answer = intToTime(ansInt);
    return answer;
}
