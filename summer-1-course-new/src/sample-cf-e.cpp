#include <bits/stdc++.h>

using pii = std::pair<int, int>;

const int INF = 1e9;

void set_pos(std::vector<int> & pos, int x, int i) {
    if (pos[x] == -1) {
        pos[x] = i;
    }
}

struct seg_t {
    int l, r;

    seg_t() {
        l = 1e9;
        r = 1e9;
    }

    seg_t(int _l, int _r) {
        l = _l;
        r = _r;
    }

    friend bool operator == (const seg_t & lhs, const seg_t & rhs) {
        return lhs.l == rhs.l and lhs.r == rhs.r;
    }

    friend bool operator < (const seg_t & lhs, const seg_t & rhs) {
        if (lhs.l != rhs.l) {
            return lhs.l < rhs.l;
        } else {
            return lhs.r < rhs.r;
        }
    }
};

/* KTO PROCHIAL, TOT ZAKROET SESSIU! */

#ifndef SEGMENT_TREE
#define SEGMENT_TREE

template<class T>
class segment_tree_t {
private:
    size_t _size;
    std::vector<T> _data;
    std::vector<T> _delay;
public:
    segment_tree_t(const size_t & n) : _size(n), _data(4 * n), _delay(4 * n) {}

    ~segment_tree_t() = default;

    void update_delay(size_t id, size_t l, size_t r) {
        if (_delay[id] == T()) {
            return;
        }
        _data[id] = std::min(_data[id], _delay[id]);
        if (id * 2 < 4 * _size) {
            _delay[id * 2] = std::min(_delay[id * 2], _delay[id]);
        }
        if (id * 2 + 1 < 4 * _size) {
            _delay[id * 2 + 1] = std::min(_delay[id * 2 + 1], _delay[id]);
        }
        _delay[id] = T();
    }

    T operator [] (int id) {
        return get(1, id, id, 1, _size);
    }

    T get(size_t ql, size_t qr) {
        return get(1, ql, qr, 1, _size);
    }

    T get(size_t id, size_t ql, size_t qr, size_t l, size_t r) {
        update_delay(id, l, r);
        if (ql <= l and r <= qr) {
            return _data[id];
        }
        size_t m = (l + r) / 2;
        if (qr <= m) {
            return get(id * 2, ql, qr, l, m);
        }
        if (ql > m) {
            return get(id * 2 + 1, ql, qr, m + 1, r);
        }
        // return get(id * 2, ql, qr, l, m) + get(id * 2 + 1, ql, qr, m + 1, r);
    }

    void delay(size_t ql, size_t qr, const T & val) {
        if (ql <= qr) {
            delay(1, ql, qr, 1, _size, val);
        }
    }

    void delay(size_t id, size_t ql, size_t qr, size_t l, size_t r, const T & val) {
        update_delay(id, l, r);
        if (ql <= l and r <= qr) {
            _delay[id] = val;
            return;
        }
        size_t m = (l + r) / 2;
        if (qr <= m) {
            delay(id * 2, ql, qr, l, m, val);
        } else if (ql > m) {
            delay(id * 2 + 1, ql, qr, m + 1, r, val);
        } else {
            delay(id * 2, ql, qr, l, m, val);
            delay(id * 2 + 1, ql, qr, m + 1, r, val);
        }
    }
};

#endif /* SEGMENT_TREE */

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<int> pos(n + 1, -1);

    for (int i = 1; i <= 2; ++i) {
        set_pos(pos, a[i - 1], i);
    }
    segment_tree_t<seg_t> st(n);
    std::vector<int> dp(n + 1, 0);
    for (int i = 3; i <= n; ++i) {
        int num = a[i - 1];
        int pos_num = pos[num];
        dp[i] = dp[i - 1];
        if (pos_num != -1) {
            seg_t cur_cov = seg_t(pos_num, i);
            dp[i] = std::max(dp[i], dp[pos_num - 1] + (i - pos_num - 1));
            st.delay(pos_num + 1, i - 1, cur_cov);
            seg_t last_covered = st[pos_num];
            // std::cout << last_covered.l << ' ' << last_covered.r << '\n';
            if (last_covered.l <= pos_num and pos_num <= last_covered.r) {
                dp[i] = std::max(dp[i], dp[last_covered.r] - 1 + (i - last_covered.r));
                st.delay(last_covered.r + 1, i - 1, cur_cov);
            }
        }
        set_pos(pos, a[i - 1], i);
    }
    // for (int i = 0; i <= n; ++i) {
    //     std::cout << "i = " << i << ", dp = " << dp[i] << std::endl;
    // }
    std::cout << dp.back() << std::endl;
}
