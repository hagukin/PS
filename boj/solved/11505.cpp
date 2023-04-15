// 세그먼트로 풀이하는게 펜윅보다 훨씬 편한 문제의 예.
// update를 구현할 때 0이 들어간다고 어렵게 생각할 필요 없다

#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
constexpr int MOD = 1000000007;
ll arr[1000001];
ll *tree;

ll init(int node, int s, int e)
{
    // [s,e]
    if(s == e) return tree[node] = arr[s];
    int mid = s + (e-s)/2;
    return tree[node] = (init(2*node,s,mid) * init(2*node+1,mid+1,e)) % MOD;
}

ll mul(int node, int s, int e, int left, int right)
{
    if(left>e || right<s) return 1;
    if(left<=s && e<=right) return tree[node];
    int mid = s+(e-s)/2;
    return (mul(node*2, s, mid, left, right) * mul(node*2+1, mid+1,e,left,right)) % MOD;
}

ll update(int node, int s, int e, int idx, long long val)
{
    if(idx > e || idx < s) return tree[node];
    else if(s==e) return tree[node]=val;
    else
    {
        int mid = s+(e-s)/2;
        return tree[node] = (update(2*node,s,mid,idx,val)*update(2*node+1,mid+1,e,idx,val)) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M, K;
    int height,a;
    ll b, c;

    cin >> N >> M >> K;
    height = ceil(log2(N));
    tree = new long long[1<<(height+1)];
    
    for(int i=0;i<N;i++) cin >> arr[i];
    init(1,0,N-1);
    
    for(int i=0;i<M+K;i++)
    {
        cin >> a >> b >> c;
        if(a==1)
        {
            arr[b-1] = c;
            update(1,0,N-1,b-1,c);
        }
        else
        {
            cout << mul(1,0,N-1,b-1,c-1) << '\n';
        }
    }
    return 0;
}
