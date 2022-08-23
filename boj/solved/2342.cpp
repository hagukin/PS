#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;
constexpr int MAXN = 100002;
int moves[MAXN];
int memo[5][5][MAXN]; // memo[l][r][c] = l,r이 좌우발이고 i를 마지막으로 밟는 경우의 cost의 최솟값
int N = 0;

int getCost(int curr, int next) // curr, next가 [1,4]임이 보장되어야함
{
    if (curr == next) return 1; // 같은 타일
    if (curr == 0) return 2; // 중앙에서 이동
    
    int tmp = (curr+2)%4;
    if (!tmp) tmp = 4;
    if (tmp==next) return 4; // 반대편
    
    return 3; // 인접
}

void setMin(int l, int r, int i, int nVal)
{
    if (memo[l][r][i] == -1) memo[l][r][i] = nVal;
    else memo[l][r][i] = min(memo[l][r][i], nVal);
}

void moveLeg(int cl, int cr, int mIdx, bool isLeft)
{
    int nPos = moves[mIdx];
    if ((isLeft && cr==nPos) || (!isLeft && cl==nPos)) return;
    if (mIdx == 1)
    {
        if (cl || cr) return; // cl, cr은 0,0이어야함
        if (isLeft) setMin(nPos, cr, mIdx, 2); // 0+2=2
        else setMin(cl, nPos, mIdx, 2);
        return;
    }
    if (memo[cl][cr][mIdx-1] == -1) return;
    int nCost;
    if (isLeft)
    {
        nCost = memo[cl][cr][mIdx-1] + getCost(cl, nPos);
        setMin(nPos, cr, mIdx, nCost);
    }
    else
    {
        nCost = memo[cl][cr][mIdx-1] + getCost(cr, nPos);
        setMin(cl, nPos, mIdx, nCost);
    }
    return;
}

void printRet()
{
    int ret = INT_MAX;
    for (int l=0;l<=4;++l)
    {
        for (int r=0;r<=4;++r)
        {
            if (memo[l][r][N] >= 0) ret = min(ret, memo[l][r][N]);
        }
    }
    if (ret == INT_MAX) ret = 0; // 모든 케이스가 -1인경우 (입력이 0인경우)
    cout << ret << '\n';
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(memo, -1, sizeof(memo));
    int tmp;
    for (int i=1;i<=MAXN;++i)
    {
        cin >> tmp;
        if (!tmp) break;
        moves[i] = tmp;
        N++;
    }
    for (int i=1;i<=N;++i)
    {
        for (int l=0;l<=4;++l) // 처음 0,0시작하므로 0,1같은 좌표도 고려하려면 0~4 다 루프 돌아야함.
        {
            for (int r=0;r<=4;++r)
            {
                // l,r에서 moves[i]를 밟기
                moveLeg(l,r,i,true); // 왼발
                moveLeg(l,r,i,false); // 오른발
            }
        }
    }
    printRet();
    return 0;
}
