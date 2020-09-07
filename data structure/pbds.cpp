// priority_queue
#include <ext/pb_ds/priority_queue.hpp>
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
// hash table
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb ds/hash_policy.hpp>
// __gnu_pbds::cc hash table <Key, Mapped>
// __gnu_pbds::gp hash table <Key, Mapped>
