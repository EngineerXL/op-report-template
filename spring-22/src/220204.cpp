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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n, 0);
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == '#') {
                a[i] |= (1ll << j);
            }
        }
    }
    const ll nax = (1ll << m);
    vector<char> good(nax, 0);
    vector<vector<char>> can(nax, vector<char>(nax, 0));
    for (ll mask = 0; mask < nax; ++mask) {
        bool ok = true;
        for (ll j = 0; j < m - 1; ++j) {
            if (((1ll << j) & mask) && ((1ll << (j + 1) & mask))) {
                ok = false;
            }
        }
        if ((1ll << (m - 1)) & mask) {
            ok = false;
        }
        if (ok)good[mask] = 1;
    }
    for (ll mask1 = 0; mask1 < nax; ++mask1) {
        for (ll mask2 = 0; mask2 < nax; ++mask2) {
            bool ok = true;
            for (ll i = 0; i < m; ++i) {
                if ((1ll << i) & mask1) {
                    bool w = false;
                    if (i - 1 >= 0 && ((1ll << (i - 1)) & mask2)) {
                        w = true;
                    }
                    if (((1ll << i) & mask2)) {
                        w = true;
                    }
                    if (i + 1 < m && ((1ll << (i + 1)) & mask2)) {
                        w = true;
                    }
                    ok &= w;
                }
            }
            if (ok)can[mask1][mask2] = 1;
        }
    }
    vector<vector<ll>> dp(n, vector<ll>(nax, INF));
    for (ll i = n - 2; i >= 0; i -= 2) {
        for (ll mask = 0; mask < nax; ++mask) {
            if (!good[mask])continue;
            ll placed = __builtin_popcountll(mask);
            ll value = mask;
            for (ll j = m - 1; j >= 1; --j) {
                if ((1ll << (j - 1)) & mask) {
                    value |= (1ll << j);
                }
            }
            if ((value & a[i]) == a[i] && (value & a[i + 1]) == a[i + 1]) {
                for (ll mask2 = 0; mask2 < nax; ++mask2) {
                    if (i == n - 2) {
                        dp[i][mask] = min(dp[i][mask], placed);
                        continue;
                    }
                    if (!good[mask2])continue;
                    if (can[mask][mask2]) {
                        dp[i][mask] = min(dp[i][mask], placed + dp[i + 2][mask2]);
                    }
                }
            }
        }
    }
    ll res = INF;
    for (ll mask = 0; mask < nax; ++mask) {
        res = min(res, dp[0][mask]);
    }
    cout << res << "\n";
    return 0;
}