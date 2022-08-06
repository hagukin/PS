#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

const int MAX = 100000;
int N; int K; int searchTime = 0; int retCnt = 0;
int turns[MAX+1];
bool visited[MAX+1];

void bfs()
{
    queue<int> q;
    q.push(N);
    while (!q.empty())
    {
        int pos = q.front();
        q.pop();
        visited[pos] = true;
        
        if (pos == K)
        {
            if (!searchTime) {searchTime = turns[pos]; retCnt++;}
            else if (turns[pos] == searchTime) retCnt++;
        }
        else
        {
            if (pos+1 <= MAX && !visited[pos+1] && (!turns[pos+1] || turns[pos+1]==turns[pos]+1)) 
            {
                q.push(pos+1);
                turns[pos+1] = turns[pos]+1;
            }
            if (pos-1 >= 0 && !visited[pos-1] && (!turns[pos-1] || turns[pos-1]==turns[pos]+1)) 
            {
                q.push(pos-1); 
                turns[pos-1] = turns[pos]+1;
            }
            if (pos*2 <= MAX && !visited[pos*2] && (!turns[pos*2] || turns[pos*2]==turns[pos]+1)) 
            {
                q.push(pos*2);
                turns[pos*2] = turns[pos]+1;
            }
        }
    }
}

int main()
{
    cin >> N >> K;
    memset(turns, 0, sizeof(turns));
    memset(visited, false, sizeof(visited));
    
    bfs();
    
    cout << searchTime << '\n' << retCnt;
    return 0;
}
