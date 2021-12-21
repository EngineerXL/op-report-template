#include <bits/stdc++.h>

using pii = std::pair<int, int>;

std::map<int64_t, std::set<int64_t> > mp;

std::set<int64_t> anagrams(int64_t x) {
    std::string s = std::to_string(x);
    std::set<int64_t> res;
    std::sort(s.begin(), s.end());
    do {
        int64_t num = std::stoll(s);
        res.insert(num);
    } while (std::next_permutation(s.begin(), s.end()));
    return res;
}

void process_num(std::string s) {
    if (s.size() > 18) {
        return;
    } else {
        int64_t number = std::stoll(s);
        std::set<int64_t> nums = anagrams(number);
        int64_t gcd_res = *nums.begin();
        for (int64_t elem : nums) {
            gcd_res = std::__gcd(elem, gcd_res);
        }
        mp[gcd_res].insert(number);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    for (int i = 0; i <= 9; ++i) {
        std::string num;
        for (int j = 1; j <= 18; ++j) {
            num.push_back('0' + i);
            int64_t nnum = std::stoll(num);
            mp[nnum].insert(nnum);
        }
    }
    for (int i = 0; i <= 9; ++i) {
        std::string num;
        num.push_back('0' + i);
        num.push_back('0');
        for (int j = 1; j <= 18; ++j) {
            num.push_back('0' + i);
            process_num(num);
        }
    }
    for (int i = 1; i <= 9; ++i) {
        std::string num;
        for (int j = 1; j <= 18; ++j) {
            num.push_back('0' + i);
            std::string magic = num;
            for (int k = 1; k <= 18; ++k) {
                magic.push_back('8');
                process_num(magic);
            }
        }
    }
    for (int64_t i = 1; i <= 1e4; ++i) {
        process_num(std::to_string(i));
    }
    // for (auto elem : mp) {
    //     std::cout << "gcd = " << elem.first << ", ";
    //     std::cout << *elem.second.begin();
    //     // for (int64_t num : elem.second) {
    //     //     std::cout << num << ' ';
    //     // }
    //     std::cout << std::endl;
    // }
    int t;
    std::cin >> t;
    while (t--) {
        int64_t n;
        std::cin >> n;
        if (!mp.count(n)) {
            std::cout << "-1\n";
        } else {
            std::cout << *mp[n].begin() << '\n';
        }
    }
}
