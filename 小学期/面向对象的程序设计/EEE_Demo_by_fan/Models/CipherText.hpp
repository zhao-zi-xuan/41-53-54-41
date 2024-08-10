//
//  CipherText.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/7/29.
//

#ifndef CipherText_hpp
#define CipherText_hpp

#include <string>
#include <ostream>
#include "MD5.hpp"
using namespace std;

//CipherText class is public derrived from MD5 class
class CipherText : public MD5 {
public:
    //default constructor
    CipherText();
    //constructor with plaintext string
    CipherText(const string& Plainext);
    //the overloading of operator assigment function, encypte plaintext, then assign
    CipherText& operator= (const string& Plaintext);
    //the overloading of operator equal function, encypte plaintext, then compare
    bool operator==(const string& Plaintext) const;
    //the overloading of operator notequal function, encypte plaintext, then compare
    bool operator!=(const string& Plaintext) const;
    //friend can not be derrived!
    //the overloading of stream insertion operator
    friend ostream& operator<<(ostream& Stream, const CipherText& aCiphertext);
    //friend can not be derrived!
    //the overloading of stream extraction operator
    friend istream& operator>>(istream& Stream, CipherText& aCiphertext);
};

#endif /* CipherText_hpp */
