#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> P; // y,x
constexpr int INF = 999999999;
constexpr int WALL = -1;
constexpr int BLANK = 987654321;
constexpr int DEADVIRUS = 987654322;
constexpr int VIRUS = 0;

int N, M;
int ret = INF;
int initGrid[51][51];
int virusCnt = 0; // 비활성, 활성 모두 포함한 바이러스 수 (2 갯수)
P viruses[10]; // 시작 바이러스들에 0~9까지의 id를 매기고 각 바이러스의 좌표 저장
int directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; // dydx

void spread(vector<vector<int >>& cGrid, vector<P>& roots)
{
    while (!roots.empty())
    {
        P cRoot = roots.back();
        roots.pop_back();
        
        vector<P> tiles;
        tiles.push_back(cRoot);
        cGrid[cRoot.first][cRoot.second] = 0; // 반드시 필요한 코드, 새 루트에서 0으로 시작하기 위해 필수
        
        while(!tiles.empty())
        {
            P cTile = tiles.back();
            tiles.pop_back();
            int cn = cGrid[cTile.first][cTile.second];
            
            for (int i=0;i<4;++i)
            {
                int ny = cTile.first+directions[i][0];
                int nx = cTile.second+directions[i][1];
                
                if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
                if (cGrid[ny][nx] == WALL) continue;
                else if (cGrid[ny][nx] == BLANK || cGrid[ny][nx] == VIRUS)
                {
                    cGrid[ny][nx] = cn+1;
                    
                    P nTile;
                    nTile.first = ny;
                    nTile.second = nx;
                    tiles.push_back(nTile);
                }
                else // 수 겹침
                {
                    if (cn+1 <= cGrid[ny][nx]) // 내 수가 같거나 더 작음
                    {
                        cGrid[ny][nx] = cn+1; // 덮어쓴다
                        
                        P nTile;
                        nTile.first = ny;
                        nTile.second = nx;
                        tiles.push_back(nTile);
                    }
                    else continue; // 내가 더 크면 현재 탐색방향으로의 탐색중단
                }
            }
        }
    }
    return;
}

inline bool isAllFilled(vector<vector<int>> cGrid)
{
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if (cGrid[i][j] == BLANK) return false;
        }
    }
    return true;
}

int doWithComb(vector<int>& cv)
{
    int funcRet = -1;
    vector<vector<int>> cGrid(N, vector<int>(N, WALL));
    vector<P> roots;
    
    // cGrid는 initGrid와 양식이 다르므로 변환
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if (initGrid[i][j] == 1) cGrid[i][j] = WALL;
            else if (initGrid[i][j] == 0) cGrid[i][j] = DEADVIRUS;
            else cGrid[i][j] = BLANK;
        }
    }
    
    // cv를 root로 변환
    for (const int& i : cv)
        roots.push_back(viruses[i]);
    
    // 선택된 바이러스들 활성화
    for (const P& p : roots)
        cGrid[p.first][p.second] = VIRUS;
    
    // bfs
    spread(cGrid, roots);
    if (!isAllFilled(cGrid)) return -1;
    
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            bool skip = false;
            for (int vv=0;vv<virusCnt;++vv)
                if (viruses[vv].first == i && viruses[vv].second == j) skip = true;

            if (!skip) funcRet = max(funcRet, cGrid[i][j]);
        }
    }
    return funcRet;
}

void combination(int pick, int searched, vector<int>& cv)
{
    if (cv.size() == pick)
    {
        int tmp = doWithComb(cv);
        if (tmp != -1) ret = min(ret, tmp);
        return;
    }
    else if ((9-searched) < (pick-cv.size())) return;
    else if (virusCnt-1 <= searched) return;
    
    cv.push_back(searched+1);
    combination(pick, searched+1, cv);
    cv.pop_back();
    combination(pick, searched+1, cv);
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    for (int i=0;i<51;++i)
    {
        for (int j=0;j<51;++j)
        {
            initGrid[i][j] = 1;
        }
    }
    
    bool hasVirus = false;
    bool hasBlank = false;
    
    cin >> N >> M;
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            cin >> initGrid[i][j];
            if (initGrid[i][j] == 2)
            {
                viruses[virusCnt].first = i;
                viruses[virusCnt].second = j;
                virusCnt++;
                hasVirus = true;
            }
            else if (initGrid[i][j] == 0) hasBlank = true;
        }
    }
    
    if (!hasBlank && hasVirus)
    {
        cout << 0 << '\n';
        return 0;
    }
    
    vector<int> v;
    combination(M, -1, v);
    
    if (ret == INF) ret = -1;
    cout << ret << '\n';

    return 0;
}
