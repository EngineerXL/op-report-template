#include <bits/stdc++.h>

using pii = std::pair<int, int>;
using bs = std::bitset<MAX_N>;

const int MAX_N = 2021;

int get_num(int x, int pos) {
    pos = 3 - pos;
    int res = x % 10;
    while (pos--) {
        x = x / 10;
        res = x % 10;
    }
    return res - 1;
}

std::vector< std::vector<bs> > dat(4, std::vector<bs>(9));

void add_num(const std::vector<int> & a, int i) {
    for (int j = 0; j < 4; ++j) {
        dat[j][get_num(a[i], j)][i] = 1;
    }
}

void rm_num(const std::vector<int> & a, int i) {
    for (int j = 0; j < 4; ++j) {
        dat[j][get_num(a[i], j)][i] = 0;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        add_num(a, i);
    }
    // for (int k = 0; k < 4; ++k) {
    //     for (int j = 0; j < 9; ++j) {
    //         std::cout << k << ' ' << j + 1 << ' ' << dat[k][j] << std::endl;
    //     }
    // }
    int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
        rm_num(a, i);
        for (int j = i + 1; j < n; ++j) {
            std::vector<bool> check(4);
            rm_num(a, j);
            // std::cout << a[i] << ' ' << a[j] << std::endl;
            for (int k = 0; k < 4; ++k) {
                check[k] = (get_num(a[i], k) == get_num(a[j], k));
            }
            bs cur;
            cur.flip();
            for (int k = 0; k < 4; ++k) {
                if (check[k]) {
                    cur &= dat[k][get_num(a[i], k)];
                } else {
                    bs pos;
                    for (int m = 1; m <= 9; ++m) {
                        int digit = m - 1;
                        if (digit != get_num(a[i], k) and digit != get_num(a[j], k)) {
                            pos |= dat[k][digit];
                        }
                    }
                    cur &= pos;
                }
                // std::cout << cur << std::endl;
            }
            // std::cout << "fin " << cur << std::endl;
            ans += cur.count();
        }
        for (int j = i + 1; j < n; ++j) {
            add_num(a, j);
        }
    }
    std::cout << ans << '\n';
}
