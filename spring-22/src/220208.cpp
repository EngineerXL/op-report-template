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
    vector<pl> a(n);
    ll s = 0;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        s += a[i].second;
    }
    if (n == 2) {
        cout << "Yes\n";
        return;
    }
    vector<pl> p;
    for (ll i = 0; i < n; ++i) {
        p.push_back({s - a[i].second + a[i].first, i});
    }
    sort(p.begin(), p.end(), [&](const pl &x, const pl &y) {
        if (x.first != y.first) {
            return x.first > y.first;
        }
        return a[x.second] > a[y.second];
    });
    for (ll i = 1; i < n; ++i) {
        if (p[i].first > a[p[i - 1].second].first) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin >> t;
    while (t--)solve();
    return 0;
}