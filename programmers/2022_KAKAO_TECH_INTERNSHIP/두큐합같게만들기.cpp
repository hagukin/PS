#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = 0;
    queue<int> q1;
    queue<int> q2;
    long long q1Sum = 0, q2Sum = 0;
    int lenSum = 0;
    for (int i=0;i<queue1.size();++i) {q1Sum += queue1[i]; q1.push(queue1[i]); ++lenSum;}
    for (int i=0;i<queue2.size();++i) {q2Sum += queue2[i]; q2.push(queue2[i]); ++lenSum;}
    if (q1Sum == q2Sum) return 0;
    
    while (q1Sum != q2Sum && !q1.empty() && !q2.empty() && answer < lenSum * 2)// 여기서 answer < lenSum이 아니라 answer < lenSum*2로 하는게 중요하다!
    /*
    2 2 2 2
    1 1 3 8
    을
    3
    8 2 2 2 2 1 1 로 만드는 경우를 생각하면
    lenSum회 이상의 이동이 필요함을 알 수 있다.
    */
    {
        int q1f = q1.front();
        int q2f = q2.front();
        ++answer;
        if (q1Sum < q2Sum)
        {
            q1.push(q2f);
            q2.pop();
            q1Sum += q2f;
            q2Sum -= q2f;
        }
        else
        {
            q2.push(q1f);
            q1.pop();
            q2Sum += q1f;
            q1Sum -= q1f;
        }
    }
    if (q1Sum != q2Sum) return -1;
    return answer;
}
