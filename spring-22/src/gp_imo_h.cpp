#include <bits/stdc++.h>

using graph_t = std::vector< std::vector<int> >;
using edge_t = std::pair<int, int>;
using graph_edges_t = std::vector<edge_t>;

bool find(int u, int v, const graph_t & g, std::vector<bool> & dp, const int mask) {
    if (dp[mask]) {
        return true;
    }
    std::cout << "u = " << u + 1 << ", v = " << v + 1 << std::endl;
    if (!(mask & (1 << v))) {
        return false;
    }
    for (size_t i = 0; i < g[v].size(); ++i) {
        int go_to = g[v][i];
        dp[mask] = dp[mask] or find(u, go_to, g, dp, mask ^ (1 << v));
    }
    return dp[mask];
}

bool find_path(int u, int v, const graph_t & g) {
    const int n = g.size();
    std::vector<bool> dp(1 << n);
    dp[1 << u] = true;
    return find(u, v, g, dp, (1 << n) - 1);
}

edge_t rand_edge(const int n) {
    int u = std::rand() % n;
    int v = std::rand() % n;
    while (v == u) {
        v = std::rand() % n;
    }
    return std::make_pair(u, v);
}

edge_t rev_edge(const edge_t & uv) {
    return std::make_pair(uv.second, uv.first);
}

graph_edges_t gen_graph(const int n, const int m) {
    std::set<edge_t> exist_edges;
    graph_edges_t res;
    for (int i = 0; i < m; ++i) {
        edge_t rnd_edge = rand_edge(n);
        while (exist_edges.count(rnd_edge) > 0 or exist_edges.count(rev_edge(rnd_edge)) > 0) {
            rnd_edge = rand_edge(n);
        }
        exist_edges.insert(rnd_edge);
        exist_edges.insert(rev_edge(rnd_edge));
        res.push_back(rnd_edge);
    }
    return res;
}

graph_t read_graph(const graph_edges_t & ge, const int n) {
    graph_t g(n);
    for (size_t i = 0; i < ge.size(); ++i) {
        int u = ge[i].first;
        int v = ge[i].second;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

int calc(int n, int m, graph_t & g) {
    const int nax = (1 << n);
    int res = 0;
    for (int st = 0; st < n; ++st) {
        std::vector< std::vector<char> > dp(nax, std::vector<char>(n, 0));
        dp[1 << st][st] = 1;
        for (int mask = (1 << st); mask < nax; ++mask) {
            for (int v = 0; v < n; ++v) {
                if (((1 << v) & mask)) {
                    for (auto to : g[v]) {
                        if ((1 << to) & mask)continue;
                        dp[mask | (1 << to)][to] |= dp[mask][v];
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (i == st)continue;
            if (dp[nax - 1][i])res++;
        }
    }
    return res / 2;
}

int main() {
    std::srand(std::time(NULL));
    // int n, m;
    // std::cin >> n >> m;
    // graph_t g(n);
    // for (int i = 0; i < m; ++i) {
    //     int u, v;
    //     std::cin >> u >> v;
    //     --u;
    //     --v;
    //     g[u].push_back(v);
    //     g[v].push_back(u);
    // }
    // for (int i = 0; i < n; ++i) {
    //     std::cout << "i = " << i + 1 << " : ";
    //     for (size_t j = 0; j < g[i].size(); ++j) {
    //         std::cout << g[i][j] + 1 << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // int ans = 0;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = i + 1; j < n; ++j) {
    //         std::cout << "find path " << i + 1 << " " << j + 1 << std::endl;
    //         if (find_path(i, j, g)) {
    //             std::cout << "found path " << i + 1 << " " << j + 1 << std::endl;
    //             ++ans;
    //         }
    //     }
    // }
    // std::cout << ans << std::endl;

    int k;
    std::cin >> k;
    if (k == 1) {
        std::cout << "2 1" << std::endl;
        std::cout << "2 1" << std::endl;
        return 0;
    }
    if (k == 2) {
        std::cout << "4 4" << std::endl;
        std::cout << "1 2" << std::endl;
        std::cout << "1 3" << std::endl;
        std::cout << "2 3" << std::endl;
        std::cout << "3 4" << std::endl;
        return 0;
    }
    // int n, m;

    if (k <= 20) {
        std::cout << k << " " << k << std::endl;
        for (int i = 0; i < k - 1; ++i) {
            std::cout << i + 1 << " " << i + 2 << std::endl;
        }
        std::cout << k << " 1" << std::endl;
        return 0;
    }
    if (k - 11 <= 20) {
        int d = k - 11;
        std::cout << d << " " << d + 3 << std::endl;
        for (int i = 0; i < d - 1; ++i) {
            std::cout << i + 1 << " " << i + 2 << std::endl;
        }
        std::cout << d << " 1" << std::endl;

        std::cout << "1 3" << std::endl;
        std::cout << "3 5" << std::endl;
        std::cout << "2 4" << std::endl;
        return 0;
    }
    if (k - 17 <= 20) {
        int d = k - 17;
        std::cout << d << " " << d + 4 << std::endl;
        for (int i = 0; i < d - 1; ++i) {
            std::cout << i + 1 << " " << i + 2 << std::endl;
        }
        std::cout << d << " 1" << std::endl;

        std::cout << "1 3" << std::endl;
        std::cout << "3 5" << std::endl;
        std::cout << "2 4" << std::endl;
        std::cout << "4 6" << std::endl;
        return 0;
    }

    if (k - 24 <= 20) {
        int d = k - 24;
        std::cout << d << " " << d + 5 << std::endl;
        for (int i = 0; i < d - 1; ++i) {
            std::cout << i + 1 << " " << i + 2 << std::endl;
        }
        std::cout << d << " 1" << std::endl;

        std::cout << "1 3" << std::endl;
        std::cout << "3 5" << std::endl;
        std::cout << "5 7" << std::endl;
        std::cout << "2 4" << std::endl;
        std::cout << "4 6" << std::endl;
        return 0;
    }

    if (k - 32 <= 20) {
        int d = k - 32;
        std::cout << d << " " << d + 6 << std::endl;
        for (int i = 0; i < d - 1; ++i) {
            std::cout << i + 1 << " " << i + 2 << std::endl;
        }
        std::cout << d << " 1" << std::endl;

        std::cout << "1 3" << std::endl;
        std::cout << "3 5" << std::endl;
        std::cout << "5 7" << std::endl;
        std::cout << "2 4" << std::endl;
        std::cout << "4 6" << std::endl;
        std::cout << "6 8" << std::endl;
        return 0;
    }

    if (k - 41 <= 20) {
        int d = k - 41;
        std::cout << d << " " << d + 7 << std::endl;
        for (int i = 0; i < d - 1; ++i) {
            std::cout << i + 1 << " " << i + 2 << std::endl;
        }
        std::cout << d << " 1" << std::endl;

        std::cout << "1 3" << std::endl;
        std::cout << "3 5" << std::endl;
        std::cout << "5 7" << std::endl;
        std::cout << "7 9" << std::endl;
        std::cout << "2 4" << std::endl;
        std::cout << "4 6" << std::endl;
        std::cout << "6 8" << std::endl;
        return 0;
    }
    // for (int aaa = 0; aaa < 1000; ++aaa) {
    //     graph_edges_t ge = gen_graph(n, m);
    //     graph_t g = read_graph(ge, n);
    //     int ans = calc(n, m, g);
    //     // for (int i = 0; i < n; ++i) {
    //     //     for (int j = i + 1; j < n; ++j) {
    //     //         // std::cout << "find path " << i << " " << j << std::endl;
    //     //         if (find_path(i, j, g)) {
    //     //             // std::cout << "found path " << i + 1 << " " << j + 1 << std::endl;
    //     //             ++ans;
    //     //         }
    //     //     }
    //     // }
    //     std::cout << ans << std::endl;
    //     if (ans == k) {
    //         std::cout << n << " " << m << std::endl;
    //         for (int i = 0; i < m; ++i) {
    //             std::cout << ge[i].first + 1 << " " << ge[i].second + 1 << std::endl;
    //         }
    //         return 0;
    //     }
    // }
    return 123;
}
