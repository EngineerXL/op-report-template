#include <bits/stdc++.h>

using namespace std;


#define flush cout.flush
//yandex moment


using ll = int;
using ull = unsigned long long;
using ld = long double;
using pl = pair<ll, ll>;
const ll INF = 1e9 + 7;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ld eps = 1e-9;
const ld PI = acos(-1);

const int N = 2505;

struct item {
    ll l, r;
    ll w;
};

struct zxc {
    ll r, w;
};

struct cmp {
    bool operator()(const zxc &a, const zxc &b) const {
        if (a.r != b.r) {
            return a.r < b.r;
        }
        return a.w < b.w;
    }
};


bool operator<(const item &a, const item &b) {
    if (a.l != b.l)return a.l < b.l;
    if (a.r != b.r)return a.r < b.r;
    return a.w > b.w;
}

item a[N];
long long dp[N + 1]{};

int main() {
    ll n, k;
    scanf("%d %d", &n, &k);
    long long res = 0;
    for (ll i = 0; i < n; ++i) {
        scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].w);
        res += a[i].w;
    }
    sort(a, a + n);
    a[n] = {INF, INF, 0};
    for (ll i = n - 1; i >= 0; --i) {
        dp[i] = dp[i + 1];
        multiset<zxc, cmp> left;
        multiset<ll> bestw;
        long long cur = 0;
        left.insert({a[i].r, a[i].w});
        for (ll j = i + 1; j <= n; ++j) {
            while (!left.empty() && left.begin()->r < a[j].l) {
                zxc it = *left.begin();
                left.erase(left.find(it));
                cur += it.w;
                bestw.insert(it.w);
                while (bestw.size() > k) {
                    ll it = *bestw.begin();
                    cur -= it;
                    bestw.erase(bestw.find(it));
                }
            }
            dp[i] = max(dp[i], dp[j] + cur);
            if (j < n) {
                left.insert({a[j].r, a[j].w});
            }
        }
    }
    res -= dp[0];
    printf("%lld\n", res);
    return 0;
}