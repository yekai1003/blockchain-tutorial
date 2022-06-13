/*************************************************************************
	> File Name: bitset.cpp
	> Author: yekai
	> Mail: yekai_23@sohu.com
	> Created Time: 一  6/13 14:04:11 2022
 ************************************************************************/

#include<iostream>
#include<bitset>
using namespace std;//必须得加上
int main()
{
	int a=0x1;
    a = a << 3;
	cout<<"默认下"<<a<<endl;
	cout<<"十进制"<<dec<<a<<endl;
	cout<<"八进制"<<oct<<a<<endl;//八进制
	cout<<"十六进制"<<hex<<a<<endl;	//十六进制
	cout<<"二进制"<<bitset<16>(a)<<endl; //输出为十六位二进制数
	return 0;
}
