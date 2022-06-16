#include <iostream>
#include <stack>
using namespace std;

struct bstree_node
{
    char data;
    bstree_node* left;
    bstree_node* right;
    bstree_node(char _data) : data(_data) {
       left = nullptr;
       right = nullptr;
    }
};
 
struct bstree
{
    bstree_node* root;
};
 
bstree* tree = NULL;

bool Insert_node(int key)
{
    if(tree == NULL)
    {
        return false;
    }
    bstree_node * btn = new bstree_node(key);
 
    if(tree->root == NULL)
    {
        tree->root = btn;
        return true;
    }
 
    bstree_node* node1= tree->root;
    bstree_node* node2= node1;
    while(node1 != nullptr)
    {
        node2= node1;
        if(key < node1->data)
        {
            node1 = node1->left;
        }
        else if(key > node1->data)
        {
            node1 = node1->right;
        }
        else
        {
            return false; // 已经存在  覆盖或者丢弃
        }
    }
 
    if(key < node2->data)
    {
        node2->left = btn;
    }
    else
    {
        node2->right = btn;
    }
 
    return true;
}

struct ParentInfo {
   int parent;
   bool isLeft;
};


bstree_node *findParent(int num)
{
   bstree_node * pnode = tree->root;
   if(num == 0) return pnode;
   stack<ParentInfo> parents;
   int parent = num;
   ParentInfo pi ;
   do
   {
      
      parent = (parent - 1) / 2;
      pi.parent = parent;
      if((parent - 1) % 2 > 0 ) {
         pi.isLeft = false;
      } else {
         pi.isLeft = true;
      }
      parents.push(pi);
   } while(parent > 0) ;
   
   while (parents.size() > 0)
   {
      pi = parents.top();
      parents.pop();
      cout<<pi.parent<<":"<<pi.isLeft<<endl;
      if(pi.isLeft) {
         pnode = pnode->left;
      } else {
         pnode = pnode->right;
      }
   }
   
   return pnode;

}

int bstree_traversal(bstree_node *node) {
	if (node == nullptr) return 0;
   printf("%4d ", node->data);
	bstree_traversal(node->left);
	
	bstree_traversal(node->right);
   return 0;
}

int main()
{
   tree = new bstree;
   // Insert_node(50);
   // Insert_node(20);
   // Insert_node(30);
   // Insert_node(40);
   // Insert_node(90);
   // Insert_node(80);

   // bstree_traversal(tree->root);
   // cout<<endl;
   findParent(10);
    delete tree;
   return 0;
}