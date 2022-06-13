//
// Created by yekai on 2020-10-30.
//

#ifndef C__BASE_BED_H
#define C__BASE_BED_H

class  Bed
{
public:
    int weight;
    Bed(int w) {
        weight = w;
    }
public:
    void  sleep();
};

#endif //C__BASE_BED_H
