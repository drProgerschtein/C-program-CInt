#include "fabric.hpp"

CDInt* CDInt0Fabric::Create(const char* data, const char* fname){
    CDInt* rez;
    CInt tmp;
    tmp.ConvertStr(data);
    rez = new CDInt0;
    rez->SetFile(fname);
    rez->SetData(tmp);
    return rez;
}

CDInt* CDInt1Fabric::Create(const char* data, const char* fname){
    CDInt* rez;
    CInt tmp;
    tmp.ConvertStr(data);
    rez = new CDInt1;
    rez->SetFile(fname);
    rez->SetData(tmp);
    return rez;
}

