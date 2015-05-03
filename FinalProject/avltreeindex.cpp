#include "AVLTreeIndex.h"

AVLTreeIndex::AVLTreeIndex(){
    root = NULL;
    
}

void AVLTreeIndex::insert(Term* value){
    insert(root, value);
}

void AVLTreeIndex::insert(AVL_Node*& root, Term* value)
{
    if (root == NULL){
        root = new AVL_Node;
        root->left = NULL;
        root->right = NULL;
        root->data = value;
        return;
    }
    else if (value->get_name() < root->data->get_name()){
        insert(root->left, value);
        root = balance(root);
    }
    
    else if (value->get_name() > root->data->get_name()){
        insert(root->right, value);
        root = balance(root);
    }
    else if(value->get_name() == root->data->get_name() == 0 ){
        return;
    }
    //return root;
    
}



// Balancing AVL Tree
AVL_Node* AVLTreeIndex::balance(AVL_Node*& temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0){
            temp = rotateLeftChild (temp);
        }else{
            temp = doubleLeftChild (temp);
        }
    }
    else if (bal_factor < -1){
        if (diff (temp->right) > 0){
            temp = doubleRightChild (temp);
        }else{
            temp = rotateRightChild (temp);
        }
    }
    return temp;
    
}
// Height Difference

int AVLTreeIndex::diff(AVL_Node*& temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
int AVLTreeIndex::height(AVL_Node*& temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
int AVLTreeIndex::max(int value1, int value2){
    return ((value1 > value2) ? value1:value2);
}


// Right- Right Rotation
AVL_Node* AVLTreeIndex::rotateRightChild(AVL_Node*& parent){
    AVL_Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// Left- Left Rotation
AVL_Node* AVLTreeIndex::rotateLeftChild(AVL_Node *& parent){
    AVL_Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}


// Left - Right Rotation

AVL_Node* AVLTreeIndex::doubleLeftChild(AVL_Node *&parent){
    parent->left = rotateRightChild(parent->left);
    return rotateLeftChild (parent);
}

// Right- Left Rotation
AVL_Node* AVLTreeIndex::doubleRightChild(AVL_Node *&parent){
    parent->right = rotateLeftChild (parent->right);
    return rotateRightChild (parent);
}
Term* AVLTreeIndex::find (string w){
    
}

Term* AVLTreeIndex::find (AVL_Node*& ptr, string word){
    AVL_Node* temp = ptr;
    string word2 = root->data->get_name();
    //Term* noWord = new Term("No Word", -1, -1);
    if (word.substr(1,1).compare(word2.substr(1,1)) < 0){
        temp = root->left;
        find(temp, word);
    }else if(word.substr(1,1).compare(word2.substr(1,1)) > 0){
        temp = root->right;
        find(temp, word);
    }else if(word.compare(word2) == 0){
        return temp->data;
    }
    //return noWord;
}



void AVLTreeIndex::display(int level, ofstream &persistence)
{
    display(root, level, persistence);
}

// Display AVL Tree
void AVLTreeIndex::display(AVL_Node*& ptr, int level, ofstream &persistence)
{
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1, persistence);
        ptr->data->write_term(persistence);
        display(ptr->left, level + 1, persistence);
    }
}

void AVLTreeIndex::clearTree(AVL_Node* r){
    if (r != NULL){
        clearTree(r->left);
        clearTree(r->right);
        delete r;
    }
    r = NULL;
}



//void IndexInterface::addAppearance(int index, string term){
//    // If the new term is a stop word, forego adding it to the inverted index.
//    if (letters[0].is_stop_word(term)) return;

//    // The word is valid; stem it.
//    Porter2Stemmer::stem(term);

//    // Once stemmed, make new appearance at term.
//    letters[index].add_valid_appearance(term);
//}
