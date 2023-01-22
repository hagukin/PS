#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

int getDiff(int a, int b)
{
    int tmp = b-a;
    if (tmp < 0) return 10+tmp;
    return tmp;
}

int N;
string A, B;
int memo[10001][10]; // memo[depth][왼쪽으로 돌린 수 % 10] = 남은 수(depth+1 이상)들을 다 맞히기 위해 추가적으로 필요한 최소 회전수

int recursive(int depth, int posMoves)
{
    // 반환: memo와 동일 
    // depth: 현재 depth번 자리까지 맞혀져 있는 상태
    // posMoves: 그동안 상위 숫자나사에서 좌측으로 돌린 누적횟수. 
    // moves: 현재까지의 회전 방향과 횟수 기록
    // 이만큼 먼저 돌려놓은 상태에서 시작해야 함.
    
    if (depth == N) // 기저, 다맞힘
    {
        return 0;
    }
    
    if (memo[depth][posMoves%10] != -1)
        return memo[depth][posMoves%10];
    
    int cA = ((A[depth]-'0')+posMoves)%10;
    int cB = B[depth]-'0';
    
    int posM = getDiff(cA,cB); // 왼쪽 회전
    int negM = posM - 10; // 우측 회전 (음수)
    
    int posCase = recursive(depth+1, posMoves+posM);
    int negCase = recursive(depth+1, posMoves);
    
    if (posCase+posM < negCase-negM)
    {
        return memo[depth][posMoves%10] = posCase+posM;
    }
    else
    {
        return memo[depth][posMoves%10] = negCase-negM;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(memo, -1, sizeof(memo));
    cin >> N >> A >> B;
    cout << recursive(0, 0) << '\n';
    return 0;
}
