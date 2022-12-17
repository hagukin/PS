#include <string>
#include <vector>
#include <iostream>
using namespace std;
constexpr int INF = 987654321;

int cardPos[17][2]; // i%2==0일때 i번과 i+1번은 무조건 페어

int getFilled()
{
    return 0b11111111'11111111'11111111'11111111;
}

int getTurns(int cardLeft, int sy, int sx, int dy, int dx)
{
    // TODO
    // BFS를 이용해 s에서 d까지의 최단거리 구하기
}

int solve(int cardLeft, int target, int cy, int cx)
{
    int ret = INF;
    
    // 타겟 찾기
    ret = getTurns(cardLeft, cy, cx, cardPos[target][0], cardPos[target][1]);
    
    // 페어도 찾기
    int nextT;
    if (target % 2 == 0) nextT = target+1;
    else nextT = target-1;
    ret += getTurns(cardLeft, cardPos[target][0], cardPos[target][1], cardPos[nextT][0], cardPos[nextT][1]);
    
    // 업데이트
    cardLeft &= (getFilled() ^ (1<<target));
    cardLeft &= (getFilled() ^ (1<<nextT));
    
    cy = cardPos[target][0];
    cx = cardPos[target][1];
    
    // 다음 타깃 모색
    int add = INF;
    for (int i=0;i<16;++i)
    {
        if (1<<i & cardLeft)
        {
            add = min(add, solve(cardLeft, i, cy, cx));
        }
    }
    if (add != INF) return ret + add;
    else return ret;
}

int solution(vector<vector<int>> board, int r, int c) 
{
    int answer = 0;
    
    // TODO
    
    return answer;
}
