#include <iostream>
using namespace std;
typedef long long ll;
constexpr ll DIV = 1000000007;
int N, M, K;
int arr[1000010];
ll BIT[1000010]; // 0번 인덱스 사용X

inline ll getLSB(ll x) // least significant bit의 인덱스 반환 O(logN)
{
    ll funcRet = 0;
    while (x!=0 && ((x&1)!=1))
    {
        x = x >> 1;
        funcRet++;
    }
    return funcRet;
}

inline ll delBit(ll x, ll bIdx) // x의 bIdx번 비트를 0으로
{
    x = (x & ~(1 << bIdx));
    return x;
}

ll getMul(ll x) // array의 1~x번 인덱스까지의 곱
{
    ll funcRet = 1;
    while(x!=0)
    {
        funcRet *= BIT[x];
        x = delBit(x,getLSB(x));
    }
    return funcRet;
}

ll getAns(int m, int n) // m <= n
{ 
    return (getMul(n) / getMul(m-1)); // TODO: mod DIV
}

inline void changeVal(int idx, int v)
{
    //arr[idx]를 v로 변경
    int originIdx = idx;
    if (BIT[idx] == 0) BIT[idx] = 1; //// TODO 이부근 수정필요
    while(idx<=N)
    {
        BIT[idx] *= v;
        if (arr[originIdx] != 0) BIT[idx] /= arr[originIdx];
        idx += 1<<(getLSB(idx));
    }
    arr[originIdx] = v;
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M >> K;

    // init array
    for (int i=1;i<=N;++i)
    {
        cin >> arr[i];
        BIT[i] = arr[i];
    }
    // construct BIT
    for (int i=1;i<=N;++i)
    {
        int adj = i + (1<<getLSB(i));
        if (adj > N) continue; // break해도 되지않나?
        BIT[adj] *= BIT[i];
    }
    
    int a, b, c;
    for (int j=0;j<M+K;++j)
    {
        cin >> a >> b >> c;
        if (a == 1) changeVal(b,c);
        else if (a == 2) cout << getAns(b,c) << '\n';
    }
    for (int i=1;i<=N;++i) cout << BIT[i] << "  &  " << getMul(i) << endl;

    return 0;
}
