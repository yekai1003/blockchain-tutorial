//函数参数传递
#include <iostream>
using namespace std;

//函数声明在前，使用在后
//int avg(int arr[5]) 函数声明不可取
//int avg(int arr[5])
//{
//    //先求和
//    int sum = 0;
//    for(int i = 0;i < 5;i ++) {
//        sum += arr[i];
//    }
//    return sum/5;
//}


//int avg(int arr[], int num)
////{
////    //先求和
////    int sum = 0;
////    for(int i = 0;i < num;i ++) {
////        sum += arr[i];
////    }
////    return sum/num;
////}
//传递数组首地址+数组元素个数
int avg(int *arr, int num)
{
    //先求和
    int sum = 0;
    for(int i = 0;i < num;i ++) {
        sum += arr[i];
    }
    return sum/num;
}

//判断一个数是否在一个数组当中
bool isExists(int *arr, int num, int val)
{
    //在循环里，如果元素相同，那么返回true
    for(int i = 0; i < num ; i ++) {
        if(val == arr[i]) {
            return true;
        }
    }
    return false;//循环都结束了，还没找到
}

//字符串是否有必要传递num，字符串的大小
//字符串是特殊的，以'\0'结尾
void showMsg(const  char *  msg)
{
    //msg = "heihei";
    //strcpy(msg, "heihei");
    cout<<msg<<endl;
}

//计算阶乘
int jiecheng(int num)
{
    //0! = 1
    //1! = 0!*1
    if(num == 0) {
        return 1;
    }
    return num * jiecheng(num - 1);
}


int main()
{
    int arr1[6] = {1, 2, 3, 4, 5, 6};
    //cout<<avg(arr1)<<endl;
    cout<<avg(arr1, 6)<<endl;
    cout<<isExists(arr1, 6, 8)<<endl;
    cout<<isExists(arr1, 6, 5)<<endl;
    cout<<isExists(arr1, 4, 5)<<endl;
    char msg[20] = "hehe";
    showMsg(msg);
    cout<<"main:"<<msg<<endl;
    cout<<jiecheng(4)<<endl;
    cout<<jiecheng(3)<<endl;
    cout<<jiecheng(2)<<endl;
    cout<<jiecheng(1)<<endl;
    cout<<jiecheng(5)<<endl;
    return 0;
}

