#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <vector>

using namespace std;

struct Point
{
    int x; int y; float angle; int prevPtr;
    
    void setAngle(int cx, int cy)
    {
        angle = atan2(x-cx, y-cy);
    }
    
    void setPrev(int index)
    {
        prevPtr = index;
    }
    
    bool operator<(Point cmp)
    {
        return cmp.angle > angle;
    }
};

struct Point pts[100001];
int N;

int ccw(int currPtr, int nextPtr)
{
    const Point& Prev= pts[pts[currPtr].prevPtr];
    int crossProd = (pts[currPtr].x-Prev.x)*(pts[nextPtr].x-pts[currPtr].x) - (pts[currPtr].y-Prev.y)*(pts[nextPtr].y-pts[currPtr].y);
    if (crossProd == 0) return 0;
    else return (crossProd > 0) ? 1 : -1;
}

int main()
{
    memset(pts, 0, sizeof(pts));
    cin >> N;
    Point lowest;
    
    // input
    for (int i=0;i<N;i++)
    {
        Point pt;
        pts[i] = pt;
        cin >> pt.x >> pt.y;
        if (lowest.y > pt.y) lowest = pt;
    }
    for (int i=0;i<N;i++)
    {
        pts[i].setAngle(lowest.x, lowest.y);
    }
    sort(pts, pts+N-1);
    
    // solve
    vector<int> stack;
    stack.push_back(0);
    stack.push_back(1);
    int currPt = 1;
    int nextPt = 2;
    
    while(nextPt < N)
    {
        for (int i=0;i<stack.size();i++)
        {
            cout << currPt << nextPt << endl;
        }
        cout << "=============" << endl;
        
        bool found = true;
        while (found)
        {
            switch (ccw(currPt, nextPt))
            {
                case -1:
                    stack.pop_back();
                    currPt = stack.back();//top of the stack
                    break;
                case 0:
                    stack.pop_back();
                case 1:
                    stack.push_back(nextPt);
                    currPt = nextPt;
                    nextPt++;
                    found = true;
                    break;
                default:
                    break;
            }
        }
    }
    
    cout << stack.size() << '\n';
    
    return 0;
}
