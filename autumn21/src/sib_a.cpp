#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        int t1 = -1, t2 = -1, t3 = -1;
        bool ans = true;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] != a[i + 1]) {
                t1 = i;
                break;
            }
        }
        for (int i = n - 1; i > 0; --i) {
            if (a[i] != a[i - 1]) {
                t3 = i;
                break;
            }
        }
        if (t3 <= t1 or t3 == -1 or t1 == -1) {
            ans = false;
        } else {
            for (int i = t1; i < std::min(t3, n - 1); ++i) {
                if (a[i + 1] <= a[i]) {
                    t2 = i;
                    break;
                }
            }
            if (t2 != -1) {
                for (int i = t1; i < t2; ++i) {
                    ans = ans & (a[i] < a[i + 1]);
                }
                for (int i = t2; i < std::min(n - 1, t3); ++i) {
                    ans = ans & (a[i] > a[i + 1]);
                }
            } else {
                ans = false;
            }
            ans = ans and (t1 < t2 and t2 < t3);
        }
        if (ans) {
            std::cout << "Freytag " << t1 + 1 << ' ' << t2 + 1 << ' ' << t3 + 1 << '\n';
        } else {
            std::cout << "Nein\n";
        }
    }
}
