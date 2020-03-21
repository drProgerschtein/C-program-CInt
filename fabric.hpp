#pragma once
#include "CDInt.hpp"

class CDIntFabric{
public:
    virtual CDInt* Create(const char* data, const char* fname) = 0;
};

class CDInt0Fabric: public CDIntFabric{
public:
    CDInt* Create(const char* data, const char* fname);
};

class CDInt1Fabric: public CDIntFabric{
public:
    CDInt* Create(const char* data, const char* fname);
};
