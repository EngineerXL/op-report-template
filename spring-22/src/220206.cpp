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
vector<vector<ll>> dp;
vector<char> isLeaf;

void dfs(ll v, ll p) {
    if (isLeaf[v]) {
        dp[v][0] = 0;
        dp[v][1] = INF;
        return;
    }
    dp[v][0] = dp[v][1] = 0;
    for (auto to : g[v]) {
        if (to == p)continue;
        dfs(to, v);
        dp[v][0] += min(dp[to][1], 1ll + min(dp[to][0], dp[to][1]));
        dp[v][1] += min(dp[to][0], 1ll + min(dp[to][0], dp[to][1]));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    g.resize(n);
    dp.assign(n, vector<ll>(2, INF));
    isLeaf.assign(n, 0);
    for (ll i = 0; i < n - 1; ++i) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (n == 1) {
        cout << "0\n";
        return 0;
    }
    if (n == 2) {
        cout << "1\n";
        return 0;
    }
    ll st = -1;
    for (ll i = 0; i < n; ++i) {
        if (g[i].size() == 1)isLeaf[i] = 1;
        else st = i;
    }
    dfs(st, -1);
    cout << min(dp[st][0], dp[st][1]) << "\n";
    return 0;
}