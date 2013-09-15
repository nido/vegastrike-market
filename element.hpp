/*

The base version of the btree by Toucan may be freely copied.

btree base version:  may 9th, 2003, by toucan@textelectric.net


These files contain a class template for elements stored in a B-tree, and a

class for a B-tree node, which provides all the methods needed to search,

insert, or delete.  A sample "main" function is also provided to show

how to use the B-tree.

To understand the identifiers and comments, visualize the tree as having

its root node at the top of the diagram, its leaf nodes at the bottom of

the diagram, and each node as containing an array oriented horizontally,

with the smallest element on the left and the largest element on the right.

the zeroth element of a node contains only a subtree pointer, no key value

or payload.



a b-tree grows "upward", by splitting the root node when the node's capacity

is exceeded.  conversely, the depth of the tree is always reduced by merging

the last remaining element of the root node with the elements of its two

child nodes, so the tree contracts "from the top".

programmer: toucan@textelectric.net

algorithm and pseudo-code found in:

"fundamentals of data structures in pascal", by Horowitz and Sahni



there is a java applet on the web that draws a b-tree diagram and allows the

user to perform insertions and deletions, so you can see how it grows and shrinks,

at: http://www.mars.dti.ne.jp/~torao/program/structure/btree.html

*/

#ifndef __ELEMENT_HPP__
#define __ELEMENT_HPP__


//#include "stdafx.h"

#include <iostream>

#include <string>

#include <vector>

#include <utility>

#include <limits.h>

using namespace std;

class Node;

extern Node* invalid_ptr;

extern Node* null_ptr;


template<class key, class secondkey, class payload> class Element {

// contains a key value, a payload, and a pointer toward the subtree

// containing key values greater than this->m_key but lower than the

// key value of the next element to the right



public:

    key m_key;

    secondkey m_secondkey;

    payload m_payload;

    Node* mp_subtree;

public:

    bool operator>   (Element& other) const { return m_key >  other.m_key || m_key == other.m_key && m_secondkey > other.m_secondkey; }

    bool operator<   (Element& other) const { return m_key <  other.m_key || m_key == other.m_key && m_secondkey < other.m_secondkey; }

    bool operator==  (Element& other) const { return m_key == other.m_key && m_secondkey == other.m_secondkey; }

    bool operator>=  (Element& other) const { return !(m_key <  other.m_key || m_key == other.m_key && m_secondkey < other.m_secondkey); }

    bool operator<=  (Element& other) const { return !(m_key >  other.m_key || m_key == other.m_key && m_secondkey > other.m_secondkey); }

    bool valid () const { return mp_subtree != invalid_ptr; }

    void invalidate () { mp_subtree = invalid_ptr; }

    Element& operator= (const Element& other) {

        m_key = other.m_key;

	m_secondkey = other.m_secondkey;

        m_payload = other.m_payload;

        mp_subtree = other.mp_subtree;

        return *this;

    }

    Element () { mp_subtree = null_ptr; }

    void dump ();

}; //______________________________________________________________________



template<class key, class secondkey, class payload> void Element<key, secondkey, payload>::dump () {

    cerr << "key=" << m_key << "second key=" << m_secondkey << "sub=" << mp_subtree << ' ' << endl;

}; //_______________________________________________________________________


#endif
