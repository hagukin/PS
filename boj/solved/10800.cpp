#include <iostream>
#include <algorithm>
using namespace std;
int n;
int C[200020],S[2020];
pair<pair<int, int>, int> arr[200020];
int ans[200020];
 
int main() {
    scanf(" %d", &n);
    for (int i = 0; i < n; i++) {
        int w, c; scanf(" %d %d", &c, &w);
        arr[i] = { {w,c-1},i };
    }
    sort(arr, arr + n);
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        int weight = arr[i].first.first;
        int color = arr[i].first.second;
        int idx = arr[i].second;
 
        C[color] += weight; // 지금까지 나온 같은 색깔들 합 (단 무게 오름차순으로 iterate하는 중이므로 현재 공과 같거나 더 가벼운 공들만 샌다)
        S[weight] += weight; // 지금까지 나온 같은 무게들 합
        sum += weight;
 
        ans[idx] = sum - C[color] - S[weight] + weight; // 전체 무게합에서 내 무게를 두번 뺐으니(색깔 같고 무게 같으므로 두번빠짐) 한 번 더해준다.
        
        // 나랑 무게도 같고 색도 같은 공이 바로 전 인덱스라면 그 값과 내 값의 정답이 똑같아야 한다.
        // 이걸 처리를 안해주면 오답이 나오는데, 이유는 C와 S가 모두 같을 경우 그 색이 같은 공의 무게 역시 2번 빼지기 때문이다.
        // (이전 루프 때 그 공의 무게가 C와 S에 각각 2번 더해졌으므로)
        if (i != 0 && weight == arr[i - 1].first.first && color == arr[i - 1].first.second)
            ans[idx] = ans[arr[i - 1].second]; // ans[idx] += weight; 로 바꿔도 풀릴 것 같다고 처음에 착각했는데, 그 방법은 중복이 2개 있을 때만 먹힌다.
            // 즉 중복이 3개 이상 나오게 되면 +weight를 중복의 갯수에 비례한 횟수만큼 더해줘야 하므로 오답이 나온다.
            // 물론 중복이 몇개 나왔는지를 계속 카운트를 해준다음 += (cnt * weight)를 해주면 되긴 한다.
    }
    for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
}
