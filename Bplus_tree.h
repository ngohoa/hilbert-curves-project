//IMPLEMENTATION OF B+ TREE IN C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef WINDOWS
#define bool char
#define false 0
#define true 1
#endif
 
 
// Default order is 4.
#define DEFAULT_ORDER 10
 
// Minimum order is necessarily 3.  We set the maximum
// order arbitrarily.
#define MIN_ORDER 3
#define MAX_ORDER 20
 
 
// TYPES.
 
typedef struct record {
    int* value;
} record;
 
 
typedef struct node {
    void ** pointers;
    int * keys;
    struct node * parent;
    bool is_leaf;
    int num_keys;
    struct node * next; // Used for queue.
} node;
void message_1( void );
void message_2( void );
void message_3( void );
void enqueue( node * new_node );
node * dequeue( void );
int height( node * root );
int path_to_root( node * root, node * child );
void print_leaves( node * root );
void display( node * root );
void find_and_print(node * root, int key, bool verbose);
int find_and_print_range(node * root, int range1, int range2, bool verbose);
int find_range( node * root, int key_start, int key_end, bool verbose,
int returned_keys[], void * returned_pointers[]);
node * find_leaf( node * root, int key, bool verbose );
record * find( node * root, int key, bool verbose );
int cut( int length );
 
// Insertion.
 
record * make_record(int* value);
node * make_node( void );
node * make_leaf( void );
int get_left_index(node * parent, node * left);
node * insert_into_leaf( node * leaf, int key, record * pointer );
node * insert_into_leaf_after_splitting(node * root, node * leaf, int key, record * pointer);
node * insert_into_node(node * root, node * parent,
        int left_index, int key, node * right);
node * insert_into_node_after_splitting(node * root, node * parent, int left_index,
        int key, node * right);
node * insert_into_parent(node * root, node * left, int key, node * right);
node * insert_into_new_root(node * left, int key, node * right);
node * start_new_tree(int key, record * pointer);
node * insert( node * root, int key, int* value );
 
// Deletion.
 
int get_neighbor_index( node * n );
node * adjust_root(node * root);
node * merge_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime);
node * redistribute_nodes(node * root, node * n, node * neighbor, int neighbor_index,
        int k_prime_index, int k_prime);
node * del_entry( node * root, node * n, int key, void * pointer );
node * del( node * root, int key );


extern int order;
extern node * queue;
extern bool verbose_output;