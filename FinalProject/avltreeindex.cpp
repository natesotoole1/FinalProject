#include "AVLTreeIndex.h"

AVLTreeIndex::AVLTreeIndex(){
    letter = "";
    root = NULL;

}

void AVLTreeIndex::insert(AVL_Node* t, Term* value)
{
    AVL_Node* temp = root;
    if (t == NULL){
        t = new AVL_Node(value, NULL, NULL);
        //return root;
    }

    else if (value < t->data){
        insert(t->left, value);
        balance(root);
    }

    else if (value >= root->data){
        insert(root->right, value);
        balance(root);
    }
    //return root;

}



// Balancing AVL Tree
void AVLTreeIndex::balance(AVL_Node* temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0){
            rotateLeftChild (temp);
        }else{
            doubleLeftChild (temp);
        }
    }
    else if (bal_factor < -1){
        if (diff (temp->right) > 0){
            doubleRightChild (temp);
        }else{
            rotateRightChild (temp);
        }
    }

}
// Height Difference

int AVLTreeIndex::diff(AVL_Node *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
int AVLTreeIndex::height(AVL_Node *temp){
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        temp->height = max_height + 1;
    }
    return temp->height;
}



// Right- Right Rotation
void AVLTreeIndex::rotateRightChild(AVL_Node *parent){
    AVL_Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    parent = temp;
}

// Left- Left Rotation
void AVLTreeIndex::rotateLeftChild(AVL_Node *parent){
    AVL_Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
}


// Left - Right Rotation

void AVLTreeIndex::doubleLeftChild(AVL_Node *parent){
    rotateRightChild(parent->left);
    rotateLeftChild (parent);
}

// Right- Left Rotation
void AVLTreeIndex::doubleRightChild(AVL_Node *parent){
    rotateLeftChild (parent->right);
    rotateRightChild (parent);
}

Term* AVLTreeIndex::find (AVL_Node* ptr, Term* value){
    AVL_Node* temp = ptr;
    string word = value->get_name();
    string word2 = root->data->get_name();
    Term* noWord = new Term("No Word", -1, -1);
    if (word.substr(1,1).compare(word2.substr(1,1)) < 0){
        temp = root->left;
        find(temp, value);
    }else if(word.substr(1,1).compare(word2.substr(1,1)) > 0){
        temp = root->right;
        find(temp,value);
    }else if(word.compare(word2) == 0){
        return value;
    }
    return noWord;
}





// Display AVL Tree
void AVLTreeIndex::display(AVL_Node *ptr, int level)
{
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        cout<<ptr->data<< endl;
        display(ptr->left, level + 1);
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

AVL_Node* AVLTreeIndex::getRoot(){
    return root;
}

string AVLTreeIndex::getLetter(){
    return letter;
}

void AVLTreeIndex::setLetter(string l){
    letter = l;
}



//void IndexInterface::addAppearance(int index, string term){
//    // If the new term is a stop word, forego adding it to the inverted index.
//    if (letters[0].is_stop_word(term)) return;

//    // The word is valid; stem it.
//    Porter2Stemmer::stem(term);

//    // Once stemmed, make new appearance at term.
//    letters[index].add_valid_appearance(term);
//}
