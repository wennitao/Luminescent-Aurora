解决问题：多个模式串，一个匹配串的匹配问题。

AC自动机构建方法：

1. 对模式串建$trie$树。(串结尾处节点打标记)
2. 使用$bfs$构建$fail$指针：设父亲节点为$v$，当前字母为$c$。沿着父亲的$fail$指针一直跳$fail$指针，直到找到节点$u$含有字母$c$的子节点，或跳至根节点。特殊的，第二层节点(即根直接指向的节点)的$fail$指针直接指向根节点。

方便起见，对于节点$v$，若其不含字母$c$的子节点，直接将字母$c$的子节点指向$v$的$fail$指针的字母$c$子节点。

###例题

---

Luogu P3690 模板AC自动机

~~~cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
    int fail, ed ;
    int ch[26] ;
}tree[100010] ;
char s[160][110], t[1000010] ;
int ans[160], cnt ;
inline void clear(int v) {
    tree[v].fail = tree[v].ed = 0 ;
    memset (tree[v].ch, 0, sizeof tree[v].ch) ;
}
void insert (char *s, int num) {
    int len = strlen (s + 1), p = 0 ;
    for (int i = 1; i <= len; i ++) {
        int c = s[i] - 'a' ;
        if (!tree[p].ch[c]) tree[p].ch[c] = ++ cnt, clear (cnt) ;
        p = tree[p].ch[c] ;
    }
    tree[p].ed = num ;
}
void build () {
    queue<int> que ;
    for (int i = 0; i < 26; i ++)
        if (tree[0].ch[i]) {
            que.push (tree[0].ch[i]) ;
            tree[tree[0].ch[i]].fail = 0 ;
        }
    while (!que.empty()) {
        int v = que.front(); que.pop() ;
        for (int i = 0; i < 26; i ++) {
            if (tree[v].ch[i]) {
                tree[tree[v].ch[i]].fail = tree[tree[v].fail].ch[i] ;
                que.push (tree[v].ch[i]) ;
            } else
                tree[v].ch[i] = tree[tree[v].fail].ch[i] ;
        }
    }
}
void query (char *s) {
    int len = strlen (s + 1), p = 0 ;
    for (int i = 1; i <= len; i ++) {
        int c = s[i] - 'a' ;
        p = tree[p].ch[c] ;
        for (int v = p; v; v = tree[v].fail) ans[tree[v].ed] ++ ;
    }
}
int main() {
    int n ;
    while (scanf("%d", &n) && n) {
        clear (0); cnt = 0 ;
        for (int i = 1; i <= n; i ++) {
            scanf("%s", s[i] + 1) ;
            insert (s[i], i) ;
            ans[i] = 0 ;
        }
        build () ;
        scanf("%s", t + 1) ;
        query (t) ;
        int mx = 0 ;
        for (int i = 1; i <= n; i ++) mx = max (mx, ans[i]) ;
        printf("%d\n", mx) ;
        for (int i = 1; i <= n; i ++)
            if (ans[i] == mx) printf("%s\n", s[i] + 1) ;
    }
    return 0 ;
}
~~~

---

Luogu P2444 POI2000 病毒

题意：给定一些01串，问是否存在无限长的不存在这些01串的字符串。

题解：对这些01串建AC自动机，即找AC自动机上除串结尾节点是否存在环。

~~~cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
    int fail; bool flag ;
    int ch[26] ;
}tree[30010] ;
char s[30010] ;
int cnt ;
bool vis[30010], ins[30010] ;
void insert (char *s) {
    int len = strlen (s + 1), p = 0 ;
    for (int i = 1; i <= len; i ++) {
        int c = s[i] - '0' ;
        if (!tree[p].ch[c]) tree[p].ch[c] = ++ cnt ;
        p = tree[p].ch[c] ;
    }
    tree[p].flag = 1 ;
}
void build () {
    queue<int> que ;
    if (tree[0].ch[0]) que.push (tree[0].ch[0]) ;
    if (tree[0].ch[1]) que.push (tree[0].ch[1]) ;
    while (!que.empty()) {
        int v = que.front(); que.pop() ;
        for (int i = 0; i < 2; i ++) {
            if (tree[v].ch[i]) {
                tree[tree[v].ch[i]].fail = tree[tree[v].fail].ch[i] ;
                tree[tree[v].ch[i]].flag |= tree[tree[tree[v].ch[i]].fail].flag ;
                que.push (tree[v].ch[i]) ;
            } else
                tree[v].ch[i] = tree[tree[v].fail].ch[i] ;
        }
    }
}
void dfs (int v) {
    ins[v] = 1 ;
    for (int i = 0; i < 2; i ++) {
        int to = tree[v].ch[i] ;
        if (ins[to]) {
            printf("TAK\n"); exit (0) ;
        }
        if (vis[to] || tree[to].flag) continue ;
        vis[to] = 1; dfs (to) ;
    }
    ins[v] = 0 ;
}
int main() {
    int n ;
    scanf("%d", &n) ;
    for (int i = 1; i <= n; i ++) {
        scanf("%s", s + 1) ;
        insert (s) ;
    }
    build () ;
    dfs (0) ;
    printf("NIE\n") ;
    return 0 ;
}
~~~

---

bzoj1030 JSOI2007 文本生成器

题意：给定$n$个单词，求长度为$m$的字符串且至少包含一个单词的方案数。

题解：转换为总方案数减去不包含任何一个单词的方案数，即求不包含任何一个单词的方案数。

对单词建AC自动机。

设$dp[i][j]$表示长度为$i$的字符串，匹配到AC自动机上$j$号节点的方案数。直接在AC自动机上转移。

最后统计$\sum_j dp[m][j]$，其中$j$不是任何一个单词的结束节点。

答案即为$26^m-\sum_j dp[m][j]$

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int M = 10007 ;
int trie[6010][27], fail[6010], sz = 1 ;
int dp[110][6010] ;
bool ed[6010] ;
char s[110] ;
void insert () {
    int len = strlen (s), now = 1 ;
    for (int i = 0; i < len; i ++) {
        int c = s[i] - 'A' ;
        if (trie[now][c]) now = trie[now][c] ;
        else now = trie[now][c] = ++ sz ;
    }
    ed[now] = 1 ;
}
void build () {
    queue<int> que ;
    que.push (1); fail[1] = 0 ;
    while (!que.empty()) {
        int now = que.front(); que.pop() ;
        for (int i = 0; i < 26; i ++) {
            if (!trie[now][i]) continue ;
            int k = fail[now] ;
            while (!trie[k][i]) k = fail[k] ;
            fail[trie[now][i]] = trie[k][i] ;
            if (ed[trie[k][i]]) ed[trie[now][i]] = 1 ;
            que.push (trie[now][i]) ;
        }
    }
}
int main() {
    int n, m ;
    cin >> n >> m ;
    for (int i = 1; i <= n; i ++) {
        scanf("%s", s) ;
        insert () ;
    }
    for (int i = 0; i < 26; i ++) trie[0][i] = 1 ;
    build () ;
    dp[0][1] = 1 ;
    for (int i = 1; i <= m; i ++)
        for (int j = 1; j <= sz; j ++) {
            if (ed[j] || !dp[i - 1][j]) continue ;
            for (int k = 0; k < 26; k ++) {
                int x = j ;
                while (!trie[x][k]) x = fail[x] ;
                dp[i][trie[x][k]] = (dp[i][trie[x][k]] + dp[i - 1][j]) % M ;
            }
        }
    int ans = 1 ;
    for (int i = 1; i <= m; i ++) ans = ans * 26 % M ;
    for (int i = 1; i <= sz; i ++)
        if (!ed[i]) ans = (ans - dp[m][i]) % M ;
    printf("%d\n", (ans % M + M) % M) ;
    return 0 ;
}
~~~

---

bzoj 2434 Noi2011 阿狸的打字机

题意：你可以输入小写字母或按下B、P按钮，按下B会删除最后一个小写字母，按下P会打印现在的小写字母串。求第$x$个打印的串在第$y$个打印的串中出现了几次。小写字母、B、P总数$n \le 10^5$，询问数$m \le 10^5$

题解：

1. 暴力。对所有字符串建AC自动机。对于每个询问暴力在AC自动机上查询：在AC自动机上一边跑一边跳$fail$统计答案。如现在跑到节点$v$，向上跳$fail$指针，统计这些$fail$指针跳到的节点是串$x$结束节点的数量。
2. 优化暴力。有许多$y$串是一样的。离线询问，按$y$排序，一起统计答案。
3. 优化跳$fail$的过程。一个节点有且仅有一个$fail$指针，即是一颗将$fail$反向父亲指向儿子的树。将在AC自动机上跑$y$串所有经过的节点$v$，打上+1的标记。询问即查询$x$串结束节点的子树和。AC自动机建好后，先$dfs$一遍，维护$dfs$序，将标记打在树状数组上，统计是子树区间求和。($dfs$序下子树为一段连续区间)
4. 优化查询$y$串时打+1标记的过程。按照原操作序列的流程，到新节点打上+1标记，B操作离开时打上-1标记，对于询问查询子树和即可。

~~~cpp
/*************************************************************************
    > File Name: P2414.cpp
    > Author: wennitao
    > Mail: wennitao@126.com 
    > Created Time: 六  3/ 3 10:12:02 2018
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10 ;
struct ques{
	int x,id ;
} ;
int t[maxn][26],fa[maxn],l[maxn],r[maxn],ans[maxn],bt[maxn],fail[maxn],pos[maxn] ;
vector<int> G[maxn] ;
vector<ques> query[maxn] ;
int tick = 0 ;
int lowbit(int x){
	return x & (-x) ;
}
void add(int x,int val){
	while(x <= tick){
		bt[x] += val ;
		x += lowbit(x) ;
	}
}
int sum(int x){
	int ret = 0 ;
	while(x){
		ret += bt[x] ;
		x -= lowbit(x) ;
	}
	return ret ;
}
int go(int p,int c){
	if(t[p][c] > 0) return t[p][c] ;
	else if(p == 1) return 1 ;
	else return t[p][c] = go(fail[p],c) ;
}
void dfs(int u){
	tick ++ ;
	l[u] = tick ;
	for(int i = 0; i < G[u].size(); i++)
		dfs(G[u][i]) ;
	r[u] = tick ;
}
int main()
{
	string s ;
	cin >> s ;
	int m = 1,id = 0,p = 1 ;
	for(int i = 0; i < s.length(); i++){
		int c = s[i] - 'a' ;
		if(s[i] == 'P'){
			id ++; pos[id] = p ;
		}
		else if(s[i] == 'B'){
			p = fa[p] ;
		}
		else{
			if(t[p][c] == 0){
				m ++; t[p][c] = m; fa[m] = p ;
			}
			p = t[p][c] ;
		}
	}
	queue<int> que ;
	fail[1] = 1 ;
	for(int c = 0; c < 26; c++){
		int u = t[1][c] ;
		if(u > 0){
			fail[u] = 1; que.push(u); G[1].push_back(u) ;
		}
	}
	while(!que.empty()){
		int u = que.front(); que.pop() ;
		for(int c = 0; c < 26; c++){
			int v = t[u][c] ;
			if(v > 0){
				fail[v] = go(fail[u],c); que.push(v);
				G[fail[v]].push_back(v) ;
			}
		}
	}
	dfs(1) ;
	cin >> m ;
	for(int i = 0; i < m; i++){
		int x,y ;
		scanf("%d%d",&x,&y) ;
		query[y].push_back((ques){x,i}) ;
	}
	p = 1; int y = 0 ;
	for(int i = 0; i < s.length(); i++){
		int c = s[i] - 'a' ;
		if(s[i] == 'P'){
			y ++ ;
			for(int j = 0; j < query[y].size(); j++){
				int id = query[y][j].id,x = query[y][j].x ;
				ans[id] = sum(r[pos[x]]) - sum(l[pos[x]] - 1) ;
			}
		}
		else if(s[i] == 'B'){
			add(l[p],-1); p = fa[p] ;
		}
		else{
			p = t[p][c] ;
			add(l[p],1) ;
		}
	}
	for(int i = 0; i < m; i++)
		printf("%d\n",ans[i]) ;
	return 0 ;
}
~~~