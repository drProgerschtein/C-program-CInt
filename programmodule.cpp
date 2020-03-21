#include "programmodule.hpp"
#include <string.h>
#include "fabric.hpp"
#include "CDInt.hpp"
#include <vector>
#include <map>
#include <string>

void ClearFile(const char* fname){
    FILE * fforclear;
    fforclear = fopen(fname, "w");
    fclose(fforclear);
    return;
}

int ProgramCData(const char* fname){
    CData** arr; int alen=0, aquan=0;
    FILE* inp = fopen(fname, "r");
    if (inp){
        //Program will make smth
        char * rstr; int len, quan; char sym = 0, fcode=0; CInt tmpInt;
        rstr = new char[1]; len = 1; quan = 0;
        arr = new CData*[1]; alen=1;

        do{//Read from file
            sym = fgetc(inp);
            if ((sym=='1')||(sym=='0')){//creation mode
                fcode = sym -'0';
            }
            else{
                break;
            }

            //new dataset
            if (alen==aquan){
                CData** tmp = new CData*[alen*2]; alen*=2;
                for (int i=0; i<aquan; i++){
                    tmp[i]=arr[i];
                }
                delete[] arr;
                arr = tmp;
            }
            if (fcode==0){
                arr[aquan++] = new CData0;
            }
            else{
                arr[aquan++] = new CData1;
            }


            fgetc(inp);//ignore space
            if ((sym=='\n')&&(sym==-1)) break;

            sym=fgetc(inp);
            if ((sym=='\n')&&(sym==-1)&&(sym==' ')) break; //empty file name

            while ((sym!='\n')&&(sym!=-1)&&(sym!=' ')) {
                if (quan==len){
                    char * tmp = new char[len*2]; len*=2;
                    memcpy(tmp,rstr,quan);
                    delete[] rstr;
                    rstr = tmp;
                }
                rstr[quan++]=sym;

                sym=fgetc(inp);
            }
            if (quan==len){
                char * tmp = new char[len*2]; len*=2;
                memcpy(tmp,rstr,quan);
                delete[] rstr;
                rstr = tmp;
            }
            rstr[quan++]=0;

            arr[aquan-1]->SetFile(rstr);

            quan=0;

            sym = fgetc(inp);
            while ((sym!='\n')&&(sym!=-1)){//eol
                if (sym==' '){
                    if (quan==len){
                        char * tmp = new char[len*2]; len*=2;
                        memcpy(tmp,rstr,quan);
                        delete[] rstr;
                        rstr = tmp;
                    }
                    rstr[quan]=0;
                    quan=0;
                    tmpInt.ConvertStr(rstr);
                    arr[aquan-1]->AddData(tmpInt);
                }
                else{
                    if (quan==len){
                        char * tmp = new char[len*2]; len*=2;
                        memcpy(tmp,rstr,quan);
                        delete[] rstr;
                        rstr = tmp;
                    }
                    rstr[quan++]=sym;
                }
                sym = fgetc(inp);
            }
            if (quan==len){
                char * tmp = new char[len*2]; len*=2;
                memcpy(tmp,rstr,quan);
                delete[] rstr;
                rstr = tmp;
            }
            rstr[quan]=0;
            tmpInt.ConvertStr(rstr);
            arr[aquan-1]->AddData(tmpInt);
            quan=0;
        }while (sym!=-1);//eof


        for (int i=0; i<aquan; i++){
            arr[i]->outfunc();
        }

        delete[] rstr; rstr =nullptr;
        for (int i=0; i<aquan;i++){
            delete arr[i];
        }
        delete[] arr;

        fclose(inp);

        return 0;
    }
    else{
        return -1;
    }
}

int ProgramCDInt(const char* fname){
    CDInt** arr; int alen=0, aquan=0;
    FILE* inp = fopen(fname, "r");
    if (inp){
        //Program will make smth
        char *rstr; int len, quan;
        char *fnstr; int lenfn;

        char sym = 0, fcode=0; CInt tmpInt;
        rstr = new char[1]; len = 1; quan = 0;
        fnstr = new char[2]; lenfn = 2;
        arr = new CDInt*[1]; alen=1;

        do{//Read from file
            sym = fgetc(inp);
            if ((sym=='1')||(sym=='0')){//creation mode
                fcode = sym -'0';
            }
            else{
                break;
            }


            fgetc(inp);//ignore space
            if ((sym=='\n')&&(sym==-1)) break;

            sym=fgetc(inp);
            if ((sym=='\n')&&(sym==-1)&&(sym==' ')) break; //empty file name

            while ((sym!='\n')&&(sym!=-1)&&(sym!=' ')) {
                if (quan==len){
                    char * tmp = new char[len*2]; len*=2;
                    memcpy(tmp,rstr,quan);
                    delete[] rstr;
                    rstr = tmp;
                }
                rstr[quan++]=sym;

                sym=fgetc(inp);
            }
            if (quan==len){
                char * tmp = new char[len*2]; len*=2;
                memcpy(tmp,rstr,quan);
                delete[] rstr;
                rstr = tmp;
            }
            rstr[quan++]=0;
            if (quan+1>lenfn){
                delete[] fnstr;
                fnstr = new char[quan+1];
                lenfn = quan+1;
            }
            strcpy(fnstr,rstr);//filename was copied
            ClearFile(fnstr);//Clear file before using


            quan=0;

            sym = fgetc(inp);
            while ((sym!='\n')&&(sym!=-1)){//eol
                if (sym==' '){
                    if (quan==len){
                        char * tmp = new char[len*2]; len*=2;
                        memcpy(tmp,rstr,quan);
                        delete[] rstr;
                        rstr = tmp;
                    }
                    rstr[quan]=0;
                    quan=0;
                    tmpInt.ConvertStr(rstr);

                    if (alen==aquan){
                        CDInt** tmp = new CDInt*[alen*2]; alen*=2;
                        for (int i=0; i<aquan; i++){
                            tmp[i]=arr[i];
                        }
                        delete[] arr;
                        arr = tmp;
                    }
                    if (fcode==0){
                        arr[aquan++] = new CDInt0;
                    }
                    else{
                        arr[aquan++] = new CDInt1;
                    }
                    arr[aquan-1]->SetFile(fnstr);
                    arr[aquan-1]->SetData(tmpInt);
                }
                else{
                    if (quan==len){
                        char * tmp = new char[len*2]; len*=2;
                        memcpy(tmp,rstr,quan);
                        delete[] rstr;
                        rstr = tmp;
                    }
                    rstr[quan++]=sym;
                }
                sym = fgetc(inp);
            }
            if (quan==len){
                char * tmp = new char[len*2]; len*=2;
                memcpy(tmp,rstr,quan);
                delete[] rstr;
                rstr = tmp;
            }
            rstr[quan]=0;
            tmpInt.ConvertStr(rstr);
            if (alen==aquan){
                CDInt** tmp = new CDInt*[alen*2]; alen*=2;
                for (int i=0; i<aquan; i++){
                    tmp[i]=arr[i];
                }
                delete[] arr;
                arr = tmp;
            }
            if (fcode==0){
                arr[aquan++] = new CDInt0;
            }
            else{
                arr[aquan++] = new CDInt1;
            }
            arr[aquan-1]->SetFile(fnstr);
            arr[aquan-1]->SetData(tmpInt);

            quan=0;
        }while (sym!=-1);//eof


        for (int i=0; i<aquan; i++){
            arr[i]->outfunc();
        }

        delete[] rstr; rstr =nullptr;
        for (int i=0; i<aquan;i++){
            delete arr[i];
        }
        delete[] arr;

        fclose(inp);

        return 0;
    }
    else{
        return -1;
    }
}

int ProgramFabricCDInt(const char* fname){
    //STL
    std::vector<CDInt*> arr;
    FILE* inp = fopen(fname, "r");
    if (inp){
        //Program will make smth
        char *rstr; int len, quan;
        char *fnstr;

        char sym = 0; CInt tmpInt;
        char* fcode;
        rstr = new char[1]; len = 1; quan = 0;

        std::map<std::string, CDIntFabric*> factory;
        factory["str"] = static_cast<CDIntFabric*>(new CDInt0Fabric);
        factory["stb"] = static_cast<CDIntFabric*>(new CDInt1Fabric);
        do{//Read from file
            sym = fgetc(inp);
            //program reads full string
            while ((sym!='\n')&&(sym!=-1)){
                if (quan==len){
                    char * tmp = new char[len*2]; len*=2;
                    memcpy(tmp,rstr,quan);
                    delete[] rstr;
                    rstr = tmp;
                }
                rstr[quan++]=sym;

                sym=fgetc(inp);
            }
            fcode = strtok(rstr, " ");

            auto curFactory = factory.find(fcode);
            if (curFactory == factory.end()){
                delete[] rstr;
                return -1;
            }
            fnstr = strtok(NULL, " ");
            ClearFile(fnstr);
            char* elem = strtok(NULL, " ");
            while (elem){
                auto curCDInt = curFactory->second->Create(elem,fnstr);
                arr.push_back(curCDInt);
                elem = strtok(NULL, " ");
            }

            quan = 0;
        }while (sym!=-1);//eof


        for (std::vector<CDInt*>::iterator it = arr.begin(); it!=arr.end(); it++){
            (*it)->outfunc();
            delete *it;
        }
        for (std::map<std::string, CDIntFabric*>::iterator it = factory.begin(); it!=factory.end(); it++){
            delete it->second;
        }
        delete[] rstr; rstr = nullptr;

        fclose(inp);

        return 0;
    }
    else{
        return -1;
    }
}

int CIntToInt(const CInt& numb){
    int rez=0;
    for (int i=numb.N-1; i>=0; i--){
        rez = rez*10+numb.numb[i];
    }
    rez = rez*numb.sgn;
    return rez;
}

int Autotest(){
    int flag=0;
    //CInt will be tested first, the next test will use this class to simple checking
    //Construct check:
    CInt rabbit01, rabbit02(5,12345);
    CInt rabbit04(5, -12345), rabbit05(5);//Who was so hungry?!!

    if ((rabbit01.N!=1)||(CIntToInt(rabbit01)!=0)) return 1;
    if ((rabbit02.N!=5)||(CIntToInt(rabbit02)!=12345)) return 1;
    if ((rabbit04.N!=5)||(CIntToInt(rabbit04)!=-12345)) return 1;
    if ((rabbit05.N!=5)||(CIntToInt(rabbit05)!=0)) return 1;

    flag=0;
    try{
        CInt raddit30(1, 100000);//Hm... I think it is number 03... But why is it so big?
    }
    catch(CInt::ErrCode err){
        flag=1; //We detected this mutation
    }
    if (!flag)
        return 2;

    //It is time to check genetic of our pets
    rabbit01 = 123;
    if ((rabbit01.N!=3)||(CIntToInt(rabbit01)!=123)) return 3;
    rabbit01 = rabbit05;
    if ((rabbit01.N!=5)||(CIntToInt(rabbit01)!=0)) return 3;
    //cout<<"It's clear"<<endl;
    rabbit01 = rabbit01 + rabbit02;
    //cout<<"It's clear1"<<endl;
    if ((rabbit01.sgn!=1)||(rabbit01.N!=5)||(CIntToInt(rabbit01)!=12345)) return 3;
    if (rabbit01!=rabbit02) return 4;
    rabbit01 = rabbit01 - rabbit02;
    if ((rabbit01.sgn!=0)||(CIntToInt(rabbit01)!=0)) return 4;


    //When the personal is alive we are ready to the next stage. The Krakens are on the horizon!!!
    CDInt0 Kraken011, Kraken012, Kraken013, Kraken01F;
    CDInt1 Kraken021, Kraken022, Kraken023, Kraken02F;
    //cout<<"Krakens lv1"<<endl;
//Krakens will broke the program total

    Kraken011.SetFile("f011");
    Kraken012.SetFile("f012");
    Kraken013.SetFile("f013");
    Kraken01F.SetFile("f01F");
    Kraken021.SetFile("f021");
    Kraken022.SetFile("f022");
    Kraken023.SetFile("f023");
    Kraken02F.SetFile("f02F");

    Kraken011.SetData(123);
    Kraken012.SetData(543);

    //cout<<(Kraken011+Kraken012).outfile<<endl;

    Kraken01F = Kraken011+Kraken012;
    //cout<<"First:"<<Kraken01F.outfile<<", "<<Kraken01F.data<<", "<<CIntToInt(Kraken01F.data)<<endl;
    if ((strcmp(Kraken01F.outfile,Kraken011.outfile))||(CIntToInt(Kraken01F.data)!=666))  return 5;

    Kraken02F = Kraken011+Kraken012;
    //cout<<Kraken02F.data<<endl;
    if ((strcmp(Kraken02F.outfile,Kraken011.outfile))||(CIntToInt(Kraken02F.data)!=666))  return 5;

    Kraken021.SetData(123);
    Kraken022.SetData(543);
    Kraken01F = Kraken021+Kraken022;
    //cout<<Kraken01F.data<<endl;
    //cout<<"Second:"<<Kraken01F.outfile<<", "<<Kraken01F.data<<", "<<CIntToInt(Kraken01F.data)<<endl;
    if ((strcmp(Kraken01F.outfile,Kraken021.outfile))||(CIntToInt(Kraken01F.data)!=666))  return 5;
    Kraken02F = Kraken021+Kraken022;
    //cout<<Kraken02F.data<<endl;
    if ((strcmp(Kraken02F.outfile,Kraken021.outfile))||(CIntToInt(Kraken02F.data)!=666))  return 5;

    //Without errors
    return 0;
}
