#include <bits/stdc++.h>

using namespace std;

#define flush cout.flush

#define double long double
using ll = long long;
using ull = unsigned long long;
using ld = double;
using pl = pair<ll, ll>;
const ll INF = 1e9 + 7;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ld eps = 1e-12;
const ld PI = acos(-1);

bool leq(double x, double y) {
    return (x < y) or abs(x - y) < eps;
}

void solve() {
    int b, k;
    cin >> b >> k;
    double total_need = b / 100.0;
    for (int a = 0; a <= 100; ++a) {
        double p = a / 100.0;
        double q = 1.0 - p;
//        cout << "p = " << p << ", q = " << q << endl;
        double total = 0;
        double q_deg = 1.0;
        for (int i = 0; i <= k; ++i) {
            total += q_deg;
            q_deg *= q;
        }
//        cout << total << endl;
        total *= p;
        if (leq(total_need, total)) {
            cout << a << '\n';
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
