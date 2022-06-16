#include <iostream>
using namespace std;

struct Block
{
   public:
   int data;
   Block *prev;
   Block(int _data) : data(_data) {};
};

static Block *current = NULL;

Block * addBlock(int _data)
{
   Block *b = new Block(_data);
   b->prev = current;
   current = b;
   return current;
}

void show()
{
   while(current != nullptr) {
      cout<<"data:"<<current->data<<endl;
      current = current->prev;
   }
}

void release()
{
   Block * b = nullptr;
   while(current != nullptr) {
      cout<<"data:"<<current->data<<endl;
      b = current;
      current = current->prev;
      delete b;
   }
}

int main()
{
   addBlock(10);
   addBlock(100);
   addBlock(1000);
   show();
   release();
   return 0;
}
