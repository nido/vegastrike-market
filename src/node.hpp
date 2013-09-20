#ifndef H_NODE
#define H_NODE
/*

The base version of the btree by Toucan may be freely copied.

btree base version:  may 9th, 2003, by toucan@textelectric.net

*/

#include "element.hpp"

//An element contains: +-price,+-time,<+-amount,bidderid>
typedef pair<int,string> Value;
typedef Element<double,long,Value> Elem;

class RootTracker;

extern Node* invalid_ptr;

extern Node* null_ptr;

const int invalid_index = -1;

const int max_elements = 200;  // max elements in a node

// size limit for the array in a vector object.  best performance was

// at 800 bytes.

const unsigned int max_array_bytes = 800;


class Node {

friend class BTree_Iterator;

protected:

    // locality of reference, beneficial to effective cache utilization,

    // is provided by a "vector" container rather than a "list"

    vector<Elem> m_vector;

    // number of elements currently in m_vector, including the zeroth element

    // which has only a subtree, no key value or payload.

    int m_count;

    Node* mp_parent;

    bool is_leaf();

    bool vector_insert (Elem& element);

    bool vector_insert_for_split (Elem& element);

    bool split_insert (Elem& element);

    bool vector_delete (Elem& target);

    bool vector_delete (int target_pos);

    void insert_zeroth_subtree (Node* subtree);

    void set_debug();

    int key_count () { return m_count-1; }

    Elem& largest_key () { return m_vector[m_count-1]; }

    Elem& smallest_key () { return m_vector[1]; }

    int index_has_subtree ();

    Node* right_sibling (int& parent_index_this);

    Node* left_sibling (int& parent_index_this);

    Node* rotate_from_left(int parent_index_this);

    Node* rotate_from_right(int parent_index_this);

    Node* merge_right (int parent_index_this);

    Node* merge_left (int parent_index_this);

    bool merge_into_root ();

    int minimum_keys ();

#ifdef _DEBUG

    Elem debug[8];

#endif

    Elem& smallest_key_in_subtree();

    Elem& largest_key_in_subtree();

public:

    Elem& search (Elem& desired, Node*& last_visited);

    bool tree_insert (Elem& element);

    bool delete_element (Elem& target);

    int delete_all_subtrees ();

    Node* find_root();

    // to return a reference when a search fails.

    static Elem m_failure;

    // to initialize special values

    static Value null_value;

    // the root of the tree may change.  this attribute keeps it accessible.

    RootTracker& m_root;

    Elem& operator[] (int i) { return m_vector[i]; }

    // node cannot be instantiated without a root tracker

    Node (RootTracker& root_track);

    void dump ();

}; //______________________________________________________________________

#endif //H_NODE
