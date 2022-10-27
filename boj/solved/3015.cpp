#include <iostream>
#include <vector>
using namespace std;
int N;
vector<pair<int,int >> arr;
int ret = 0;

int main()
{
    cin >> N;
    pair<int,int> tmp;
    for (int i=0;i<N;++i)
    {
        tmp.second = 1;
        cin >> tmp.first;
        
        if (arr.empty()) // 빈 경우
        {
            arr.push_back(tmp);
            continue;
        }
        else if (arr[arr.size()-1].first == tmp.first) // 크기가 같은 경우
        {
            ret += arr[arr.size()-1].second;
            cout << "같은 경우 +" << arr[arr.size()-1].second << endl;
            if (arr.size()-1 > 0) {ret += 1; cout << "같은경우 추가로 큰거랑 마주침 +1" << endl;} // 뒤에 큰게 하나 이상이 있음이 보장되는 경우
            arr[arr.size()-1].second++;
        }
        else // 크기가 다른 경우
        {
            if (arr[arr.size()-1].first > tmp.first) // 큰 경우
            {
                ret += 1;
                cout << "큰경우 +1" << endl;
            }
            else // 작은 경우
            {
                while(!arr.empty() && arr[arr.size()-1].first < tmp.first)
                {
                    ret += arr.back().second;
                    cout << "작은경우 +" << arr.back().second << endl;
                    arr.pop_back();
                }
                if (!arr.empty()) ret++; // 큰거와 만남
            }
            arr.push_back(tmp);
        }
    }
    
    //test
    for (auto& x : arr)
    {
        cout << x.first << x.second << endl;
    }
    
    cout << ret << '\n';
    
    return 0;
}
