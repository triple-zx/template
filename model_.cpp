#include <algorithm>
#include <array>
#include <assert.h>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>

#include <map>
#include <math.h>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace asl
{
    typedef long long i64;

#include <stdint.h>

    template <typename numeric_type>
    class point
    {
    public:
        numeric_type x, y;

        point(numeric_type x = 0, numeric_type y = 0) : x(x), y(y) {}

        bool operator<(const point<numeric_type> &ri) const
        {
            if (x != ri.x)
                return x < ri.x;
            return y < ri.y;
        }

        point<numeric_type> &operator-=(const point<numeric_type> &ri)
        {
            x -= ri.x;
            y -= ri.y;
            return *this;
        }

        friend point<numeric_type> operator-(const point<numeric_type> &a, const point<numeric_type> &b)
        {
            return point<numeric_type>(a) -= b;
        }
    };

    template <typename numeric_type>
    std::ostream &operator<<(std::ostream &out, const point<numeric_type> &p)
    {
        return out << p.x << " " << p.y;
    }

    template <typename numeric_type>
    numeric_type cross(point<numeric_type> a, point<numeric_type> b)
    {
        return a.x * b.y - a.y * b.x;
    }

    template <typename numeric_type>
    int sign(numeric_type v)
    {
        if (v < 0)
            return -1;
        else if (v > 0)
            return +1;
        else
            return 0;
    }

    template <typename T>
    using vec = std::vector<T>;

} // namespace asl

#include <experimental/optional>

namespace asl
{
    template <typename numeric_type>
    using polygon = std::vector<point<numeric_type>>;

    template <typename numeric_type>
    polygon<numeric_type> convex_hull(std::vector<point<numeric_type>> cloud, bool allow_collinear = false, bool ccw = false)
    {
        int n = cloud.size(), k;
        std::vector<point<numeric_type>> ch(2 * n);

        sort(cloud.begin(), cloud.end());

        for (int i = k = 0; i < n; ch[k++] = cloud[i++])
            while (k > 1 && sign(cross(ch[k - 1] - ch[k - 2], cloud[i] - ch[k - 2])) >= int(allow_collinear))
                --k;

        for (int i = n - 2, t = k; i >= 0; ch[k++] = cloud[i--])
            while (k > t && sign(cross(ch[k - 1] - ch[k - 2], cloud[i] - ch[k - 2])) >= int(allow_collinear))
                --k;

        ch.resize(k - (k > 1));

        if (ccw)
        {
            std::reverse(ch.begin() + 1, ch.end());
        }

        return ch;
    }

} // namespace asl

#include <utility>

#include <tuple>

#include <random>

#define endl '\n'

using namespace std;
using namespace asl;

void solve()
{

    const int R = 98000;

    vec<i64> Y;
    Y.push_back(0);

    for (int i = 1; Y.back() + i <= R; i += 1)
        Y.push_back(Y.back() + i);

    reverse(Y.begin(), Y.end());

    vec<point<i64>> points;
    for (int i = 0; i < Y.size(); ++i)
        points.push_back({i, Y[i]});

    auto hull = convex_hull(points);
    hull.push_back(hull[0]);
    reverse(hull.begin(), hull.end());

    int p = 0;
    while (p + 1 < hull.size() && hull[p + 1].y < hull[p].y)
        ++p;

    hull.resize(p + 1);

    cerr << p + 1 << endl;
    for (int i = 0; i <= p; ++i)
        cerr << hull[i] << endl;
    cerr << "--" << endl;

    int bad = hull.back().x, good = hull[0].y;

    int n = bad + 1 + good;

    vec<pair<int, int>> edges;

    for (int i = 1; i <= bad - 1; ++i)
    {
        int u = i, v = i + 1;
        if (i & 1)
            swap(u, v);
        edges.push_back({u, v});
    }

    if (hull.back().y == 0)
    {
        int u = bad, v = n;
        if (bad & 1)
            swap(u, v);
        edges.push_back({u, v});
    }

    for (int i = 0; i < good; ++i)
        edges.push_back({n - i - 1, n - i});

    for (auto r : hull)
    {
        if (r.y == 0)
            continue;

        int u = r.x + 1;
        int v = n - r.y + 1;

        if (u % 2 == 0)
        {
            u--;
            v--;
            swap(u, v);
        }
        edges.push_back({u, v});
    }

    cout << n << " " << edges.size() << endl;
    for (auto [x, y] : edges)
        cout << x << " " << y << endl;
}

int main()
{
    srand(0);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
