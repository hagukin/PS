#include <iostream>
using namespace std;
typedef long long ll;
int N, M, K;
ll arr[1000001]; // 1번부터 입력
ll tree[1<<21]; // 노드는 1번(루트)부터 시작 (1000001 * 2 -1)

void init(int node, int start, int end)
{
    // arr의 start부터 end까지의 합이 node번 노드가 된다
    if (start == end)
    {
        tree[node] = arr[start];
        return;
    }
    init(node*2, start, (start+end)/2);
    init(node*2+1, (start+end)/2+1, end);
    // 이 시점부터 tree의 node*2와 node*2+1은 초기화되었음이 보장됨
    tree[node] = tree[node*2]+tree[node*2+1];
    return;
}

ll getSum(int node, int start, int end, const int& left, const int& right)
{
    // left에서 right까지의 합을 재귀적으로 구하기
    // start와 end는 현재 탐색중인 노드의 arr 범위
    // 1. start,end가 left,right에 완전히 포함될 경우
    if (left <= start && right >= end) return tree[node];
    // 2. 완전히 안겹치는 경우
    if (left > end || right < start) return 0;
    // 3. left,right가 start,end에 완전히 포함될 경우
    // 4. left,right가 start,end와 겹치는 경우
    ll l = getSum(node*2, start, (start+end)/2, left, right);
    ll r = getSum(node*2+1, (start+end)/2+1, end, left, right);
    return l+r;
}

void changeVal(const int& idx, int node, int start, int end, const ll& val)
{
    // 최초 호출 시 node는 루트가 되어야 한다.
    //  arr[idx]번 값을 val로 바꾸고 연관된 tree의 모든 값들을 수정한다.
    // 일단 arr[idx]까지 찾아 내려가고 찾으면 거슬러 올라오면서 연관된 값들은 수정해준다.
    if (start > idx || end < idx) return; // 수정하려는 값과 상관없는 노드임
    // start <= idx && end >= idx 이면서 start == end인 경우는 start == end == idx인 경우밖에 없음. 
    // 고로 == idx는 없애줘도 되는 부분이긴 함.
    if (start == end)
    {
        arr[idx] = val;
        tree[node] = val;
        return;
    }
    // 재귀적으로 l,r에서 idx를 찾아나선다
    changeVal(idx, node*2, start, (start+end)/2, val);
    changeVal(idx, node*2+1, (start+end)/2+1, end, val);
    // 이 부분부터는 이미 idx를 찾아 바꿨고, 자신의 자식 노드들이 업데이트되었음이 보장되기 때문에 값을 업데이트해준다.
    tree[node] = tree[node*2] + tree[node*2+1];
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M >> K;
    for (int i=1;i<=N;i++)
    {
        cin >> arr[i];
    }
    init(1, 1, N);
    int a, b; ll c;
    for (int j=0;j<M+K;j++)
    {
        cin >> a >> b >> c;
        if (a==1) changeVal(b, 1, 1, N, c);
        else if (a==2) cout << getSum(1, 1, N, b, c) << '\n';
    }
    return 0;
}
