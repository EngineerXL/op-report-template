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

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    vector<ll> p;
    for (ll i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            for (ll j = 0; j < n; ++j)p.push_back(a[i][j]);
        } else
            for (ll j = n - 1; j >= 0; --j) {
                p.push_back(a[i][j]);
            }
    }
    ll good = 0, bad = 0;
    for (ll i = 1; i < p.size(); ++i) {
        if (p[i] > p[i - 1])++bad;
        else ++good;
    }
    if (good < bad) {
        reverse(p.begin(), p.end());
    }
    for (ll i = 0; i < p.size(); ++i) {
        cout << p[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin >> t;
    while (t--)solve();
    return 0;
}
