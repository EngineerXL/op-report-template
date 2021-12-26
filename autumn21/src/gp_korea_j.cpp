#include <bits/stdc++.h>

using namespace std;

#define flush cout.flush

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pl = pair<ll, ll>;
const ll INF = 2e18;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ld eps = 1e-9;
const ld PI = acos(-1);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, l, t;
    cin >> n >> l >> t;
    vector<vector<pl>> g(n);
    for (ll i = 0; i < l; ++i) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        g[b].push_back({a, i});
    }
    vector<ll> a(n);
    for (ll &i : a)cin >> i;
    vector<ll> res(n, 0);
    for (ll i = 0; i < 8; ++i) {
        set<pl> s;
        vector<ll> d(n, INF);
        for (ll j = 0; j < n; ++j) {
            if ((1ll << i) & a[j]) {
                d[j] = -1;
                s.insert({d[j], j});
            }
        }
        while (!s.empty()) {
            auto it = *(s.begin());
            s.erase(it);
            ll v = it.second;
            ll w = it.first;
            for (auto to : g[v]) {
                ll rem = (w % l);
                ll edge_rem = (to.second % l);
                ll new_w = (edge_rem > rem ? w + edge_rem - rem : (w / l + 1) * l + edge_rem);
                if (w == -1)new_w = edge_rem;
                if (new_w < d[to.first]) {
                    s.erase({d[to.first], to.first});
                    d[to.first] = new_w;
                    s.insert({d[to.first], to.first});
                }
            }
        }
        for (ll k = 0; k < n; ++k) {
            if (d[k] + 1 <= t) {
                res[k] |= (1ll << i);
            }
        }
    }
    for (auto x : res) {
        cout << x << " ";
    }
    return 0;
}