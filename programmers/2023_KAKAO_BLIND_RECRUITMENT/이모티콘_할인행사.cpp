#include <string>
#include <vector>
#include <iostream>
using namespace std;

constexpr int SUBSCRIBED = -987654321;

int saleChart[4] = {10,20,30,40};

int totalSubs = 0;
int totalEmojiSales = 0;

void solve(vector<int>& sales, vector<int>& emoticons, vector<vector<int>>& users, const vector<vector<int>>& originUsers)
{
    // 기저: sales 길이가 emoticons의 길이가 되었을 경우
    if (sales.size() == emoticons.size())
    {
        users = originUsers;
        int plusSubs = 0;
        int emojiSales = 0;
        
        for (int u=0;u<users.size();++u)
        {
            for (int i=0;i<sales.size();++i)
            {
                if (sales[i] >= users[u][0]) // i번 이모티콘 구매 결정함
                {
                    int currPrice = emoticons[i] * (100-sales[i]) / 100.0f;
                    if (users[u][1] == SUBSCRIBED) {} // 이미 구독한 경우에는 그냥 안구매하고 지나감
                    else if (users[u][1] - currPrice <= 0) // 가격 초과, 환불 후 구독
                    {
                        emojiSales -= (originUsers[u][1] - users[u][1]); // 쓴 가격 환급
                        users[u][1] = SUBSCRIBED; // 더이상 소비하지 못하게 막는 장치
                        plusSubs++;
                    }
                    else
                    {
                        users[u][1] -= currPrice;
                        emojiSales += currPrice; // 매출 증가
                    }
                }
            }
        }
        
        // 최종 결과 저장
        if (plusSubs > totalSubs)
        {
            totalSubs = plusSubs;
            totalEmojiSales = emojiSales;
        }
        else if (plusSubs == totalSubs && emojiSales > totalEmojiSales)
        {
            totalEmojiSales = emojiSales;
        }
        return;
    }

    for (int s : saleChart)
    {
        sales.push_back(s);
        solve(sales, emoticons, users, originUsers);
        sales.pop_back();
    }
    return;
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer;
    vector<vector<int>> originUsers = users;
    
    vector<int> v;
    solve(v, emoticons, users, originUsers);
    answer.push_back(totalSubs);
    answer.push_back(totalEmojiSales);
    
    return answer;
}
