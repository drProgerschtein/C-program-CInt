#include "CData.hpp"
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

void CData::SetFile(const char* fname){
    delete[] outfile; outfile=nullptr;
    outfile = new char[strlen(fname)+1];
    strcpy(outfile,fname);
}

int CData::AddData(const CInt& elem){
    if (memsize==0){
        data = new CInt[1];
        memsize=1;
    }
    if (quan==memsize){
        CInt* tmp = new CInt[memsize*2];
        memsize*=2;
        for (int i=0; i<quan; i++){
            tmp[i]=data[i];
        }
        delete[] data;
        data=tmp;
    }

    data[quan++]=elem;

    return 0;
}

int CData::outfunc(){
    return output(outfile);
}

int CData0::output(const char *FileName){
    if (FileName){
        ofstream fout;
        fout.open(FileName);
        for (int i=0; i<quan-1; i++){
            fout<<data[i]<<" ";
        }
        fout<<data[quan-1]<<endl;
        fout.close();
        return 1;
    }
    else
        return 0;
}

int CData1::output(const char *FileName){
    if (FileName){
        ofstream fout;
        fout.open(FileName);
        for (int i=0; i<quan-1; i++){
            fout<<data[i]<<"\n";
        }
        fout<<data[quan-1]<<endl;
        fout.close();
        return 1;
    }
    else
        return 0;
}
