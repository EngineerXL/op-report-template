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

const ll N = 150;

set<ll> res;


ll k(ll x, ll p) {
    ll rem = ((x % p) + p) % p;
    return (x - rem) / p;
}


void gen(ll x, ll y) {
    ll d = abs(y - x);
    if (d == 0) {
        return;
    }
    vector<ll> divs;
    for (ll i = 1; i * i <= d; ++i) {
        if (d % i == 0) {
            divs.push_back(i);
            if (i != d / i)divs.push_back(d / i);
        }
    }
    for (auto cur : divs) {
        ll k1 = k(x, cur), k2 = k(y, cur);
        if (k2 - k1 == 0 || d % abs(k2 - k1) != 0)continue;
        res.insert(cur);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<vector<ll>> a(N);
    for (ll i = 0; i < n; ++i) {
        ll pos, x;
        cin >> pos >> x;
        a[x].push_back(pos);
    }
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < i; ++j) {
            for (auto x : a[i]) {
                for (auto y : a[j]) {
                    gen(x, y);
                }
            }
        }
    }
    for (ll i = 1; i < N; ++i) {
        vector<ll> have(i, -1);
        for (ll j = 0; j < N; ++j) {
            for (auto p : a[j]) {
                have[(p % i + i) % i] = j;
            }
        }
        bool ok = true;
        for (auto x : have) {
            if (x == -1)ok = false;
        }
        if (!ok)continue;
        vector<ll> cnt(N, 0);
        for (ll j = 0; j < i; ++j) {
            cnt[have[j]]++;
        }
        for (auto x : cnt) {
            if (x == 1) {
                ok = false;
            }
        }
        if (!ok)continue;
        set<ll> check;
        for (ll j = 0; j < i; ++j) {
            for (ll k = 0; k < j; ++k) {
                if (have[j] == have[k])check.insert(j - k);
            }
        }
        for (auto step : check) {
            bool ok = true;
            for (ll j = step; j < i; ++j) {
                if (have[j] != have[j - step])ok = false;
            }
            if (ok && res.count(step) == 0) {
                res.insert(i);
                break;
            }
        }
    }
    cout << res.size() << " ";
    ll s = 0;
    for (auto x : res) {
        s += x;
    }
    cout << s << "\n";
    return 0;
}
