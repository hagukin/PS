#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string ret;
int apeachScore;
int scoreDiff; // 아피치 - 라이언
vector<int> answer;

void solve(const vector<int>& info, vector<int>& v, int shotsLeft, int currIdx, int cRyan, int cApeach)
{
    // 벡터[i]는 i점을 맞힌 경우임 즉 입력벡터를 뒤집음.
    int cDiff = cRyan - cApeach;
    
    // 기저
    if (currIdx == 11 || shotsLeft == 0)
    {
        if (currIdx == 11 && shotsLeft) 
            v[0] += shotsLeft; // 점수는 변하지 않음 (shotsLeft<=아피치의 v[0])
        if (cDiff > scoreDiff) // 같으면 무시 (낮은 점수를 더 많이 맞힌 경우가 우선이므로 탐색 순서에 따라 걸러짐)
        {  
            answer = v; // 복사
            scoreDiff = cDiff;
        }
        if (currIdx == 11 && shotsLeft)
            v[0] -= shotsLeft;
        return;
    }
    
    // 탐색
    int tmp = v[currIdx];
    if (shotsLeft >= info[currIdx]+1)
    {
        v[currIdx] = info[currIdx]+1;
        if (info[currIdx]) // 둘다 1발 이상 쐈는데 라이언이 더 많이 쏜 경우
            solve(info, v, shotsLeft-(info[currIdx]+1), currIdx+1, cRyan+currIdx, cApeach-currIdx);
        else // 어피치는 안쐈을 경우
            solve(info, v, shotsLeft-(info[currIdx]+1), currIdx+1, cRyan+currIdx, cApeach);
        v[currIdx] = tmp;
    }
    solve(info, v, shotsLeft, currIdx+1, cRyan, cApeach); // 안쏘는 경우
    return;
}

vector<int> solution(int n, vector<int> info) {
    // a점에 i발을 맞혔을 경우 a점에 0발 혹은 i+1발을 맞혀야 함
    // -> 2^10으로 완전탐색 가능
    
    vector<int> tmp(11);
    for (int i=0;i<info.size();++i)
    {
        if (info[i] > 0) apeachScore += (10-i);
    }
    
    reverse(info.begin(), info.end());
    solve(info, tmp, n, 0, 0, apeachScore);
    if (scoreDiff <= 0) // 비기거나 졌을 경우
    {
        vector<int> nv;
        nv.push_back(-1);
        return nv;
    }
    reverse(answer.begin(), answer.end());
    return answer;
}
