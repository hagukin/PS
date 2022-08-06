#include <iostream>
#include <queue>
#include <stdlib.h>
using namespace std;

struct Area
{
    int x1, y1, x2, y2;
};

struct Area quadrants[5];
int ret;

int main()
{
    for (int i=1;i<=4;i++)
    {
        int tx1, tx2, ty1, ty2;
        cin>>tx1>>ty1>>tx2>>ty2;
        Area a = {tx1, ty1, tx2, ty2};
        quadrants[i] = a;
    }
    
    int ax = max(quadrants[2].x2, quadrants[3].x2);
    int ay = min(quadrants[2].y2, quadrants[1].y2);
    
    int bx = min(quadrants[1].x2, quadrants[4].x2);
    int by = max(quadrants[4].y2, quadrants[3].y2);
    
    int cx = min(quadrants[2].x1, quadrants[3].x1);
    int cy = max(quadrants[2].y1, quadrants[1].y1);
    
    int dx = max(quadrants[4].x1, quadrants[1].x1);
    int dy = min(quadrants[4].y1, quadrants[3].y1);
    
    int kx = abs(dx-cx);
    int ky = abs(cy-dy);
    int k = abs(kx-ky);
    
    int combSqX = abs(cx-ax)+abs(bx-dx);
    int combSqY = abs(ay-cy)+abs(dy-by);
    
    if (kx > ky)
    {
        for (int i=1;i+k<=combSqY;i++)
        {
            int xdiff = (combSqX - i) + 1;
            int ydiff = (combSqY - i - k) + 1;
            
            if (!xdiff) ret += ydiff;
            if (!ydiff) ret += xdiff;
            if (xdiff && ydiff) ret += xdiff * ydiff;
        }
    }
    else
    {
        for (int i=1;i+k<=combSqX;i++)
        {
            int xdiff =  (combSqX - i - k) + 1;
            int ydiff = (combSqY - i) + 1;
            
            if (!xdiff) ret += ydiff;
            if (!ydiff) ret += xdiff;
            if (xdiff && ydiff) ret += xdiff * ydiff;
        }
    }
    cout << ret << '\n';

    return 0;
}
