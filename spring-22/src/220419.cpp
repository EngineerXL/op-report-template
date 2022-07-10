#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e18;

struct edge {
    int u, v;
    int64_t c, f;
};

using pii = pair<int, int>;
using graph = vector< vector<int> >;

vector<int> build_network(const graph & g, const vector<edge> & e, int start, int64_t b) {
    int n = g.size();
    vector<int> d(n, -1);
    d[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int ind : g[u]) {
            int64_t c = e[ind].c;
            int64_t f = e[ind].f;
            int v = e[ind].v;
            if (c - f >= b and d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d;
}

int64_t dfs_push(graph & g, vector<edge> & e, int u, int finish, const vector<int> & d, vector<int> & ptr, int64_t b, int64_t flow) {
    if (u == finish) {
        return flow;
    }
    for (; ptr[u] < (int)g[u].size(); ++ptr[u]) {
        int ind = g[u][ptr[u]];
        edge uv = e[ind];
        int v = uv.v;
        if (d[u] + 1 != d[v]) {
            continue;
        }
        int64_t f = uv.f;
        int64_t c = uv.c;
        if (c - f >= b) {
            flow = min(flow, c - f);
            int64_t pushed = dfs_push(g, e, v, finish, d, ptr, b, flow);
            if (pushed) {
                e[ind].f += pushed;
                e[ind ^ 1].f -= pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int64_t diniz(graph & g, vector<edge> & e, int start, int finish, int64_t b) {
    int64_t res = 0;
    int n = g.size();
    while (1) {
        vector<int> d = build_network(g, e, start, b);
        if (d[finish] == -1) {
            break;
        }
        vector<int> ptr(n);
        while (1) {
            int64_t flow = dfs_push(g, e, start, finish, d, ptr, b, INF);
            if (flow) {
                res += flow;
            } else {
                break;
            }
        }
    }
    return res;
}

int64_t max_flow(graph & g, vector<edge> & e, int start, int finish) {
    int64_t res = 0;
    const int64_t MAX_B = 1 << 30;
    for (int64_t b = MAX_B; b > 0; b = b >> 1) {
        res += diniz(g, e, start, finish, b);
    }
    return res;
}

void add_edge(graph & g, vector<edge> & e, int u, int v, int64_t w) {
    edge e_uv = {u, v, w, 0};
    edge e_vu = {v, u, 0, 0};
    g[u].push_back(e.size());
    e.push_back(e_uv);
    g[v].push_back(e.size());
    e.push_back(e_vu);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    graph g(n);
    vector<edge> e;
    for (int i = 0; i < m; ++i) {
        int u, v;
        int64_t w;
        cin >> u >> v >> w;
        --u;
        --v;
        add_edge(g, e, u, v, w);
    }
    cout << max_flow(g, e, 0, n - 1) << '\n';
    for (int i = 0; i < m; ++i) {
        edge uv = e[2 * i];
        cout << uv.f << '\n';
    }
}

