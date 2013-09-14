 /*
 * Iterator for the toucan's btree
 * @author peter.schaefer@gmail.com
 */
#ifndef __BTREE_ITERATOR_HPP__
#define __BTREE_ITERATOR_HPP__


#include "element.hpp"

#include "node.hpp"

class BTree_Iterator {
public:
	BTree_Iterator(Node *mp_root,bool forward);
	Elem *next();
	Elem *prev();
	Elem *current();
	void dump();
private:
    	vector<int> i_vector;
	Node *mp_root;
	Node *mp_here;
}; //_______________________________________________________________________

#endif
