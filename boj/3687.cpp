// 풀이1 - 2~100 사이의 모든 값에 대해 정답이 나오는데도 boj에서 채점시 50%에서 오답. 원인불명...
#include <iostream>
#include <cstring>
#include <math.h>
#include <limits.h>
using namespace std;
typedef long long ll;
constexpr ll INF = LLONG_MAX;
int TC;
ll dp[101]; // dp[i] = i개 사용해서 만들 수 있는 최소값

void init()
{
    // bottom-up dp 초기화
    memset(dp, -1, sizeof(dp));
    
    // i<=7까지 초기화
    dp[2] = 1; dp[3] = 7; dp[4]=4; dp[5]=2; dp[6]=0; dp[7]=8;
    
    // i<=14까지 초기화
    for (int i=8;i<=14;i++)
    {
        if (dp[i] == -1) dp[i] = INF;
        for (int j=2;j<=7;j++)
        {
            int dpj = dp[j]; // 혹시라도 dp[6]이 나오면 0 말고 6을 대신 사용해줘야 하기 때문에 있는 장치
            if (dpj == 0) dpj=6; // 0으로 시작 X, 따라서 다음으로 작은 6으로 변경
            if (i-j>7) continue; // 2~7 사이 값만이 한자리 수
            dp[i] = min(dpj*10+dp[i-j], dp[i]);
        }
    }
    
    // i<=100까지 초기화
    for (int i=15;i<=100;i++)
    {
        ll value = 0;
        int sevCnt = i/7;
        
        // 8~13 사이의 '나머지값' 찾기
        int rem = i % 7;
        if (rem) {rem += 7; sevCnt--;}
        
        // 8 끝에서부터 채워넣기
        for(int j=0;j<sevCnt;j++)
        {
            value += 8 * pow(10,j);
        }
        // 나머지값 맨 앞에 추가
        if (rem) value += dp[rem] * pow(10,sevCnt);
        
        dp[i] = value;
    }
    
    dp[6] = 6; // 0으로 시작할 수 없으므로 6으로 바꿔줌.
    dp[0] = 0; dp[1] = 0;
}

void printMax(int x) // 값이 너무커서 ll으로도 안됨. 동적으로 출력해줘야 함.
{
    int rem = x % 2;
    int oneCnt = x/2;
    if (rem) {oneCnt--; cout << 7;}
    for(int j=0;j<oneCnt;j++)
    {
        cout << 1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> TC;
    for (int i=0;i<TC;i++)
    {
        int N;
        cin >> N;
        init();
        cout << dp[N] << " "; // 최솟값 출력
        printMax(N);
        cout << '\n';
    }
    return 0;
}



// 답안
// 성냥개비
// #include <iostream>
// #include <climits>
 
// using namespace std;
 
// int n, testcase;
// int num[9] = {0, 0, 1, 7, 4, 2, 0, 8, 10};
// long long minDP[101] = {0, };
 
// void minCal()
// {
//     for(int i=1; i<=9; i++){
//         minDP[i] = num[i];
//     }
//     minDP[6] = 6; // 처음 시작은 0으로 할 수 없으니, 6으로 시작
//     // 또한, 9부터 시작하는 이유는, 8부터 하면 10이 아닌, 08(j=7일 경우) 값을 최소로 인식한다.
//     for(int i=9; i<=100; i++){
//         minDP[i] = 888888888888888;
//         for(int j=2; j<8; j++){
//             minDP[i] = min(minDP[i], minDP[i-j]*10+num[j]);
//         }
//     }
// }
 
// int main()
// {
//     cin>>testcase;
//     minCal(); 
//     while(testcase--){
//         cin>>n;
//         // 최소
//         cout<<minDP[n]<<" ";
 
//         // 최대(홀수, 짝수 나누어서)
//         while(n){
//             if(n % 2 != 0){
//                 cout << 7;
//                 n -= 3;
//             }
//             else{
//                 cout << 1;
//                 n -= 2;
//             }
//         }
//         cout << "\n";
//     }
 
//     return 0;
// }
