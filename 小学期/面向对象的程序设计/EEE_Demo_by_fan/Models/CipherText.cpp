//
//  CipherText.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/7/29.
//
#include "CipherText.hpp"
#include <string>
using namespace std;

//default constructor
CipherText::CipherText() : MD5(){
}

//constructor with plaintext string
CipherText::CipherText(const string& Plainext) : MD5(Plainext){
}

//the overloading of operator assigment function, encypte plaintext, then assign
CipherText& CipherText::operator= (const string& Plaintext){
    MD5::operator=(Plaintext);
    return *this;
}

//the overloading of operator equal function, encypte plaintext, then compare
bool CipherText::operator==(const string& Plaintext) const {
    return MD5::operator==(MD5(Plaintext));
}

//the overloading of operator notequal function, encypte plaintext, then compare
bool CipherText::operator!=(const string& Plaintext) const{
    return !operator==(Plaintext);
}

//friend can not be derrived!
//the overloading of stream insertion operator
ostream& operator<<(ostream& stream, const CipherText& aCiphertext){
    stream << static_cast<MD5>(aCiphertext);
    return stream;
}

//friend can not be derrived!
//the overloading of stream extraction operator
istream& operator>>(istream& stream, CipherText& aCiphertext){
    MD5* ptr = &aCiphertext;
    stream >> *ptr;
    return stream;
}

