#include <iostream>
#include <vector>
using namespace std;

struct Node {
  Node * right = nullptr;
  Node * left = nullptr;
  int value;
};

class Tree {
  private:
    Node * _root;
    void delete_func(Node*& node);
  public:    
    Tree();
    Tree(const Tree &) = delete;
    Tree& operator=(const Tree &) = delete;
    Tree(Tree &&) = delete;
    Tree& operator=(Tree &&) = delete;
    ~Tree();

    void add(int element);
    void pre_order() const;
};

void Tree::delete_func(Node*& node) {
  if(node) {
    delete_func(node->left);
    delete_func(node->right);
    delete node;
  }
}
Tree::Tree() : _root(nullptr) {}
Tree::~Tree()  {
  delete_func(_root);
}

void Tree::add(int element) {
  Node * iterator = _root;
  if(_root == nullptr) {
    _root = new Node;
    _root->value = element;
    return;
  }
  while(true) {
    if(element < iterator->value) {
      if(iterator->left == nullptr) {
        iterator->left = new Node;
        iterator->left->value = element;
        return;
      }
      iterator = iterator->left;
    }
    else {
      if(iterator->right == nullptr) {
        iterator->right = new Node;
        iterator->right->value = element;
        return;
      }
      iterator = iterator->right;
    }
  }
}

void Tree::pre_order() const {
  Node * iterator = _root;
  vector<Node*> stack;
  stack.push_back(nullptr);
  do {
    if(iterator) {
      stack.push_back(iterator);    
      std::cout << iterator->value << ' ';
      iterator = iterator->left;
    } 
    else if(stack.back()) {
      iterator = stack.back();
      stack.pop_back();
      iterator = iterator->right;
    }
  } while(stack.back() || iterator);
} 

int main() {
  Tree tree;
  int n = 0;
  cin >> n;
  int element = 0;
  while(n--) {
    cin >> element;
    tree.add(element);
  }
  tree.pre_order();
  cout << endl;
  return 0;
}
