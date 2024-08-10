//
//  Controler_CommandLine.hpp
//  CommandLine_Demo
//
//  Created by Jingtao Fan on 2021/8/8.
//

#ifndef Controler_CommandLine_hpp
#define Controler_CommandLine_hpp

#include "ControlerAbstractBase.hpp"

//controler class for CommandLine
class Controler_CommandLine : public ControlerAbstractBase
{
public:
    //using base class'constructor as own, C++11 feature
    using ControlerAbstractBase::ControlerAbstractBase;
    //implement for CommandLine, overriding to non-pure virtual fuction
    enum Message::Type StrToMessageType(const string& TypeStr)  const override;
    //implement for CommandLine, overriding to non-pure virtual fuction
    string MessageToString(const shared_ptr<Message>& Message)  const override;
    //Search for CommandLine
    RES SearchMessageBetween(unsigned int Year1, unsigned int Month1,  unsigned int Day1,
                             unsigned int Hour1, unsigned int Minute1, unsigned int Second1,
                             unsigned int Year2, unsigned int Month2,  unsigned int Day2,
                             unsigned int Hour2, unsigned int Minute2, unsigned int Second2,
                             SearchRes& SearchResult) const;

};

#endif /* Controler_CommandLine_hpp */
