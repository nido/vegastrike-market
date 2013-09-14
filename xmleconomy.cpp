/*
 * Copyright(c) 2009: peter.schaefer@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * xmleconomy for saving an economy, v 0.0.6
 * @author peter.schaefer@gmail.com
 */

#define USE_SCEW 1

#include "xmleconomy.hpp"
#include <scew.h>

XMLEconomy::XMLEconomy():Economy(){
}

bool XMLEconomy::writeToFile(string filename){
    //clear the sold, buy and payback queues, so that these do no need to be saved
    executeTransactions();

    scew_tree* tree = NULL;
    scew_element* root = NULL;
    tree = scew_tree_create();

    /* Add the root of this object */
    root = scew_tree_add_root(tree, "economy");
    addElement(root);
    if (!scew_writer_tree_file(tree, filename.c_str()))
    {
        cerr << "Unable to create "<<filename<<endl;
        return false;
    }

     /* Frees the SCEW tree */
    scew_tree_free(tree);
	return true;
}

XMLEconomy *XMLEconomy::readFromFile(string filename){
    FILE * fp = fopen(filename.c_str(), "r"); // "r" for reading, "w" for writing

    scew_parser* parser = NULL;
    parser = scew_parser_create();

    scew_parser_ignore_whitespaces(parser, 1);

    if (!scew_parser_load_file_fp(parser, fp))
    {
     return NULL;
    }

    scew_tree* tree = NULL;
    tree = scew_parser_tree(parser);

    scew_element * root = scew_tree_root(tree);

	XMLEconomy *xe = xmleconomyFromElement(root);

    scew_tree_free(tree);
    scew_parser_free(parser);
    fclose(fp);

	return xe;
}

XMLEconomy *XMLEconomy::xmleconomyFromElement(scew_element* root){
    XMLEconomy *peconomy = new XMLEconomy();
    (void)economyFromElement(root, peconomy);
    return peconomy;
}


XMLEconomy::~XMLEconomy(){
}


