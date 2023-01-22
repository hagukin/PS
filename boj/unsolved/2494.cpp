#include <iostream>
#include <string>
#include <vector>
using namespace std;
constexpr int INF = 987654321;
int N;

int getDiff(int a, int b)
{
    int tmp = b-a;
    if (tmp < 0) return 10+tmp;
    return tmp;
}

string A, B;
int retCnt = INF;
vector<int> retMoves;

int recursive(int depth, int cnt, int posMoves, vector<int>& moves)
{
    // depth: 현재 depth번 자리까지 맞혀져 있는 상태
    // cnt: 누적회전수
    // posMoves: 그동안 상위 숫자나사에서 좌측으로 돌린 누적횟수. 
    // moves: 현재까지의 회전 방향과 횟수 기록
    // 이만큼 먼저 돌려놓은 상태에서 시작해야 함.
    
    if (depth == N) // 기저, 다맞힘
    {
        if (cnt < retCnt)
        {
            retCnt = cnt;
            retMoves = moves; // deepcopy
        }
        return cnt;
    }
    
    int cA = ((A[depth]-'0')+posMoves)%10;
    int cB = B[depth]-'0';
    
    int posM = getDiff(cA,cB); // 왼쪽 회전
    int negM = posM - 10; // 우측 회전 (음수)
    
    //cout << "d: " << depth+1 << " cnt: " << cnt << " posMoves: " << posMoves  << " cA: " << cA << " cB: " << cB << " move: " << posM << "vs" << negM << endl;
    
    moves.push_back(posM);
    int posCase = recursive(depth+1, cnt+posM, posMoves+posM, moves);
    moves.pop_back();
    
    moves.push_back(negM);
    int negCase = recursive(depth+1, cnt+abs(negM), posMoves, moves);
    moves.pop_back();
    
    if (posCase < negCase)
    {
        return posCase;
    }
    else
    {
        return negCase;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> A >> B;
    vector<int> v;
    cout << recursive(0, 0, 0, v) << '\n';
    for (int i=0;i<N;++i)
        cout << i+1 << " " << retMoves[i] << '\n';
    return 0;
}
