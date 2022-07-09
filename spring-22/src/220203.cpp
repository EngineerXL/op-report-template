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

using graph = vector< vector<int> >;

void dfs(int u, int prev, const graph & g, vector<int> & dp, int & ans) {
//    cout << "dfs " << u + 1<< endl;
    for (int v : g[u]) {
        if (v != prev) {
            dfs(v, u, g, dp, ans);
            dp[u] += dp[v];
        }
    }
//    cout << "dfs " << u + 1 << ' ' << dp[u] << endl;
    if (dp[u] >= 2) {
        ++ans;
        dp[u] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int m = n - 1;
    graph g(n);
    for (int i = 0; i < m; ++i) {
        int p;
        cin >> p;
        --p;
        g[i + 1].push_back(p);
        g[p].push_back(i + 1);
    }
    vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
        dp[i] = (g[i].size() > 1 ? 0 : 1);
//        cout << i + 1 << ' ' << dp[i] << endl;
    }
    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (!dp[i]) {
            start = i;
            break;
        }
    }
    if (start == -1) {
        cout << "1\n";
    } else {
        int ans = 0;
        dfs(start, -1, g, dp, ans);
        cout << ans << '\n';
    }
    return 0;
}