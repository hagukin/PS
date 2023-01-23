#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<ll> Vec2;
typedef vector<vector<ll >> Mat2;
constexpr int MOD = 1000000007;
ll N;
Vec2 fibVec = {0,1};
Mat2 fibMat {{0,1},{1,1}};

// dx식 행렬연산 사용
Mat2 mulMatMat(Mat2& m1, Mat2& m2)
{
    Mat2 ret;
    ret.push_back(Vec2(2,0));
    ret.push_back(Vec2(2,0));

    ret[0][0] = m1[0][0]*m2[0][0] + m1[1][0]*m2[0][1];
    ret[0][1] = m1[0][1]*m2[0][0] + m1[1][1]*m2[0][1];
    ret[1][0] = m1[0][0]*m2[1][0] + m1[1][0]*m2[1][1];
    ret[1][1] = m1[0][1]*m2[1][0] + m1[1][1]*m2[1][1];
    
    ret[0][0] %= MOD;
    ret[0][1] %= MOD;
    ret[1][0] %= MOD;
    ret[1][1] %= MOD;
    return ret;
}

Mat2 powMat(Mat2& m, ll power)
{
    if (power == 1) return m;
    Mat2 tmp;
    if (!(power%2))
    {
        Mat2 tmp = powMat(m, power/2);
        return mulMatMat(tmp, tmp);
    }
    tmp = powMat(m, power-1);
    return mulMatMat(m, tmp);
}

Vec2 mulVecMat(Vec2& v, Mat2& m)
{
    Vec2 ret(2, 0);
    ret[0] = m[0][0]*v[0] + m[0][1]*v[1];
    ret[1] = m[1][0]*v[0] + m[1][1]*v[1];
    
    ret[0] %= MOD;
    ret[1] %= MOD;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int ret;
    if (N==0) ret = 0;
    else if (N==1) ret = 1;
    else
    {
        Mat2 powedMat = powMat(fibMat, N-1);
        ret = mulVecMat(fibVec, powedMat)[1];
    }
    cout << ret << '\n';
    return 0;
}
