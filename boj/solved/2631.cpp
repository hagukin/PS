#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

vector<int> v;
int N;

int solve()
{
    int lis[201];
    int ret = 0;
    
    // find lis
    for (int k = 0; k < N; k++) {
        lis[k] = 1;
        for (int j = 0; j < k; j++) {
            if (v[k] > v[j])
            {
                lis[k] = max(lis[k], lis[j] + 1);
            }
        }
        ret = max(lis[k], ret);
    }
    
    return N - ret;
}

int main()
{

    cin >> N;
    int tmp;
    for (int i = 0 ; i < N; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    
    cout << solve();

    return 0;
}
