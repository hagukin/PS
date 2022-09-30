#include <string>
#include <vector>

using namespace std;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    int chToPts[7] = {-3,-2,-1,0,1,2,3};
    char types[4][2] = {{'R','T'},{'C','F'},{'J','M'},{'A','N'}};
    int typePts[4] = {0,0,0,0};
    
    for (int i=0;i<survey.size();i++)
    {
        char tFirst = survey[i][0];
        char tSecond = survey[i][1];
        
        int typeNum; // 0~3
        for (int j=0;j<4;j++)
        {
            if (types[j][0] == tFirst || types[j][0] == tSecond) 
            {
                typeNum = j; break;
            }
        }
        
        int alpOrder = (tFirst < tSecond) ? 1 : -1; // 알파뱃 역순이면 포인트 부호 뒤집기
        typePts[typeNum] += chToPts[choices[i] - 1] * alpOrder;
    }
    
    for (int i=0;i<4;i++)
    {
        if (typePts[i] <= 0) answer += types[i][0];
        else answer += types[i][1];
    }
    
    for (int i=0;i<4;i++) cout << typePts[i] << endl;
    
    return answer;
}
