#include "AVLTreeIndex.h"


/*
 * Insert Element into the tree
 */
void AVLTreeIndex::insert(AVL_Node *root, Term* value)
{
    AVL_Node* temp = root;
    if (root == NULL){
        root = new AVL_Node(value, NULL, NULL);
        //return root;
    }

    else if (value < root->data){
        insert(root->left, value);
        balance (root);
    }

    else if (value >= root->data){
        insert(root->right, value);
        balance (root);
    }
    //return root;
}
/*
 * Balancing AVL Tree
 */
void AVLTreeIndex::balance(AVL_Node *temp){
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

int AVLTreeIndex::height(AVL_Node *temp){
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        temp->height = max_height + 1;
    }
    return temp->height;
}

/*
 * Height Difference
 */
int AVLTreeIndex::diff(AVL_Node *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

/*
 * Right- Right Rotation
 */
void AVLTreeIndex::rotateRightChild(AVL_Node *parent){
    AVL_Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    parent = temp;
}
/*
 * Left- Left Rotation
 */
void AVLTreeIndex::rotateLeftChild(AVL_Node *parent){
    AVL_Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    parent = temp;
}

/*
 * Left - Right Rotation
 */
void AVLTreeIndex::doubleLeftChild(AVL_Node *parent){
    rotateRightChild(parent->left);
    rotateLeftChild (parent);
}

/*
 * Right- Left Rotation
 */
void AVLTreeIndex::doubleRightChild(AVL_Node *parent){
    rotateLeftChild (parent->right);
    rotateRightChild (parent);
}

Term* AVLTreeIndex::find (AVL_Node* root, Term* value){
    AVL_Node* temp;
    string word = value->get_name();
    string word2 = root->data->get_name();
    if (word.substr(1,1).compare(word2.substr(1,1)) < 0){
        temp = root->left;
        find(temp, value);
    }else if(word.substr(1,1).compare(word2.substr(1,1)) > 0){
        temp = root->right;
        find(temp,value);
    }else if(word.compare(word2) == 0){
        return value;
    }
}



/*
 * Display AVL Tree
 */
void AVLTreeIndex::display(AVL_Node *ptr, int level)
{
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        cout<<ptr->data<< endl;
        display(ptr->left, level + 1);
    }
}
//void IndexInterface::addAppearance(int index, string term){
//    // If the new term is a stop word, forego adding it to the inverted index.
//    if (letters[0].is_stop_word(term)) return;

//    // The word is valid; stem it.
//    Porter2Stemmer::stem(term);

//    // Once stemmed, make new appearance at term.
//    letters[index].add_valid_appearance(term);
//}
