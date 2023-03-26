#include <string>
#include <vector>
#include <memory.h>
#include <iostream>

using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    // 도착점까지의 x,y 차이
    int dy = r-x; // x,y가 바뀌어있으므로 주의
    int dx = c-y;
    int minMoveCnt = abs(dx) + abs(dy);
    
    if (minMoveCnt > k || (minMoveCnt - k)%2) return "impossible";

    string cOrder = "dlru";
    int mDir[4][2] = {{0,1},{-1,0},{1,0},{0,-1}};
    int mQueue[4] = {0,}; // dlru순
    int qCnt = 0;
    if (dy > 0) {mQueue[0] += abs(dy); qCnt += abs(dy);}
    if (dx < 0) {mQueue[1] += abs(dx); qCnt += abs(dx);}
    if (dx > 0) {mQueue[2] += abs(dx); qCnt += abs(dx);}
    if (dy < 0) {mQueue[3] += abs(dy); qCnt += abs(dy);} // 큐에 필수 moves만큼을 넣어둔다
    
    int cy = x, cx = y; // yx순
    for (int i=0;i<k;++i)
    {
        if (qCnt == k-i) // 이제 공간이 없어 큐부터 해결해야 하는 경우
        {
            for (int d=0;d<4;++d)
            {
                while (mQueue[d])
                {
                    mQueue[d]--;
                    qCnt--;
                    answer.push_back(cOrder[d]);
                }
            }
            return answer;
        }
        
        for (int d=0;d<4;++d)
        {
            int ny = cy + mDir[d][1];
            int nx = cx + mDir[d][0];
            if (ny > 0 && ny <= n && nx > 0 && nx <= m)
            {
                if (mQueue[d]>0) {mQueue[d]--; qCnt--;} // 큐에 있으면 먼저 그거부터 사용
                else {mQueue[3-d]++; qCnt++;} // 반대쪽 방향으로도 이동해줘야함, qCnt를 하나 증가시킴
                answer.push_back(cOrder[d]);
                cy = ny;
                cx = nx;
                break;
            }
        }
    }
    
    return answer;
}
