#pragma once
#include "CInt.hpp"

class CDInt{
protected:
    char* outfile;
    CInt data;

    void SetZero(){outfile=nullptr;}
public:
    void SetData(const int& numb){data = numb;}
    void SetData(const CInt& numb){data = numb;}

    void SetFile(const char* fname);
    void ResetFile(){delete[] outfile; outfile=nullptr;}
    virtual int output(const char *FileName=NULL)=0;
    int outfunc();
    virtual ~CDInt(){/*cout<<"~CDInt\n"<<endl;*/ ResetFile();}
    friend class CDInt0;
    friend class CDInt1;
    friend int Autotest();
};

class CDInt0:public CDInt{
public:
    CDInt0(){/*cout<<"+CDInt0"<<endl;*/ SetZero();}
    CDInt0(const CDInt0& other){/*cout<<"+CDInt0"<<endl;*/ SetZero(); if (other.outfile) SetFile(other.outfile); data=other.data;}
    CDInt0(const CDInt& other){/*cout<<"+CDInt0"<<endl;*/ SetZero(); if (other.outfile) SetFile(other.outfile); data=other.data;}
    int output(const char *FileName);
    ~CDInt0(){/*cout<<"~CDInt0"<<endl;*/ ResetFile();}
    CDInt0& operator=(const CDInt0& other);
    CDInt0& operator=(const CDInt& other);
    CDInt0 operator+() const;
    CDInt0 operator+(const CDInt& other) const;
    CDInt0 operator-() const;
    CDInt0 operator-(const CDInt& other) const;
};

class CDInt1:public CDInt{
public:
    CDInt1(){/*cout<<"+CDInt1"<<endl;*/ SetZero();}
    CDInt1(const CDInt1& other){/*cout<<"+CDInt1"<<endl;*/ SetZero(); if (other.outfile) SetFile(other.outfile); data=other.data;}
    CDInt1(const CDInt& other){/*cout<<"+CDInt1"<<endl;*/ SetZero(); if (other.outfile) SetFile(other.outfile); data=other.data;}
    int output(const char *FileName);
    ~CDInt1(){/*cout<<"~CDInt1"<<endl;*/ ResetFile();}

    CDInt1& operator=(const CDInt1& other);
    CDInt1& operator=(const CDInt& other);
    CDInt1 operator+() const;
    CDInt1 operator+(const CDInt& other) const;
    CDInt1 operator-() const;
    CDInt1 operator-(const CDInt& other) const;
};
