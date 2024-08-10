//
//  Message.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/6.
//

#ifndef Message_hpp
#define Message_hpp

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "DateTime.hpp"
using namespace std;


class Message {
public:
    //default constructor, copy constructor and assignment operator are not allowed
    Message() = delete;
    Message(const Message&) = delete;
    Message& operator=(const Message&) = delete;
    //destructor, not used
    ~Message();

    //check value and set to private member
    void UpdateTitle(const string& Title);
    //check value and set to private member
    void UpdateContent(const string& Content);
    //inner type class
    enum class Type{WORD, ACTION, THOUGHT};
    //check value and set to private member
    void UpdateType(enum Type Type);

    //overlading relationship operators
    bool operator==(const Message& aMessage) const;
    bool operator!=(const Message& aMessage) const;

    //overloading stream insertion(extraction) operators
    friend ostream& operator<<(ostream& Stream, const Message& aMessage);
    friend istream& operator>>(istream& Stream, Message& aMessage);

    //class function(static, no object's function) to Add a Message object
    static void Add(const DateTime& Time, const string& Title, const string& Content, enum Type Type);
    //class function(static, no object's function) to Add a Message object, via it's pointer
    static void Delete(shared_ptr<Message> ToDelete);

    //class function(static, no object's function) to read and create all  messages from the specified file
    static void LoadFromFile(const string& FileName);
    //class function(static, no object's function) to save all users to the specified file, including derived objects
    static void SaveToFile(const string& FileName);

    //inner sort type class
    enum class SortType {ORIGINAL, TIME_ASCENDING, TIME_DESCENDING, TITLE_ASCENDING, TITLE_DESCENDING};

    //class functions(static, no object's function) to search message, according to Range, Keywords and sort type
    static vector<shared_ptr<Message>> Search(const DateTimeRange& Range, const vector<string>& KeyWords, SortType Sortby = SortType::ORIGINAL);
    //class functions(static, no object's function) to search message, according to Range and sort type
    static vector<shared_ptr<Message>> Search(const DateTimeRange& Range, SortType SortBy = SortType::ORIGINAL);
    //class functions(static, no object's function) to search message, according to Keywords and sort type
    static vector<shared_ptr<Message>> Search(const vector<string>& KeyWords, SortType SortBy = SortType::ORIGINAL);

    //data members'const references, read only
    const DateTime& Time;
    const string& Title;
    const string& Content;
    const enum Type& Type;

private:
    //Message objects can only be dynamically instantiated through the new operator
    //When messages are created, their pointers are automatically saved to the list of all messages
    Message(const DateTime& AddTime, const string& Title, const string& Content, enum Type Type);

    //private inner class, an functional object to filter messages in many ways
    class Filter{
    public:
        Filter(const DateTimeRange& Range, const vector<string>& KeyWords);
        bool operator()(const shared_ptr<Message>& pMessage);
    private:
        DateTimeRange m_DateTimeRange;
        vector<string> m_KeyWords;
    };

    //private inner class, an functional object to sort messages in many ways
    class Sorter{
    public:
        Sorter(SortType SortBy);
        bool operator()(const shared_ptr<Message>& pMessage1, const shared_ptr<Message>& pMessage2);
    private:
        SortType m_SortBy;
    };

    //data members
    DateTime m_Time;
    string m_Title;
    string m_Content;
    enum Type m_Type;

    //A list of smart pointers to all message objects
    static vector<shared_ptr<Message>> m_All;
};
#endif /* Message_hpp */
