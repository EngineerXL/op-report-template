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

vector<vector<ll>> g;
vector<ll> a;
vector<ll> t;
vector<ll> dp;
vector<ll> dp_vis;

void dfs(ll v, ll p) {
    dp[v] = 0;
    dp_vis[v] = 0;
    for (auto to : g[v]) {
        if (to == p)continue;
        dfs(to, v);
    }
    ll s = 0;
    for (auto to : g[v]) {
        if (to == p)continue;
        dp_vis[v] += dp[to] - a[to];
        s += dp[to] - a[to];
    }
    for (auto to : g[v]) {
        if (to == p)continue;
        dp[v] = max(dp[v], s - (dp[to] - a[to]) + dp[to]);
    }
    ll m = g[v].size();
    vector<ll> d(m, 0);
    vector<ll> suff(m, 0);
    vector<ll> pref(m, 0);
    for (ll i = 0; i < m; ++i) {
        if (g[v][i] == p)continue;
        ll to = g[v][i];
        d[i] = dp_vis[to] + a[to] - (dp[to] - a[to]);
    }
    for (ll i = 0; i < m; ++i) {
        pref[i] = max((i - 1 >= 0 ? pref[i - 1] : 0), d[i]);
    }
    for (ll i = m - 1; i >= 0; --i) {
        suff[i] = max((i + 1 < m ? suff[i + 1] : 0), d[i]);
    }
    for (ll i = 0; i < m; ++i) {
        if (g[v][i] == p)continue;
        ll to = g[v][i];
        if (t[to] != 3)continue;
        dp[v] = max(dp[v],
                    s - (dp[to] - a[to]) + dp[to] + max((i - 1 >= 0 ? pref[i - 1] : 0), (i + 1 < m ? suff[i + 1] : 0)));
    }
    dp[v] += a[v];
}

void solve() {
    g.clear();
    dp.clear();
    dp_vis.clear();
    ll n;
    cin >> n;
    dp.resize(n);
    dp_vis.resize(n);
    g.resize(n);
    a.resize(n);
    t.resize(n);
    for (ll &i : a)cin >> i;
    for (ll &i : t)cin >> i;
    for (ll i = 0; i < n - 1; ++i) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, 0);
    cout << dp[0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin >> t;
    while (t--)solve();
    return 0;
}
