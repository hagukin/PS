/*
5
-2 6 -97 -6 98
일단 정렬
-97 -6 -2 6 98
O = 두 수를 더한 합의 모든 경우의 수(5000+4999+...+1 = 약 1250만) * 그 경우의 수와 가장 가까운값 찾기(약 log2 5000 * 7)
*/
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
typedef long int lint;
int N;
lint retSum = LONG_MAX; // 세 수의 합
lint ret[3]; // 세 수
lint arr[5001];
int ds[9] = {-4,-3,-2,-1,0,1,2,3,4}; // -3~3도 될듯함

int getClosest(lint x, int i, int j)
{
    // arr 수 중 x에 가장 근접한 값의 인덱스를 반환한다.
    int lbi = lower_bound(arr, arr+N, x) - arr;
    // x를 찾은 경우
    if (arr[lbi] == x && lbi != i && lbi != j) return lbi;
    // -24 -6 -3 -2 61 98 100
    //      c  i  j             (c=closest to -1*(i+j))
    // 어차피 답은 c-3, c-2, c-1, c, c+1, c+2, c+3 중 하나이므로 다 해보면 됨.
    lint tmp = LONG_MAX; 
    int fRet;
    for (int d : ds)
    {
        if (lbi+d >= N || lbi+d < 0 || lbi+d==i || lbi+d==j) continue;
        if (abs(arr[lbi+d]-x) < tmp)
        {
            tmp = abs(arr[lbi+d]-x);
            fRet = lbi+d;
        }
    }
    return fRet;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i=0;i<N;i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr+N);
    
    lint sum, tmp;
    int thirdIdx;
    for (int i=0;i<N;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            sum = arr[i] + arr[j];
            thirdIdx = getClosest(sum*-1, i, j);
            tmp = abs(sum + arr[thirdIdx]);
            if (tmp < retSum)
            {
                retSum = tmp;
                ret[0] = arr[i];
                ret[1] = arr[j];
                ret[2] = arr[thirdIdx];
            }
        }
    }
    sort(ret, ret+3);
    cout << ret[0] << " " << ret[1] << " " << ret[2] << '\n';
    return 0;
}
