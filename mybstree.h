//Name: Jack Eddy
//Class: cs1510
//Desc: Program that shows knowlege of the tree ADT
#include "abstractbstree.h"

template <typename T>
struct TreeNode
{
  T m_data;
  TreeNode* m_right;
  TreeNode* m_left;
};

template <typename T>
class MyBSTree: public AbstractBSTree<T>
{
public:
  MyBSTree<T>();
  
  ~MyBSTree<T>();
  
  MyBSTree<T>(MyBSTree<T>* &t)
  {
    *this = copy;
  }
  
  MyBSTree& operator=(const MyBSTree<T> &t)
  {
    if(this != &t)
    {
      if(this != NULL)
      {
        clear();
      }
      m_root = clone(t.m_root);
    }
    return *this;
  }
  
  TreeNode<T>* m_root;
  
  int m_size;
  
  TreeNode<T>* clone(const TreeNode<T>* t);
  
  int size() const { return m_size; }
  
  bool isEmpty() const;
  
  int height() const;
  
  int recursive_Height(const TreeNode<T>* t) const;
  
  const T& recursive_findMax(const TreeNode<T>* t) const;
  
  const T& findMax() const throw (Oops);
  
  const T& recursive_findMin(const TreeNode<T>* t) const;
  
  const T& findMin() const throw (Oops);
  
  int find(const T& x) const;
  
  int recursive_find(const T& x, const TreeNode<T>* t) const;
  
  //Mutators
  
  void clear();
  
  void insert(const T& x);
  
  void recursive_insert(const T& x, TreeNode<T>& t);
  
  void remove(const T& x);
  
  void recursive_remove(TreeNode<T>* &t, const T& x);
  
  //Output
  
  void printPreOrder() const;
  
  void recursive_printPreOrder(TreeNode<T>* t) const;
  
  void printPostOrder() const;
  
  void recursive_printPostOrder(TreeNode<T>* t) const;
  
  void print() const;
  
  void prettyPrint(const TreeNode<T>* t, int pad) const;
  
};

#include "mybstree.hpp"