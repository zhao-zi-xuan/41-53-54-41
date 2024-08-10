//
//  ControlerBase.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/7.
//

#ifndef ControlerBase_hpp
#define ControlerBase_hpp

#include "../Models/User.hpp"
#include "../Models/Administrator.hpp"
#include "../Models/MD5.hpp"
#include "../Models/CipherText.hpp"
#include "../Models/Date.hpp"
#include "../Models/Time.hpp"
#include "../Models/DateTime.hpp"
#include "../Models/Message.hpp"
#include <string>
using namespace std;

//marco trick
#define enum_to_string(x) #x

//the return values of controler's functions
enum class ControlerRet{
    NO_USER,
    WRONG_PASSWORD,
    ADMIN_LOGINED,
    USER_LOGINED,
    NO_RIGHTS_CREATE_USER,
    USER_CREATED,
    DUPLICATE_USER,
    DUPLICATE_ADMIN,
    INVALID_DATE,
    INVALID_TIME,
    TITLE_EMPTY,
    CONTENT_EMPTY,
    MESSAGE_SUBMIT_OK,
    SEARCH_OK,
    UNKNOWN_TYPE
};

//shorter type name
using RES = ControlerRet;

//the return value strings of controler's functions
const string ResStr[] {
  enum_to_string(NO_USER),
  enum_to_string(WRONG_PASSWORD),
  enum_to_string(ADMIN_LOGINED),
  enum_to_string(USER_LOGINED),
  enum_to_string(NO_RIGHTS_CREATE_USER),
  enum_to_string(USER_CREATED),
  enum_to_string(DUPLICATE_USER),
  enum_to_string(DUPLICATE_ADMIN),
  enum_to_string(INVALID_DATE),
  enum_to_string(INVALID_TIME),
  enum_to_string(TITLE_EMPTY),
  enum_to_string(CONTENT_EMPTY),
  enum_to_string(MESSAGE_SUBMIT_OK),
  enum_to_string(SEARCH_OK),
  enum_to_string(UNKNOWN_TYPE)
};

//search result type
struct SearchRes{
    unsigned int CountOfWords;
    unsigned int CountOfActions;
    unsigned int CountOfThoughts;
    vector<string> Messages;
};

//abstract class of controler
class ControlerAbstractBase{
public:
    //constructor, load users and messages from files
    ControlerAbstractBase(const string& UserFileName, const string& MessageFileName);
    //destructor, save users and messages to files
    virtual ~ControlerAbstractBase();

    //----------------------------------------------------------------------------------
    //NOTE: CONTROLER IS A SOFTWARE, WITHOUT USER INTERFACE(Window, dialog, console...)
    //----------------------------------------------------------------------------------

    //login
    RES Login(const string& UserName, const string& PassWord);
    //create new user
    RES CreateNewUser(const string& UserName, const string& PassWord) const;
    //Submit message
    RES SumbitMessage(unsigned int Year, unsigned int Month,  unsigned int Day,
                      unsigned int Hour, unsigned int Minute, unsigned int Second,
                      const string& Title, const string& Content, const string& TypeStr) const;
protected:
    //inner search reslut type
    struct MessageSearchRes{
        unsigned int CountOfWords;
        unsigned int CountOfActions;
        unsigned int CountOfThoughts;
        vector<shared_ptr<Message>> Messages;
    };

    //DO search, can called form derrived controlers
    RES SearchMessageBetween_inner(unsigned int Year1, unsigned int Month1,  unsigned int Day1,
                             unsigned int Hour1, unsigned int Minute1, unsigned int Second1,
                             unsigned int Year2, unsigned int Month2,  unsigned int Day2,
                             unsigned int Hour2, unsigned int Minute2, unsigned int Second2,
                             MessageSearchRes& SearchResult) const;

    //pure virtual functions, must be implemented in derrived controler class
    //how to convert string to message type, different in GUI design
    virtual enum Message::Type StrToMessageType(const string& TypeStr)  const = 0;
    //how to convert message to string, different in GUI design
    virtual string MessageToString(const shared_ptr<Message>& Message)  const = 0;

private:
    //file names
    string m_UsersFileName;
    string m_MessagesFileName;

    //logined user
    shared_ptr<User> m_pLoginedUser = nullptr;
};


#endif /* ControlerBase_hpp */
