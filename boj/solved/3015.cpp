#include <iostream>
#include <vector>
using namespace std;
long N;
vector<pair<long,long >> arr; // 문제 조건이 키가 2^31까지 가능하다 인데 int는 양수범위일때 2^31-1까지만 표현이 가능하므로 long 사용.
// unsigned int로도 풀이 가능해보이지만 내가 구현한 로직에서 prevI를 -1로 처음에 두고 시작해야 하므로 귀찮아서 일단 long으로 풀이
long ret = 0;

int main()
{
    cin >> N;
    pair<long,long> tmp;
    long i=0; long prevI=-1; // prevI의 초기값이 -1이어야 하는 이유: i>prevI 조건문을 처음 루프에서 만족한 상태여야 tmp가 초기화가 되기 때문.
    while (i<N)
    {
        // 같은 인풋에 대해 한번 더 루프를 도는 경우 cin을 무시하고 계속 이전 tmp값으로 진행
        if (i>prevI)
        {
            tmp.second = 1;
            cin >> tmp.first;
            prevI = i;
        }
    
        if (arr.empty()) // 빈 경우
        {
            arr.push_back(tmp);
            i++; //끝냄
        }
        else if (arr.back().first == tmp.first) // 크기가 같은 경우
        {
            ret += arr.back().second;
            arr.back().second++;
            //다시 루프 진행할 필요X, 대신 뒤에 큰게 있을 경우 +1
            if (arr.size() >= 2) ret += 1;
            i++; //끝냄
        }
        else
        {
            if (arr.back().first > tmp.first) //큰 경우
            {
                ret += 1;
                arr.push_back(tmp);
                i++; //끝냄
            }
            else //작은 경우
            {
                while(!arr.empty() && arr.back().first < tmp.first)
                {
                    ret += arr.back().second;
                    arr.pop_back(); //pop후 다시 루프 (그 뒤에 같거나 큰걸 만날 수 있으므로)
                }
            }
        }
    }
    cout << ret << '\n';
    
    return 0;
}

