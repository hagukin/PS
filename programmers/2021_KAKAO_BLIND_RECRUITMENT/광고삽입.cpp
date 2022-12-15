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
    string ret = "";
    int h = n/3600;
    int m = (n-(h*3600))/60;
    int s = n - (3600*h + 60*m);
    if (h<10) ret += "0";
    ret += to_string(h) + ":"; 
    if (m<10) ret += "0";
    ret += to_string(m) + ":";
    if (s<10) ret += "0";
    ret += to_string(s);
    return ret;
}

string solution(string play_time, string adv_time, vector<string> logs) 
{
    string answer = "";
    int watchCnt[360060] = {0,}; // 반드시 0으로 초기화해줘야함
    int te = timeToInt(play_time);
    int ta = timeToInt(adv_time);
    ll maxWatchTime = 0;
    int ans = 0;
    
    int t1, t2;
    string s1, s2;
    for (string& log : logs)
    {
        pair<string,string> s1s2 = modString(log);
        t1 = timeToInt(s1s2.first);
        t2 = timeToInt(s1s2.second);
        for (int i=t1;i<t2;++i) ++watchCnt[i];
    }
    
    // 슬라이딩 윈도우
    ll curr = 0;
    for (int i=0;i<ta;++i)
    {
        curr += watchCnt[i];
    }
    maxWatchTime = curr;
    
    for (int i=1;i<=te-ta;++i)
    {
        curr -= watchCnt[i-1];
        curr += watchCnt[i+ta-1];
        if (curr > maxWatchTime)
        {
            maxWatchTime = curr;
            ans = i;
        }
    }
    
    answer = intToTime(ans);
    return answer;
}
