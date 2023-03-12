#include <string>
#include <iostream>
#include <vector>

using namespace std;
constexpr int MAXN = 201;

// union-find로 풀이 가능

int uf[MAXN]; // group

void init()
{
    for (int i=0;i<MAXN;++i) uf[i] = i;
    return;
}

int find_group(int x)
{
    if (uf[x] == x) return uf[x];
    int tmp = find_group(uf[x]);
    return uf[x] = tmp; // 찾는 과정에서의 최적화
}

void union_two(int a, int b)
{
    // a 예하로 b가 속한 그룹 전체가 들어간다
    uf[find_group(b)] = find_group(a);
    return;
}

int get_group_cnt(int n)
{
    int funcRet = 0;
    bool counted[MAXN] = {false,};
    for (int i=0;i<n;++i)
    {
        int c = find_group(uf[i]);
        if (!counted[c])
        {
            counted[c] = true;
            funcRet++;
        }
    }
    return funcRet;
}

int solution(int n, vector<vector<int>> computers) 
{
    init();

    for (int i=0;i<n;++i)
    {
        for (int j=i+1;j<n;++j)
        {
            if (computers[i][j]) union_two(i,j);
        }
    }

    return get_group_cnt(n);
}
