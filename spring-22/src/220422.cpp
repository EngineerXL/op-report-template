#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

struct suffix_tree {
    using table = map<char, int>;
    using item = pair<char, int>;

    const int INF = 1e9;

    struct node {
        table go;
        int l;
        int len;

        int link = 0;

        node(int _l, int _len) {
            l = _l;
            len = _len;
        }

        int r(int str_size) {
            return min(str_size, l + len);
        }
    };

    vector<node> data;
    string s;

    int create_node(int _l, int _len) {
        data.push_back(node(_l, _len));
        ++nodes;
        return nodes;
    }

    bool can_go(int id, char c) {
        // cout << "id = " << id << ", data.size() = " << data.size() << endl;
        // for (item elem : data[id].go) {
        //     cout << "LALALAL " << elem.first << ' ' << elem.second << endl;
        // }
        return data[id].go.count(c);
    }

    int go(int id, char c) {
        return data[id].go[c];
    }

    int size;
    int nodes;

    int u = 0;
    int rem = 0;

    void go_edge() {
        while (1) {
            char c = s[size - rem];
            if (!can_go(u, c)) {
                return;
            }
            int v = go(u, c);
            if (data[v].len < rem) {
                rem -= data[v].len;
                u = v;
            } else {
                return;
            }
        }
    }

    void extend(char c) {
        ++size;
        ++rem;
        int last = 0;
        while (rem) {
            go_edge();
            char a = s[size - rem];
            if (!can_go(u, a)) {
                data[u].go[a] = create_node(size - rem, INF);
                data[last].link = u;
                last = u;
            } else {
                int v = go(u, a);
                int good_len = rem - 1;
                int edge_left = data[v].l;
                char t = s[edge_left + good_len];
                if (t != c) {
                    int split = create_node(edge_left, good_len);
                    int new_v = create_node(size - 1, INF);
                    data[split].go[t] = v;
                    data[split].go[c] = new_v;
                    data[u].go[a] = split;

                    data[v].len -= good_len;
                    data[v].l += good_len;

                    data[last].link = split;
                    last = split;
                } else {
                    data[last].link = u;
                    return;
                }
            }
            if (u == 0) {
                --rem;
            } else {
                u = data[u].link;
            }
        }
    }

    void build() {
        size = 0;
        nodes = 0;

        u = 0;
        rem = 0;
        for (char c : s) {
            extend(c);
        }
    }

    suffix_tree(const string & _s) : s(_s) {
        size = 0;
        nodes = 0;
        create_node(0, INF);
        build();
    }

    int cnt = 0;

    void dfs(int u, int prev) {
        if (u) {
            cout << prev << ' ' << data[u].l << ' ' << data[u].r(size) << '\n';
            // for (int i = data[u].l; i < data[u].r(size); ++i) {
            //     cout << s[i];
            // }
            // cout << '\n';
        }
        int cur_id = cnt;
        ++cnt;
        for (item elem : data[u].go) {
            int v = elem.second;
            dfs(v, cur_id);
        }
    }

    void walk_tree() {
        cout << data.size() << '\n';
        dfs(0, -1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    suffix_tree st(s);
    st.walk_tree();
}

