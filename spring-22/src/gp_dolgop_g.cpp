#include <bits/stdc++.h>

using namespace std;

#define flush cout.flush

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pl = pair<ll, ll>;
const ll INF = 1e9 + 7;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ld eps = 1e-9;
const ld PI = acos(-1);

struct line {
    ld k;
    ld b;
};

ld inter(line f, line s) {
    return (s.b - f.b) / (f.k - s.k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<ll> a(n), b(n), x(n);
    for (ll i = 0; i < n; ++i)cin >> a[i] >> b[i] >> x[i];
    vector<pl> z;
    for (ll i = 0; i < n; ++i) {
        z.push_back({a[i], i});
        z.push_back({b[i], i});
    }
    z.push_back({1, -1});
    sort(z.begin(), z.end());
    ll m = z.size();
    vector<ld> pref(m, 0.0);
    ld bad = 0.0;
    for (ll i = 1; i < m; ++i) {
        pref[i] = pref[i - 1] + (ld) x[z[i].second] * 0.5;
        bad += (ld) x[z[i].second] * 0.5;
    }
    ld res = -1e18;
    deque<line> lines;
    for (ll i = 0; i < m; ++i) {
        ld k = -z[i].first;
        ld b = pref[i] - bad;
        line now = {k, b};
        bool need = true;
        while (!lines.empty()) {
            if (lines.front().k == k) {
                if (b > lines.front().b) {
                    lines.pop_front();
                } else {
                    need = false;
                    break;
                }
            } else {
                if (lines.size() == 1)break;
                line f = lines.front();
                lines.pop_front();
                line s = lines.front();
                lines.push_front(f);
                ld xx = inter(f, s);
                ld it = inter(f, now);
                if (it > xx - eps) {
                    lines.pop_front();
                } else break;
            }
        }
        if (need) {
            lines.push_front(now);
        }
        while (lines.size() > 1) {
            line f = lines.front();
            lines.pop_front();
            line s = lines.front();
            lines.push_front(f);
            ld xx = inter(f, s);
            if (xx < z[i].first + eps) {
                lines.pop_front();
            } else break;
        }
        ld it = lines.front().k * z[i].first + lines.front().b + pref[i];
        res = max(res, it);
//        cout << "found: " << it << " | ";
//        for (ll j = 0; j <= i; ++j) {
//            ld E = pref[i] + pref[j] - bad;
//            E -= (ld) (z[i].first * z[j].first);
//            cout << E << " ";
//        }
//        cout << "\n";
    }
    cout << fixed << setprecision(20);
    cout << res << "\n";
    return 0;
}
