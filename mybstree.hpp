//Name: Jack Eddy
//Class: cs1510
//Desc: Program that shows knowlege of the tree ADT
#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename T>
MyBSTree<T>::MyBSTree()
{
  m_size = 0;
  m_root = NULL;
}

template <typename T>
MyBSTree<T>::~MyBSTree()
{
  m_root = NULL;
}

template <typename T>
void MyBSTree<T>::prettyPrint (const TreeNode<T>* t, int pad) const
{
  string s(pad, ' ');
  if (t == NULL)
    cout << endl;
  else{
    prettyPrint(t -> m_right, pad+4);
    cout << s << t -> m_data << endl;
    prettyPrint(t -> m_left, pad+4);
  }
}

template <typename T>
bool MyBSTree<T>::isEmpty() const
{
  if(m_size == 0){
    return true;
  }
  else{
    return false;
  }
}

template <typename T>
TreeNode<T>* MyBSTree<T>::clone(const TreeNode<T>* t)
{
  if (t == NULL){
    return NULL;
  }
  else{
    TreeNode<T> *copy = new TreeNode<T>;
    copy -> m_data = t -> m_data;
    copy -> m_left = clone(t -> m_left);
    copy -> m_right = clone(t -> m_right);
    return copy;
  }
}

template <typename T>
int MyBSTree<T>::height() const
{
  if(m_root != NULL)
  {
    if(m_root -> m_left == NULL && m_root -> m_right == NULL)
    {
      return 1;
    }
    else
    {
      return recursive_Height(m_root);
    }
  }
  else
  {
    return 0;
  }
}

template <typename T>
int MyBSTree<T>::recursive_Height(const TreeNode<T>* t) const
{
  int value = 1;
  
  if(t != NULL)
  {
    int left_Height = recursive_Height(t -> m_left);
    int right_Height = recursive_Height(t -> m_right);
    
    if(left_Height > right_Height)
    {
      value += left_Height;
    }
    else
    {
      value += right_Height;
    }
    
    return value;
  }
  else
  {
    return 0;
  }
}

template <typename T>
const T& MyBSTree<T>::findMax() const throw (Oops)
{
  if(isEmpty())
  {
    throw Oops("OOPS! : Tree is Empty!!");
  }
  else
  {
    return recursive_findMax(m_root);
  }
}

template <typename T>
const T& MyBSTree<T>::findMin() const throw (Oops)
{
  if(isEmpty())
  {
    throw Oops("OOPS! : Tree is Empty!!");
  }
  else
  {
    return recursive_findMin(m_root);
  }
}

template <typename T>
const T& MyBSTree<T>::recursive_findMin(const TreeNode<T>* t) const
{
  if(t -> m_left != NULL)
  {
    return recursive_findMin(t -> m_left);
  }
  else
  {
    return t -> m_data;
  }
}

template <typename T>
const T& MyBSTree<T>::recursive_findMax(const TreeNode<T>* t) const
{
  if(t -> m_right != NULL)
  {
    return recursive_findMax(t -> m_right);
  }
  else
  {
    return t -> m_data;
  }
}

template <typename T>
int MyBSTree<T>::recursive_find(const T& x, const TreeNode<T>* t) const
{
  if(x == t -> m_data)
  {
    return 1;
  }
  else
  {
    if(x < t -> m_data)
    {
      if(t -> m_left != NULL)
      {
        int value = recursive_find(x, t -> m_left);
        return (value*(1 + abs(value)))/abs(value); //Increments correctly
      }
      else
      {
        return -1;
      }
    }
    else
    {
      if(t -> m_right != NULL)
      {
        int value = recursive_find(x, t -> m_right);
        return ((value*(1 + abs(value)))/abs(value)); //Increments correctly
      }
      else
      {
        return -2;
      }
    }
  }
}

template <typename T>
int MyBSTree<T>::find(const T& x) const
{
  if(!isEmpty())
  {
    return recursive_find(x, m_root);
  }
  else
  {
    return -1;
  }
}

template <typename T>
void MyBSTree<T>::clear()
{
  while(m_root != NULL)
  {
    remove(m_root -> m_data);
  }
}

template <typename T>
void MyBSTree<T>::insert(const T& x)
{
  if(isEmpty())
  {
    m_root = new TreeNode<T>();
    m_root  ->  m_data = x;
    m_size++;
  }
  else
  {
    if(find(x) < 0)
    {
      recursive_insert(x, *m_root);
    }
    m_size++;
  }
}

template <typename T>
void MyBSTree<T>::recursive_insert(const T& x, TreeNode<T>& t)
{
  if(x < t.m_data)
  {
    if(t.m_left == NULL)
    {
      t.m_left = new TreeNode<T>();
      t.m_left -> m_data = x;
    }
    else
    {
      recursive_insert(x, *t.m_left);
    }
  }
  else
  {
    if(t.m_right == NULL)
    {
      t.m_right = new TreeNode<T>();
      t.m_right -> m_data = x;
    }
    else
    {
      recursive_insert(x, *t.m_right);
    }
  }
}

template <typename T>
void MyBSTree<T>::remove(const T& x)
{
  recursive_remove(m_root, x);
  m_size--;
}

template <typename T>
void MyBSTree<T>::recursive_remove(TreeNode<T>* &t, const T& x)
{
  if(t == NULL)
  {
    return;
  }
  else if(x < t -> m_data)
  {
    recursive_remove(t -> m_left, x);
  }
  else if(x > t -> m_data)
  {
    recursive_remove(t -> m_right, x);
  }
  else
  {
    if(t -> m_left == NULL && t -> m_right == NULL)
    {
      delete t;
      t = NULL;
    }
    else if(t -> m_left == NULL || t -> m_right == NULL)
    {
      TreeNode<T>* child = t -> m_left;
      if(child == NULL)
      {
        child = t -> m_right;
      }
      
      delete t;
      t = child;
    }
    else
    {
      t -> m_data = recursive_findMax(t -> m_left);
      recursive_remove(t -> m_left, t -> m_data);
    }
  }
}

template <typename T>
void MyBSTree<T>::printPreOrder() const
{
  recursive_printPreOrder(m_root);
  cout << endl;
}

template <typename T>
void MyBSTree<T>::recursive_printPreOrder(TreeNode<T>* t) const
{
  cout << t -> m_data << " ";
  if(t -> m_left != NULL)
  {
    recursive_printPreOrder(t -> m_left);
  }
  if(t -> m_right != NULL)
  {
    recursive_printPreOrder(t -> m_right);
  }
}

template <typename T>
void MyBSTree<T>::printPostOrder() const
{
  recursive_printPostOrder(m_root);
  cout << endl;
}

template <typename T>
void MyBSTree<T>::recursive_printPostOrder(TreeNode<T>* t)  const
{
  if(t -> m_left != NULL)
  {
    recursive_printPostOrder(t -> m_left);
  }
  if(t -> m_right != NULL)
  {
    recursive_printPostOrder(t -> m_right);
  }
  cout << t -> m_data << " ";
}

template <typename T>
void MyBSTree<T>::print() const
{
  prettyPrint(m_root, 0);
}