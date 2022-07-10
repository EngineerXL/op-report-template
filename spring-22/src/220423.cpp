#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

using base = complex<double>;
using vc = vector<base>;

const double PI = acos(-1);

void fft(vc & a, bool invert) {
    int n = a.size();
    if (n == 1) {
        return;
    }
    vc a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);
    double phi = (2 * PI) / n;
    if (invert) {
        phi *= -1;
    }
    base w = 1, wn = complex(cos(phi), sin(phi));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }
    if (invert) {
        for (int i = 0; i < n; ++i) {
            a[i] /= 2;
        }
    }
}

int rev_bits(int x, int lg_n) {
    int y = 0;
    for (int i = 0; i < lg_n; ++i) {
        y = y << 1;
        y ^= (x & 1);
        x = x >> 1;
    }
    return y;
}

void fft_fast(vc & a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n) {
        ++lg_n;
    }
    for (int i = 0; i < n; ++i) {
        if (i < rev_bits(i, lg_n)) {
            swap(a[i], a[rev_bits(i, lg_n)]);
        }
    }
    for (int layer = 1; layer <= lg_n; ++layer) {
        int cluster = 1 << layer;
        double phi = (2.0 * PI) / cluster;
        if (invert) {
            phi *= -1;
        }
        base wn = base(cos(phi), sin(phi));
        for (int i = 0; i < n; i += cluster) {
            base w(1);
            for (int j = 0; j < cluster / 2; ++j) {
                base u = a[i + j];
                base v = a[i + j + cluster / 2] * w;
                a[i + j] = u + v;
                a[i + j + cluster / 2] = u - v;
                w *= wn;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}

string mult(string a, string b) {
    int ab = a.size() + b.size();
    int n = 1;
    while (n < ab) {
        n *= 2;
    }
    n *= 2;
    reverse(a.begin(), a.end());
    vc ac(n);
    for (size_t i = 0; i < a.size(); ++i) {
        ac[i] = a[i] - '0';
    }
    reverse(b.begin(), b.end());
    vc bc(n);
    for (size_t i = 0; i < b.size(); ++i) {
        bc[i] = b[i] - '0';
    }
    fft_fast(ac, false);
    fft_fast(bc, false);
    for (int i = 0; i < n; ++i) {
        ac[i] *= bc[i];
    }
    fft_fast(ac, true);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        // cout << ac[i].real() << endl;
        c[i] = round(ac[i].real());
    }
    for (int i = 0; i < n - 1; ++i) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    while (c.size() > 1 and c.back() == 0) {
        c.pop_back();
    }
    reverse(c.begin(), c.end());
    string res;
    for (int elem : c) {
        res.push_back('0' + elem);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    cin >> a >> b;
    bool flag = false;
    if (a[0] == '-') {
        flag ^= 1;
        string an;
        for (size_t i = 1; i < a.size(); ++i) {
            an += a[i];
        }
        a = an;
    }
    if (b[0] == '-') {
        flag ^= 1;
        string bn;
        for (size_t i = 1; i < b.size(); ++i) {
            bn += b[i];
        }
        b = bn;
    }
    bool is_null = false;
    is_null = is_null or (a.size() == 1 and a[0] == '0');
    is_null = is_null or (b.size() == 1 and b[0] == '0');
    if (flag and !is_null) {
        cout << '-';
    }
    cout << mult(a, b) << endl;
}

