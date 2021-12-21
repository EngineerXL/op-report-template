#include <bits/stdc++.h>

#ifndef TREAP_HPP
#define TREAP_HPP

#include <ctime>
#include <iostream>

class treap_t {
    static const int TAB_SIZE = 4;

    struct treap_node_t {
        treap_node_t * _left;
        treap_node_t * _right;
        int _key;
        int _priority;

        int _value;
        int _delay;
        int _suf0;
        int _suf9;

        treap_node_t(int key, int num) {
            _left = nullptr;
            _right = nullptr;
            _key = key;
            _priority = std::rand();
            _value = num;
            _suf0 = 0;
            _suf9 = 0;
            if (num == 0) {
                ++_suf0;
            }
            if (num == 9) {
                ++_suf9;
            }
            _delay = -1;
        }
    };

    using treap_ptr = treap_node_t *;

    treap_ptr root;

    int get_key(treap_ptr t) {
        if (t != nullptr) {
            return t->_key;
        } else {
            return 0;
        }
    }

    int get_value(treap_ptr t) {
        if (t != nullptr) {
            return t->_value;
        } else {
            return 0;
        }
    }

    int get_suf0(treap_ptr t) {
        if (t != nullptr) {
            if (t->_delay != -1) {
                return t->_delay == 0 ? t->_key : 0;
            } else {
                return t->_suf0;
            }
        } else {
            return 0;
        }
    }

    int get_suf9(treap_ptr t) {
        if (t != nullptr) {
            if (t->_delay != -1) {
                return t->_delay == 9 ? t->_key : 0;
            } else {
                return t->_suf9;
            }
        } else {
            return 0;
        }
    }

    void enqueue_delay(treap_ptr t, int delay_value) {
        if (t != nullptr) {
            t->_delay = delay_value;
        }
    }

    void update(treap_ptr t) {
        if (t != nullptr) {
            t->_key = 1 + get_key(t->_left) + get_key(t->_right);
            int delay_val = t->_delay;
            if (delay_val != -1) {
                t->_value = delay_val;
                t->_delay = -1;
                t->_suf0 = 0;
                t->_suf9 = 0;
                if (delay_val == 0) {
                    t->_suf0 = t->_key;
                }
                if (delay_val == 9) {
                    t->_suf9 = t->_key;
                }
                enqueue_delay(t->_left, delay_val);
                enqueue_delay(t->_right, delay_val);
            } else {
                if (get_key(t->_right) == get_suf0(t->_right)) {
                    if (t->_value == 0) {
                        t->_suf0 = get_suf0(t->_left) + get_suf0(t->_right) + 1;
                    } else {
                        t->_suf0 = get_suf0(t->_right);
                    }
                } else {
                    t->_suf0 = get_suf0(t->_right);
                }

                if (get_key(t->_right) == get_suf9(t->_right)) {
                    if (t->_value == 9) {
                        t->_suf9 = get_suf9(t->_left) + get_suf9(t->_right) + 1;
                    } else {
                        t->_suf9 = get_suf9(t->_right);
                    }
                } else {
                    t->_suf9 = get_suf9(t->_right);
                }
            }
        }
    }

    void split(treap_ptr t, int key, treap_ptr & l, treap_ptr & r) {
        if (t == nullptr) {
            l = nullptr;
            r = nullptr;
            return;
        }
        update(t);
        int key_left_subtree = get_key(t->_left);
        if (key > key_left_subtree + 1) {
            split(t->_right, key - key_left_subtree - 1, t->_right, r);
            l = t;
        } else {
            split(t->_left, key, l, t->_left);
            r = t;
        }
        update(l);
        update(r);
    }

    treap_ptr merge(treap_ptr l, treap_ptr r) {
        if (l == nullptr) {
            return r;
        }
        if (r == nullptr) {
            return l;
        }
        update(l);
        update(r);
        if (l->_priority > r->_priority) {
            l->_right = merge(l->_right, r);
            update(l);
            return l;
        } else {
            r->_left = merge(l, r->_left);
            update(r);
            return r;
        }
    }

    void delete_treap(treap_ptr t) {
        if (t != nullptr) {
            delete_treap(t->_left);
            delete_treap(t->_right);
            delete t;
        }
    }


    friend std::ostream & operator << (std::ostream & out, treap_t t) {
        print_treap(out, t.root, 0);
        return out;
    }

    friend std::ostream & operator << (std::ostream & out, treap_ptr t) {
        print_treap(out, t, 0);
        return out;
    }

    friend void print_treap(std::ostream & out, treap_ptr t, int h) {
        if (t != nullptr) {
            print_treap(out, t->_left, h + 1);
            for (int i = 0; i < TAB_SIZE * h; ++i) {
                out << " ";
            }
            out << "{ x = " << t->_key << ", val = " << t->_value << ", suf0 = " << t->_suf0 << ", suf9 = " << t->_suf9 << ", delay = " << t->_delay << "}\n";
            print_treap(out, t->_right, h + 1);
        }
    }

public:
    treap_t() {
        std::srand(std::time(NULL));
        root = nullptr;
    }

    void enqueue(int key_l, int key_r, int value) {
        treap_ptr l = nullptr;
        treap_ptr m = nullptr;
        treap_ptr r = nullptr;
        split(root, key_r + 1, m, r);
        split(m, key_l, l, m);
        enqueue_delay(m, value);
        root = merge(merge(l, m), r);
    }

    int get(int key_l, int key_r) {
        treap_ptr l = nullptr;
        treap_ptr m = nullptr;
        treap_ptr r = nullptr;
        split(root, key_r + 1, m, r);
        split(m, key_l, l, m);
        int ans = get_value(m);
        root = merge(merge(l, m), r);
        return ans;
    }

    int get0(int key_l, int key_r) {
        treap_ptr l = nullptr;
        treap_ptr m = nullptr;
        treap_ptr r = nullptr;
        split(root, key_r + 1, m, r);
        split(m, key_l, l, m);
        int ans = get_suf0(m);
        root = merge(merge(l, m), r);
        return ans;
    }

    int get9(int key_l, int key_r) {
        treap_ptr l = nullptr;
        treap_ptr m = nullptr;
        treap_ptr r = nullptr;
        split(root, key_r + 1, m, r);
        split(m, key_l, l, m);
        int ans = get_suf9(m);
        root = merge(merge(l, m), r);
        return ans;
    }

    void push_back(int value) {
        treap_ptr m = new treap_node_t(1, value);
        root = merge(root, m);
    }

    void push_front(int value) {
        treap_ptr m = new treap_node_t(1, value);
        root = merge(m, root);
    }

    void destruct() {
        delete_treap(root);
    }
};

#endif /* TREAP_HPP */

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;
    std::string str1, str2;
    std::cin >> str1 >> str2;
    std::vector<int> s1(n);
    std::vector<int> s2(n);
    for (int i = 0; i < n; ++i) {
        s1[i] = str1[i] - '0';
        s2[i] = str2[i] - '0';
    }
    std::vector<int> arr(n);
    int remainder = 0;
    for (int i = n - 1; i >= 0; --i) {
        arr[i] = s1[i] + s2[i] + remainder;
        remainder = 0;
        if (arr[i] > 9) {
            arr[i] = arr[i] - 10;
            remainder = 1;
        }
    }
    treap_t t;
    for (int i = 0; i < n; ++i) {
        t.push_back(arr[i]);
    }
    // std::cout << t << "------" << std::endl;
    while (q--) {
        int r, c, d;
        std::cin >> r >> c >> d;
        // std::cout << "query " << r << ", " << c << ", " << d << '\n';
        bool dec = true;
        int num_was = t.get(c, c);
        int delta = 0;
        if (r == 1) {
            if (s1[c - 1] == d) {
                std::cout << num_was << " 0\n";
                continue;
            }
            delta = std::abs(s1[c - 1] - d);
            if (s1[c - 1] < d) {
                dec = false;
            }
            s1[c - 1] = d;
        }
        if (r == 2) {
            if (s2[c - 1] == d) {
                std::cout << num_was << " 0\n";
                continue;
            }
            delta = std::abs(s2[c - 1] - d);
            if (s2[c - 1] < d) {
                dec = false;
            }
            s2[c - 1] = d;
        }
        int ans = 1;
        if (dec) {
            int num_next = num_was - delta;
            if (num_next < 0) {
                int suf = t.get0(1, c - 1);
                int pos = c - 1 - suf;
                t.enqueue(c, c, num_next + 10);
                // std::cout << "dec suf = " << suf << ", pos = " << pos << ", num_next = " << num_next << std::endl;
                if (suf == c - 1) {
                    t.enqueue(1, c - 1, 9);
                    ans = ans + suf + 1;
                } else {
                    t.enqueue(pos + 1, c - 1, 9);
                    // std::cout << t << std::endl;
                    t.enqueue(pos, pos, t.get(pos, pos) - 1);
                    ans = ans + suf + 2;
                }
                // std::cout << t << std::endl;
            } else {
                t.enqueue(c, c, num_next);
                ++ans;
            }
        } else {
            int num_next = num_was + delta;
            if (num_next > 9) {
                int suf = t.get9(1, c - 1);
                int pos = c - 1 - suf;
                t.enqueue(c, c, num_next - 10);
                // std::cout << "inc suf = " << suf << ", pos = " << pos << ", num_next = " << num_next << std::endl;
                // std::cout << t << std::endl;
                if (suf == c - 1) {
                    t.enqueue(1, c - 1, 0);
                    ans = ans + suf + 1;
                } else {
                    t.enqueue(pos + 1, c - 1, 0);
                    t.enqueue(pos, pos, 1 + t.get(pos, pos));
                    ans = ans + suf + 2;
                }
                // std::cout << t << std::endl;
            } else {
                t.enqueue(c, c, num_next);
                ++ans;
            }
        }
        // std::cout << t << std::endl;
        std::cout << t.get(c, c) << ' ' << ans << '\n';

        // std::cout << t << "------" << std::endl;
    }
}
