#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) 
{
    vector<int> answer;
    int cntToRank[7] = {6,6,5,4,3,2,1};
    bool isWinNum[46] = {0,};
    
    for (const int& i : win_nums) 
        isWinNum[i] = true;
    
    int correctN = 0;
    int zeros = 0;
    for (const int& j : lottos)
    {
        if (isWinNum[j]) correctN++;
        else if (j == 0) zeros++;
    }
    answer.push_back(cntToRank[correctN + zeros]);
    answer.push_back(cntToRank[correctN]);
    return answer;
}
