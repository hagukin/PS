#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
constexpr int MAXN = 14;
struct Piece
{
    int _y, _x;
    int dydx; // rlud 1234
    list<int> pStack; // 이 말이 속해있는 stack. l->r: 맨 위에서 맨 아래로
};

int N, K, ret=-1;
int gridColor[14][14] = {0,};
int gridPieces[14][14] = {0,}; // 해당 칸의 가장 아래에 있는 말의 번호. 없으면 0
Piece pieces[11];
pair<int,int> nToDir[5] = {{0,0},{1,0},{-1,0},{0,-1},{0,1}}; // rlud 1234
int reverseDir[5] = {0,2,1,4,3};

bool canMove(int idx)
{
    // idx번 말이 가장 아래에 있는가?
    return idx == pieces[idx].pStack.back();
}

int getY(int idx)
{
    if (canMove(idx)) return pieces[idx]._y;
    else return getY(pieces[idx].pStack.back());
}

int getX(int idx)
{
    if (canMove(idx)) return pieces[idx]._x;
    else return getX(pieces[idx].pStack.back());
}

void setY(int idx, int val)
{
    for (int nidx : pieces[idx].pStack)
    {
        pieces[nidx]._y = val;
    }
}

void setX(int idx, int val)
{
    for (int nidx : pieces[idx].pStack)
    {
        pieces[nidx]._x = val;
    }
}

int getTileColor(int cy, int cx, int dy, int dx)
{
    return gridColor[cy+dy][cx+dx];
}

void moveAndStack(int idx, int cy, int cx, int dy, int dx)
{
    int ny = cy+dy; 
    int nx = cx+dx;
    int tp = gridPieces[ny][nx];
    if (tp)
    {
        // 리스트 합치기
        pieces[tp].pStack.splice(pieces[tp].pStack.end(), pieces[idx].pStack);
    }
    // 기존 위치에서 정보 삭제
    gridPieces[pieces[idx]._y][pieces[idx]._x] = 0;
    // 동기화
    for (int nidx : pieces[idx].pStack)
    {
        pieces[nidx]._y = ny;
        pieces[nidx]._x = nx;
        pieces[nidx].pStack = pieces[tp].pStack;
    }
    // 새 위치 정보 입력
    gridPieces[ny][nx] = pieces[idx].pStack.back();
    return;
}

void reverseCurrStack(int idx)
{
    // idx번 말이 속해있는 스택에서 idx를 기준으로 idx 및 그 위에 있는 모든 말들을 뒤집는다.
    list<int>& st = pieces[idx].pStack;
    auto idxPos = st.begin();
    for (int c : st)
    {
        if (c == idx) break;
        idxPos++;
    }
    reverse(idxPos, st.end());
    return;
}

bool processMove(int idx)
{
    // return: 길이 4 이상의 stack이 만들어졌는가?
    if (!canMove(idx)) return false;
    pair<int,int> nDir = nToDir[pieces[idx].dydx];
    int tColor = getTileColor(getY(idx), getX(idx), nDir.first, nDir.second);
    switch(tColor)
    {
        case 0:
            moveAndStack(idx, getY(idx), getX(idx), nDir.first, nDir.second);
            break;
        case 1:
            moveAndStack(idx, getY(idx), getX(idx), nDir.first, nDir.second);
            reverseCurrStack(idx);
            break;
        case 2:
            pieces[idx].dydx = reverseDir[pieces[idx].dydx];
            nDir = nToDir[pieces[idx].dydx];
            if (getTileColor(getY(idx), getX(idx), nDir.first, nDir.second) == 2) break;
            else moveAndStack(idx, getY(idx), getX(idx), nDir.first, nDir.second);
            break;
        default:
            break;
    }
    cout << idx << getX(idx) << getY(idx) << endl;
    for (int i : pieces[idx].pStack)
    {
        cout << i << "S" << endl;
    }
    if (pieces[idx].pStack.size() >= 4) return true;
    return false;
}

bool processTurn()
{
    // return: 게임이 이번 턴 동안 끝났는가?
    for (int ci=0;ci<K;ci++)
    {
        if (processMove(ci)) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // 외곽을 파란색으로
    for (int i=0;i<MAXN;i++)
    {
        gridColor[0][i] = 2;
        gridColor[N+1][i] = 2; // 가로
        gridColor[i][0] = 2;
        gridColor[i][N+1] = 2; // 세로
    }
    
    // 인풋
    cin >> N >> K;
    for (int i=1;i<=N;i++)
    {
        for (int j=1;j<=N;j++)
        {
            cin >> gridColor[i][j];
        }
    }
    int ty, tx, tDir;
    for (int i=0;i<K;i++)
    {
        cin >> ty >> tx >> tDir;
        list<int> nl;
        nl.push_back(i);
        Piece np = {ty, tx, tDir, nl}; // 두 말이 겹친 상태는 입력으로 주어지지 않는다.
        pieces[i] = np;
        gridPieces[ty][tx] = i;
    }
    
    // Solve
    for (int turn=0;turn<1000;turn++)
    {
        if (processTurn())
        {
            ret = turn;
            break;
        }
    }
    cout << ret << '\n';
    return 0;
}
