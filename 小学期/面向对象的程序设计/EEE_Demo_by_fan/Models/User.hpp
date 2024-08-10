#ifndef USER_H
#define USER_H

#include<string>
#include<vector>
#include<iostream>
#include<memory>
#include<stdexcept>
#include"CipherText.hpp"
using namespace std;

//The NO USER exception class
class ExecptionNoUser : public invalid_argument{
public:
    ExecptionNoUser();
};

//The HAS USER BUT WRONG PASSWORD exception class
class ExecptionWrongPassword : public invalid_argument{
public:
    ExecptionWrongPassword();
};

//The ADMINISTRATOR EXISTS exception class
class ExecptionAdministratorExists : public invalid_argument{
public:
    ExecptionAdministratorExists();
};

//The TRIVIAL USER EXISTS exception class
class ExecptionUserExists : public invalid_argument{
public:
    ExecptionUserExists();
};

//The CAN'T DELETE ADMINISTRATOR exception class
class ExecptionCannotDeleteAdministrator : public invalid_argument{
public:
    ExecptionCannotDeleteAdministrator();
};


//User Class as a base class
class User
{
public:
    //default constructor, copy constructor and assignment operator are not allowed
    User() = delete;
    User(const User&) = delete;
    User& operator=(const User&) = delete;
    //as the base class, considering the possibility of subsequent expansion and modification, the destructor should be a virtual function
    virtual ~User();
    //The virtual function is used to determine whether the user object is an administrator
    virtual bool IsAdministrator() const;
    //chang password
    void changePassword(const CipherText& NewPassord);
    //Operator Overloading function of stream insertion operator
    friend ostream& operator<<(ostream& Stream, const User& anUser);
    //Operator Overloading function of stream extraction operator
    friend istream& operator>>(istream& Stream, User& anUser);
    //class function(static, no object's function) to save all users to the specified file, including derived objects
    static void SaveToFile(const string& FileName);
    //class function(static, no object's function) to read and create all users from the specified file, including administrator
    static void LoadFromFile(const string& FileName);
    //class function(static, no object's function)
    //verify the specified user by user name and password.
    //the user name does not exist, an ExecptionNoUser will be thrown
    //the user exists but the password is wrong, an ExecptionWrongPassword will be thrown
    //the return value is the smart pointer to the user object
    static shared_ptr<User> Verify(const string& Name, const string& Password);
protected:
    //User objects can only be dynamically instantiated through the new operator
    //When user objects (including derived class objects) are created, their pointers are automatically saved to the list of all users
    User(const string& Name, const CipherText& Password);
    //Create a user instance that wraps the protected constructor
    //When user objects (including derived class objects) are created, their pointers are automatically saved to the list of all users
    void Add(const string& Name, const CipherText& Password);
    //Delete a user instance , can invoke by Administrator
    void Delete(const string& Name);
private:
    //A list of smart pointers to all user objects, including derived class objects
    static vector<shared_ptr<User>> m_All;
    //user's name
    string m_Name;
    //user's password in chiphertext
    CipherText m_Password;
};

#endif // USER_H
