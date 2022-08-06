#include <iostream>
#include <cstring>
#include <math.h>

using namespace std;
int N, L;
int hmap[101][101];
bool slope[101][101];
int ret = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    memset(hmap, 0, sizeof(hmap));
    memset(slope, false, sizeof(slope));
    cin >> N >> L;
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++)
        {
            cin >> hmap[i][j];
        }
    }
    
    // 가로줄 경로
    for (int i=0;i<N;i++)
    {
        bool valid = true;
        for (int j=0;j<N;j++)
        {
            if (j+1>=0 && j+1<N)
            {
                int hdiff = hmap[i][j+1] - hmap[i][j];
                switch(hdiff)
                {
                    case -1:
                        for (int k=1; k<=L; k++)
                        {
                            valid = valid && (j+k>=0 && j+k<N && hmap[i][j+k] == hmap[i][j+1] && !slope[i][j+k]); // 연달아 k개가 같고 그 위치들에 경사로가 없어야 함.
                        }
                        if (valid)
                        {
                            for (int k=1; k<=L; k++) slope[i][j+k] = true;
                        }
                        break;
                    case 1:
                        for (int k=0; k<L; k++)
                        {
                            valid = valid && (j-k>=0 && j-k<N && hmap[i][j-k] == hmap[i][j] && !slope[i][j-k]); // 연달아 k개가 같고 그 위치들에 경사로가 없어야 함.
                        }
                        if (valid)
                        {
                            for (int k=0; k<L; k++) slope[i][j-k] = true;
                        }
                        break;
                    case 0:
                        break;
                    default:
                        valid = false;
                        break; // 높이차가 커서 불가능한 경로. 다음 경로로
                }
            }
            if (!valid) break;
        }
        if (valid) {ret++;}
    }
    
    // 경사로 삭제
    memset(slope, false, sizeof(slope));
    
    // 세로줄 경로
    for (int i=0;i<N;i++)
    {
        bool valid = true;
        for (int j=0;j<N;j++)
        {
            if (j+1>=0 && j+1<N)
            {
                int hdiff = hmap[j+1][i] - hmap[j][i];
                switch(hdiff)
                {
                    case -1:
                        for (int k=1; k<=L; k++)
                        {
                            valid = valid && (j+k>=0 && j+k<N && hmap[j+k][i] == hmap[j+1][i] && !slope[j+k][i]); // 연달아 k개가 같고 그 위치들에 경사로가 없어야 함.
                        }
                        if (valid)
                        {
                            for (int k=1; k<=L; k++) slope[j+k][i] = true;
                        }
                        break;
                    case 1:
                        for (int k=0; k<L; k++)
                        {
                            valid = valid && (j-k>=0 && j-k<N && hmap[j-k][i] == hmap[j][i] && !slope[j-k][i]); // 연달아 k개가 같고 그 위치들에 경사로가 없어야 함.
                        }
                        if (valid)
                        {
                            for (int k=0; k<L; k++) slope[j-k][i] = true;
                        }
                        break;
                    case 0:
                        break;
                    default:
                        valid = false;
                        break; // 높이차가 커서 불가능한 경로. 다음 경로로
                }
            }
            if (!valid) break;
        }
        if (valid) {ret++;}
    }
    
    cout << ret << '\n';
    return 0;
}
