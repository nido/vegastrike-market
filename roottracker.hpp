#ifndef __ROOTTRACKER_HPP__
#define __ROOTTRACKER_HPP__

#include "node.hpp"

class RootTracker {

// all the node instances that belong to a given tree have a reference to one

// instance of RootTracker.  as the Node instance that is the root may change

// or the original root may be deleted, Node instances must access the root

// of the tree through this tracker, and update the root pointer when they

// perform insertions or deletions.  using a static attribute in the Node

// class to hold the root pointer would limit a program to just one B-tree.

protected:

    Node* mp_root;

public:

    RootTracker() { mp_root = null_ptr; }

    void set_root (Node* old_root, Node* new_root) {

        // ensure that the root is only being changed by a node belonging to the

        // same tree as the current root

        if (old_root != mp_root)

            throw "wrong old_root in RootTracker::set_root";

        else

            mp_root = new_root;

    }

    Node* get_root () const { return mp_root; }



    ~RootTracker () {

        // safety measure

        if (mp_root) {

            mp_root->delete_all_subtrees();

            delete mp_root;

        }

    }

}; //_______________________________________________________________________

#endif
