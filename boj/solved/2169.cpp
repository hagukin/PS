#include <iostream>
#include <cstring>
using namespace std;

int N, M;

int arr[1001][1001] = {0};
int memo[1001][1001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
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
        
        tmp[0] = memo[i-1][0] + arr[i][0];
        for (int j=1;j<M+1;++j)
        {
            tmp[j] = max(tmp[j-1], memo[i-1][j]) + arr[i][j];
        }
        
        tmp2[M-1] = memo[i-1][M-1] + arr[i][M-1];
        for (int j=M-2;j>=0;--j)
        {
            tmp2[j] = max(tmp2[j+1], memo[i-1][j]) + arr[i][j];
        }
        for (int j=0;j<M;++j) memo[i][j] = max(tmp[j], tmp2[j]);
    }
    
    cout << memo[N-1][M-1] << '\n';
    return 0;
}
