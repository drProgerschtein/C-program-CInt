#include "CInt.hpp"
#include <string.h>
#include <iostream>

using namespace std;

int Min(const int a, const int b){
    return (a>b)?b:a;
}

int Max(const int a, const int b){
    return (a>b)?a:b;
}

int CInt::NumbSize(const int rnum){
    int crnum=(rnum>0)?rnum:-rnum;
    int rez=0;
    while (crnum>0){
        crnum/=10;
        rez++;
    }
    return rez;
}

/*CInt::CInt(int nnumb=0, int nN=1){
    int dig=0;
    if (nN<=0) throw ConstrErr;//nN must be positive
    nN = Max(nN, NumbSize(nnumb));

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
}*/

CInt::CInt(const CInt& other){
    N = other.N;
    sgn = other.sgn;
    numb = new char[N];
    memcpy(numb, other.numb, N);
}

CInt::CInt(CInt&& willdelete){
    N = willdelete.N;
    sgn = willdelete.sgn;
    numb = willdelete.numb;
    willdelete.SetZero();
}

CInt& CInt::operator=(const CInt& other){
    if (this!=&other){
        if (other.N>N){//if other CInt is longer we must resize this CInt
            Clear();
            sgn = other.sgn;
            N = other.N;
            numb = new char[N];
            memcpy(numb, other.numb, N);
        }
        else{
            memset(numb, 0, N);//Clearing
            sgn = other.sgn;
            for (int i=0; i<other.N; i++){
                numb[i] = other.numb[i];
            }
        }
    }
    return *this;
}

CInt& CInt::operator=(CInt&& willdelete){
    if (this!=&willdelete){
        if (willdelete.N>N){//if other CInt is longer we must resize this CInt
            Clear();
            sgn = willdelete.sgn;
            N = willdelete.N;
            numb = willdelete.numb;
        }
        else{
            memset(numb, 0, N);//Clearing
            sgn = willdelete.sgn;
            for (int i=0; i<willdelete.N; i++){
                numb[i] = willdelete.numb[i];
            }
        }
    }
    return *this;
}

CInt& CInt::operator=(const int other){
    int nsize = NumbSize(other), cnum, dig;
    if (N<nsize){
        Clear();
        N=nsize;
        numb = new char[N];
    }
    memset(numb, 0, N);

    sgn = (other>0)? 1: ((other<0)? -1 : 0);
    cnum = other*sgn;

    dig=0;
    for (int i=0; cnum>0 && i<N; i++){//Convert number to the number sequence
        dig = cnum%10;
        cnum = cnum/10;
        numb[i] = dig;
    }

    return *this;
}

bool CInt::operator>(const CInt& other) const{
    if (this->sgn>0){
        if (other.sgn<=0){
            return true;
        }
        else{
            int dig1,dig2;
            for (int i=Max(N,other.N)-1;i>=0;i--){
                dig1 = (i<N)?numb[i]:0;
                dig2 = (i<other.N)?other.numb[i]:0;
                if (dig1<dig2){
                    return false;
                }
                if (dig1>dig2){
                    return true;
                }
            }
            return false;
        }
    }
    else{
        if (this->sgn==0){
            return (other.sgn<0);
        }
        else{
            if (other.sgn>0){
                return false;
            }
            else{
                return (-other > -*this);
            }
        }
    }
}

bool CInt::operator<(const CInt& other) const{
    return (other>*this);
}

bool CInt::operator==(const CInt& other) const{
    if (this->sgn>0){
        if (other.sgn<=0){
            return false;
        }
        else{
            int dig1,dig2;
            for (int i=Max(N,other.N)-1;i>=0;i--){
                dig1 = (i<N)?numb[i]:0;
                dig2 = (i<other.N)?other.numb[i]:0;
                if (dig1!=dig2){
                    return false;
                }
            }
            return true;
        }
    }
    else{
        if (this->sgn==0){
            return (other.sgn==0);
        }
        else{
            if (other.sgn>=0){
                return false;
            }
            else{
                return (-other==-*this);
            }
        }
    }
}

bool CInt::operator!=(const CInt& other) const{
    return !(*this==other);
}

CInt CInt::operator+() const{
    return *this;
}

CInt CInt::operator-() const{
    CInt rez(*this);
    rez.sgn*=-1;
    return rez;
}

CInt CInt::operator+(const CInt& other) const{
    if (*this==CInt(1,0)){
        return other;
    }
    if (other==CInt(1,0)){
        return *this;
    }

    if (*this>CInt(1,0)){
        if (other<CInt(1,0)){
            return (*this-(-other));
        }
        else{
            CInt sum(Max(N,other.N),0);//An overflow can arise
            int dig1,dig2,shift=0, digs=0;
            sum.sgn = 1;
            for (int i=0; i<sum.N; i++){
                digs = 0;
                dig1 = (i<N)?numb[i]:0;
                dig2 = (i<other.N)?other.numb[i]:0;

                digs = dig1+dig2+shift;
                shift = digs/10;
                digs = digs%10;

                sum.numb[i] = digs;
            }
            if (shift>0){
                throw ArithmOverflow;
            }
            return sum;
        }
    }
    else{
        if (other>CInt(1,0)){
            return -((-(*this))-other);
        }
        else{
            return -((-(*this))+(-other));
        }
    }
}

CInt CInt::operator-(const CInt& other) const{
    if (*this==CInt(1,0)){
        return -other;
    }
    if (other==CInt(1,0)){
        return *this;
    }

    if (*this>CInt(1,0)){
        if (other<CInt(1,0)){
            return (*this+(-other));//An overflow can arise
        }
        else{
            CInt dif(Max(N,other.N),0);
            if (*this>other){
                int dig1,dig2,digd;
                dif.sgn = 1;
                for (int i=0; i<dif.N; i++){
                    digd = 0;
                    dig1 = (i<N)?numb[i]:0;
                    dig2 = (i<other.N)?other.numb[i]:0;

                    digd = dig1-dig2;
                    if (digd<0){
                        int j=1;
                        while (numb[i+j]==0){
                            numb[i+j]=9;
                            j++;
                        }
                        numb[i+j]--;
                        digd+=10;
                    }
                    dif.numb[i] = digd;
                }
            }
            else{
                if (*this<other)
                    return -(other-*this);
            }
            return dif;
        }
    }
    else{
        if (other>CInt(1,0)){
            return -((-(*this))+other);//An overflow can arise
        }
        else{
            return -((-(*this))-(-other));
        }
    }
}

void CInt::ConvertStr(const char *strint){
    int intlen = strlen(strint);

    //Check that strint is correct (we need this to didn't change the CInt variable)
    if (intlen==0){
        *this=CInt(1,0);
    }
    if ((intlen==1)&& ((strint[0]<'0')||(strint[0]>'9'))){
        throw ConvertErr;
    }
    else{
        if (intlen>1){//intlen==1 - correct
            if (!((strint[0]=='+')||(strint[0]=='-')||((strint[0]>='0')&&(strint[0]<='9')))){
                throw ConvertErr;
            }
            for (int i=1; i<intlen; i++){
                if (!((strint[i]>='0')&&(strint[i]<='9'))){
                    throw ConvertErr;
                }
            }
        }
    }

    //If we are here the string is correct
    if ( ((N<intlen)&&((strint[0]>='0')&&(strint[0]<='9'))) || //Without a sign
        ((N<intlen-1)&&(!((strint[0]>='0')&&(strint[0]<='9')))) ){//With a sign
        Clear();
        N = intlen;
        if (!((strint[0]>='0')&&(strint[0]<='9'))){
            N--;
        }
        numb = new char[N];
    }//memory realoc
    memset(numb, 0, N);
    sgn = 0;

    for (int i=intlen-1; i>0; i--){
        numb[intlen-1-i] = strint[i]-'0';
        if (strint[i]!='0') sgn = 1;
    }
    if ((strint[0]>='0')&&(strint[0]<='9')){
        numb[intlen-1] = strint[0]-'0';
        if (strint[0]!='0') sgn = 1;
    }
    if (strint[0]=='-') sgn = -sgn; // if strint was 0 CInt must don't be -0
}

ostream& operator<<(ostream& input, const CInt& indata){
    if (indata.sgn<0){
        input<<"-";
    }
    for (int i=indata.N-1;i>=0;i--){
        input<<static_cast<int>(indata.numb[i]);
    }
    return input;
}

/*ofstream& operator<<(ofstream& input, const CInt& indata){
    if (indata.sgn<0){
        input<<"-";
    }
    for (int i=indata.N-1;i>=0;i--){
        input << static_cast<int>(indata.numb[i]);
    }
    return input;
}*/


