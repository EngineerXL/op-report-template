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

const ll N = 2e5;

ll fact[N + 1];
ll inv[N + 1];

ll modPow(ll x, ll n, ll m) {
    if (n == 0)return 1;
    ll u = modPow(x, n / 2, m);
    u = (u * u) % m;
    if (n % 2 == 1) u = (u * x) % m;
    return u;
}

ll C(ll n, ll k) {
    if (n < k)return 0;
    return (((fact[n] * inv[k]) % mod2) * inv[n - k]) % mod2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    fact[0] = 1;
    for (ll i = 1; i <= N; ++i) {
        fact[i] = (fact[i - 1] * i) % mod2;
    }
    inv[N] = modPow(fact[N], mod2 - 2, mod2);
    for (ll i = N - 1; i >= 0; --i) {
        inv[i] = (inv[i + 1] * (i + 1)) % mod2;
    }
    ll n, m;
    cin >> n >> m;
    ll bot = C(n + m - 1, n) % mod2;
    ll top = 0;
    for (ll ind = 0; ind <= m; ++ind) {
        top += ((ind % 2 == 0 ? 1 : -1) * C(m, ind)) % mod2 * modPow(m - ind, m + n, mod2);
        top %= mod2;
        top += mod2;
        top %= mod2;
    }
    top = (top * inv[m]) % mod2;
    ll res = (top * modPow(bot, mod2 - 2, mod2)) % mod2;
    cout << res << "\n";
    return 0;
}