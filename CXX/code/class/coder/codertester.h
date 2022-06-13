//
// Created by yekai on 2020-10-30.
//

#ifndef C__BASE_CODERTESTER_H
#define C__BASE_CODERTESTER_H

#include "coder.h"
#include "tester.h"

class  CoderTester :public Coder, public Tester
{
public:
    virtual void eating();
};

#endif //C__BASE_CODERTESTER_H
