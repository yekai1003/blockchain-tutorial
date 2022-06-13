#include <iostream>
#include <fstream>

using  namespace std;

int main1()
{
    //创建一个文件，写入helloworld
    //创建一个流
    ofstream fout;
    //将流与文件绑定
    fout.open("a.txt", ios_base::out|ios_base::app);
    if(fout.fail() ) {
        cout<<"failed to open file"<<endl;
        return 0;
    }
    //流操作
    fout<<"hello-world"<<endl;
    fout<<"heihei-hehe"<<endl;
    fout<<"0123456789"<<endl;
    fout<<"are you ok?"<<endl;
    return 0;
}




int main()
{
    main1();
    ifstream fin("a.txt");
    if(!fin.is_open()) {
        cout<<"failed to open a.txt"<<endl;
        return 0;
    }
    char buf[256] = {0};
//    while (fin.getline(buf, 256)) {
//        cout<<"------"<<endl;
//        cout<< buf<<endl;
//    }
    //文件位置读取操作
    //第二个参数代表一个大方向的位置，开始，结束，当前
    //第一个参数根据大方向小范围调整
    fin.seekg(72, ios_base::beg);
    fin.getline(buf, 256);
    cout<<buf<<endl;


    fin.close();
    return 0;
}