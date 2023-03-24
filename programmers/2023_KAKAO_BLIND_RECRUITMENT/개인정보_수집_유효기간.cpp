#include <string>
#include <vector>
#include <iostream>

using namespace std;

int vDays[27] = {0,};

int ymdToDays(string date)
{
    int ret = 0;
    ret += stoi(date.substr(0,4)) * 12 * 28;
    ret += stoi(date.substr(5,2)) * 28;
    ret += stoi(date.substr(8,2));
    return ret;
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    int cDay = ymdToDays(today);

    for (string& s : terms)
    {
        char c = s[0];
        int m = stoi(s.substr(2,s.size()-2));
        vDays[c - 'A'] = m * 28;
    }
    
    for (int i=0;i<privacies.size();++i)
    {
        string& s = privacies[i];
        int pDay = ymdToDays(s.substr(0,10));
        if (pDay + vDays[s[s.size()-1] - 'A'] <= cDay) answer.push_back(i+1);
    }
    
    return answer;
}
