#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Lec
{
    int payment;
    int days;
    bool selected;
};

bool compLec(const Lec& l1, const Lec& l2)
{
    if (l1.days == l2.days)
        return l1.payment > l2.payment; // higher first
    return l1.days > l2.days; // higher first
}

int N;
vector<Lec> v;

void solve()
{
    int maxDay = v[0].days;
    for(int i=maxDay;i>=1;i--)
    {
        int tmp = -1;
        for (int j=0;j<N;j++)
        {
            if(v[j].days>=i && !v[j].selected && (tmp == -1 || v[j].payment > v[tmp].payment))
            {
                tmp = j;
            }
        }
        v[tmp].selected = true;
        
//         if (tmp != -1)
//             cout << i << "일은 " << v[tmp].payment << "원" << endl;
    }
    return;
}

int main()
{
    cin >> N;
    for(int i=0;i<N;i++)
    {
        int tp; int td;
        cin >> tp >> td;
        Lec lec = {tp, td, false};
        v.push_back(lec);
    }
    sort(v.begin(), v.end(), compLec);
    solve();
    return 0;
}
