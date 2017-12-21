#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <assert.h>

using namespace std;

const int MAX_LEN_S = 20;

pair<vector<int>, vector<vector<int>>> get_suff_array(string s) {
    vector<int> p(s.size()), cl(s.size());
    vector<int> cnt((unsigned long) max((int) s.size(), 255));
    for (int i = 0; i < (int)s.size(); i++) ++cnt[s[i]];
    for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < (int)s.size(); i++) p[--cnt[s[i]]] = i;
    cl[p[0]] = 0;
    for (int i = 1; i < (int)s.size(); i++) cl[p[i]] = cl[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    int num_cl = 1 + cl[p[(int)s.size() - 1]];
    vector<vector<int>> cls;
    cls.push_back(cl);
    vector<int> pn(s.size()), cn(s.size());
    for (int h = 0; (1<<h) < (int)s.size(); h++) {
        for (int i = 0; i < (int)s.size(); i++) {
            pn[i] = p[i] - (1<<h);
            if (pn[i] < 0) pn[i] += (int)s.size();
        }
        cnt.assign((unsigned long) num_cl, 0);
        for (int i = 0; i < (int)s.size(); i++) ++cnt[cl[pn[i]]];
        for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = (int)s.size() - 1; i >= 0; i--) p[--cnt[cl[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        for (int i = 1; i < (int)s.size(); i++) {
            int u = (int) ((p[i] + (1 << h)) % s.size());
            int v = (int) ((p[i - 1] + (1 << h)) % s.size());
            cn[p[i]] = cn[p[i - 1]] + ((cl[p[i]] != cl[p[i - 1]]) || (cl[u] != cl[v]));
        }
        cl = cn;
        num_cl = 1 + cl[p[(int)s.size() - 1]];
        cls.push_back(cl);
    }
    return make_pair(p, cls);
}

string solve(string a, string b) {
    vector<bool> letter_was(26);
    for (int i = 0; i < (int)a.size(); i++) letter_was[a[i] - 'a'] = true;
    bool found = false;
    for (int i = 0; i < (int)b.size(); i++) {
        if (letter_was[b[i] - 'a']) {
            found = true;
            break;
        }
    }
    if (!found) return "";


    reverse(b.begin(), b.end());
    string ab = a + "#" + b;
    pair<vector<int>, vector<vector<int>>> suff = get_suff_array(ab);
    vector<int> p = suff.first;
    vector<vector<int>> cl = suff.second;

    vector<int> z(a.size());
    vector<vector<pair<int, int>>> g(a.size(), vector<pair<int, int>>());
    int l = 0, r = -1;
    for (int i = 0; i < (int)a.size(); i++) {
        int cur = (i <= r ? min(r - i + 1, z[l + r - i]) : 1);
        while ((i - cur >= 0) && (i + cur < (int)a.size()) && (a[i + cur] == a[i - cur])) ++cur;
        z[i] = cur - 1;
        if (i + cur - 1 > r) {
            l = i - cur + 1;
            r = i + cur - 1;
        }
        g[i].push_back(make_pair(+1, i));
        g[i - cur + 1].push_back(make_pair(-1, i));
    }
    l = 0, r = -1;
    for (int i = 0; i + 1 < (int)a.size(); i++) {
        if (a[i] != a[i + 1]) continue;
        int cur = (i < r ? min(r - i, z[l + r - i - 1]) : 1);
        while ((i - cur >= 0) && (i + cur + 1 < (int)a.size()) && (a[i + cur + 1] == a[i - cur])) ++cur;
        z[i] = cur - 1;
        if (i + cur > r) {
            l = i - cur + 1;
            r = i + cur;
        }
        g[i].push_back(make_pair(+2, i));
        g[i - cur + 1].push_back(make_pair(-2, i));
    }
    set<int> s1, s2;
    vector<int> maxpal(a.size() + 1);
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        for (int j = 0; j < (int)g[i].size(); j++) {
            if (g[i][j].first == +1) s1.insert(g[i][j].second);
            if (g[i][j].first == +2) s2.insert(g[i][j].second);
        }
        maxpal[i] = (*s1.rbegin() - i) * 2 + 1;
        if (!s2.empty()) maxpal[i] = max(maxpal[i], (*s2.rbegin() - i) * 2 + 2);
        for (int j = 0; j < (int)g[i].size(); j++) {
            if (g[i][j].first == -1) s1.erase(g[i][j].second);
            if (g[i][j].first == -2) s2.erase(g[i][j].second);
        }
    }
//    cerr << a << endl;
//    for (int i = 0; i < (int)maxpal.size(); i++) cerr << maxpal[i] << " ";
//    cerr << endl;
    int last = -1;
    int ans = -1;
    l = -1, r = -1;
    vector<int> next(p.size(), -1);
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        if (p[i] > (int)a.size()) last = p[i];
        next[i] = last;
    }
    last = -1;
    for (int i = 0; i < (int)p.size(); i++) {
        if (p[i] > (int)a.size()) last = p[i];
        if ((p[i] < (int)a.size()) && (last != -1)) {
            int u = last;
            int v = p[i];
            int len = 0;
            for (int j = (int)cl.size() - 1; j >= 0; j--) {
                if ((u + (1 << j) <= (int)ab.size()) && (v + (1 << j) <= a.size()) && (cl[j][u] == cl[j][v])) {
                    len += (1 << j);
                    u += (1 << j);
                    v += (1 << j);
                }
            }
            if (len != 0) {
                int cur = len * 2 + maxpal[v];
                if (cur > ans) {
                    ans = cur;
                    l = p[i];
                    r = v + maxpal[v];
                }
            }
        }
        if ((p[i] < (int)a.size()) && (next[i] != -1)) {
            int u = next[i];
            int v = p[i];
            int len = 0;
            for (int j = (int)cl.size() - 1; j >= 0; j--) {
                if ((u + (1 << j) <= (int)ab.size()) && (v + (1 << j) <= a.size()) && (cl[j][u] == cl[j][v])) {
                    len += (1 << j);
                    u += (1 << j);
                    v += (1 << j);
                }
            }
            if (len == 0) continue;
            int cur = len * 2 + maxpal[v];
            if (cur > ans) {
                ans = cur;
                l = p[i];
                r = v + maxpal[v];
            }
        }
    }
    string res = "";
    for (int i = l; i < r; i++) res += a[i];
    for (int i = 0; i < ans - (r - l); i++) {
        res += res[ans - (r - l) - 1 - i];
    }
    return res;
}

string fast_solve(string s, string t) {
    string ans1 = solve(s, t);
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    string ans2 = solve(t, s);
    if ((ans2.size() > ans1.size()) || ((ans1.size() == ans2.size()) && (ans2 < ans1))) ans1 = ans2;
    if (ans1 == "") ans1 = "-1";
    return ans1;
}

bool is_pal(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

string slow_solve(string s, string t) {
    string ans = "";
    for (int l = 0; l < (int)s.size(); l++) {
        string cur = "";
        for (int r = l; r < (int)s.size(); r++) {
            cur += s[r];
            for (int l2 = 0; l2 < (int)t.size(); l2++) {
                string cur2 = cur;
                for (int r2 = l2; r2 < (int)t.size(); r2++) {
                    cur2 += t[r2];
                    if ((is_pal(cur2)) && ((cur2.size() > ans.size()) || ((cur2.size() == ans.size()) && (cur2 < ans)))) {
                        ans = cur2;
                    }
                }
            }
        }
    }
    if (ans == "") ans = "-1";
    return ans;
}

void tester(bool flag) {
    if (!flag) return;
    for (int it = 0; it < 100; it++) {
        string s = "", t = "";
        int len_s = rand() % MAX_LEN_S + 1;
        int len_t = rand() % MAX_LEN_S + 1;
        for (int i = 0; i < len_s; i++) s += char(rand() % 26 + 'a');
        for (int i = 0; i < len_t; i++) t += char(rand() % 26 + 'a');
        string ans1 = fast_solve(s, t);
        string ans2 = slow_solve(s, t);
        if (ans1 == ans2) {
            cout << "Ok!" << endl;
        } else {
            cerr << s << " " << t << endl;
            cerr << ans1 << " instead of " << ans2 << endl;
            assert(false);
        }
    }
}

int main() {
    tester(0);
//    freopen("input.txt", "r", stdin);
    int tt;
    scanf("%d\n", &tt);
    while (tt--) {
        string s, t;
        cin >> s >> t;
        cout << fast_solve(s, t) << endl;
    }
    return 0;
}

