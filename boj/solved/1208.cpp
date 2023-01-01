#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int N, S;
ll ret = 0;
int nums[41];
vector<int> v1; // [0,N/2)
vector<int> v2; // [N/2,end)

void dfs(int ci, int e, vector<int>& v, int csum)
{
    // nums인덱스 [s,e)에서 가능한 모든 조합들의 합들을 v에 저장한다
    if (ci==e)
    {
        v.push_back(csum);
        return;
    }
    dfs(ci+1,e,v,csum+nums[ci]); // ci 선택
    dfs(ci+1,e,v,csum); // 미선택
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> S;
    for (int i=0;i<N;++i)
    {
        cin >> nums[i];
    }
    dfs(0,N/2,v1,0);
    dfs(N/2,N,v2,0);
    
    // v2를 정렬
    // 어차피 벡터 둘 중 하나는 for loop을 돌릴 거기 때문에 정렬은 하나만 해줘도 된다
    sort(v2.begin(), v2.end());
    for (const auto& x : v1)
    {
        auto&& tmp = lower_bound(v2.begin(), v2.end(), S-x);
        if (*tmp != S-x) continue; // 정확한 값이 아님
        if (tmp == v2.end()) continue; // 값 없음
        // cout << *tmp << " and " << x << endl;
        
        // 값이 존재함을 확인했다면 그 값이 몇개 존재하는지도 확인해야함
        // v2 = 1 2 3 3 3 4인데 이분탐색으로 3을 찾으면 idx 2에 위치한 3이 걸리므로 나머지 3의 갯수도 파악해야함.
        int cnt = upper_bound(v2.begin(), v2.end(), S-x) - tmp;
        ret += cnt;
    }
    // 목표값이 0인 경우 {} + {} 도 0으로 취급하므로 이 경우의 수를 빼주어야 한다.
    // (문제 조건에서 크기가 "양수"인 부분수열만 고려한다)
    if (S == 0) ret--;
    cout << ret << '\n';
    return 0;
}
