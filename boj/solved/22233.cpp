#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

unordered_set<string> m;
int N, M, ret = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    
    string s;
    for(int i=0;i<N;i++)
    {
        cin >> s;
        m.insert(s);
        ret += 1;
    }
    
    for(int i=0;i<M;i++)
    {
        int start = 0;
        cin >> s;
        for(int j=0; j<=s.size(); j++)
        {
            if (s[j]==',' || j==s.size())
            {
                string tmp = s.substr(start, j-start);
                if (m.find(tmp) != m.end())
                {
                    m.erase(tmp);
                    ret--;
                }
                start = j+1;
            }
            
        }
        cout << ret << '\n';
    }

    return 0;
}
