//
//  ControlerBase.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/7.
//

#include "ControlerAbstractBase.hpp"

//----------------------------------------------------------------------------------
//NOTE: CONTROLER IS A SOFTWARE, WITHOUT USER INTERFACE(Window, dialog, console...)
//----------------------------------------------------------------------------------


//constructor, load users and messages from files
ControlerAbstractBase::ControlerAbstractBase(const string& UserFileName, const string& MessageFileName){
    m_UsersFileName = UserFileName;
    m_MessagesFileName = MessageFileName;
    User::LoadFromFile(m_UsersFileName);
    Message::LoadFromFile(m_MessagesFileName);
}

//destructor, save users and messages to files
ControlerAbstractBase::~ControlerAbstractBase() {
    User::SaveToFile(m_UsersFileName);
    Message::SaveToFile(m_MessagesFileName);
}

//login
RES ControlerAbstractBase::Login(const string& UserName, const string& PassWord) {
    try {
        m_pLoginedUser = User::Verify(UserName, PassWord);
    }
    catch(ExecptionNoUser e) {
        return ControlerRet::NO_USER;
    }
    catch(ExecptionWrongPassword e) {
        return ControlerRet::WRONG_PASSWORD;
    }
    if (m_pLoginedUser->IsAdministrator()) {
        return ControlerRet::ADMIN_LOGINED;
    }
    else {
        return ControlerRet::USER_LOGINED;
    }
}

//Create new user
RES ControlerAbstractBase::CreateNewUser(const string& UserName, const string& PassWord)  const{
    //only administrator can create new user
    if (!m_pLoginedUser->IsAdministrator()) {
        return RES::NO_RIGHTS_CREATE_USER;
    }
    try {
        shared_ptr<Administrator> ptrAdmin = dynamic_pointer_cast<Administrator>(m_pLoginedUser);
        ptrAdmin->Add(UserName, CipherText(PassWord));
    }
    catch (ExecptionUserExists e){
        return RES::DUPLICATE_USER;
    }
    catch (ExecptionAdministratorExists e){
        return RES::DUPLICATE_ADMIN;
    }
    return RES::USER_CREATED;
}

//Submit message
RES ControlerAbstractBase::SumbitMessage(unsigned int Year, unsigned int Month,  unsigned int Day,
                                         unsigned int Hour, unsigned int Minute, unsigned int Second,
                                         const string& Title, const string& Content, const string& TypeStr) const {

    try {
        DateTime Time(Year, Month, Day, Hour, Minute, Second);
        enum Message::Type Type = StrToMessageType(TypeStr);
        Message::Add(Time, Title, Content, Type);
    }
    catch (invalid_argument e) {
        if (e.what() == string("Is not valid date")) {
            return RES::INVALID_DATE;
        }
        else if (e.what() == string("Hour should be 0~23.")) {
            return RES::INVALID_TIME;
        }
        else if (e.what() == string("Minute should be 0~59.")) {
            return RES::INVALID_TIME;
        }
        else if (e.what() == string("Second should be 0~59.")) {
            return RES::INVALID_TIME;
        }
        else if (e.what() == string("Title is empty.")) {
            return RES::TITLE_EMPTY;         //"Title is empty."
        }
        else if (e.what() == string("Content is empty.")) {
            return RES::CONTENT_EMPTY;
        }
        else  {
            return RES::UNKNOWN_TYPE;
        }
    }
    return ControlerRet::MESSAGE_SUBMIT_OK;
    
}

//DO search, can called form derrived controlers
RES ControlerAbstractBase::SearchMessageBetween_inner(unsigned int Year1, unsigned int Month1,  unsigned int Day1,
                                                      unsigned int Hour1, unsigned int Minute1, unsigned int Second1,
                                                      unsigned int Year2, unsigned int Month2,  unsigned int Day2,
                                                      unsigned int Hour2, unsigned int Minute2, unsigned int Second2,
                                                      MessageSearchRes& SearchResult)  const{
    
    try {
        //no keywords
        vector<string> NoKeyWords;
        //DoSearch
        vector<shared_ptr<Message>> Messages = Message::Search(
            //Time range
            DateTime::Between(DateTime(Year1, Month1, Day1, Hour1, Minute1, Second1),
                              DateTime(Year2, Month2, Day2, Hour2, Minute2, Second2)),
            //no keywords
            NoKeyWords,
            //ASCENDING, by time
            Message::SortType::TIME_ASCENDING);
        //Clear search result
        SearchResult.Messages = Messages;
        SearchResult.CountOfWords    = 0;
        SearchResult.CountOfActions  = 0;
        SearchResult.CountOfThoughts = 0;

        //count to search result, in types
        auto Counter = [&](const shared_ptr<Message>& ptr) {
            if (ptr->Type == Message::Type::WORD) {
                SearchResult.CountOfWords++;
            }
            else if (ptr->Type == Message::Type::ACTION) {
                SearchResult.CountOfActions++;
            }
            else  {
                SearchResult.CountOfThoughts++;
            }
        };
        for_each(Messages.begin(), Messages.end(), Counter);
    }
    catch (invalid_argument e) {
        if (e.what() == string("Is not valid date")) {
            return RES::INVALID_DATE;
        }
        else if (e.what() == string("Hour should be 0~23.")) {
            return RES::INVALID_TIME;
        }
        else if (e.what() == string("Minute should be 0~59.")) {
            return RES::INVALID_TIME;
        }
        else if (e.what() == string("Second should be 0~59.")) {
            return RES::INVALID_TIME;
        }
        else if (e.what() == string("Title is empty.")) {
            return RES::TITLE_EMPTY;
        }
        else if (e.what() == string("Content is empty.")) {
            return RES::CONTENT_EMPTY;
        }
        else  {
            return RES::UNKNOWN_TYPE;
        }
    }
    return RES::SEARCH_OK;
}


