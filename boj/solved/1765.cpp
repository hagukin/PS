#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, m;
vector<int> enemList[1001];
int group[1001];
bool isRoot[1001];

int getRoot(int a)
{
    if (group[a] == a) return a;
    else
    {
        int tmp = getRoot(group[a]);
        group[a] = tmp; // update root
        return tmp;
    }
}

void unionTwo(int a, int b)
{
    // 루트끼리 합쳐야 한다
    int ra = getRoot(a); 
    int rb = getRoot(b);
    
    if (rb > ra) group[rb] = ra;
    else group[ra] = rb;
}

int getGroupCnt()
{
    // 총 group의 갯수를 구한다
    int cnt = 0;
    for (int i=1;i<=n;i++)
    {
        int tmp = getRoot(i);
        if(!isRoot[tmp])
        {
            isRoot[tmp] = true;
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    // init
    cin >> n >> m;
    memset(isRoot, false, sizeof(isRoot));
    for (int i=0;i<=n;i++)
    {
        group[i] = i;
    }
    
    char rl; int ta, tb;
    for (int j=0;j<m;j++)
    {
        cin >> rl >> ta >> tb;
        if (rl == 'E') 
        {
            enemList[ta].push_back(tb);
            enemList[tb].push_back(ta); 
            /*
            이 부분 때문에 다 맞혀놓고 두번 틀림. friends인 경우 그냥 unionFind(ta, tb); 한번만 해주면 되는데 enemy인 경우 ta에 tb를 넣어주고 tb에도 ta를 넣어줘야 함.
            이유는 만약 tb에 ta를 안넣어줄 경우 F 1 5 입력 이후 F 5 8 같은 입력이 주어질 경우 1에는 5가, 5에는 8이 들어가지만 1과 8이 서로 연결되지 않음.
            1: 5
            5: 8
            8: 
            
            그러나 양쪽에 다 넣어주면 다음과 같은 형태가 됨.
            1: 5
            5: 1 8
            8: 5
            때문에 1,8이 같은 vector 내에 들어가게 되므로 얘들이 union될 수 있게 됨.
            
            처음에 이런 실수를 하게 된 이유는 입력 시 p<q는 보장되지만 p1<p2는 보장되지 않기 때문임. (즉 하나의 입력 내에서만 대소관계가 보장되고 입력들 간에는 대소관계가 바뀔 수도 있음)
            */
        }
        else unionTwo(ta, tb); // 친구
    }
    
    // 적의 적 union
    for (int k=1;k<=n;k++)
    {
        int root;
        if (enemList[k].empty()) continue;
        root = enemList[k][0];
        for (int l : enemList[k])
        {
            unionTwo(root, l);
        }
    }
    
    // 답 구하기
    cout << getGroupCnt() << '\n';
    return 0;
}
