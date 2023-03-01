#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

deque<int> l;
deque<int> r;
deque<deque<int>> m;

template <typename T>
void backToFront(deque<T>& dq)
{
    dq.push_front(std::move(dq.back()));
    /*
    아주아주 중요하고 쉽게 놓칠만한 부분으로, 이 문제를 C++로 풀기에 불리한 이유이다.
    T가 deque<int>일 경우 우리는 dq에 최대 길이 50000의 덱을 push_front 해주어야 하는데,
    이때 아무 생각없이 그냥 dq.back()을 push해버리면 내부적으로 복사되어 시간초과가 발생한다. (shiftRow의 시간복잡도가 O(N)이 되어버리기 때문)
    때문에 std::move()를 이용하여 강제적으로 이동생성자를 호출해주어야 한다.
    여기서 이동생성자를 호출하는 것이 가능한 이유는 어차피 다음 라인에서 dq.pop_back()으로 비어있는(값이 텅 빈) dq.back()을 pop해줄 것이기 때문에
    미리 이동생성자로 옮겨버려도 아무런 지장이 없다.
    */
    dq.pop_back();
    return;
}

void shiftRow()
{
    backToFront<int>(l);
    backToFront<int>(r);
    backToFront<deque<int>>(m);
    return;
}

void rotate()
{
    int tmp3 = r.back();
    r.pop_back();
    
    int tmp4 = l.front();
    l.pop_front();
    
    m[0].push_front(tmp4);
    m[m.size()-1].push_back(tmp3);
    
    int tmp1 = m[0].back();
    int tmp2 = m[m.size()-1].front();
    
    r.push_front(tmp1);
    l.push_back(tmp2);
    
    m[0].pop_back();
    m[m.size()-1].pop_front();
    return;
}

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) {
    vector<vector<int>> answer;
    int R = rc.size();
    int C = rc[0].size();

    for (int i=0;i<R;++i)
    {
        l.push_back(rc[i][0]);
        r.push_back(rc[i][C-1]);
        deque<int> tmp;
        for (int j=1;j<C-1;++j) tmp.push_back(rc[i][j]);
        m.push_back(tmp);
    }
    
    int rotN = 0;
    for (string& s : operations)
    {
        if (s == "Rotate") rotate();
        else if (s == "ShiftRow") shiftRow();
    }
    
    for (int i=0;i<R;++i)
    {
        answer.push_back(vector<int>());
        answer[i].push_back(l.front());
        l.pop_front();
        for (int j=1;j<C-1;++j)
        {
            answer[i].push_back(m.front().front());
            m.front().pop_front();
        }
        m.pop_front();
        answer[i].push_back(r.front());
        r.pop_front();
    }
    
    return answer;
}
