// priority_queue
#include <bits/stdc++.h>
#include <bits/extc++.h>
#include <ext/rope>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std;
int main() {
__gnu_pbds::priority_queue <int, std::greater<int>,
__gnu_pbds::pairing_heap_tag> pq;
// template < typename Value_Type ,
// typename Cmp_Fn = std :: less < Value_Type > ,
// typename Tag = pairing_heap_tag ,
// typename Allocator = std :: allocator < char > >
// class priority_queue
__gnu_pbds::priority_queue <int> p ;
__gnu_pbds::priority_queue <int>::point_iterator it = p.push (0);
p.push(1); p.push(2);
p.modify (it, 3);
assert(p.top() == 3);
p.erase(it);
assert(p.top() == 2);
// merge
// void join(priority_queue &other)
// other will be cleared
}
// binary search tree
#include <ext/pb_ds/assoc_container.hpp>
/*
template <
typename Key , typename Mapped ,
typename Cmp_Fn = std :: less < Key > ,
typename Tag = rb_tree_tag ,
template <
typename Const_Node_Iterator ,
typename Node_Iterator ,
typename Cmp_Fn_ , typename Allocator_ >
class Node_Update = null_tree_node_update ,
typename Allocator = std :: allocator < char > >
class tree ;
*/
// Mapped: null_type
// tag: rb_tree_tag, splay_tree_tag, ov_tree_tag
// Node_Update: tree_order_statistics_node_update
// find_by_order(0-indexed), order_of_key
// void join(tree &oth)
// void split(const_key_reference r_key, tree &other)

cc_hash_table<int, bool> h1;
gp_hash_table<int, bool> h2; // faster.
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr;
/*
Type: int
null_type 无映射
less<int> 从小到大排序
rb_tree_tag 红黑树
tree_order_statistics_node_update 更新方式
tr.insert(x);
tr.erase(x);
tr.order_of_key(x);
tr.find_by_order(x);
tr.join(b); 将同样的树b并入tr，前提是两棵树类型一样且没有重复元素
tr.split(v, b); 分裂，key小于等于v的元素属于tr，其余的属于b
tr.lower_bound(x);
tr.upper_bound(x);
Complexity: O(logn) 
*/
using trs = trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update>;
using it = trs :: iterator;
trs t;
/*
第一个参数必须为字符串类型
t.insert(s);
t.erase(s);
t.join(b);
pair使用方法:
pair<it, it> range = base.prefix_range(x)
for(auto i = range.first; i != range.end(); ++ i)
	cout << *it << " ";
cout << endl;
*/
rope<int> tre;
/*
t.push_back(x); //在末尾添加x
t.insert(pos,x); //在pos插入x　　
t.erase(pos,x); //从pos开始删除x个
t.copy(pos,len,x); //从pos开始到pos+len为止用x代替
t.replace(pos,x); //从pos开始换成x
t.substr(pos,x); //提取pos开始x个
t.at(x)/t[x]; //访问第x个元素
Complexity: O(nsqrtn)
*/
