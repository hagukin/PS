#include <iostream>
#include <memory.h>
using namespace std;
constexpr int MAXN = 50001;
int T, K;
int guests[MAXN] = {0,};
int dp[MAXN][3];

int getMax(int start, int count)
{
    // start번 객차부터 맨 끝까지 객차묶음을 count개 선택했을 때 가능한 최대 승객수
    if (count <= 0) return 0;
    else if (dp[start][count] != -1) return dp[start][count];
        
    int& ret = dp[start][count];
    // 이번 인덱스번 객차묶음을 선택하거나, 안하거나
    ret = max(guests[start] + getMax(start+K, count - 1), getMax(start+1, count));
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> T;
    for (int i=0; i<T; ++i) {
        cin >> guests[i];
    }
    cin >> K;
    
    memset(dp, -1, sizeof(dp));
    
    // 누적합
    int sum = 0;
    for (int i=0; i<K; ++i) {
        sum += guests[i];
    }
    int temp = sum;
    
    for (int i=K; i<T; ++i) {
        sum -= guests[i-K];
        sum += guests[i];
        guests[i-K] = temp;
        temp = sum;
    }
    guests[T-K] = sum;
    
    sum = 0;
    for (int i=T-K+1; i<T; ++i) {
        sum += guests[i];
    }
    for (int i=T-K+1; i<T; ++i) {
        temp = guests[i];
        guests[i] = sum;
        sum -= temp;
    }
    
    cout << getMax(0, 3) << '\n';
    return 0;
}
