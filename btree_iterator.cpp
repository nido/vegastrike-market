/*
This is free software.
License: GNU GPL 2 or later.
Copyright 2009: peter.schaefer@gmail.com

Iterator for the toucan's btree
Current version: 16th of january 2009 by peter.schaefer@gmail.com

*/
#include "btree_iterator.hpp"

BTree_Iterator::BTree_Iterator(Node *_mp_root,bool forward = true){
	mp_root= _mp_root;
	mp_here = _mp_root;
	if(forward) {
	    	while (!mp_here->is_leaf()){
		        i_vector.push_back(0);
        	 	mp_here= mp_here->m_vector[0].mp_subtree;
		}

		if(mp_here->m_count>0){
	        	i_vector.push_back(1-1);
	 	}
	}else{
	    	while (!mp_here->is_leaf()){
		        i_vector.push_back(mp_here->m_count-1);
        	 	mp_here= mp_here->m_vector[mp_here->m_count-1].mp_subtree;
		}

		if(mp_here->m_count>0){
	        	i_vector.push_back(mp_here->m_count-1+1);
	 	}
	}
} //_______________________________________________________________________

Elem *BTree_Iterator::next(){
	if(i_vector.size() == 0){
		return NULL;
	}
	if( NULL == mp_here ){
		return NULL;
	}
	int m_pos;
        m_pos = i_vector[i_vector.size()-1];
	if(!(m_pos>=mp_here->m_count)){
	    	while(!mp_here->is_leaf()){

	       	 	mp_here= mp_here->m_vector[m_pos].mp_subtree;
	       	 	m_pos = 0;

		        i_vector.push_back(m_pos);
			if( NULL == mp_here ){
				return NULL;
			}
		}
	}
	Elem *pelem;
	m_pos += 1;
	while(m_pos>=mp_here->m_count){
		mp_here= mp_here->mp_parent;
		if( NULL == mp_here ){
			return NULL;
		}
		i_vector.pop_back();
		m_pos = i_vector[i_vector.size()-1];
		m_pos += 1;
	}
        i_vector[i_vector.size()-1] = m_pos;
	pelem = &mp_here->m_vector[m_pos];
	return pelem;
} //_______________________________________________________________________

Elem* BTree_Iterator::prev(){
	if(i_vector.size() == 0){
		return NULL;
	}
	if( NULL == mp_here ){
		return NULL;
	}
	int m_pos;
        m_pos = i_vector[i_vector.size()-1];
        m_pos -= 1;

        if(!(m_pos<0)){
	        i_vector[i_vector.size()-1] = m_pos;
	    	while (!mp_here->is_leaf()){

	       	 	mp_here= mp_here->m_vector[m_pos].mp_subtree;
	       	 	m_pos = mp_here->m_count-1;
		        i_vector.push_back(m_pos);
			if( NULL == mp_here ){
				return NULL;
			}
		}
	}
	Elem *pelem;
	while(m_pos<=0){
		mp_here= mp_here->mp_parent;
		if( NULL == mp_here ){
			return NULL;
		}
		i_vector.pop_back();
		m_pos = i_vector[i_vector.size()-1];
	}
        i_vector[i_vector.size()-1] = m_pos;
	pelem = &mp_here->m_vector[m_pos];
	return pelem;
} //_______________________________________________________________________

Elem *BTree_Iterator::current(){
	if( NULL == mp_here ){
		return NULL;
	}
	return &mp_here->m_vector[i_vector[i_vector.size()-1]];
} //_______________________________________________________________________

void BTree_Iterator::dump(){
	cerr << "current path:";
	for(int i=0; i< static_cast<int>(i_vector.size());++i){
		cerr << i_vector[i] << " ";
	}
	cerr << endl;
} //_______________________________________________________________________
