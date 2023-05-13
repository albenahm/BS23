#include <iostream>



class Hello{
public:
    Hello(const char * name):name(name){
        std::cout<< name <<"\n";
        std::cout<< "ctor;" <<"\n";
    }
    ~Hello (){
        std::cout<< name <<"\n";
        std::cout<< "dtor;" <<"\n";
    }

    void body(){
        std::cout<< name <<"\n";
        std::cout<< "body ;" <<"\n";
    }

const char * name ;
 } ;

int main(){
    std::cout<<"main1;"<<"\n";
    Hello anton("Anton");
    Hello betra("Berta");
    anton.body();
    std::cout<<"main3;"<<"\n";
    return 0;
}



