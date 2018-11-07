#include <iostream>
#include <algorithm>
#include <vector>

template <class T> class AVLTree;
template <class T>
class AVLNode {
  AVLNode* left;
  AVLNode* right;
  
  const T value;
  int count; // AVLNodes in this subtree
  int height;
  
  AVLNode(const T& value);
  void updateValues();
  int balanceFactor() const;
  
  AVLNode* rotateLeft();
  AVLNode* rotateRight();

  friend class AVLTree<T>;
};

// NOT AVL YET
template <class T>
class AVLTree {
  int _size;
  AVLNode<T>* root;
  
  void balance(std::vector<AVLNode<T>**> path);
  void print(AVLNode<T>* cur, std::ostream& outputStream = std::cout,
             int depth=0, int state=0);
    
public:
  AVLTree();
  ~AVLTree();
  
  void insert(const T& value);
  void erase(const T& value);
  
  void clear();
  bool empty() const;
  int size() const;
  
  void print(std::ostream& outputStream = std::cout);

  bool contains(const T& value) const;
};


int main() {
  srand(42);
  AVLTree<int> tree;
  int size = 10;
  for (int i=0; i < size; i++){
    int x = rand() % 5981;
    tree.insert(x);
  }

  tree.print();

  tree.clear();
  return 0;
}


template <class T>
AVLNode<T>::AVLNode(const T& value): value(value){
  count = 1;
  height = 1;
    
  left = nullptr;
  right = nullptr;
}

template <class T>
void AVLNode<T>::updateValues(){
  count = (left != nullptr ? left->count : 0) +
          (right != nullptr ? right->count : 0) + 1;
    
  height = std::max(left != nullptr ? left->height : 0,
                    right != nullptr ? right->height : 0) + 1;
}

template <class T>
int AVLNode<T>::balanceFactor() const{
  return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height: 0);
}

template <class T>
AVLNode<T>* AVLNode<T>::rotateLeft(){
  // ...
  return this;
}

template <class T>
AVLNode<T>* AVLNode<T>::rotateRight(){
  // ...
  return this;
}


template <class T>
AVLTree<T>::AVLTree(){
  root = nullptr;
  _size = 0;
}

template <class T>
AVLTree<T>::~AVLTree(){
  clear();
}

template <class T>
void AVLTree<T>::clear(){
  std::vector<AVLNode<T>*> stack;
  
  if (root != nullptr)
    stack.push_back(root);
  
  while (!stack.empty()){
    AVLNode<T>* AVLNode = stack.back();
    stack.pop_back();
    
    if (AVLNode->left != nullptr)
      stack.push_back(AVLNode->left);
    
    if (AVLNode->right != nullptr)
      stack.push_back(AVLNode->right);
    
    _size--;
    delete AVLNode;
  }
  
  root = nullptr;
}


template <class T>
void AVLTree<T>::insert(const T& value){
  AVLNode<T>** indirect = &root; // to generalize insertion
  std::vector<AVLNode<T>**> path; // to update height values
  
  while (*indirect != nullptr){
    path.push_back(indirect);
    if ((*indirect)->value > value)
      indirect = &((*indirect)->left);
    else
      indirect = &((*indirect)->right);
  }
  
  *indirect = new AVLNode<T>(value);
  path.push_back(indirect);
  
  balance(path);
  _size++;
}


template <class T>
void AVLTree<T>::erase(const T& value){
  AVLNode<T>** indirect = &root;
  std::vector<AVLNode<T>**> path;
  
  // ...
  
  balance(path);
}

template <class T>
void AVLTree<T>::balance(std::vector<AVLNode<T> **> path) {
  // starting from root
  std::reverse(path.begin(), path.end());
  
  for (auto indirect: path) {
    (*indirect)->updateValues();
    
    if ((*indirect)->balanceFactor() >= 2 and
        (*indirect)->left->balanceFactor() >= 0) {
      // left - left
      *indirect = (*indirect)->rotateRight();
    } else if ((*indirect)->balanceFactor() >= 2) {
      // left - right
      (*indirect)->left = (*indirect)->left->rotateLeft();
      *indirect = (*indirect)->rotateRight();
    } else if ((*indirect)->balanceFactor() <= -2 and
               (*indirect)->right->balanceFactor() <= 0) {
      // right - right
      *indirect = (*indirect)->rotateLeft();
    } else if ((*indirect)->balanceFactor() <= -2) {
      // right - left
      (*indirect)->right = ((*indirect)->right)->rotateRight();
      *indirect = (*indirect)->rotateLeft();
    }
  }
}

template <class T>
bool AVLTree<T>::empty() const{
  return _size == 0;
}

template <class T>
int AVLTree<T>::size() const{
  return _size;
}

template <class T>
void AVLTree<T>::print(std::ostream& outputStream){
  outputStream << "\n";
  if (root != nullptr)
    print(root, outputStream);
  else
    outputStream << "Empty";
  outputStream << "\n";
}

template <class T>
void AVLTree<T>::print(AVLNode<T> *cur, std::ostream& outputStream,
                         int depth, int state){
  // state: 1 -> left, 2 -> right , 0 -> root
  if (cur->left) {
    print(cur->left, outputStream, depth + 1, 1);
  }
  for (int i=0; i < depth; i++) {
    outputStream << "     ";
  }
  if (state == 1) {
    // left
    outputStream << "┌───";
  } else if (state == 2) {
    // right
    outputStream << "└───";
  }
  outputStream << "[" << cur->value << "] - (" << cur->count <<
                  ", " << cur->height << ")" << std::endl;
  
  if (cur->right) {
    print(cur->right, outputStream, depth + 1, 2);
  }
}

template <class T>
bool AVLTree<T>::contains(const T& value) const{
  AVLNode<T>* direct = root;

  while (direct != nullptr and direct->value != value){
    if (direct->value > value)
      direct = direct->left;
    else{
      direct = direct->right;
    }
  }
  
  return direct != nullptr;
}
