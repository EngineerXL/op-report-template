#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

struct item {
    int pos;
    int type;
    int id;

    friend bool operator < (item lhs, item rhs) {
        if (lhs.pos != rhs.pos) {
            return lhs.pos < rhs.pos;
        } else {
            return lhs.id > rhs.id;
        }
    }
};

int OPEN = 0;
int CLOSE = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<item> a;

    bool ans = true;
    string s;
    int cnt = 1;
    while (cin >> s) {
        if (s == "END") {
            break;
        }
        if (s == "if") {
            string s1, s2, s3;
            cin >> s1 >> s2 >> s3;
            string sub1 = s1.substr(6, s1.size() - 9);
            int n1 = stoi(sub1);
            string sub3 = s3.substr(5, s3.size() - 6);
            int n3 = stoi(sub3);
            if (n3 > n1) {
                ans = false;
            }
            a.push_back({n3, OPEN, cnt});
            a.push_back({n1, CLOSE, cnt});
            ++cnt;
        } else {
            string s1;
            cin >> s1;
        }
    }
    sort(a.begin(), a.end());
    stack<int> ids;
    for (item elem : a) {
        if (elem.type == OPEN) {
            ids.push(elem.id);
        } else {
            if (ids.empty() or ids.top() != elem.id) {
                ans = false;
            } else {
                ids.pop();
            }
        }
    }
    if (ans) {
        cout << "good\n";
    } else {
        cout << "bad\n";
    }
}

