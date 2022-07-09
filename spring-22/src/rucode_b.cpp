#include <bits/stdc++.h>

using grid_t = std::vector< std::vector<int> >;

void draw_sq(grid_t & a, int x1, int y1, int x2, int y2) {
    a[x1][y1] = 3;
    a[x2][y1] = 2;
    a[x1][y2] = 4;
    a[x2][y2] = 1;
    for (int i = x1 + 1; i < x2; ++i) {
        a[i][y1] = 6;
        a[i][y2] = 6;
    }
    for (int i = y1 + 1; i < y2; ++i) {
        a[x1][i] = 5;
        a[x2][i] = 5;
    }
}

int rot[7] = {0, 1, 4, 3, 2, 6, 5};

grid_t transpose(const grid_t & gr) {
    int h = gr.size();
    int w = gr.back().size();
    grid_t res(w, std::vector<int>(h));
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            res[i][j] = rot[gr[j][i]];
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int w, h;
    std::cin >> w >> h;
    grid_t ans(h, std::vector<int>(w));
    if (w == 1 or h == 1) {
        std::cout << "-1\n";
        return 0;
    }
    if (w == 2 or h == 2) {
        draw_sq(ans, 0, 0, h - 1, w - 1);
    } else if (w & 1) {
        if (h & 1) {
            if (h == 3 and w == 3) {
                std::cout << "-1\n";
                return 0;
            }
            bool flag = false;
            if (h == 3) {
                std::swap(h, w);
                flag = true;
                ans = transpose(ans);
            }
            ans[0][0] = 3;
            ans[0][1] = 5;
            for (int i = 2; i < w - 1; ++i) {
                ans[0][i] = (i & 1 ? 3 : 4);
            }
            ans[0].back() = 4;
            ans[1][0] = 2;
            ans[1][1] = 4;
            for (int i = 2; i < w; ++i) {
                ans[1][i] = 6;
            }
            for (int j = 2; j < h - 2; ++j) {
                ans[j][0] = (j & 1 ? 2 : 3);
                for (int i = 1; i < w - 1; ++i) {
                    ans[j][i] = 6;
                }
                ans[j].back() = (j & 1 ? 4 : 1);
            }
            ans[h - 2][w - 1] = 4;
            ans[h - 2][w - 2] = 2;
            for (int i = 0; i < w - 2; ++i) {
                ans[h - 2][i] = 6;
            }
            ans.back()[0] = 2;
            for (int i = 1; i < w - 2; ++i) {
                ans.back()[i] = (i & 1 ? 1 : 2);
            }
            ans.back()[w - 2] = 5;
            ans.back()[w - 1] = 1;
            if (flag) {
                std::swap(h, w);
                ans = transpose(ans);
            }
        } else {
            for (int i = 0; i < std::min(h / 2, w / 2); ++i) {
                draw_sq(ans, i, i + 1, h - 1 - i, w - 1 - i);
            }
            ans[0][0] = 3;
            ans[0][1] = 5;
            for (int i = 1; i < h - 1; i = i + 2) {
                ans[i][0] = 2;
                ans[i][1] = 4;
                ans[i + 1][0] = 3;
                ans[i + 1][1] = 1;
            }
            ans.back()[0] = 2;
            ans.back()[1] = 5;
        }
    } else {
        if (h & 1) {
            for (int i = 0; i < std::min(h / 2, w / 2); ++i) {
                draw_sq(ans, i + 1, i, h - 1 - i, w - 1 - i);
            }
            ans[0][0] = 3;
            ans[1][0] = 6;
            for (int i = 1; i < w - 1; i = i + 2) {
                ans[0][i] = 4;
                ans[1][i] = 2;
                ans[0][i + 1] = 3;
                ans[1][i + 1] = 1;
            }
            ans[0].back() = 4;
            ans[1].back() = 6;
        } else {
            for (int i = 0; i < std::min(h / 2, w / 2); ++i) {
                draw_sq(ans, i, i, h - 1 - i, w - 1 - i);
            }
        }
    }
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            std::cout << ans[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
