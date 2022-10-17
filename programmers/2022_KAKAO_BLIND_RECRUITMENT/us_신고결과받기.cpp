#include <string>
#include <vector>
#include <map>

#include <iostream>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    map<string,int> nameIdx;
    bool hasReported[1002][1002]; // i가 j 신고했는가?
    int repCnt[1002]; // i가 신고받은 횟수(서로 다른 유저로부터)
    
    for (int i=0;i<id_list.size();++i)
    {
        nameIdx.insert({id_list[i],i});
    }
    
    for (int i=0;i<report.size();++i)
    {
        string reporter = "";
        string reported = "";
        string* cs = &reporter;
        for (int j=0;j<report[i].size();++j)
        {
            char cc = report[i][j];
            if (cc == ' ') {cs = &reported; continue;}
            cs->push_back(cc);
        }
        int reporterIdx = nameIdx[reporter];
        int reportedIdx = nameIdx[reported];
        if (!hasReported[reporterIdx][reportedIdx]) repCnt[reportedIdx]++;
        hasReported[reporterIdx][reportedIdx] = true;
    }
    
    vector<int> answer;
    for (int i=0;i<id_list.size();++i)
    {
        answer.push_back(0);
        for (int j=0;j<id_list.size();++j)
        {
            if (i == j) continue; // 자기자신은 신고할 수 없음
            if (hasReported[i][j] && repCnt[j] >= k) 
                ++answer[answer.size()-1];
        }
    }
    
    return answer;
}
