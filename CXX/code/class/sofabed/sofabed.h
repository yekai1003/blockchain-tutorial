//
// Created by yekai on 2020-10-30.
//

#ifndef C__BASE_SOFABED_H
#define C__BASE_SOFABED_H

#include "bed.h"
#include "sofa.h"

//多重继承，每个基类前面都要加public关键字，不加则认为是private继承
class SofaBed :public Bed, public Sofa
{
public:
    SofaBed(int w):Bed(w),Sofa(w)
    {}
};

#endif //C__BASE_SOFABED_H
