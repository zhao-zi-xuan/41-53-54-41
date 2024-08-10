#include "Administrator.hpp"

//default constructor
//Administrator objects can only be dynamically instantiated through the new operator
//When Administrator objectsare created, their pointers are automatically saved to the list of all users
Administrator::Administrator():User("Admin", CipherText{"Admin"}) {
}

//constructor by password;
//Administrator objects can only be dynamically instantiated through the new operator
//When Administrator objectsare created, their pointers are automatically saved to the list of all users
Administrator::Administrator(const CipherText& Password):User("Admin", Password) {
}

//The virtual function is used to determine whether the user object is an administrator
//virtual function to return true, this is an Administrator
bool Administrator::IsAdministrator() const {
    return true;
}


