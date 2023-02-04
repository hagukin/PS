#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> P; // y,x
constexpr int WALL = -1;
constexpr int BLANK = 987654321;

int N, M;
int ret = -1;
int initGrid[51][51];
P viruses[10]; // 시작 바이러스들에 0~9까지의 id를 매기고 각 바이러스의 좌표 저장

void spread(vector<vector<int >>& cGrid, vector<P>& roots)
{
    return; // TODO
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

void doWithComb(vector<int>& cv)
{
    vector<vector<int>> cGrid(N, vector<int>(N, WALL));
    vector<P> roots;
    
    // cGrid는 initGrid와 양식이 다르므로 변환
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if (initGrid[i][j] == 1) cGrid[i][j] = WALL;
            else if (initGrid[i][j] == 0 || initGrid[i][j] == 2) cGrid[i][j] = BLANK;
        }
    }
    
    // cv를 root로 변환
    for (const int& i : cv)
        roots.push_back(viruses[i]);
        
    // root 좌표들을 0으로
    for (const P& p : roots)
        cGrid[p.first][p.second] = 0;
    
    // 일단 첫 step 돌림.
    spread(cGrid, roots);
    
    
    /*** DEBUG ***/
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if (cGrid[i][j] == WALL) cout << '#';
            else if (cGrid[i][j] == BLANK) cout << '.';
            else cout << cGrid[i][j];
        }
        cout << endl;
    }
    cout << "================" << endl;
    
    
    
    // 클리어 가능한 격자인지 판정
    if (!isAllFilled(cGrid)) return;
    
    while (!roots.empty())
    {
        // 이 과정에서 roots가 하나씩 지워지고 cGrid는 변형됨, 또 겹치는 좌표는 roots에 추가됨.
        spread(cGrid, roots);
    }
    
    // 답안 구하기 o(25000)
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            for (const P& v : viruses)
                if (v.first == i && v.second == j) continue;
            
            ret = max(ret, cGrid[i][j]);
        }
    }
    return;
}

void combination(int pick, int searched, vector<int>& cv)
{
    // 0~9중 pick개를 뽑는 가능한 모든 경우를 탐색함 (dfs)
    // 0부터 9까지 순서대로 진행하며 뽑을지 안뽑을지를 선택하므로 총 시간복잡도는 2^10 이하
    // searched는 현재 searched번까지 뽑을지 안뽑을지가 결정되었음을 의미 (0~9)
    // cv가 pick개가 되는 순간 doWithComb()를 호출 후 탐색 종료
    // searched가 9를 넘었는데 pick개가 아직 안되었으면 곧장 탐색종료
    // 여기서 최적화 가능 
    // -> pick이 7이고 searched가 5인데 cv.size()가 0이면 어차피 남은 어떤 경우에도 7개를 뽑을 수 가 없으므로 곧장 탐색 종료시켜버려도 됨.)
    if (cv.size() == pick)
    {
        /*** DEBUG ***/
        for (auto i : cv) cout << i << ", ";
        cout << endl;
        
        
        
        return doWithComb(cv);
    }
    else if ((9-searched) < (pick-cv.size())) return; // TODO: +-1 오차있을수도, 검증 필요
    
    cv.push_back(searched+1); // 선택한 경우
    combination(pick, searched+1, cv);
    cv.pop_back(); // 안한 경우
    combination(pick, searched+1, cv);
    return;
}

int main()
{
    /*
    bfs로 모든 접근 가능한 빈칸 탐색하면서 각 빈칸들에 택시거리 작성.
    이때 만약 이미 해당 칸에 수가 있다면 더 작은 수를 남기고 해당 좌표에서의 추가적인 탐색을 중단
    (어차피 다음 스텝에 이어서 할꺼니까), 또 해당 좌표 기록. 겹치는 칸은 아래에서는 #으로 표기
    이때 바이러스도 먹어야 함. (바이러스를 안먹으면 못먹는 빈칸이 있을 수 있음)
    단 우리가 구하는 건 모든 빈칸을 채우는 최소시간이므로 이후 정답을 구하는 과정에서는 
    해당 격자에서의 최대 숫자를 구할 때 바이러스가 있던 칸들에 기재된 수들은 제외해야함.
    
    0 1 2 # - - 2
    1 2 - 3 - 0 1
    2 - - 2 - 1 2
    3 - 2 1 2 2 3
    # 2 1 0 1 - -
    5 - 2 1 2 3 4
    6 - 3 2 3 4 5
    
    if 이시점에서 만약 빈 칸이 남아있다면 -1 return
    else 방금 전 겹쳤던 칸들에 대해 동일한 작업 진행 (bfs)
    0 1 2 3 - - 2
    1 2 - 3 - 0 1
    2 - - 2 - 1 2
    3 - 2 1 2 2 3
    3 2 1 0 1 - -
    4 - 2 1 2 3 4
    5 - 3 2 3 4 5  (5,0)가 변경되었음에 유의
    
    느낌상 한번 시행후 또 겹칠 수는 없는 것 같음.
    그렇다면 최악의 경우는 10*50*4*2 이하로 잡힘.
    그럼 총 시간복잡도는
    
    10C5 (바이러스 선택중 최악의 경우) * 10 * 400 = 1008000 미만.. 너무 작은데??
    만약 두 번 이상 겹칠 수 있다고 해도 이정도면 커버 가능할듯하다
    */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // 벽으로 채우기
    for (int i=0;i<51;++i)
    {
        for (int j=0;j<51;++j)
        {
            initGrid[i][j] = 1;
        }
    }
    
    cin >> N >> M;
    int vCnt = 0;
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            cin >> initGrid[i][j];
            if (initGrid[i][j] == 2)
            {
                viruses[vCnt++] = {i,j};
            }
        }
    }
    
    // 10 C M
    // 최대 M개 활성화 시킬수 있을 때 최대한 많이(=M개만큼) 활성화시키는게 무조건 유리함
    vector<int> v;
    combination(M, -1, v);

    return 0;
}
