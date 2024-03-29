#include <string>
#include <iostream>
#include <vector>

using namespace std;

void turnCCW(const vector<vector<int>>& origin, vector<vector<int>>& ret)
{
    int M = origin.size();
    for (int i=0;i<M;++i)
    {
        for (int j=0;j<M;++j)
        {
            ret[M-1-j][i] = origin[i][j];
        }
    }
    return;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    int M = key.size();
    int N = lock.size();
    
    // 회전
    vector<vector<int>> k2 = vector<vector<int>>(key.size(), vector<int>(key[0].size(),0));
    vector<vector<int>> k3 = vector<vector<int>>(key.size(), vector<int>(key[0].size(),0));
    vector<vector<int>> k4 = vector<vector<int>>(key.size(), vector<int>(key[0].size(),0));
    turnCCW(key, k2);
    turnCCW(k2, k3);
    turnCCW(k3, k4);
    
    vector<vector<vector<int>>> v;
    v.push_back(key);
    v.push_back(k2);
    v.push_back(k3);
    v.push_back(k4);
    
     // 홈 갯수
    int lockBlankCnt = 0;
    for (int i=0;i<N;++i)
        for (int j=0;j<N;++j)
            if (lock[i][j] == 0) lockBlankCnt++;
    
    // solve
    for (vector<vector<int>>& cKey : v)
    {
        for (int i=-M+1;i<N;++i)
        {
            for (int j=-M+1;j<N;++j)
            {
                // scan
                int filled = 0;
                bool collision = false;
                for (int sy=0;sy<N;++sy)
                {
                    for (int sx=0;sx<N;++sx)
                    {
                        int ky = -i+sy;
                        int kx = -j+sx;
                        if (ky >= 0 && kx >= 0 && ky < M && kx < M)
                        {
                            if (lock[sy][sx] == 0 && cKey[ky][kx] == 1) filled++;
                            if (lock[sy][sx] == 1 && cKey[ky][kx] == 1) collision = true;
                        }
                    }
                }
                if (filled == lockBlankCnt && !collision) return true;
            }
        }
    }
    return false;
}
