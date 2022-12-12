#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) 
{
    int grid[101][101] = {0,};
    for (int x=1;x<=columns;++x)
    {
        for (int y=1;y<=rows;++y)
        {
            grid[y][x] = columns * (y-1) + x;
        }
    }
    
    vector<int> answer;
    vector<int> affected;
    for (vector<int>& query : queries)
    {
        affected.clear();
        int y1 = query[0];
        int x1 = query[1];
        int y2 = query[2];
        int x2 = query[3];
        
        int nGrid[101][101] = {0,};
        for (int i=0;i<=rows;++i)
            for (int j=0;j<=columns;++j)
                nGrid[i][j] = grid[i][j];
        
        // 규칙: affected에는 변경 후의 값을 push한다
        // 상단 가로줄 변경 (좌상단 변경안됨)
        for (int cx=x2-1;cx>=x1;--cx)
        {
            nGrid[y1][cx+1] = grid[y1][cx];
            affected.push_back(nGrid[y1][cx+1]);
        }
        // 상단 가로줄 마무리 (좌상단 채우기)
        nGrid[y1][x1] = grid[y1+1][x1];
        affected.push_back(nGrid[y1][x1]);
        
        // 하단 가로줄 변경 (우하단 변경안됨)
        for (int cx=x1+1;cx<=x2;++cx)
        {
            nGrid[y2][cx-1] = grid[y2][cx];
            affected.push_back(nGrid[y2][cx-1]);
        }
        // 하단 가로줄 마무리 (우하단 채우기)
        nGrid[y2][x2] = grid[y2-1][x2];
        affected.push_back(nGrid[y2][x2]);
        
        // 좌측 세로줄 변경 (맨위,맨아래 무시)
        for (int cy=y1+1;cy<y2;++cy)
        {
            nGrid[cy][x1] = grid[cy+1][x1];
            affected.push_back(nGrid[cy][x1]);
        }
        // 우측 세로줄 변경 (맨위, 맨아래 무시)
        for (int cy=y2-1;cy>y1;--cy)
        {
            nGrid[cy][x2] = grid[cy-1][x2];
            affected.push_back(nGrid[cy][x2]);
        }
        
        sort(affected.begin(), affected.end());
        answer.push_back(affected.front());
        
        for (int i=0;i<=rows;++i)
        {
            for (int j=0;j<=columns;++j)
                grid[i][j] = nGrid[i][j];
        }
            
    }
    
    return answer;
}
