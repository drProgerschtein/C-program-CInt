#include <iostream>
#include "programmodule.hpp"
#include "prmod2.hpp"

using namespace std;

int main()
{
    switch (Autotest()){
    case 0:
        cout<<"Congratulation! You are still alive!"<<endl;
        break;
    case 1:
        cout<<"My fingers!!! This rabbits bit me!"<<endl;
        break;
    case 2:
        cout<<"Warning!!! A radiation pollution!"<<endl;
        break;
    case 3:
        cout<<"Population problem-3!"<<endl;
        break;
    case 4:
        cout<<"Population problem-4!"<<endl;
        break;
    case 5:
        cout<<"Warning!!! The Krakens are here!!!"<<endl;
        break;
    }

    cout<<"Begin the test"<<endl;
    if (false){
        if (true){
            if (ProgramCDInt("dataset.txt")){
                cout<<"File problem"<<endl;
            }
            else{
                cout<<"Complete!"<<endl;
            }
        }
        else{
            if (ProgramCData("dataset.txt")){
                cout<<"File problem"<<endl;
            }
            else{
                cout<<"Complete!"<<endl;
            }
        }
    }
    else{
        //Fabrics
        if (ProgramFabricCDInt("factoryset.txt")){
            cout<<"File problem"<<endl;
        }
        else{
            cout<<"Complete!"<<endl;
        }
    }


    return 0;
}
