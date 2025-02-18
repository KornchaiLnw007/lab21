#include<iostream>

using namespace std;

int main(int argc,char *argv[]){
    
    if(argc ==1){
    cout<<"Please input numbers to find average.\n";
    }else{
    double sum=0;
    int count=0;
    for(int i=1;i<argc;i++){
        sum += atof(argv[i]);
        count++;
    }
    cout<<"---------------------------------\n";
    cout<<"Average of "<< argc-1 <<" numbers = "<< sum/count <<endl;
    cout<<"---------------------------------\n";
    }

    return 0;
}
