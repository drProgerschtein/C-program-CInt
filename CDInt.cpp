#include "CDInt.hpp"
#include <string.h>
#include <iostream>
#include <fstream>

void CDInt::SetFile(const char* fname){
    delete[] outfile; outfile=nullptr;
    outfile = new char[strlen(fname)+1];
    strcpy(outfile,fname);
}

int CDInt::outfunc(){
    return output(outfile);
}

int CDInt0::output(const char *FileName){
    if (FileName){
        ofstream fout;
        fout.open(FileName, ofstream::app);
        fout<<data<<" ";
        fout.close();
        return 1;
    }
    else
        return 0;
}

int CDInt1::output(const char *FileName){
    if (FileName){
        ofstream fout;
        fout.open(FileName, ofstream::app);
        fout<<data<<"\n";
        fout.close();
        return 1;
    }
    else
        return 0;
}


CDInt0& CDInt0::operator=(const CDInt0& other){
    SetData(other.data);
    SetFile(other.outfile);
    return *this;
}

CDInt0& CDInt0::operator=(const CDInt& other){
    SetData(other.data);
    SetFile(other.outfile);
    return *this;
}

CDInt0 CDInt0::operator+() const{
    CDInt0 tmp=*this;
    return tmp;
}

CDInt0 CDInt0::operator+(const CDInt& other) const{
    CDInt0 tmp=(*this);
    tmp.data=(tmp.data+other.data);
    return tmp;
}

CDInt0 CDInt0::operator-() const{
    CDInt0 tmp=*this;
    tmp.data=-tmp.data;
    return tmp;
}

CDInt0 CDInt0::operator-(const CDInt& other) const{
    CDInt0 tmp=*this;
    tmp.data=tmp.data-other.data;
    return tmp;
}

CDInt1& CDInt1::operator=(const CDInt1& other){
    SetData(other.data);
    SetFile(other.outfile);
    return *this;
}

CDInt1& CDInt1::operator=(const CDInt& other){
    SetData(other.data);
    SetFile(other.outfile);
    return *this;
}

CDInt1 CDInt1::operator+() const{
    CDInt1 tmp=*this;
    return tmp;
}

CDInt1 CDInt1::operator+(const CDInt& other) const{
    CDInt1 tmp=*this;
    tmp.data=tmp.data+other.data;
    return tmp;
}

CDInt1 CDInt1::operator-() const{
    CDInt1 tmp=*this;
    tmp.data=-tmp.data;
    return tmp;
}

CDInt1 CDInt1::operator-(const CDInt& other) const{
    CDInt1 tmp=*this;
    tmp.data=tmp.data-other.data;
    return tmp;
}

