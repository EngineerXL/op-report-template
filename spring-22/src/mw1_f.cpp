#include <bits/stdc++.h>

using pii = std::pair<int, int>;

class segment_tree_t {
private:
    struct item_t {
        int64_t even;
        int64_t odd;
        int n;

        item_t() = default;

        item_t(int64_t x, int64_t b) {
            if (x % b == 0) {
                n = x / b;
                odd = b * (n / 2);
                even = b * (n / 2);
                if (n & 1) {
                    even += b;
                }
            } else {
                n = (x + b - 1) / b;
                odd = b * (n / 2);
                even = b * (n / 2);
                if (n & 1) {
                    even = even + x % b;
                } else {
                    odd = odd - b + x % b;
                }
            }
            // std::cout << "x = " << x << ", b = " << b << ", odd = " << odd << ", even = " << even << ", n = " << n << std::endl;
        }

        friend item_t operator + (const item_t & lhs, const item_t & rhs) {
            item_t res;
            res.n = lhs.n + rhs.n;
            if (lhs.n & 1) {
                res.even = lhs.even + rhs.odd;
                res.odd = lhs.odd + rhs.even;
            } else {
                res.even = lhs.even + rhs.even;
                res.odd = lhs.odd + rhs.odd;
            }
            return res;
        }
    };

    std::vector<item_t> data;
    int n;

public:
    segment_tree_t(int _n) {
        n = _n;
        data.resize(4 * n);
    }

    void set(int p, int64_t x, int64_t b) {
        set(1, 1, n, p, x, b);
    }

    void set(int id, int l, int r, int p, int64_t x, int64_t b) {
        if (l >= r) {
            data[id] = item_t(x, b);
            return;
        }
        int m = (l + r) / 2;
        if (p <= m) {
            set(id * 2, l, m, p, x, b);
        } else {
            set(id * 2 + 1, m + 1, r, p, x, b);
        }
        data[id] = data[id * 2] + data[id * 2 + 1];
    }

    int64_t get(int l, int r) {
        item_t ans = get(1, 1, n, l, r);
        return ans.even;
    }

    item_t get(int id, int l, int r, int ql, int qr) {
        if (ql <= l and r <= qr) {
            return data[id];
        }
        int m = (l + r) / 2;
        if (qr <= m) {
            return get(id * 2, l, m, ql, qr);
        }
        if (ql > m) {
            return get(id * 2 + 1, m + 1, r, ql, qr);
        }
        return get(id * 2, l, m, ql, qr) + get(id * 2 + 1, m + 1, r, ql, qr);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        using item_t = std::pair<int64_t, int>;
        std::list<item_t> lst;
        int64_t max_a = 0;
        for (int i = 0; i < n; ++i) {
            int64_t a;
            std::cin >> a;
            max_a = std::max(a, max_a);
            lst.push_back({a, i + 1});
        }
        segment_tree_t st(n);
        using iter = std::list<item_t>::iterator;
        for (int b = 1; b <= max_a; ++b) {
            for (iter it = lst.begin(); it != lst.end();) {
                iter next = it;
                ++next;
                item_t elem = *it;
                if (elem.first < b) {
                    lst.erase(it);
                } else {
                    st.set(elem.second, elem.first, b);
                }
                it = next;
            }
            std::cout << st.get(1, n) << '\n';
        }
    }
}
