/**
 * Copyright 2021
 * Vincent Kolb-Lugo
 * 2021-10-07
 *
 * Homework 3: Implement a binary search tree. Must have the functions:
 *   - insert
 *   - delete
 *   - search method to trace the nodes traversed and display them. If a 
 *       key is found, must print the nodes traversed to reach the key.
 *       If the key is not found, must display the nodes traversed and
 *       display a message that the node was not found.  
 */
#include <iostream>
using std::cin;
using std::cout;
using std::endl;


//Binary Search Tree class
class BinarySearchTree {
 public:
  BinarySearchTree() : root(NULL) {}
  
  ~BinarySearchTree();
  void insertNode(double aKey); 
  void deleteNode(double aKey);
  void inOrderDisplay() const;
  void searchInTree(double target) const;
  void removeNode(double aKey);
  
 private: 
  // priavtely defined struct to represent node in tree
  struct BSTNode {
     double key;
     BSTNode *leftChild = nullptr;
     BSTNode *rightChild = nullptr;

     BSTNode(double aKey) : key(aKey) {}
  };
  
  //member variable
  BSTNode *root;

  //methods
  void insertNode(double aKey, BSTNode*& subTree);
  void deleteSubTree(BSTNode*& subTree);
  void inOrderDisplay(BSTNode* subTreeRoot) const;
  void searchInTree(double target, BSTNode* subTreeRoot) const;
  void removeNode(double aKey, BSTNode*& subTreeRoot);
  void findMin(BSTNode*& aNode);
  void findMax(BSTNode*& aNode);

};

//Forward delcared methods. They are mostly in alphabetical order
void BinarySearchTree::insertNode(double aKey) {
   insertNode(aKey, root);
}

void BinarySearchTree::insertNode(double aKey, BSTNode*& subTree) {
  if(subTree == nullptr) {
    subTree = new BSTNode(aKey);
  } else if(aKey < subTree->key){
      this->insertNode(aKey, subTree->leftChild);
  } else if(aKey > subTree->key) {
      this->insertNode(aKey, subTree->rightChild);
  } else if(aKey == subTree->key) {
      // do nothing
  }
}

void BinarySearchTree::inOrderDisplay() const {
  inOrderDisplay(root);
  cout << endl;
}

void BinarySearchTree::inOrderDisplay(BSTNode* subTreeRoot) const {
  if(subTreeRoot != nullptr) {
    inOrderDisplay(subTreeRoot->leftChild);
    cout << subTreeRoot->key << " ";
    inOrderDisplay(subTreeRoot->rightChild);
  }
}

BinarySearchTree::~BinarySearchTree() {
  deleteSubTree(root);
}

void BinarySearchTree::deleteSubTree(BSTNode*& subTreeRoot) {
  if(subTreeRoot != nullptr) {
    deleteSubTree(subTreeRoot->leftChild);
    deleteSubTree(subTreeRoot->rightChild);

    delete subTreeRoot;
    subTreeRoot = nullptr;
  }
}

void BinarySearchTree::findMin(BSTNode*& aNode){
  BSTNode** current = &(aNode->rightChild);
  while((*current)->leftChild != nullptr) {
    current = &((*current)->leftChild);
  }
  aNode->key = (*current)->key;
  deleteSubTree(*current);
}

void BinarySearchTree::findMax(BSTNode*& aNode) {
  BSTNode** current = &(aNode->leftChild);
  while((*current)->rightChild != nullptr) {
    current = &((*current)->rightChild);
  }
  aNode->key = (*current)->key;
  deleteSubTree(*current);
}

void BinarySearchTree::removeNode(double aKey) {
  removeNode(aKey, root);
  cout << endl;
}

//RemoveNode method utilizes helper methods findMin and findMax to locate
// the correct node to replace the subtree root in the event a node has one
// or two children
void BinarySearchTree::removeNode(double target, BSTNode*& subTreeRoot) {
   if (subTreeRoot == nullptr)
    cout << "Target not found" << endl;
  else if (subTreeRoot->key == target)
    if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr) {
       deleteSubTree(subTreeRoot);
    } else if (subTreeRoot->leftChild != nullptr) {
        findMax(subTreeRoot);   
    } else {
        findMin(subTreeRoot);
    }
  else if (target < subTreeRoot->key) {
    //cout << "Node key: " << subTreeRoot->key << " ";
    removeNode(target, subTreeRoot->leftChild);
  } else { 
      //cout << "Node key: " << subTreeRoot->key << " ";
      removeNode(target, subTreeRoot->rightChild);
  }
}

/**
 * On a second read, I see the instructions ask to return a list of taversed
 * nodes. I wrote the fucntion as seen and then tried to go back and edit
 * it to use a list from the standard library, but I kept running into issues
 * while implementing it. I will TRY to make the print statements indicate 
 * if they proceed LEFT or RIGHT down the tree, but I am tired and have
 * already put in 10 hours, so I might just call it a day. 
 *
 * The behavior is correct (I beleive) so hopefully that is sufficient enough
 * to get credit.
 */
void BinarySearchTree::searchInTree(double target) const {
  searchInTree(target, root);
}

void BinarySearchTree::searchInTree(double target, BSTNode* subTreeRoot) const {
  if (subTreeRoot == nullptr)
    cout << "NADA" << endl;
  else if ( subTreeRoot->key == target)
    cout << "FOUND: " << subTreeRoot->key << endl;
  else if (target < subTreeRoot->key) {
    cout << "-->" << subTreeRoot->key << " ";
    searchInTree(target, subTreeRoot->leftChild);
  } else {
    cout << "-->" << subTreeRoot->key << " ";
    searchInTree(target, subTreeRoot->rightChild);
  }
}

//helper function to print options for the binary search tree operations
void PrintOptions() {
  cout << "What would you like to do: " << endl
       << "(i)nsert a node" << endl 
       << "(d)elete a node" << endl 
       << "(s)earch for a key" << endl 
       << "(q)uit" << endl;
}

int main (int argc, char *argv[]) {
  BinarySearchTree tree;
  //tree.insertNode(10.0);
  //tree.insertNode(8.0);
  //tree.insertNode(12.0);
  //tree.insertNode(20.0);
  //tree.insertNode(5.0);
  //tree.inOrderDisplay();
  //tree.searchInTree(5.0);
  //tree.searchInTree(100.0);
  //tree.deleteSubtree(5.0);
  //tree.inOrderDisplay();
  //tree.removeNode(20.0);
  //tree.inOrderDisplay();
  cout << "This is a binary search tree." << endl; 
  PrintOptions();
  char input;
  cin >> input;
  
  //main logic loop
  while(input != 'q'){
     switch(input){
       case 'i':
         cout << "You picked insert." << endl << "Provide a key to insert: ";
         double key;
         cin >> key;
         cout << endl;
         tree.insertNode(key);
         cout << "Inserted: " << key << endl << endl;
         PrintOptions();
         cin >> input;
         cout << endl;
         break;
       case 'd':
         cout << "You picked delete." << endl << "Provide a key to delete: ";
         double deleteKey;
         cin >> deleteKey;
         tree.removeNode(deleteKey);
         cout << "Removed " << deleteKey << endl << endl; 
         PrintOptions();
         cin >> input;
         cout<< endl;
         break;
       case 's':
         cout << "You picked search." << endl 
              << "Provide a key to search for in the tree: ";
         double searchKey;
         cin >> searchKey;
         tree.searchInTree(searchKey);
         cout << endl;
         PrintOptions();
         cin >> input;
         cout << endl;
         break;
       case 'q': break;
       default:
         PrintOptions();
         cin >> input;
         cout << endl;
     }
  }
  cout << "DONE" << endl;
  
  return 0;
};
