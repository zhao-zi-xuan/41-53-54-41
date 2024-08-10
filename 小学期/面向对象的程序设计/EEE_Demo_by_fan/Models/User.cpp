#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include "User.hpp"
#include "Administrator.hpp"
using namespace std;


//Static data members must be explicitly initialized outside the class
//The Initialization for the list of smart pointers to all user objects, including derived class objects
vector<shared_ptr<User>> User::m_All{};

//The default constructor of NO USER exception class
ExecptionNoUser::ExecptionNoUser() : invalid_argument("No such user."){
}

//The default constructor of HAS USER BUT WRONG PASSWORD exception class
ExecptionWrongPassword::ExecptionWrongPassword() : invalid_argument("Wrong password."){
}

//The default constructor of ADMINISTRATOR EXISTS exception class
ExecptionAdministratorExists::ExecptionAdministratorExists() : invalid_argument("Administrator exist."){
}

//The default constructor of TRIVIAL USER EXISTS exception class
ExecptionUserExists::ExecptionUserExists() : invalid_argument("User Exist."){
}

//he default constructor of CAN'T DELETE ADMINISTRATOR exception class
ExecptionCannotDeleteAdministrator::ExecptionCannotDeleteAdministrator() : invalid_argument("Can't delete administrator."){
}

//The virtual destructor of user
//as the base class, considering the possibility of subsequent expansion and modification, the destructor should be a virtual function
User::~User(){
}

//---- NON-STATIC MEMBER FUNCTIONS BEGIN ---//

//NOTE: THIS CONSTRUCTOR CAN ONLY BEEN CALLED BY NEW OPERATOR
User::User(const string& Name, const CipherText& Password)
    : m_Password(Password){
    //Lambda functional object，for name comparison
    auto Finder = [&Name](shared_ptr<User> ptr)->bool{return (ptr->m_Name == Name);};
    //To find out the first user specified by name
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    //Found
    if (it != m_All.end()) {
        //Administrator
        if ((*it)->IsAdministrator()) {
            throw ExecptionAdministratorExists();
        }
        //Trivial user
        else {
            throw ExecptionUserExists();
        }
    }
    //Name field assigment
    m_Name = Name;
    //Saving the new user's pointer to list.
    m_All.push_back(shared_ptr<User>(this));
}

//Create a user instance that wraps the protected constructor
void User::Add(const string& Name, const CipherText& Password){
    //User objects can only be dynamically instantiated through the new operator
    new User(Name, Password);
}

//The virtual function is used to determine whether the user object is an administrator
bool User::IsAdministrator() const{
    //Trivial user is not an administrator
    return false;
}

//chang password
void User::changePassword(const CipherText& NewPassord) {
    m_Password = NewPassord;
}

//Operator Overloading function of stream insertion operator
ostream& operator<<(ostream& Stream, const User& anUser){
    //insert user's name, password(in ciphertext), by two lines
    Stream << anUser.m_Name << endl << anUser.m_Password;
    return Stream;
}

//Operator Overloading function of stream extraction operator
istream& operator>>(istream& Stream, User& anUser){
    //extract two lines from stream to user's name and password(in ciphertext)
    //need not to handle with the endl, which has been handled by string extraction operator
    Stream >> anUser.m_Name >> anUser.m_Password;
    return Stream;
}

//Delete a user instance, can invoke by Administrator
void User::Delete(const string& Name){
    //Lambda functional object，for name comparison
    auto Finder = [&Name](shared_ptr<User> ptr)->bool{return (ptr->m_Name == Name);};
    //To find out the first user specified by name
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    //Found
    if (it != m_All.end()) {
        //Administrator
        if ((*it)->IsAdministrator()) {
            throw ExecptionCannotDeleteAdministrator();
        }
        //delete user
        m_All.erase(it);
    }
}
//---- NON-STATIC MEMBER FUNCTIONS END ---//

//---- STATIC MEMBER FUNCTIONS BEGIN ---//

//Static function to save all users to the specified file, including derived objects
//If the file can't be opend, the try to create the file
//If the file can't be create, the invalid_argument exception will be thrown
void User::SaveToFile(const string& FileName){
    //Open or create the file specified by FileName
    ofstream File(FileName);
    //Can't create or open file
    if (!File.is_open()) {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    //Lambda functional object for save one user
    auto Saver = [&File](shared_ptr<User> Ptr){File << *Ptr << endl;};
    //Save the users count to the begin of the file, fist of all
    File << m_All.size() << endl;
    //traversal for save all users' data
    for_each(m_All.begin(), m_All.end(),Saver);
    //close means save to physical file system
    File.close();
}

//Static function to read and create all users from the specified file, including administrator
//If the file can't be opend, the try to create the file
//If the file can't be create, the invalid_argument exception will be thrown
void User::LoadFromFile(const string& FileName){
    //try to open file
    ifstream File(FileName);
    //can't open
    if (!File.is_open()) {
        //try to create a file by FileName
        ofstream NewFile(FileName);
        //can't create file
        if (!NewFile.is_open()) {
            throw invalid_argument("Can't open/create for loading, file: " + FileName);
        }
        //write zero to users' count in file
        NewFile << 0 << endl;
        //close means save to physical file system
        NewFile.close();
        
        //open the new File
        File.open(FileName);
    }
    unsigned long UserCount;
    //get the users' count from the file
    File >> UserCount;
    //drop the endl after the users' count
    File.get();
    //Clear all users
    m_All.clear();
    //Zero user, then create the administrator by default name and password;
    if (UserCount < 1) {
        new Administrator{};
    }
    //at least one user
    else{
        //dynamic create the administrator by default name and password;
        new Administrator{};
        //then update the administrator from file stream
        File >> *(*(m_All.end() - 1));
        //for each user
        for (unsigned long i = 0; i < UserCount - 1; i++) {
            //dynamic create an user by empty name and simple password;
            new User{string{""}, CipherText{"123456"}};;
            //then update the user from file stream
            File >> *(*(m_All.end() - 1));
        }
    }
    //close file
    File.close();
}

//static function to verify the specified user by user name and password.
//the user name does not exist, an ExecptionNoUser will be thrown
//the user exists but the password is wrong, an ExecptionWrongPassword will be thrown
//the return value is the smart pointer to the user object
shared_ptr<User> User::Verify(const string& Name, const string& Password){
    //Lambda functional object for name comparision
    auto Finder = [&Name](shared_ptr<User> ptr)->bool{return (ptr->m_Name == Name);};
    //To find out the first user specified by name
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    //not found, throw NO USER excption
    if (it == m_All.end()) {
        throw ExecptionNoUser();
    }
    //found，but wrong password, throw WRONG PASSWORD exception
    else if ((*it)->m_Password != Password){
        throw ExecptionWrongPassword();
    }
    //return the user's smart pointer
    else {
        return *it;
    }
}

//---- STATIC MEMBER FUNCTIONS END ---//
