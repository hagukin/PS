#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int,int> P;

int getDiff(int a, int b)
{
    int tmp = b-a;
    if (tmp < 0) return 10+tmp;
    return tmp;
}

int N;
string A, B;
P memo[10001][10];
// memo[depth][왼쪽으로 돌린 수 % 10].first = 남은 수(depth+1 이상)들을 다 맞히기 위해 추가적으로 필요한 최소 회전수
// memo[depth][왼쪽으로 돌린 수 % 10].second = 현재(depth+1) 나사를 돌린 횟수 (최적의 경우)

int recursive(int depth, int posMoves)
{
    // 반환: memo의 first값 
    // depth: 현재 depth번 자리까지 맞혀져 있는 상태
    // posMoves: 그동안 상위 숫자나사에서 좌측으로 돌린 누적횟수
    // 이만큼 먼저 돌려놓은 상태에서 시작해야 함
    if (depth == N) // 기저, 다맞힘
        return 0;
    
    if (memo[depth][posMoves%10].first != -1)
        return memo[depth][posMoves%10].first;
    
    int cA = ((A[depth]-'0')+posMoves)%10;
    int cB = B[depth]-'0';
    
    int posM = getDiff(cA,cB); // 왼쪽 회전
    int negM = posM - 10; // 우측 회전 (음수)
    
    int posCase = recursive(depth+1, posMoves+posM);
    int negCase = recursive(depth+1, posMoves);
    
    if (posCase+posM < negCase-negM)
    {
        memo[depth][posMoves%10].first = posCase+posM;
        memo[depth][posMoves%10].second = posM;
    }
    else
    {
        memo[depth][posMoves%10].first = negCase-negM;
        memo[depth][posMoves%10].second = negM;
    }
    return memo[depth][posMoves%10].first;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // 메모이제이션 초기화
    for (int i=0;i<10001;++i)
        for (int j=0;j<10;++j)
            memo[i][j].first = -1;
    
    cin >> N >> A >> B;
    cout << recursive(0, 0) << '\n';
    
    // 역추적
    // 이 부분을 이해하는 게 아주 중요하다!
    // 깃헙에 같이 첨부한 사진 참고하면 상위 노드에서 하위 노드로 내려갈 때 
    // memo.second의 값을 이용해서 좌측 자식인지 우측 자식인지 결정해나가는 것을 볼 수있다.
    int cDepth = 0, posCnt = 0;
	for (int cDepth=0;cDepth<N;++cDepth) 
	{
		cout << cDepth + 1 << ' ' << memo[cDepth][posCnt].second << '\n';
		if (memo[cDepth][posCnt].second > 0) 
		{
			posCnt += memo[cDepth][posCnt].second;
			posCnt %= 10;
		}
	}
	
    return 0;
}
