#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define N	150000
#define Q	150000
#define D	1000

int min(int a, int b) { return a < b ? a : b; }

unsigned int Z;

int rand_() {
	return (Z *= 3) >> 1;
}

void srand_() {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	Z = tv.tv_sec ^ tv.tv_usec | 1;
}

int ll[Q], rr[Q], xx[Q];

void sort(int *hh, int l, int r) {
	while (l < r) {
		int i = l, j = l, k = r, h = hh[l + rand_() % (r - l)], tmp;

		while (j < k)
			if (xx[hh[j]] == xx[h])
				j++;
			else if (xx[hh[j]] > xx[h]) {
				tmp = hh[i], hh[i] = hh[j], hh[j] = tmp;
				i++, j++;
			} else {
				k--;
				tmp = hh[j], hh[j] = hh[k], hh[k] = tmp;
			}
		sort(hh, l, i);
		l = k;
	}
}

int main() {
	int t;

	srand_();
	scanf("%d", &t);
	while (t--) {
		static long long aa[N + 1];
		static int hh[Q], ii[Q], kk[Q], ii_[D + 1];
		int n, q, h, h_, i, d, k, k_, lower, upper;
		long long x;

		scanf("%d%d", &n, &q);
		aa[0] = 0;
		for (i = 1; i <= n; i++) {
			scanf("%lld", &aa[i]);
			aa[i] += aa[i - 1];
		}
		for (h = 0; h < q; h++)
			scanf("%d%d%d", &ll[h], &rr[h], &xx[h]), ll[h]--;
		for (h = 0; h < q; h++)
			hh[h] = h;
		sort(hh, 0, q);
		memset(ii_, 0, (D + 1) * sizeof *ii_);
		for (h_ = 0; h_ < q; h_++) {
			h = hh[h_], x = xx[h];
			for (d = 1; d <= D && d <= n; d++) {
				i = ii_[d];
				while (i + d <= n && aa[i + d] - aa[i] >= x)
					i++;
				ii_[d] = i;
			}
			i = ll[h], k = 0;
			for (d = 1; d <= D && d <= n; d++)
				if (i < ii_[d]) {
					k_ = min(rr[h] - i, ii_[d] - i + d - 1) / d;
					i += k_ * d, k += k_;
				}
			lower = 0;
			while (1) {
				while (i + lower + D <= rr[h] && aa[i + lower + D] - aa[i] < x)
					lower += D;
				upper = min(lower + D, rr[h] - i + 1);
				while (upper - lower > 1) {
					d = (lower + upper) / 2;
					if (aa[i + d] - aa[i] >= x)
						upper = d;
					else
						lower = d;
				}
				if (i + upper > rr[h])
					break;
				i += upper, k++;
			}
			ii[h] = i, kk[h] = k;
		}
		for (h = 0; h < q; h++)
			printf("%d %lld\n", kk[h], aa[rr[h]] - aa[ii[h]]);
	}
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N	500000
#define Q	500000
#define N_	(1 << 19)	/* N_ = pow2(ceil(log2(N + 2))) */
#define A	26
#define K	4

int max(int a, int b) { return a > b ? a : b; }

char cc[N + 1]; int n;

void append(int **ej, int *eo, int i, int j) {
	int o = eo[i]++;

	if (o >= 2 && (o & o - 1) == 0)
		ej[i] = (int *) realloc(ej[i], o * 2 * sizeof *ej[i]);
	ej[i][o] = j;
}

int tt[N + 2][A], fff[N + 2][A], ff[N + 2], ff_[N + 2], len[N + 2];
int *ev[N + 2], eo[N + 2], ta[N + 2], tb[N + 2];

int node(int l) {
	static int _;

	len[_] = l;
	ev[_] = (int *) malloc(2 * sizeof *ev[_]);
	return _++;
}

void dfs(int u) {
	static int t_;
	int o;

	ta[u] = t_++;
	for (o = eo[u]; o--; ) {
		int v = ev[u][o];

		dfs(v);
	}
	tb[u] = t_;
}

int uu[N + 1];

void eertree() {
	int i, a, u;

	node(0), node(-1);
	for (a = 0; a < A; a++)
		fff[0][a] = fff[1][a] = 1;
	ff[0] = ff_[0] = 1;
	append(ev, eo, 1, 0);
	uu[0] = u = 0;
	for (i = 0; i < n; i++) {
		a = cc[i] - 'a';
		if (i <= len[u] || cc[i - 1 - len[u]] != a + 'a')
			u = fff[u][a];
		if (!tt[u][a]) {
			int v = node(len[u] + 2), f = tt[fff[u][a]][a];

			ff[v] = f;
			ff_[v] = f == 0 || len[v] - len[f] != len[f] - len[ff[f]] ? f : ff_[f];
			memcpy(fff[v], fff[f], sizeof fff[f]);
			fff[v][cc[i - len[f]] - 'a'] = f;
			append(ev, eo, f, v);
			tt[u][a] = v;
		}
		uu[i + 1] = u = tt[u][a];
	}
	dfs(1);
}

int ft[N];

void ft_update(int i, int x) {
	while (i < n) {
		ft[i] = max(ft[i], x);
		i |= i + 1;
	}
}

int ft_query(int i) {
	int x = -1;

	while (i >= 0) {
		x = max(x, ft[i]);
		i &= i + 1, i--;
	}
	return x;
}

int st1[N_ * 2], st2[N_ * 2], n_;

void build() {
	memset(ft, 0, n * sizeof *ft);
	n_ = 1;
	while (n_ < n + 2)
		n_ <<= 1;
	memset(st1, -1, n_ * 2 * sizeof *st1);
	memset(st2, -1, n_ * 2 * sizeof *st2);
}

void st1_pul(int i) {
	st1[i] = max(st1[i << 1 | 0], st1[i << 1 | 1]);
}

void st1_update(int i, int x) {
	i += n_;
	st1[i] = max(st1[i], x);
	while (i > 1)
		st1_pul(i >>= 1);
}

int st1_query(int l, int r) {
	int x = -1;

	for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
		if ((l & 1) == 1)
			x = max(x, st1[l++]);
		if ((r & 1) == 0)
			x = max(x, st1[r--]);
	}
	return x;
}

void st2_update(int l, int r, int x) {
	for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
		if ((l & 1) == 1) {
			st2[l] = max(st2[l], x);
			l++;
		}
		if ((r & 1) == 0) {
			st2[r] = max(st2[r], x);
			r--;
		}
	}
}

int st2_query(int i) {
	int x = -1;

	for (i += n_; i > 0; i >>= 1)
		x = max(x, st2[i]);
	return x;
}

int main() {
	static int *eh[N], eo[N], ii[Q], ans[Q];
	int q, h, i, i_, j, j_, k, o, u, v, w, d, x;

	scanf("%d%d%s", &n, &q, cc);
	for (j = 0; j < n; j++)
		eh[j] = (int *) malloc(2 * sizeof *eh[j]);
	for (h = 0; h < q; h++) {
		scanf("%d%d", &i, &j), i--, j--;
		ii[h] = i;
		append(eh, eo, j, h);
	}
	eertree();
	build();
	for (j = 0; j < n; j++) {
		u = uu[j + 1];
		if (u) {
			i = st1_query(ta[u], tb[u] - 1);
			if (i != -1)
				ft_update(n - 1 - (i - len[u] + 1), len[u]);
		}
		v = u;
		while (v) {
			ft_update(n - 1 - (j - len[v] + 1), len[ff[v]]);
			w = ff_[v], d = len[v] - len[ff[v]];
			if (w) {
				i = st1_query(ta[w], tb[w] - 1);
				if (i != -1)
					ft_update(n - 1 - (i - len[w] + 1), len[w]);
			}
			for (k = 1; k <= K && len[w] + d * k <= len[v]; k++) {
				i = j - len[w] - d * k + 1;
				ft_update(n - 1 - i, len[w] + d * (k - 1));
			}
			if (len[v] - len[w] >= d * K) {
				i = j - len[w] - d * K + 1;
				st2_update(j - len[v] + 2, i, j);
			}
			v = w;
		}
		u = uu[j + 1];
		st1_update(ta[u], j);
		for (o = eo[j]; o--; ) {
			h = eh[j][o], i = ii[h];
			x = ft_query(n - 1 - i);
			j_ = st2_query(i);
			if (j_ != -1 && j_ >= i) {
				u = uu[j_ + 1];
				while (j_ - len[ff_[u]] + 1 < i)
					u = ff_[u];
				d = len[u] - len[ff[u]];
				i_ = j_ - len[u] + 1;
				i_ += (i - i_ + d - 1) / d * d;
				x = max(x, j_ - i_ + 1 - d);
				if (i_ > i)
					x = max(x, j_ - i_ - (d - i_ + i) * 2 + 1);
			}
			ans[h] = x;
		}
	}
	for (h = 0; h < q; h++)
		printf("%d\n", ans[h]);
	return 0;
}
