#include <bits/stdc++.h>

int parse_time(const std::string & s) {
    int minutes = std::stoi(s.substr(0, 2));
    int seconds = std::stoi(s.substr(3, 2));
    int mseconds = s[6] - '0';
    return 60 * 10 * minutes + 10 * seconds + mseconds;
}

std::string to_time(int time) {
    int mseconds = time % 10;
    int seconds = (time / 10) % 60;
    int minutes = time / 600;
    std::string s1;
    s1.push_back(minutes / 10 + '0');
    s1.push_back(minutes % 10 + '0');
    std::string s2;
    s2.push_back(seconds / 10 + '0');
    s2.push_back(seconds % 10 + '0');
    std::string s3;
    s3.push_back(mseconds + '0');
    return s1 + ":" + s2 + "." + s3;
}

struct item_t {
    int t;
    int team;
    std::string what;

    friend bool operator < (const item_t & lhs, const item_t & rhs) {
        return lhs.t < rhs.t;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    const int MAX_TIME = 60 * 60 * 10;

    int n;
    std::cin >> n;
    std::vector<item_t> data;
    for (int i = 0; i < n; ++i) {
        std::string tt;
        int team;
        std::string s;
        std::cin >> tt >> team >> s;
        data.push_back({parse_time(tt), team, s});
    }
    std::stable_sort(data.begin(), data.end());

    const int TN = 5;
    const int PLAY = 0;
    const int MINOR = 1;
    const int MAJOR = 2;
    const int MINOR_TIME = 2 * 60 * 10;
    const int MAJOR_TIME = 5 * 60 * 10;
    std::vector<int> penalty_a(TN);
    std::vector<int> penalty_ta(TN);
    std::vector<int> penalty_b(TN);
    std::vector<int> penalty_tb(TN);
    std::vector< std::vector<int> > res(TN + 1, std::vector<int>(TN + 1));
    int j = 0;
    for (int i = 0; i < MAX_TIME; ++i) {

        for (int ii = 0; ii < TN; ++ii) {
            if (penalty_ta[ii] != PLAY) {
                --penalty_a[ii];
                if (penalty_a[ii] == 0) {
                    penalty_ta[ii] = PLAY;
                }
            }
            if (penalty_tb[ii] != PLAY) {
                --penalty_b[ii];
                if (penalty_b[ii] == 0) {
                    penalty_tb[ii] = PLAY;
                }
            }
        }

        while (j < n and data[j].t <= i) {
            item_t event = data[j];
            if (event.team == 1) {
                if (event.what == "major") {
                    for (int ii = 0; ii < TN; ++ii) {
                        if (penalty_ta[ii] == PLAY) {
                            penalty_ta[ii] = MAJOR;
                            penalty_a[ii] = MAJOR_TIME;
                            break;
                        }
                    }
                }

                if (event.what == "minor") {
                    for (int ii = 0; ii < TN; ++ii) {
                        if (penalty_ta[ii] == PLAY) {
                            penalty_ta[ii] = MINOR;
                            penalty_a[ii] = MINOR_TIME;
                            break;
                        }
                    }
                }

                if (event.what == "goal") {
                    int count_a = 0;
                    int count_b = 0;
                    for (int ii = 0; ii < TN; ++ii) {
                        if (penalty_ta[ii] == PLAY) {
                            ++count_a;
                        }
                        if (penalty_tb[ii] == PLAY) {
                            ++count_b;
                        }
                    }
                    if (count_b < count_a) {
                        int min_time_left = -1;
                        for (int ii = 0; ii < TN; ++ii) {
                            if (penalty_tb[ii] == MINOR) {
                                if (min_time_left == -1 or penalty_b[ii] < penalty_b[min_time_left]) {
                                    min_time_left = ii;
                                }
                            }
                        }
                        if (min_time_left != -1) {
                            penalty_tb[min_time_left] = PLAY;
                            penalty_b[min_time_left] = 0;
                        }
                    }
                }
            }

            if (event.team == 2) {
                if (event.what == "major") {
                    for (int ii = 0; ii < TN; ++ii) {
                        if (penalty_tb[ii] == PLAY) {
                            penalty_tb[ii] = MAJOR;
                            penalty_b[ii] = MAJOR_TIME;
                            break;
                        }
                    }
                }

                if (event.what == "minor") {
                    for (int ii = 0; ii < TN; ++ii) {
                        if (penalty_tb[ii] == PLAY) {
                            penalty_tb[ii] = MINOR;
                            penalty_b[ii] = MINOR_TIME;
                            break;
                        }
                    }
                }

                if (event.what == "goal") {
                    int count_a = 0;
                    int count_b = 0;
                    for (int ii = 0; ii < TN; ++ii) {
                        if (penalty_ta[ii] == PLAY) {
                            ++count_a;
                        }
                        if (penalty_tb[ii] == PLAY) {
                            ++count_b;
                        }
                    }
                    if (count_a < count_b) {
                        int min_time_left = -1;
                        for (int ii = 0; ii < TN; ++ii) {
                            if (penalty_ta[ii] == MINOR) {
                                if (min_time_left == -1 or penalty_a[ii] < penalty_a[min_time_left]) {
                                    min_time_left = ii;
                                }
                            }
                        }
                        if (min_time_left != -1) {
                            penalty_ta[min_time_left] = PLAY;
                            penalty_a[min_time_left] = 0;
                        }
                    }
                }
            }
            ++j;
        }
        {
            int count_a = 0;
            int count_b = 0;
            for (int ii = 0; ii < TN; ++ii) {
                if (penalty_ta[ii] == PLAY) {
                    ++count_a;
                }
                if (penalty_tb[ii] == PLAY) {
                    ++count_b;
                }
            }
            ++res[count_a][count_b];
        }
    }

    for (int i = 0; i < TN + 1; ++i) {
        for (int j = 0; j < TN + 1; ++j) {
            if (res[i][j] > 0) {
                std::cout << i << 'x' << j << " " + to_time(res[i][j]) << '\n';
            }
        }
    }
}
