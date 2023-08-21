// References: Stepik 5.2 Editorial Solution, Project 1 Breakdown Slides, In class PPT module 3-4
// Created by Pablo on 9/27/2022.
//

#ifndef PROJECT1_TREE_H
#define PROJECT1_TREE_H

#include <vector>

struct TreeNode {
    std::string name;
    std::string ID;
    TreeNode *left;
    TreeNode *right;
    int height;

    TreeNode(std::string name, std::string ID){
        this->name = name;
        this->ID = ID;
        height = 1;
        left = nullptr;
        right = nullptr;
    }

};

class AVLTree {
public:
   AVLTree(){
       root = nullptr;
   }
   AVLTree(TreeNode *root){
       this->root = root;
   }

   TreeNode* insert(std::string name, std::string ID);

   void printInorder();
   void printPreorder();
   void printPostorder();
   void printLevelCount();

   void searchID(std::string ID);
   void searchName(std::string NAME);

   TreeNode* remove(std::string ID);
   TreeNode* removeInOrder(int N);

   void destruct(TreeNode* root);

private:
    TreeNode *root;

    TreeNode* getRoot();

    TreeNode* insertHelp(TreeNode* root,std::string name, std::string ID, bool& found);
    int getHeight(TreeNode *root);
    int balanceFactor(TreeNode *root);
    TreeNode* rotateLeft(TreeNode* root);
    TreeNode* rotateRight(TreeNode* root);
    TreeNode* rotateLeftRight(TreeNode* root);
    TreeNode* rotateRightLeft(TreeNode* root);

    void printInorderHelp(TreeNode* root, std::vector<std::string>& list);
    void printPreorderHelp(TreeNode* root, std::vector<std::string>& list);
    void printPostorderHelp(TreeNode* root, std::vector<std::string>& list);
    void printLevelCountHelp(TreeNode* root);
    void searchHelpID(TreeNode* root,std::string ID, bool& found);
    void searchHelpName(TreeNode* root, std::string NAME, bool& found);

    TreeNode* removeHelp(TreeNode* root,std::string ID, bool& found);
    TreeNode* inOrderSuccessor(TreeNode* root);

    TreeNode* removeInOrderHelp(TreeNode* root, int N, int& count, bool& found);
};

TreeNode* AVLTree::getRoot() {
    return root;
}

TreeNode* AVLTree::insert(std::string name, std::string ID) {
    bool found;

    TreeNode* insert = insertHelp(getRoot(),name,ID, found);

    if (!found){
        std::cout << "unsuccessful" << std::endl;
    }
    else std::cout << "successful" << std::endl;

    return insert;

}

TreeNode* AVLTree::insertHelp(TreeNode* root,std::string name, std::string ID, bool& found) {
    if (root == nullptr){
        found = true;
        return new TreeNode(name, ID);
    }
    if (ID < root->ID){
        root->left = insertHelp(root->left, name, ID, found);
    }
    else if (ID > root->ID) {
        root->right = insertHelp(root->right, name, ID, found);
    }
    else {
        return root;
    }
    // basic Insert from BST lecture *needs to be balanced*
    // make sure the ID is unique

    if (getHeight(root->left) > getHeight(root->right)){
        root->height = getHeight(root->left) + 1;
    }
    else{
        root->height = getHeight(root->right) + 1;
    }
    // updates height

    int balFact = balanceFactor(root);

    // gets the balance number to determine which rotation to use

    if (balFact > 1){
        if (ID < root->left->ID){
            return rotateRight(root);
        }
        else if (ID > root->left->ID){
            return rotateLeftRight(root);
        }
    }

    if (balFact < -1){
        if(ID > root->right->ID){
            return rotateLeft(root);
        }
        else if(ID < root->right->ID){
            return rotateRightLeft(root);
        }
    }

    return root;
}

int AVLTree::balanceFactor(TreeNode *root) {
    if (root == nullptr){
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
    // calculates the balance factor of the current node by looking at the heights of the child node

}

TreeNode* AVLTree::rotateLeft(TreeNode *root) {
    // Right Right Case Based on Stepik 5.2
    TreeNode* rightChild = root->right;
    root->right = rightChild->left;
    rightChild->left = root;

    if(getHeight(root->left) > getHeight(root->right)){
        root->height = getHeight(root->left) + 1;
    }
    else {
        root->height = getHeight(root->right) + 1;
    }

    if (getHeight(rightChild->left) > getHeight(rightChild->right)){
        rightChild->height = getHeight(rightChild->left) + 1;
    }
    else {
        rightChild->height = getHeight(rightChild->right) + 1;
    }

    return rightChild;
}

TreeNode* AVLTree::rotateRight(TreeNode *root) {
    // Left Left Case Based on Stepik 5.2
    TreeNode* leftChild = root->left;
    root->left = leftChild->right;
    leftChild->right = root;

    if(getHeight(root->left) > getHeight(root->right)){
        root->height = getHeight(root->left) + 1;
    }
    else {
        root->height = getHeight(root->right) + 1;
    }

    if (getHeight(leftChild->left) > getHeight(leftChild->right)){
        leftChild->height = getHeight(leftChild->left) + 1;
    }
    else {
        leftChild->height = getHeight(leftChild->right) + 1;
    }

    return leftChild;
}

TreeNode* AVLTree::rotateLeftRight(TreeNode *root) {
    // Left Right case Based on Stepik 5.2
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}

TreeNode* AVLTree::rotateRightLeft(TreeNode *root) {
    // Right Left case Based on Stepik 5.2
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}

void AVLTree::printInorder() {
    std::vector<std::string> print;
    printInorderHelp(getRoot(),print);

    for (int i = 0; i < print.size(); ++i) {
        std::cout << print[i];
        if (i < print.size()-1){
            std::cout << ", ";
        }
    }
}

void AVLTree::printInorderHelp(TreeNode *root, std::vector<std::string>& list){
    if(root == nullptr){
        return;
    }
    printInorderHelp(root->left, list);

    list.push_back(root->name);

    printInorderHelp(root->right, list);

    // print list of names using inorder traversal based on code from Stepik 5.2
}

void AVLTree::printPreorder(){
    std::vector<std::string> print;
    printPreorderHelp(getRoot(),print);

    for (int i = 0; i < print.size(); ++i) {
        std::cout << print[i];
        if (i < print.size()-1){
            std::cout << ", ";
        }
    }
}

void AVLTree::printPreorderHelp(TreeNode *root, std::vector<std::string>& list){
    if(root == nullptr){
        return;
    }
    list.push_back(root->name);

    printPreorderHelp(root->left, list);

    printPreorderHelp(root->right, list);

    // print list of names using preorder traversal adapted from code from Stepik 5.2
}

void AVLTree::printPostorder(){
    std::vector<std::string> print;
    printPostorderHelp(getRoot(), print);

    for (int i = 0; i < print.size(); ++i) {
        std::cout << print[i];
        if (i < print.size()-1){
            std::cout << ", ";
        }
    }
}

void AVLTree::printPostorderHelp(TreeNode *root, std::vector<std::string>& list) {
    if(root == nullptr){
        return;
    }
    printPostorderHelp(root->left, list);

    printPostorderHelp(root->right, list);

    list.push_back(root->name);

    // print list of names using postorder traversal adapted from code from Stepik 5.2
}

int AVLTree::getHeight(TreeNode *root) {
    if(root == nullptr){
        return 0;
    }
    return root->height;
    // helper method used to prevent accessing null memory
}

void AVLTree::printLevelCount() {
    printLevelCountHelp(getRoot());
}

void AVLTree::printLevelCountHelp(TreeNode *root) {
    if(root == nullptr){
        std::cout << "0" << std::endl;
        return;
    }
    std::cout << root->height << std::endl;
    // returns the height of the root node which corresponds to the level count of the tree 0 based.
}

void AVLTree::searchID(std::string ID) {
    bool found;
    searchHelpID(getRoot(),ID, found);
    if (!found){
        std::cout << "unsuccessful" << std::endl;
    }

}
 void AVLTree::searchHelpID(TreeNode *root, std::string ID, bool& found) {
    if(root == nullptr){
        return;
    }
    if (root->ID == ID){
        found = true;
        std::cout << root->name << std::endl;
        return;
    }

    searchHelpID(root->left, ID,found);

    searchHelpID(root->right, ID,found);

    return;
    // uses preorder traversal to search prints when ID is found

}

void AVLTree::searchName(std::string NAME) {
    bool found;
    searchHelpName(getRoot(),NAME, found);
    if (!found){
        std::cout << "unsuccessful" << std::endl;
    }

}

void AVLTree::searchHelpName(TreeNode* root, std::string NAME, bool& found){

    if(root == nullptr){
        return;
    }
    if (root->name == NAME){
        std::cout << root->ID << std::endl;
        found = true;
    }

    searchHelpName(root->left, NAME, found);

    searchHelpName(root->right, NAME, found);

    // inorder traversal of the tree printing each instance of the given name
}

TreeNode* AVLTree::remove(std::string ID) {
    bool found = false;

    TreeNode* remove = removeHelp(getRoot(),ID, found);

    if (!found){
        std::cout << "unsuccessful" << std::endl;
    }
    else std::cout << "successful" << std::endl;

    return remove;
}

TreeNode* AVLTree::removeHelp(TreeNode *root, std::string ID, bool& found) {
    // based on the logic given in the project 1 ppt

    if (root == nullptr){
        return root;
    }
    if (ID < root->ID){
        root->left = removeHelp(root->left,ID, found);
    }
    else if (ID > root->ID){
        root->right = removeHelp(root->right,ID, found);
    }
    // looks for the node through the tree when found goes into else
    else{

        if(root->left == nullptr && root->right == nullptr){
            found = true;
            return nullptr;
        }
        // node has no children case 1

        else if (root->left == nullptr){
            found = true;
            struct TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == nullptr){
            found = true;
            struct TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // root has only one child case 2

        TreeNode* temp = inOrderSuccessor(root->right);
        // inorder replacement uses logic from ppt and gfg

        root->ID = temp->ID;
        root->name = temp->name;
        root->height = temp->height-1;

        root->right = removeHelp(root->right,temp->ID, found);

        // case 3 where 2 children find inorder successor and replace the current node with it then removes current

    }
    return root;
}

TreeNode *AVLTree::inOrderSuccessor(TreeNode *root) {
    if (root == nullptr){
        return root;
    }
    if (root->left == nullptr){
        return root;
    }
    return inOrderSuccessor(root->left);

    // takes in the right root and then goes all the way down to find inorder successor
}

TreeNode *AVLTree::removeInOrder(int N) {
    int count = 0;
    bool found;
    TreeNode* removeInOrder = removeInOrderHelp(getRoot(),N, count, found);

    if (!found){
        std::cout << "unsuccessful" << std::endl;
    }

    return removeInOrder;
}

TreeNode *AVLTree::removeInOrderHelp(TreeNode *root, int N, int& count, bool& found) {

    if(root == nullptr){
        return root;
    }

    if (count <= N){

        removeInOrderHelp(root->left,N, count, found);


        if (count == N){
            count = 0;

            found = true;

            return remove(root->ID);
            // prints successful from remove
        }
        count++;

        removeInOrderHelp(root->right,N, count, found);

    }

    // goes through tree using inorder traversal starts counting all the way to the left the first node accessed
    // uses the static counter to find out which node and then calls the remove function.

    return root;
}

void AVLTree::destruct(TreeNode *root) {
    if (root->left)
        destruct(root->left);
    if (root->right)
        destruct(root->right);
    delete root;
    // used the code from the sumOfLevelQuiz
}

#endif //PROJECT1_TREE_H
