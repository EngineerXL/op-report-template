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
const ll MAGIC = 32;

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
    for (ll i = 0; i < m; ++i) {
        for (ll j = max(0ll, i - MAGIC); j <= i; ++j) {
            ld E = pref[i] + pref[j] - bad;
            E -= (ld) (z[i].first * z[j].first);
            res = max(res, E);
        }
    	for (ll j = 0; j <= min(i, MAGIC); ++j) {
            ld E = pref[i] + pref[j] - bad;
            E -= (ld) (z[i].first * z[j].first);
            res = max(res, E);
        }
    }
    cout << fixed << setprecision(20);
    cout << res << "\n";
    return 0;
}
