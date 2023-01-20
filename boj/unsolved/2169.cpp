#include <iostream>
#include <cstring>
using namespace std;

int N, M;

int arr[1001][1001] = {0};
int memo[1001][1001];

int main()
{
    cin >> N >> M;
    for (int i=0;i<N;++i)
        for (int j=0;j<M;++j)
        {
            cin >> arr[i][j];
            memo[i][j] = -987654321;
        }
    
    memo[0][0] = arr[0][0];
    for (int j=1;j<M;++j) memo[0][j] = memo[0][j-1] + arr[0][j];
    for (int i=1;i<N;++i)
    {
        int tmp[1001] = {0,}; // i번행 고정
        int tmp2[1001] = {0,};
        
        for (int j=0;j<M;++j)
        {
            // 윗칸에서 내려온 경우
            tmp[j] = memo[i-1][j] + arr[i][j];
            // 좌에서 온 경우
            tmp[j+1] = max(tmp[j+1], tmp[j] + arr[i][j+1]);
        }
        // 현 시점에서 tmp에는 위에서 온 경우와 좌에서 온 경우중 더 큰 값이 들어있다.
        
        
        for (int j=M-1;j>=0;--j)
        {
            // 윗칸에서 내려온 경우
            tmp2[j] = memo[i-1][j] + arr[i][j];
            // 우에서 온 경우 (위에서 내려온 값이 좌로 한 칸 이동한 경우)
            tmp2[j-1] = max(tmp2[j-1], tmp2[j] + arr[i][j-1]);
        }
        // 현 시점에서 tmp에는 위에서 온 경우와 우에서 온 경우중 더 큰 값이 들어있다.
        
        for (int j=0;j<M;++j) memo[i][j] = max(tmp[j], tmp2[j]);
    }
    
    cout << memo[N-1][M-1] << '\n';
    
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<M;++j)
        {
            cout << memo[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
