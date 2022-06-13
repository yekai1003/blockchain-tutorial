//
// Created by yekai on 2020-10-30.
//

#ifndef C__BASE_WORKER_H
#define C__BASE_WORKER_H

#include <iostream>

class Worker
{
public:
    void workhard() {
        std::cout<<"I am working hard"<<std::endl;
    }
    virtual  void eating() = 0; //纯虚函数
};

#endif //C__BASE_WORKER_H
