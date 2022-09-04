#include <iostream>
#include <list>
using namespace std;
constexpr int MAXN = 14;

// TODO: 시간없어서 일단 스킵
// 작성할거 많음

struct Piece
{
private:
    int _y, _x;
    int _dir; // rlud 1234
public:
    list<int>& pStack; // 이 말이 속해있는 stack. l->r: 맨 위에서 맨 아래로
    void getY(int idx)
    {
        if (canMove(idx)) return pieces[idx]._y;
        else return getY(pieces[idx].pStack.back());
    }
    
    void getX(int idx)
    {
        if (canMove(idx)) return pieces[idx]._x;
        else return getX(pieces[idx].pStack.back());
    }
    
    void setY(int idx, int val)
    {
        pieces[idx].y = val;
        if (canMove(idx))
    }
    
    void setX(int idx, int val)
    {
        
    }
};

int N, K, ret=-1;
int gridColor[14][14] = {0,};
int gridPieces[14][14]; // 해당 칸의 가장 아래에 있는 말의 번호. 없으면 0
int pieces[11];
pair<int,int> nToDir[4] = {{0,0},{1,0},{-1,0},{0,-1},{0,1}}; // rlud 1234


int getTileColor(int cy, int cx, int dy, int dx)
{
    return gridColor[cy+dy][cx+dx];
}

bool canMove(int idx)
{
    // idx번 말이 가장 아래에 있는가?
    return idx == piece[idx].pStack.back();
}

bool processMove(int idx)
{
    // return: 길이 4 이상의 stack이 만들어졌는가?
    if (!canMove(idx)) return false;
    
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
        Piece np = {ty, tx, tDir}; // 두 말이 겹친 상태는 입력으로 주어지지 않는다.
        piece[i] = np;
        gridPieces[ty][tx].push_back(i);
    }
    
    // Solve
    for (int turn=0;turn<1000;turn++)
    {
        if (processTurn())
        {
            ret = turn;
            gameCouldEnd = true;
            break;
        }
    }
    cout << ret << '\n';
    return 0;
}
