#pragma once
#include "CInt.hpp"

using namespace std;

class CData{
protected:
    char* outfile;
    int quan, memsize;
    CInt* data;

    void SetZero(){quan=0; memsize=0; data=nullptr; outfile=nullptr;}
public:
    void SetFile(const char* fname);
    int AddData(const CInt& elem);
    void Clear(){delete[] data; delete[] outfile; SetZero();}
    virtual int output(const char *FileName)=0;
    int outfunc();
    virtual ~CData(){/*cout<<"~CData\n"<<endl;*/ Clear();}
};

class CData0:public CData{
public:
    CData0(){SetZero();}
    int output(const char *FileName);
};

class CData1:public CData{
public:
    CData1(){SetZero();}
    int output(const char *FileName);
};

