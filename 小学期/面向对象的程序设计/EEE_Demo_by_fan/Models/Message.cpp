//
//  Message.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/6.
//

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "Message.hpp"
using namespace std;

//out class definition, A list of smart pointers to all message objects
vector<shared_ptr<Message>> Message::m_All{};

//destructor, not used
Message::~Message(){
}

//check value and set to private member,
void Message::UpdateTitle(const string& Title){
    if (Title.empty()) {
        throw invalid_argument(string("Title is empty."));
    }
    m_Title = Title;
}

//check value and set to private member
void Message::UpdateContent(const string& Content){
    if (Content.empty()) {
        throw invalid_argument("Content is empty.");
    }
    m_Content = Content;
}

//check value and set to private member
void Message::UpdateType(enum Type Type){
    switch (Type) {
        case Type::WORD :
        case Type::ACTION :
        case Type::THOUGHT :
            m_Type = Type;
            break;
        default:
            throw invalid_argument("Unknown message type");
    }
}

//overlading relationship operators
bool Message::operator==(const Message& aMessage) const{
    return (Time == aMessage.Time) && (Title == aMessage.Title) && (Content == aMessage.Content);
}

bool Message::operator!=(const Message& aMessage) const{
    return !operator==(aMessage);
}

//overloading stream insertion(extraction) operators
ostream& operator<<(ostream& Stream, const Message& aMessage){
    Stream << aMessage.m_Time << endl;
    Stream << aMessage.m_Title << endl;
    Stream << aMessage.m_Content << endl;
    switch (aMessage.Type) {
        case Message::Type::WORD :
            Stream << "WORD";
            break;
        case Message::Type::ACTION :
            Stream << "ACTION";
            break;
        case Message::Type::THOUGHT :
            Stream << "THOUGHT";
            break;
    }
    return Stream;
}

istream& operator>>(istream& Stream, Message& aMessage){
    string TypeStr;
    Stream >> aMessage.m_Time;
    Stream.get();
    getline(Stream, aMessage.m_Title);
    getline(Stream, aMessage.m_Content);
    getline(Stream, TypeStr);

    if (TypeStr == "WORD") {
        aMessage.UpdateType(Message::Type::WORD);
    }
    else if(TypeStr == "ACTION"){
        aMessage.UpdateType(Message::Type::ACTION);
    }
    else if (TypeStr == "THOUGHT") {
        aMessage.UpdateType(Message::Type::THOUGHT);
    }
    else {
        throw invalid_argument(TypeStr + " is an unknown message type");
    }
    return Stream;
}

//class function(static, no object's function) to Add a Message object
void Message::Add(const DateTime& Time, const string& Title, const string& Content, enum Type Type){
    new Message(Time, Title, Content, Type);
}

//class function(static, no object's function) to Add a Message object, via it's pointer
void Message::Delete(shared_ptr<Message> ToDelete){
    auto Finder = [=](shared_ptr<Message> Current)->bool {return *ToDelete == *Current;};
    remove_if(m_All.begin(), m_All.end(), Finder);
}

//class function(static, no object's function) to read and create all  messages from the specified file
void Message::LoadFromFile(const string& FileName){
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
        //write zero to Messages'count in file
        NewFile << 0 << endl;
        //close means save to physical file system
        NewFile.close();
        
        //open the new File
        File.open(FileName);
    }
    unsigned long MessageCount;
    //get the messagess'count from the file
    File >> MessageCount;
    //drop the endl after the messages'count
    File.get();
    //Clear all messages
    m_All.clear();
    for (unsigned long i = 0; i < MessageCount; i++) {
        //dynamic create a message;
        new Message{DateTime(1, 1, 1, 0, 0, 0),"1", "1", Type::WORD};
        //then update the message from file stream
        File >> *(*(m_All.end() - 1));
    }
    //close file
    File.close();
}

//class function(static, no object's function) to save all users to the specified file, including derived objects
void Message::SaveToFile(const string& FileName){
    //Open or create the file specified by FileName
    ofstream File(FileName);
    //Can't create or open file
    if (!File.is_open()) {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    //Lambda functional object for save one user
    auto Saver = [&File](shared_ptr<Message> Ptr){File << *Ptr << endl;};
    //Save the messages'count to the begin of the file, fist of all
    File << m_All.size() << endl;
    //traversal for save all messages'data
    for_each(m_All.begin(), m_All.end(), Saver);
    //close means save to physical file system
    File.close();
}

//class functions(static, no object's function) to search message, according to Range, Keywords and sort type
vector<shared_ptr<Message>> Message::Search(const DateTimeRange& Range, const vector<string>& KeyWords, SortType Sortby){
    vector<shared_ptr<Message>> Res;
    Filter aFilter{Range, KeyWords};
    // iterative search, in all messages
    auto it = m_All.begin();
    while(it != m_All.end()) {
        it = find_if(it, m_All.end(), aFilter);
        if (it != m_All.end()) {
            Res.push_back(*it);
            it++;
        }
    }

    //sort the filtered message
    Sorter aSorter{Sortby};
    sort(Res.begin(), Res.end(), aSorter);
    return Res;
}

//class functions(static, no object's function) to search message, according to Range, Keywords and sort type
vector<shared_ptr<Message>> Message::Search(const DateTimeRange& Range, SortType SortBy){
    vector<string> NoKeyWords;
    return Search(Range, NoKeyWords, SortBy);
}

//class functions(static, no object's function) to search message, according to Range and sort type
vector<shared_ptr<Message>> Message::Search(const vector<string>& KeyWords, SortType SortBy){
    return Search(DateTime::All(), KeyWords, SortBy);
}

//class functions(static, no object's function) to search message, according to Keywords and sort type
Message::Message(const DateTime& AddTime, const string& Title, const string& Content, enum Type Type): Time(m_Time), Title(m_Title), Content(m_Content), Type(m_Type), m_Time(AddTime){
    UpdateTitle(Title);
    UpdateContent(Content);
    UpdateType(Type);
    m_All.push_back(shared_ptr<Message>(this));
}

//private inner class constructor
Message::Filter::Filter(const DateTimeRange& Range, const vector<string>& KeyWords){
    m_DateTimeRange = Range;
    m_KeyWords = KeyWords;
}

//overloading operator()
bool Message::Filter::operator()(const shared_ptr<Message>& pMessage){
    //time range
    if (pMessage->Time < m_DateTimeRange.first || pMessage->Time > m_DateTimeRange.second) {
        return false;
    }
    //keywors match
    if (m_KeyWords.empty()) {
        return true;
    }
    else {
        //match keyword in title and content
        auto Matcher = [&](const string& Key)->bool {return pMessage->Title.find(Key) != string::npos || pMessage->Content.find(Key) != string::npos;};
        //count match records
        unsigned int KeyWordsCounter = (unsigned int)count_if(m_KeyWords.begin(), m_KeyWords.end(), Matcher);
        //at least one match
        return KeyWordsCounter != 0;
    }
}

//private inner class constructor
Message::Sorter::Sorter(SortType SortBy){
    m_SortBy = SortBy;
}

//overloading operator()
bool Message::Sorter::operator()(const shared_ptr<Message>& pMessage1, const shared_ptr<Message>& pMessage2){
    switch (m_SortBy) {
        case SortType::TIME_ASCENDING :
            return pMessage1->Time < pMessage2->Time;
        case SortType::TIME_DESCENDING :
            return pMessage1->Time > pMessage2->Time;
        case SortType::TITLE_ASCENDING :
            return pMessage1->Title < pMessage2->Title;
        case SortType::TITLE_DESCENDING :
            return pMessage1->Title > pMessage2->Title;
        default:
            return true;
    }
}

