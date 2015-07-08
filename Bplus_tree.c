/*//IMPLEMENTATION OF B+ TREE IN C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef WINDOWS
#define bool char
#define false 0
#define true 1
#endif
 
 
// Default order is 4.
#define DEFAULT_ORDER 4
 
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
} node;*/
 
#include "Bplus_tree.h" 
 
 
// FUNCTION PROTOTYPES.
 
 
/*void message_1( void );
void message_2( void );
void message_3( void );
void enqueue( node * new_node );
node * dequeue( void );
int height( node * root );
int path_to_root( node * root, node * child );
void print_leaves( node * root );
void display( node * root );
void find_and_print(node * root, int key, bool verbose);
void find_and_print_range(node * root, int range1, int range2, bool verbose);
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
node * del( node * root, int key );*/
 
int order = DEFAULT_ORDER;
 
node * queue = NULL;
 
bool verbose_output = false; 
 
 
// FUNCTION DEFINITIONS.
 
// Prints the bottom row of keys of the tree (with their respective
// pointers, if the verbose_output flag is set.
void print_leaves( node * root ) {
    int i;
    node * c = root;
    if (root == NULL) {
        printf("Empty tree.\n");
        return;
    }
    while (!c->is_leaf)
        c = c->pointers[0];
    while (true) {
        for (i = 0; i < c->num_keys; i++) {
            if (verbose_output)
                printf("%lx ", (unsigned long)c->pointers[i]);
            printf("%d ", c->keys[i]);
        }
        if (verbose_output)
            printf("%lx ", (unsigned long)c->pointers[order - 1]);
        if (c->pointers[order - 1] != NULL) {
            printf(" | ");
            c = c->pointers[order - 1];
        }
        else
            break;
    }
    printf("\n");
}
 
 
//FUNCTION FOR RETURNING HEIGHT OF THE TREE
int height( node * root ) {
    int h = 0;
    node * c = root;
    while (!c->is_leaf) {
        c = c->pointers[0];
        h++;
    }
    return h;
}
 
 
//FUNCTION RETURNS THE LENGTH IN PATH
int path_to_root( node * root, node * child ) {
    int length = 0;
    node * c = child;
    while (c != root) {
        c = c->parent;
        length++;
    }
    return length;
}
 
/* Helper function for printing the
 * tree out.  See display.
 */
void enqueue( node * new_node ) {
    node * c;
    if (queue == NULL) {
        queue = new_node;
        queue->next = NULL;
    }
    else {
        c = queue;
        while(c->next != NULL) {
            c = c->next;
        }
        c->next = new_node;
        new_node->next = NULL;
    }
}
 
 
/* Helper function for printing the
 * tree out.  See display.
 */
node * dequeue( void ) {
    node * n = queue;
    queue = queue->next;
    n->next = NULL;
    return n;
}
 
//print the tree in the order of the level of nodes. || symbol is used to seperate the nodes
//if verbose flag is set, the pointer to the keys will also be displayed
void display( node * root ) {
 
    node * n = NULL;
    int i = 0;
    int rank = 0;
    int new_rank = 0;
 
    if (root == NULL) {
        printf("Empty tree.\n");
        return;
    }
    queue = NULL;
    enqueue(root);
    while( queue != NULL ) {
        n = dequeue();
        if (n->parent != NULL && n == n->parent->pointers[0]) {
            new_rank = path_to_root( root, n );
            if (new_rank != rank) {
                rank = new_rank;
                printf("\n");
            }
        }
        if (verbose_output)
            printf("(%lx)", (unsigned long)n);
        for (i = 0; i < n->num_keys; i++) {
            if (verbose_output)
                printf("%lx ", (unsigned long)n->pointers[i]);
            printf("%d ", n->keys[i]);
        }
        if (!n->is_leaf)
            for (i = 0; i <= n->num_keys; i++)
                enqueue(n->pointers[i]);
        if (verbose_output) {
            if (n->is_leaf)
                printf("%lx ", (unsigned long)n->pointers[order - 1]);
            else
                printf("%lx ", (unsigned long)n->pointers[n->num_keys]);
        }
        printf("| ");
    }
    printf("\n");
}
 
 
// Finds the record under a given key and prints an appropriate message
void find_and_print(node * root, int key, bool verbose) {
    record * r = find(root, key, verbose);
    /*if (r == NULL)
        printf("Record not found under key %d.\n", key);
    else
        printf("Record at %lx -- key %d, value %d %d.\n",
                (unsigned long)r, key, r->value[0], r->value[1]);*/
}
 
 
// Finds and prints the keys, pointers, and values within a range
int find_and_print_range( node * root, int key_start, int key_end,
        bool verbose ) {
    int max_x = 0, max_y = 0;
    int min_x = 600, min_y = 600;
    int i;
    int array_size = key_end - key_start + 1;
    int returned_keys[array_size];
    void * returned_pointers[array_size];
    int num_found = find_range( root, key_start, key_end, verbose,
            returned_keys, returned_pointers );
    if (!num_found)
        printf("Not found.\n");
    else {
        for (i = 0; i < num_found; i++) {
            int first, second;
            first = ((record *) returned_pointers[i])->value[0];
            second = ((record *) returned_pointers[i])->value[1];

            if (first <= min_x)
                min_x = first;
            if (first >= max_x)
                max_x = first;
            if (second <= min_y)
                min_y = second;
            if (second >= max_y)
                max_y = second;
        }
    }
    return (max_x-min_x+1)*(max_y-min_y+1);
}
 
 
int find_range( node * root, int key_start, int key_end, bool verbose,
        int returned_keys[], void * returned_pointers[]) {
    int i, num_found;
    num_found = 0;
    node * n = find_leaf( root, key_start, verbose );
    if (n == NULL) return 0;
    for (i = 0; i < n->num_keys && n->keys[i] < key_start; i++) ;
    if (i == n->num_keys) return 0;
    while (n != NULL) {
        for ( ; i < n->num_keys && n->keys[i] <= key_end; i++) {
            returned_keys[num_found] = n->keys[i];
            returned_pointers[num_found] = n->pointers[i];
            num_found++;
        }
        n = n->pointers[order - 1];
        i = 0;
    }
    return num_found;
}
 
 
//Displays information about leaf path if verbose flag is set
node * find_leaf( node * root, int key, bool verbose ) {
    int i = 0;
    node * c = root;
    if (c == NULL) {
        if (verbose)
            printf("Empty tree.\n");
        return c;
    }
    while (!c->is_leaf) {
        if (verbose) {
            printf("[");
            for (i = 0; i < c->num_keys - 1; i++)
                printf("%d ", c->keys[i]);
            printf("%d] ", c->keys[i]);
        }
        i = 0;
        while (i < c->num_keys) {
            if (key >= c->keys[i]) i++;
            else break;
        }
        if (verbose)
            printf("%d ->\n", i);
        c = (node *)c->pointers[i];
    }
    if (verbose) {
        printf("Leaf [");
        for (i = 0; i < c->num_keys - 1; i++)
            printf("%d ", c->keys[i]);
        printf("%d] ->\n", c->keys[i]);
    }
    return c;
}
 
 
// Finds and returns the record to which a key refers.
record * find( node * root, int key, bool verbose ) {
    int i = 0;
    node * c = find_leaf( root, key, verbose );
    if (c == NULL) return NULL;
    for (i = 0; i < c->num_keys; i++)
        if (c->keys[i] == key) break;
    if (i == c->num_keys)
        return NULL;
    else
        return (record *)c->pointers[i];
}
 
// Finds the appropriate place to split a node that is too big into two.
int cut( int length ) {
    if (length % 2 == 0)
        return length/2;
    else
        return length/2 + 1;
}
 
 
// INSERTION
 
// Creates a new record to hold the value to which a key refers.
record * make_record(int* value) {
    record * new_record = (record *)malloc(sizeof(record));
    if (new_record == NULL) {
        perror("Record creation.");
        exit(EXIT_FAILURE);
    }
    else {
        new_record->value = value;
    }
    return new_record;
}
 
 
//Creates a new node
node * make_node( void ) {
    node * new_node;
    new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        perror("Node creation.");
        exit(EXIT_FAILURE);
    }
    new_node->keys = malloc( (order - 1) * sizeof(int) );
    if (new_node->keys == NULL) {
        perror("New node keys array.");
        exit(EXIT_FAILURE);
    }
    new_node->pointers = malloc( order * sizeof(void *) );
    if (new_node->pointers == NULL) {
        perror("New node pointers array.");
        exit(EXIT_FAILURE);
    }
    new_node->is_leaf = false;
    new_node->num_keys = 0;
    new_node->parent = NULL;
    new_node->next = NULL;
    return new_node;
}
 
// Creates a new leaf by creating a node and then adapting it appropriately.
node * make_leaf( void ) {
    node * leaf = make_node();
    leaf->is_leaf = true;
    return leaf;
}
 
 
// Helper function used in insert_into_parent to find the index of the parent's pointer to
// the node to the left of the key to be inserted.
int get_left_index(node * parent, node * left) {
 
    int left_index = 0;
    while (left_index <= parent->num_keys &&
            parent->pointers[left_index] != left)
        left_index++;
    return left_index;
}
 
// Inserts a new pointer to a record and its corresponding key into a leaf. Returns the altered leaf.
node * insert_into_leaf( node * leaf, int key, record * pointer ) {
 
    int i, insertion_point;
 
    insertion_point = 0;
    while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key)
        insertion_point++;
 
    for (i = leaf->num_keys; i > insertion_point; i--) {
        leaf->keys[i] = leaf->keys[i - 1];
        leaf->pointers[i] = leaf->pointers[i - 1];
    }
    leaf->keys[insertion_point] = key;
    leaf->pointers[insertion_point] = pointer;
    leaf->num_keys++;
    return leaf;
}
 
 
// Inserts a new key and pointer to a new record into a leaf so as to exceed the tree's order, causing the leaf to be split
// in half.
node * insert_into_leaf_after_splitting(node * root, node * leaf, int key, record * pointer) {
 
    node * new_leaf;
    int * temp_keys;
    void ** temp_pointers;
    int insertion_index, split, new_key, i, j;
 
    new_leaf = make_leaf();
 
    temp_keys = malloc( order * sizeof(int) );
    if (temp_keys == NULL) {
        perror("Temporary keys array.");
        exit(EXIT_FAILURE);
    }
 
    temp_pointers = malloc( order * sizeof(void *) );
    if (temp_pointers == NULL) {
        perror("Temporary pointers array.");
        exit(EXIT_FAILURE);
    }
 
    insertion_index = 0;
    while (insertion_index < order - 1 && leaf->keys[insertion_index] < key)
        insertion_index++;
 
    for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {
        if (j == insertion_index) j++;
        temp_keys[j] = leaf->keys[i];
        temp_pointers[j] = leaf->pointers[i];
    }
 
    temp_keys[insertion_index] = key;
    temp_pointers[insertion_index] = pointer;
 
    leaf->num_keys = 0;
 
    split = cut(order - 1);
 
    for (i = 0; i < split; i++) {
        leaf->pointers[i] = temp_pointers[i];
        leaf->keys[i] = temp_keys[i];
        leaf->num_keys++;
    }
 
    for (i = split, j = 0; i < order; i++, j++) {
        new_leaf->pointers[j] = temp_pointers[i];
        new_leaf->keys[j] = temp_keys[i];
        new_leaf->num_keys++;
    }
 
    free(temp_pointers);
    free(temp_keys);
 
    new_leaf->pointers[order - 1] = leaf->pointers[order - 1];
    leaf->pointers[order - 1] = new_leaf;
 
    for (i = leaf->num_keys; i < order - 1; i++)
        leaf->pointers[i] = NULL;
    for (i = new_leaf->num_keys; i < order - 1; i++)
        new_leaf->pointers[i] = NULL;
 
    new_leaf->parent = leaf->parent;
    new_key = new_leaf->keys[0];
 
    return insert_into_parent(root, leaf, new_key, new_leaf);
}
 
 
// Inserts a new key and pointer to a node into a node into which these can fit
// without violating the B+ tree properties.
node * insert_into_node(node * root, node * n,
        int left_index, int key, node * right) {
    int i;
 
    for (i = n->num_keys; i > left_index; i--) {
        n->pointers[i + 1] = n->pointers[i];
        n->keys[i] = n->keys[i - 1];
    }
    n->pointers[left_index + 1] = right;
    n->keys[left_index] = key;
    n->num_keys++;
    return root;
}
 
 
// Inserts a new key and pointer to a node into a node, causing the node's size to exceed
// the order, and causing the node to split into two.
node * insert_into_node_after_splitting(node * root, node * old_node, int left_index,
        int key, node * right) {
 
    int i, j, split, k_prime;
    node * new_node, * child;
    int * temp_keys;
    node ** temp_pointers;
 
    /* First create a temporary set of keys and pointers
     * to hold everything in order, including
     * the new key and pointer, inserted in their
     * correct places.
     * Then create a new node and copy half of the
     * keys and pointers to the old node and
     * the other half to the new.
     */
 
    temp_pointers = malloc( (order + 1) * sizeof(node *) );
    if (temp_pointers == NULL) {
        perror("Temporary pointers array for splitting nodes.");
        exit(EXIT_FAILURE);
    }
    temp_keys = malloc( order * sizeof(int) );
    if (temp_keys == NULL) {
        perror("Temporary keys array for splitting nodes.");
        exit(EXIT_FAILURE);
    }
 
    for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {
        if (j == left_index + 1) j++;
        temp_pointers[j] = old_node->pointers[i];
    }
 
    for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {
        if (j == left_index) j++;
        temp_keys[j] = old_node->keys[i];
    }
 
    temp_pointers[left_index + 1] = right;
    temp_keys[left_index] = key;
 
    /* Create the new node and copy
     * half the keys and pointers to the
     * old and half to the new.
     */
    split = cut(order);
    new_node = make_node();
    old_node->num_keys = 0;
    for (i = 0; i < split - 1; i++) {
        old_node->pointers[i] = temp_pointers[i];
        old_node->keys[i] = temp_keys[i];
        old_node->num_keys++;
    }
    old_node->pointers[i] = temp_pointers[i];
    k_prime = temp_keys[split - 1];
    for (++i, j = 0; i < order; i++, j++) {
        new_node->pointers[j] = temp_pointers[i];
        new_node->keys[j] = temp_keys[i];
        new_node->num_keys++;
    }
    new_node->pointers[j] = temp_pointers[i];
    free(temp_pointers);
    free(temp_keys);
    new_node->parent = old_node->parent;
    for (i = 0; i <= new_node->num_keys; i++) {
        child = new_node->pointers[i];
        child->parent = new_node;
    }
 
    /* Insert a new key into the parent of the two
     * nodes resulting from the split, with
     * the old node to the left and the new to the right.
     */
 
    return insert_into_parent(root, old_node, k_prime, new_node);
}
 
 
 
/* Inserts a new node (leaf or internal node) into the B+ tree.
 * Returns the root of the tree after insertion.
 */
node * insert_into_parent(node * root, node * left, int key, node * right) {
 
    int left_index;
    node * parent;
 
    parent = left->parent;
 
    /* Case: new root. */
 
    if (parent == NULL)
        return insert_into_new_root(left, key, right);
 
    /* Case: leaf or node. (Remainder of
     * function body.)
     */
 
    /* Find the parent's pointer to the left
     * node.
     */
 
    left_index = get_left_index(parent, left);
 
 
    /* Simple case: the new key fits into the node.
     */
 
    if (parent->num_keys < order - 1)
        return insert_into_node(root, parent, left_index, key, right);
 
    /* Harder case:  split a node in order
     * to preserve the B+ tree properties.
     */
 
    return insert_into_node_after_splitting(root, parent, left_index, key, right);
}
 
 
/* Creates a new root for two subtrees
 * and inserts the appropriate key into
 * the new root.
 */
node * insert_into_new_root(node * left, int key, node * right) {
 
    node * root = make_node();
    root->keys[0] = key;
    root->pointers[0] = left;
    root->pointers[1] = right;
    root->num_keys++;
    root->parent = NULL;
    left->parent = root;
    right->parent = root;
    return root;
}
 
 
 
/* First insertion:
 * start a new tree.
 */
node * start_new_tree(int key, record * pointer) {
 
    node * root = make_leaf();
    root->keys[0] = key;
    root->pointers[0] = pointer;
    root->pointers[order - 1] = NULL;
    root->parent = NULL;
    root->num_keys++;
    return root;
}
 
 
 
//Main insertion function
node * insert( node * root, int key, int* value ) {
 
    record * pointer;
    node * leaf;
 
    /* The current implementation ignores
     * duplicates.
     */
 
    if (find(root, key, false) != NULL)
        return root;
 
    /* Create a new record for the
     * value.
     */
    pointer = make_record(value);
 
 
    /* Case: the tree does not exist yet.
     * Start a new tree.
     */
 
    if (root == NULL)
        return start_new_tree(key, pointer);
 
 
    /* Case: the tree already exists.
     * (Rest of function body.)
     */
 
    leaf = find_leaf(root, key, false);
 
    /* Case: leaf has room for key and pointer.
     */
 
    if (leaf->num_keys < order - 1) {
        leaf = insert_into_leaf(leaf, key, pointer);
        return root;
    }
 
 
    /* Case:  leaf must be split.
     */
 
    return insert_into_leaf_after_splitting(root, leaf, key, pointer);
}
 
 
 
 
// DELETION.
 
int get_neighbor_index( node * n ) {
 
    int i;
 
    /* Return the index of the key to the left
     * of the pointer in the parent pointing
     * to n.
     * If n is the leftmost child, this means
     * return -1.
     */
    for (i = 0; i <= n->parent->num_keys; i++)
        if (n->parent->pointers[i] == n)
            return i - 1;
 
    // Error state.
    printf("Search for nonexistent pointer to node in parent.\n");
    printf("Node:  %#lx\n", (unsigned long)n);
    exit(EXIT_FAILURE);
}
 
 
node * remove_entry_from_node(node * n, int key, node * pointer) {
 
    int i, num_pointers;
 
    // Remove the key and shift other keys accordingly.
    i = 0;
    while (n->keys[i] != key)
        i++;
    for (++i; i < n->num_keys; i++)
        n->keys[i - 1] = n->keys[i];
 
    // Remove the pointer and shift other pointers accordingly.
    // First determine number of pointers.
    num_pointers = n->is_leaf ? n->num_keys : n->num_keys + 1;
    i = 0;
    while (n->pointers[i] != pointer)
        i++;
    for (++i; i < num_pointers; i++)
        n->pointers[i - 1] = n->pointers[i];
 
 
    // One key fewer.
    n->num_keys--;
 
    // Set the other pointers to NULL for tidiness.
    // A leaf uses the last pointer to point to the next leaf.
    if (n->is_leaf)
        for (i = n->num_keys; i < order - 1; i++)
            n->pointers[i] = NULL;
    else
        for (i = n->num_keys + 1; i < order; i++)
            n->pointers[i] = NULL;
 
    return n;
}
 
 
node * adjust_root(node * root) {
 
    node * new_root;
 
    if (root->num_keys > 0)
        return root;
 
    if (!root->is_leaf) {
        new_root = root->pointers[0];
        new_root->parent = NULL;
    }
 
    // If it is a leaf (has no children),
    // then the whole tree is empty.
 
    else
        new_root = NULL;
 
    free(root->keys);
    free(root->pointers);
    free(root);
 
    return new_root;
}
 
 
//merge nodes that became small after deletion
node * merge_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime) {
 
    int i, j, neighbor_insertion_index, n_start, n_end, new_k_prime;
    node * tmp;
    bool split;
 
    /* Swap neighbor with node if node is on the
     * extreme left and neighbor is to its right.
     */
 
    if (neighbor_index == -1) {
        tmp = n;
        n = neighbor;
        neighbor = tmp;
    }
 
    /* Starting point in the neighbor for copying
     * keys and pointers from n.
     * Recall that n and neighbor have swapped places
     * in the special case of n being a leftmost child.
     */
 
    neighbor_insertion_index = neighbor->num_keys;
 
    
    split = false;
 
    
    if (!n->is_leaf) {
 
        /* Append k_prime.
         */
 
        neighbor->keys[neighbor_insertion_index] = k_prime;
        neighbor->num_keys++;
 
 
        /* Case (default):  there is room for all of n's keys and pointers
         * in the neighbor after appending k_prime.
         */
 
        n_end = n->num_keys;
 
        /* Case (special): k cannot fit with all the other keys and pointers
         * into one merged node.
         */
        n_start = 0; // Only used in this special case.
        if (n->num_keys + neighbor->num_keys >= order) {
            split = true;
            n_end = cut(order) - 2;
        }
 
        for (i = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_keys++;
            n->num_keys--;
            n_start++;
        }
 
        /* The number of pointers is always
         * one more than the number of keys.
         */
 
        neighbor->pointers[i] = n->pointers[j];
 
        /* If the nodes are still split, remove the first key from
         * n.
         */
        if (split) {
            new_k_prime = n->keys[n_start];
            for (i = 0, j = n_start + 1; i < n->num_keys; i++, j++) {
                n->keys[i] = n->keys[j];
                n->pointers[i] = n->pointers[j];
            }
            n->pointers[i] = n->pointers[j];
            n->num_keys--;
        }
 
        /* All children must now point up to the same parent.
         */
 
        for (i = 0; i < neighbor->num_keys + 1; i++) {
            tmp = (node *)neighbor->pointers[i];
            tmp->parent = neighbor;
        }
    }
 
    /* In a leaf, append the keys and pointers of
     * n to the neighbor.
     * Set the neighbor's last pointer to point to
     * what had been n's right neighbor.
     */
 
    else {
        for (i = neighbor_insertion_index, j = 0; j < n->num_keys; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_keys++;
        }
        neighbor->pointers[order - 1] = n->pointers[order - 1];
    }
 
    if (!split) {
        root = del_entry(root, n->parent, k_prime, n);
        free(n->keys);
        free(n->pointers);
        free(n);
    }
    else
        for (i = 0; i < n->parent->num_keys; i++)
            if (n->parent->pointers[i + 1] == n) {
                n->parent->keys[i] = new_k_prime;
                break;
            }
 
    return root;
 
}
 
 
/* Redistributes entries between two nodes when
 * one has become too small after deletion
 * but its neighbor is too big to append the
 * small node's entries without exceeding the
 * maximum
 */
node * redistribute_nodes(node * root, node * n, node * neighbor, int neighbor_index,
        int k_prime_index, int k_prime) {
 
    int i;
    node * tmp;
 
    /* Case: n has a neighbor to the left.
     * Pull the neighbor's last key-pointer pair over
     * from the neighbor's right end to n's left end.
     */
 
    if (neighbor_index != -1) {
        if (!n->is_leaf)
            n->pointers[n->num_keys + 1] = n->pointers[n->num_keys];
        for (i = n->num_keys; i > 0; i--) {
            n->keys[i] = n->keys[i - 1];
            n->pointers[i] = n->pointers[i - 1];
        }
        if (!n->is_leaf) {
            n->pointers[0] = neighbor->pointers[neighbor->num_keys];
            tmp = (node *)n->pointers[0];
            tmp->parent = n;
            neighbor->pointers[neighbor->num_keys] = NULL;
            n->keys[0] = k_prime;
            n->parent->keys[k_prime_index] = neighbor->keys[neighbor->num_keys - 1];
        }
        else {
            n->pointers[0] = neighbor->pointers[neighbor->num_keys - 1];
            neighbor->pointers[neighbor->num_keys - 1] = NULL;
            n->keys[0] = neighbor->keys[neighbor->num_keys - 1];
            n->parent->keys[k_prime_index] = n->keys[0];
        }
    }
 
    /* Case: n is the leftmost child.
     * Take a key-pointer pair from the neighbor to the right.
     * Move the neighbor's leftmost key-pointer pair
     * to n's rightmost position.
     */
 
    else {
        if (n->is_leaf) {
            n->keys[n->num_keys] = neighbor->keys[0];
            n->pointers[n->num_keys] = neighbor->pointers[0];
            n->parent->keys[k_prime_index] = neighbor->keys[1];
        }
        else {
            n->keys[n->num_keys] = k_prime;
            n->pointers[n->num_keys + 1] = neighbor->pointers[0];
            tmp = (node *)n->pointers[n->num_keys + 1];
            tmp->parent = n;
            n->parent->keys[k_prime_index] = neighbor->keys[0];
        }
        for (i = 0; i < neighbor->num_keys; i++) {
            neighbor->keys[i] = neighbor->keys[i + 1];
            neighbor->pointers[i] = neighbor->pointers[i + 1];
        }
        if (!n->is_leaf)
            neighbor->pointers[i] = neighbor->pointers[i + 1];
    }
 
    /* n now has one more key and one more pointer;
     * the neighbor has one fewer of each.
     */
 
    n->num_keys++;
    neighbor->num_keys--;
 
    return root;
}
 
 
// removes an entry from the B+ tree.
 node * del_entry( node * root, node * n, int key, void * pointer ) {
 
    int min_keys;
    node * neighbor;
    int neighbor_index;
    int k_prime_index, k_prime;
    int capacity;
 
    // Remove key and pointer from node.
 
    n = remove_entry_from_node(n, key, pointer);
 
    /* Case:  deletion from the root.
     */
 
    if (n == root)
        return adjust_root(root);
 
 
    // Case:  deletion from a node below the root.
    
    // Determine minimum allowable size of node, to be preserved after deletion.
 
 
    min_keys = n->is_leaf ? cut(order - 1) : cut(order) - 1;
 
    // Case:  node stays at or above minimum.
    
    if (n->num_keys >= min_keys)
        return root;
 
    /* Find the appropriate neighbor node with which
     * to merge.
     * Also find the key (k_prime) in the parent
     * between the pointer to node n and the pointer
     * to the neighbor.
     */
 
    neighbor_index = get_neighbor_index( n );
    k_prime_index = neighbor_index == -1 ? 0 : neighbor_index;
    k_prime = n->parent->keys[k_prime_index];
    neighbor = neighbor_index == -1 ? n->parent->pointers[1] :
        n->parent->pointers[neighbor_index];
 
    capacity = n->is_leaf ? order : order - 1;
 
    /* mergence. */
 
    if (neighbor->num_keys + n->num_keys < capacity)
        return merge_nodes(root, n, neighbor, neighbor_index, k_prime);
 
    /* Redistribution. */
 
    else
        return redistribute_nodes(root, n, neighbor, neighbor_index, k_prime_index, k_prime);
}
 
 
 
/* Master deletion function.
 */
node * del(node * root, int key) {
 
    node * key_leaf;
    record * key_record;
 
    key_record = find(root, key, false);
    key_leaf = find_leaf(root, key, false);
    if (key_record != NULL && key_leaf != NULL) {
        root = del_entry(root, key_leaf, key, key_record);
        free(key_record);
    }
    return root;
}
 
 
void destroy_tree_nodes(node * root) {
    int i;
    if (root->is_leaf)
        for (i = 0; i < root->num_keys; i++)
            free(root->pointers[i]);
    else
        for (i = 0; i < root->num_keys + 1; i++)
            destroy_tree_nodes(root->pointers[i]);
    free(root->pointers);
    free(root->keys);
    free(root);
}
 
 
node * destroy_tree(node * root) {
    destroy_tree_nodes(root);
    return NULL;
}
 
/* First message to the user.
 */
void message_1( void ) {
    printf("B+ Tree of Order %d.\n", order);
    printf("____________________________________\nTo start with input from a file\nof newline-delimited integers, \n");
    printf("enter as below while executing:\n"
            "\tbpt <order> <inputfile> .\n____________________________________\n");
}
 
 
/* Second message to the user.
 */
void message_2( void ) {
    printf("ENTER THE COMMAND :\n");
    printf("\ti <key>         =>  INSERT <key> (an integer) AS BOTH KEY & VALUE).\n");
    printf("\tf <key>         =>  DISPLAY THE VALUE OF THE KEY.\n");
    printf("\tr <key1> <key2> =>  PRINT THE KEYS IN THE ENTERED RANGE [<key1>,<key2>]\n");
    printf("\td <key>         =>  DELETE THE KEY & ITS ASSOCIATED VALUE.\n\n");
    printf("\tx => DELETE THE TREE.\n");
    printf("\tp => PRINT THE B+ TREE.\n");
    printf("\tl => PRINT THE KEYS OF LEAVES (bottom row of the tree).\n");
    printf("\tv => TOGGLE OUTPUT OF POINTER ADDRESS(\"verbose\")\n");
    printf("\tq => QUIT.\n");
    printf("\t? => DISPLAY THIS LIST OF COMMANDS.\n");
}
 
 
void message_3( void ) {
    printf("Message: ./bpt [<order>]\n");
    printf("\twhere %d <= order <= %d .\n", MIN_ORDER, MAX_ORDER);
}
 
 
/*int main( int argc, char ** argv ) {
 
    char * input_file;
    FILE * fp;
    node * root;
    int input, range2;
    char instruction;
    char license_part;
 
    root = NULL;
    verbose_output = false;
 
    if (argc > 1) {
        order = atoi(argv[1]);
        if (order < MIN_ORDER || order > MAX_ORDER) {
            fprintf(stderr, "Invalid order: %d .\n\n", order);
            message_3();
            exit(EXIT_FAILURE);
        }
    }
 
    
    message_1();  
    message_2();
 
    if (argc > 2) {
        input_file = argv[2];
        fp = fopen(input_file, "r");
        if (fp == NULL) {
            perror("Failure to open input file.");
            exit(EXIT_FAILURE);
        }
        while (!feof(fp)) {
            fscanf(fp, "%d\n", &input);
            int* inv = malloc(2 * sizeof(int));
            inv[0] = input + 1;
            inv[1] = input + 2;
            root = insert(root, input, inv);
        }
        fclose(fp);
        display(root);
    }
 
    printf("> ");
    while (scanf("%c", &instruction) != EOF) {
        switch (instruction) {
        case 'd':
            scanf("%d", &input);
            root = del(root, input);
            break;
        case 'i':
            scanf("%d", &input);
            int* inv = malloc(2 * sizeof(int));
            inv[0] = input + 1;
            inv[1] = input + 2;
            root = insert(root, input, inv);
            printf("Key %d inserted\n",input);
            break;
        case 'f':
            scanf("%d", &input);
            find_and_print(root, input, instruction == 'p');
            break;
        case 'r':   
            scanf("%d %d", &input, &range2);
            if (input > range2) {
                int tmp = range2;
                range2 = input;
                input = tmp;
            }
            find_and_print_range(root, input, range2, instruction == 'p');
            break;
        case 'l':
            print_leaves(root);
            break;
        case 'q':
            while (getchar() != (int)'\n');
            return EXIT_SUCCESS;
        case 'p':
            display(root);
            break;
        case 'v':
            verbose_output = !verbose_output;
            break;
        case 'x':
            if (root)
                root = destroy_tree(root);
            display(root);
            break;
        default:
            message_2();
            break;
        }
        while (getchar() != (int)'\n');
        printf("> ");
    }
    printf("\n");
 
    return EXIT_SUCCESS;
}*/