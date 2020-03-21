#pragma once
#include "CData.hpp"
#include "CDInt.hpp"

void ClearFile(const char* fname);
int ProgramCData(const char* fname);
int ProgramCDInt(const char* fname);
int ProgramFabricCDInt(const char* fname);

int CIntToInt(const CInt& numb);
int Autotest();
