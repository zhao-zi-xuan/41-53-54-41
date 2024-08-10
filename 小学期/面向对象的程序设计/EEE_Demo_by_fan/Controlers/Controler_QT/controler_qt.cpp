#include "controler_qt.h"
#include <sstream>

//implement for QT GUI, overriding to non-pure virtual fuction
//Word, Action, Though, type string to enum type value
enum Message::Type Controler_QT::StrToMessageType(const string& TypeStr)  const{
    if (TypeStr == "Word") {
        return Message::Type::WORD;
    }
    else if (TypeStr == "Action") {
        return Message::Type::ACTION;
    }
    else if (TypeStr == "Thought") {
        return Message::Type::THOUGHT;
    }
    else {
        throw invalid_argument(TypeStr + " is unknown type");
    }
}

//implement for QT GUI, overriding to non-pure virtual fuction
//each message to 2 lines string:
//DateTime  [type]  title
//content
string Controler_QT::MessageToString(const shared_ptr<Message>& Message) const{
    stringstream Stream;
    Stream << Message->Time << '\t' << '(';
    if (Message->Type == Message::Type::WORD) {
        Stream << "Word";
    }
    else if (Message->Type == Message::Type::WORD) {
        Stream << "Action";
    }
    else {
        Stream << "Though";
    }
    Stream << ')'<< '\t'<<Message->Title << endl << Message->Content;
    return Stream.str();
}

//Search for QT GUI
RES Controler_QT::SearchMessageBetween(unsigned int Year1, unsigned int Month1,  unsigned int Day1,
                         unsigned int Hour1, unsigned int Minute1, unsigned int Second1,
                         unsigned int Year2, unsigned int Month2,  unsigned int Day2,
                         unsigned int Hour2, unsigned int Minute2, unsigned int Second2,
                         SearchRes& SearchResult) const{
    MessageSearchRes MRes;
    //call inner search
    RES Res = SearchMessageBetween_inner(Year1, Month1, Day1, Hour1, Minute1, Second1,
                                         Year2, Month2, Day2, Hour2, Minute2, Second2,
                                         MRes);
    //copy counter
    SearchResult.CountOfWords = MRes.CountOfWords;
    SearchResult.CountOfActions = MRes.CountOfActions;
    SearchResult.CountOfThoughts = MRes.CountOfThoughts;
    //clear
    SearchResult.Messages.clear();

    //translate each message to string ,via MessageToString function
    auto Translater = [&](const shared_ptr<Message> ptr) {SearchResult.Messages.push_back(MessageToString(ptr));};
    for_each(MRes.Messages.begin(), MRes.Messages.end(), Translater);

    return Res;
}
