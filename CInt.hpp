#pragma once

#include <iostream>
#include <fstream>
#include <string.h>

int Max(const int a, const int b);
int Min(const int a, const int b);

using namespace std;

class CInt{
protected:
    enum ErrCode{ConstrErr, ConvertErr, ArithmOverflow, ReadError};
    int N; signed char sgn; char* numb;

    int NumbSize(const int rnum);
    void SetZero(){N=0; sgn=0; numb=nullptr;}
    void Clear(){delete[] numb; SetZero();}
    //void CopyOnly(const CInt);
public:
    CInt(int nN=1, int nnumb=0){
        int dig=0;
        if (nN<=0) throw ConstrErr;//nN must be positive
        //nN = Max(nN, NumbSize(nnumb));

        N=nN;
        sgn = (nnumb>0)? 1: ((nnumb<0)? -1 : 0);
        numb = new char[N];
        memset(numb,0,N);

        int cnum=(nnumb>0)?nnumb:-nnumb;
        for (int i=0; cnum>0 && i<N; i++){//Convert number to the number sequence
            dig = cnum%10;
            cnum = cnum/10;
            numb[i] = dig;
        }
        if (cnum>0) throw ConstrErr;//the number must be not greater than maximum of this CInt
    }

    CInt(const CInt& other);
    CInt(CInt&& willdelete);
    ~CInt(){/*cout<<"~CInt"<<endl;*/ Clear();}

    CInt& operator=(const CInt& other);
    CInt& operator=(const int other);
    CInt& operator=(CInt&& willdelete);

    bool operator>(const CInt& other) const;
    bool operator<(const CInt& other) const;
    bool operator==(const CInt& other) const;
    bool operator!=(const CInt& other) const;

    CInt operator+() const;
    CInt operator-() const;
    CInt operator+(const CInt& other) const;
    CInt operator-(const CInt& other) const;

    void ConvertStr(const char *strint);
    friend ostream& operator<<(ostream& input, const CInt& indata);
    friend int Autotest();
    friend int CIntToInt(const CInt& numb);
    //friend ofstream& operator<<(ofstream& input, const CInt& indata);
};

ostream& operator<<(ostream& input, const CInt& indata);
//ofstream& operator<<(ofstream& input, const CInt& indata);
