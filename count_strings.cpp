#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <unordered_map>
#include <vector>

static const int MOD = 1000000007;
static const int NMAX = 200;

typedef std::pair<int, int> PII;
typedef PII NFA;
typedef std::bitset<NMAX> BS;

struct NState {
	int nxt[2];
	int eps;
	int lst[NMAX];

	void init() {
		nxt[0] = -1;
		nxt[1] = -1;
		eps = 0;
	}

	void push(int x) {
		lst[eps++] = x;
	}
};

struct DState {
	bool ac;
	int nxt[2];
};

static int M;
class Matrix {
	private:
		int *data;
	public:
		Matrix() {memset(data = new int[M * M], 0x00, M * M * sizeof(*data));}
		~Matrix() {delete[] data;}
		int& operator()(int i, int j)       {return data[i * M + j];}
		int  operator()(int i, int j) const {return data[i * M + j];}
		void operator=(const Matrix &that) {
			memcpy(data, that.data, M * M * sizeof(*data));
		}
};

static char RE[NMAX / 2 + 1];
static int L;
static const char *pptr;
static int N;
static NState ns[NMAX];
static std::vector<DState> ds;

static void mul(Matrix &C, const Matrix &A, const Matrix &B) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			long long t = 0;
			for(int k = 0; k < M; k++) {
				t = (t + (long long)A(i, k) * B(k, j)) % MOD;
			}
			C(i, j) = t;
		}
	}
}

static int solve() {
	M = ds.size();
	Matrix A, B, C;
	for(int i = 0; i < M; i++) {
		C(i, i) = 1;
		for(int j = 0; j < 2; j++) if(ds[i].nxt[j] >= 0) A(i, ds[i].nxt[j])++;
	}
	for(; ; ) {
		if((L & 1) != 0) {
			mul(B, C, A);
			C = B;
		}
		if((L >>= 1) == 0) break;
		mul(B, A, A);
		A = B;
	}
	int ret = 0;
	for(int i = 0; i < M; i++) {
		if(ds[i].ac) {
			ret += C(0, i);
			if(ret >= MOD) ret -= MOD;
		}
	}
	return ret;
}

static void expand(BS &bs) {
	static int sp, s[NMAX];
	for(int i = 0; i < N; i++) if(bs[i]) s[sp++] = i;
	while(sp != 0) {
		auto u = s[--sp];
		for(int i = 0; i < ns[u].eps; i++) {
			auto v = ns[u].lst[i];
			if(!bs[v]) {
				bs.set(v);
				s[sp++] = v;
			}
		}
	}
	for(int i = 0; i < N; i++) if(bs[i] && ns[i].eps != 0) bs.reset(i);
}

static void NFA2DFA(NFA nfa) {
	static std::vector<std::unordered_map<BS, int>::iterator> v;
	std::unordered_map<BS, int> m;
	{
		BS bs;
		bs.set(nfa.first);
		expand(bs);
		v.push_back(m.emplace(bs, ds.size()).first);
		ds.emplace_back();
	}
	do {
		auto it = v.back();
		v.pop_back();
		BS _[2];
		ds[it->second].ac = it->first[nfa.second];
		for(int i = 0; i < N; i++) {
			if(it->first[i]) {
				for(int c = 0; c < 2; c++) {
					if(ns[i].nxt[c] >= 0) _[c].set(ns[i].nxt[c]);
				}
			}
		}
		for(int c = 0; c < 2; c++) {
			expand(_[c]);
			if(!_[c].any()) {
				ds[it->second].nxt[c] = -1;
			} else {
				auto jt = m.emplace(_[c], -1).first;
				if(jt->second < 0) {
					jt->second = ds.size();
					v.push_back(jt);
					ds.emplace_back();
				}
				ds[it->second].nxt[c] = jt->second;
			}
		}
	} while(!v.empty());
}

static inline int NewNState() {
	ns[N].init();
	return N++;
}

static inline NFA CAT(NFA a, NFA b) {
	ns[a.second].push(b.first);
	return NFA(a.first, b.second);
}

static inline NFA OR(NFA a, NFA b) {
	auto x = NewNState(), y = NewNState();
	ns[x].push(a.first);
	ns[x].push(b.first);
	ns[a.second].push(y);
	ns[b.second].push(y);
	return NFA(x, y);
}

static inline NFA STAR(NFA a) {
	auto x = NewNState(), y = NewNState();
	ns[x].push(y);
	ns[x].push(a.first);
	ns[a.second].push(y);
	ns[a.second].push(a.first);
	return NFA(x, y);
}

static NFA parse() {
	if(*pptr != '(') {
		auto x = NewNState(), y = NewNState();
		ns[x].nxt[*pptr++ - 'a'] = y;
		return NFA(x, y);
	}
	pptr++;
	auto a = parse();
	if(*pptr == '|') {
		pptr++;
		auto b = parse();
		pptr++;
		return OR(a, b);
	}
	if(*pptr == '*') {
		pptr += 2;
		return STAR(a);
	}
	auto b = parse();
	pptr++;
	return CAT(a, b);
}

int main() {
	int t;
	for(scanf("%d", &t); t > 0; t--) {
		scanf("%s%d", RE, &L);
		pptr = RE;
		N = 0;
		NFA2DFA(parse());
		printf("%d\n", solve());
		ds.clear();
	}
	return 0;
}
