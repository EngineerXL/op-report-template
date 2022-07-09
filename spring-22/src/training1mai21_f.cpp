#include <bits/stdc++.h>

struct problem {
    std::string solved;
    int a;
    int t;
};

struct team {
    std::string name;
    std::vector<problem> total;

    team() = default;

    team(const std::string & s, const std::vector<problem> & stotal) {
        name = s;
        total = stotal;
    }

    int getSolved() {
        int res = 0;
        for (size_t i = 0; i < total.size(); ++i) {
            if (total[i].solved == "+") {
                ++res;
            }
        }
        return res;
    }

    int getPenalty() {
        int res = 0;
        for (size_t i = 0; i < total.size(); ++i) {
            if (total[i].solved == "+") {
                res = res + total[i].t + 20 * (total[i].a - 1);
            }
        }
        return res;
    }

    int getLastAc() {
        int res = 0;
        for (size_t i = 0; i < total.size(); ++i) {
            if (total[i].solved == "+" and total[i].t >= res) {
                res = total[i].t;
            }
        }
        return res;
    }
};

struct team_score {
    int solved;
    int penalty;
    int lastAc;
    std::string name;

    team_score(team t) {
        name = t.name;
        solved = t.getSolved();
        penalty = t.getPenalty();
        lastAc = t.getLastAc();
    }

    friend bool operator < (const team_score & lhs, const team_score & rhs) {
        if (lhs.solved != rhs.solved) {
            return lhs.solved > rhs.solved;
        } else if (lhs.penalty != rhs.penalty) {
            return lhs.penalty < rhs.penalty;
        } else if (lhs.lastAc != rhs.lastAc) {
            return lhs.lastAc < rhs.lastAc;
        } else {
            return lhs.name < rhs.name;
        }
    }
};

team_score getBetter(team t) {
    for (size_t i = 0; i < t.total.size(); ++i) {
        if (t.total[i].solved != "+") {
            t.total[i].solved = "+";
            ++t.total[i].a;
            t.total[i].t = 240;
        }
    }
    return team_score(t);
}

team_score getWorse(team t) {
    return team_score(t);
}

team readTeam(int n) {
    std::string s;
    std::cin >> s;
    std::vector<problem> stotal;
    problem cur;
    for (int i = 0; i < n; ++i) {
        std::cin >> cur.solved >> cur.a >> cur.t;
        stotal.push_back(cur);
    }
    team res(s, stotal);
    // std::cout << "team name = " << s << res.name << std::endl;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<team> frozen;
    for (int i = 0; i < m; ++i) {
        team cur = readTeam(n);
        frozen.push_back(cur);
    }
    std::set<std::string> used;
    std::vector<team> leak;
    for (int i = 0; i < k; ++i) {
        team cur = readTeam(n);
        leak.push_back(cur);
        used.insert(cur.name);
        // std::cout << "insert " << leak.back().name << std::endl;
    }
    team_score best(leak[0]);
    team_score worst(leak.back());
    bool ans = false;

    int could_be_better = 0;
    int could_be_worse = 0;
    int could_be = 0;
    std::set<std::string> used_better;
    for (int i = 0; i < m; ++i) {
        if (used.count(frozen[i].name)) {
            continue;
        }
        team_score better = getBetter(frozen[i]);
        team_score worse = getWorse(frozen[i]);
        // std::cout << frozen[i].name << " bet = " << better.solved << " wor = " << worse.solved << std::endl;
        if (worst < worse) {
            if (better < best) {
                ++could_be;
            } else {
                ++could_be_worse;
            }
        } else if (better < best) {
            ++could_be_better;
        }
    }

    // std::cout << "worse " << could_be_worse << " better" << could_be_better << " be" << could_be << std::endl;
    if (could_be_worse + could_be_better + could_be == m - k) {
        ans = true;
    }

    if (ans) {
        std::cout << "Leaked\n";
    } else {
        std::cout << "Fake\n";
    }
}
