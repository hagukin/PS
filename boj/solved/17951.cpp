#include <iostream>
#include <cstring>
using namespace std;

int N, K, sum;
int score[100001];

int getGroupCnt(int x)
{
    int groupCnt = 0;
    int tmp = 0;
    for (int i=0;i<N;i++)
    {
        tmp += score[i];
        if (tmp >= x)
        {
            tmp = 0;
            groupCnt++;
        }
    }
    return groupCnt;
}

// 틀린 풀이 (off by one)
// int solve()
// {
//     int lo = 0, hi = sum, mid;
//     while (lo+1 < hi)
//     {
//         mid = (lo+hi)/2;
//         if (getGroupCnt(mid) >= K) lo = mid;
//         else hi = mid;
//     }
//     return lo;
// }
// 반례: lo가 맨 우측 t까지 닿기 전에 lo+1 < hi가 만족되어 값이 반환되어버림.
// f f f f t t
// l         h
//     l     h
//       l   h
//         l h
//         m

// 바른 풀이
int solve()
{
    int lo = 0, hi = sum, mid;
    while (lo <= hi)
    {
        mid = (lo+hi)/2;
        if (getGroupCnt(mid) >= K) lo = mid+1;
        else hi = mid-1;
    }
    return hi;
}
// f f f f t t
// l         h
//       l   h
//           lh
//           h l
// return h
// t t f f f f
// l         h
// l h
//   lh
//   h l
// return h

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(score, 0, sizeof(score));
    cin >> N >> K;
    for (int i=0;i<N;++i)
    {
        cin >> score[i];
        sum += score[i];
    }
    cout << solve() << '\n';
    return 0;
}
