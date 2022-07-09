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
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll &i : a)cin >> i;
    sort(a.begin(), a.end());
    ll t;
    cin >> t;
    ll res = 0;
    ll cur = -1;
    for (ll i = 0; i < n; ++i) {
        if (cur != -1 && a[i] / t != cur)++res;
        cur = a[i] / t;
    }
    ++res;
    cout << res << "\n";
    return 0;
}