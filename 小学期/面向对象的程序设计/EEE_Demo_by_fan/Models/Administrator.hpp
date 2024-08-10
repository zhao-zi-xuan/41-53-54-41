#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include "User.hpp"
#include "CipherText.hpp"
using namespace std;

//Administrator class is public derrived from user class
class Administrator : public User
{
public:
    //default copy constructor and assignment operator are not allowed
    Administrator(const Administrator&) = delete ;
    Administrator& operator=(const Administrator&) = delete;
    //default constructor
    //Administrator objects can only be dynamically instantiated through the new operator
    //When Administrator objectsare created, their pointers are automatically saved to the list of all users
    Administrator();
    //constructor by password;
    //Administrator objects can only be dynamically instantiated through the new operator
    //When Administrator objectsare created, their pointers are automatically saved to the list of all users
    Administrator(const CipherText& Password);
    //using the protected Add(const string& Name, const CipherText& Password) funciton in User class, as a public function in Administrator class
    using User::Add;
    //using the protected Delete(const string& Name) funciton in User class, as a public function in Administrator class
    using User::Delete;
    //The virtual function is used to determine whether the user object is an administrator
    //virtual function to return true;
    bool IsAdministrator() const override;
};

#endif // ADMINISTRATOR_H
