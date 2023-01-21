#include <iostream>
#include <string>
using namespace std;
int N;

/*
    예시 326 -> 446
    3 4 : 1
    2 4 : 2
    6 6 : 0
    -> 1 2 0을 만들어야 함
    
    1  1  1
    0  1  1
    0  0 -2
    =
    1  2  0
    
    그러나 
    
    1  1  1
    0  0 -1
    0  1  1
    0  0 -1
    
    혹은
    
    1  1  1
    0  0 -2
    0  1  1
    도 복수정답이다.

    문제가 발생하는게 왼쪽으로 계속 돌리면 정답에서 멀어졌다 가까워졌다를 반복함 (원형이므로)
    
    d1 d2 d3 ... dn
    저장하면
    최소횟수를 구하기
    
    
    int [10][10][10][10] ... 은 불가능
    0~9니까 십진수로 저장가능
    1만자리 십진수 너무큰데
    그럼 일단 vector로 십진수 저장
    
    결국 현재값 벡터와 목표값 벡터의 diff를 구한 차이벡터
    차이벡터 파라미터로 받고 정답을 도출하는 solve 함수
    를 구현
    
    solve는 어떻게할까
    일단 bf생각해보면
    정답은 반드시 나사수가 커지는 방향일 때도 존재한다 (복수정답이 있을 수는 있어도 반드시 이렇게 해도 정답을 구할 수 있다)
    이에대한 논증? 일단 직감
    논증시도: 지금 i번 나중에 j번 돌릴 경우랑 지금 i+j번 돌릴 경우 모두 나사수 및 그 하위 나사에 i+j만큼 더하거나 빼주는 건 동일
    
    오케이 그럼 무조건 나사수가 커지는 방향으로 접근
    
    처음 숫자나사1의 수를 i1
    screw1을 돌리는 횟수를 s1
    숫자나사1의 수를 n1이라 하자
    
    n1 = (i1 + s1) % 10
    n2 = (i2 + s1 + s2) % 10
    ...
    nx = (ix + s1 + ... sx) % 10
    
    근데 위에서부터 내려오니까 s1 후보는 사실 추려짐
    예시의 경우 즉 3->4의 경우
    ... -19, -9, 1, 11, 21, ... 1+10x임 (x는 양음 가능)
    10x+1의 정답 상,하한이 있을 것 같은데...
아니 근데 생각해보니까 의미없다
그냥 1이 정답이네

물론 경우에 따라 ex.1->7인 경우
정답이 6대신 -4임
근데 이 경우
6을 선택하는게 이득일 수도 있는게
-4는 무조건 -1을 4번해야 하는 반면
6은 상위 나사에서 이득보면 오히려 더 빨리 끝날 수 있음!

정리해보면
일단 현재 수랑 목표수의 각 자리들의 diff를 구할 수 있음
이때 diff는 양수 혹은 음수 하나씩이 나올 수 있음
그럼 우린 이 양수 음수로 케이스를 2개로 나누어 top-down으로 dp를 하는 거임
3 2 6을 살펴보면

우선 1자리 3은
3->4이므로
1 or -9임

재귀함수로 1, -9 case로 나누어 진행
이때 이 결과를 dp로 기록해야 함.
어떻게?

void recursive(vector<int>& cNum, int cnt)
{
    // cNum은 길이 10000 이하, 현재 숫자들을 나타낸 수로 아직 수.

    // cnt는 그동안 몇회 회전시켰는지
    
void recursive(int depth, int cnt)
// 다시 생각하니까 벡터도 필요가 없는게 어차피 목표값은 하나고, 우리는 한 자리씩 맞춰나가는 거기 때문에
같은 depth에서는 수가 동일함. 즉 depth 정보만 저장해도됨.
이때 depth가 10000이하임!
dp 가능!!!

dp[10001]
    
    
    
}





내 느낌상 한 자리에서 10회 이상 돌릴 필요가 없음.
정답에는 절대 그런 경우가 없을 것이라 생각함.
(직감)
*/

int getDiff(int a, int b)
{
    int tmp = abs(a-b);
    if (tmp > 5) return (10-tmp);
    return tmp;
}

int memo[10001]; // memo[depth]: depth번 자리까지 맞힌 상태가 되기 위한 이동횟수 (최소)
string A, B;
int ret[10001];

int recursive(int depth, int cnt, int posMoves)
{
    // depth: 현재 depth번 자리까지 맞혀져 있는 상태
    // cnt: 누적회전수
    // posMoves: 그동안 상위 숫자나사에서 좌측으로 돌린 누적횟수. 
    // 이만큼 먼저 돌려놓은 상태에서 시작해야 함.
    
    cout << "d: " << depth+1 << "cnt: " << cnt << "posMoves: " << posMoves << endl; 
    
    if (depth == N) return cnt; // 기저, 다맞힘
    
    int cA = A[depth]+posMoves;
    int cB = B[depth];
    
    int posM = getDiff(cA,cB); // 왼쪽 회전
    int negM = posM - 10; // 우측 회전 (음수)
    
    int posCase = recursive(depth+1, cnt+posM, posMoves+posM);
    int negCase = recursive(depth+1, cnt+abs(negM), posMoves);
    
    if (posCase < negCase) 
    {
        ret[depth] = posM;
        return posCase;
    }
    else
    {
        ret[depth] = negM;
        return negCase;
    }
}

int main()
{
    cin >> N >> A >> B;
    
    cout << recursive(0, 0, 0) << '\n';
    for (int i=0;i<N;++i)
        cout << i+1 << " " << ret[i] << '\n';

    return 0;
}
