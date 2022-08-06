#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int N;
int M; // 현재 mi의 인덱스 이상의 인덱스를 가진 값들 중 최댓값
int mi = INT_MAX; // 현재까지 입력받은 값들 중 최솟값
int prevM;
int prevRet = 0;
vector<int> A;

void updateM(int x, bool force)
{
    if (x>M || force) M = x;
}

void coutRet(int ret)
{
    prevRet = ret;
    cout << ret << ' ';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> N;
    int tmp;
    for (int i=0;i<N;i++)
    {
        cin >> tmp;
        A.push_back(tmp);
        
        bool miChanged = false;
        if (mi > tmp) { mi = tmp; prevM = INT_MIN; miChanged = true; }
        
        updateM(tmp, miChanged); // tmp는 항상 mi와 인덱스가 같거나 크므로 무조건 넘겨준다.
        
        if (M - mi > prevRet) coutRet(M - mi);
        else coutRet(prevRet);
    }

    return 0;
}
