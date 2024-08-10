//
//  Time.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/5.
//

#ifndef Time_hpp
#define Time_hpp

#include <iostream>
using namespace std;

class Time{
public:
    //constructor with parameters, and default values
    Time(unsigned int Hour = 0, unsigned int Minute = 0, unsigned int Second = 0);
    //copy constructor
    Time(const Time& aTime);
    //default assigmnet operator
    Time& operator=(const Time& aTime);
    //destructor, not used
    ~Time();
    
    //check values and set to private members
    void Set(unsigned int Hour, unsigned int Minute, unsigned int Second);
    //check value and set to private member
    void SetHour(unsigned int Hour);
    //check value and set to private member
    void SetMinute(unsigned int Minute);
    //check value and set to private member
    void SetSecond(unsigned int Second);
    
    //return the Seconds'count from 00:00:00, 00:00:00 is the first(1, not 0) second
    unsigned int InSeconds() const;
    
    //overlading relationship operators
    bool operator> (const Time& aTime) const;
    bool operator< (const Time& aTime) const;
    bool operator>=(const Time& aTime) const;
    bool operator<=(const Time& aTime) const;
    bool operator==(const Time& aTime) const;
    bool operator!=(const Time& aTime) const;
    
    //overloading increment operators, to increase one second
    //++23:59:50 is 00:00:00
    Time& operator++();
    Time  operator++(int);
    //overloading decrement operators, to decrease one second
    //--00:00:00 is 23:59:50
    Time& operator--();
    Time  operator--(int);
    
    //return days'count between two time, 00:00:01-00:00:00 is 1, 00:00:00-00:00:01 is -1
    long long operator-(const Time& aTime) const;
    
    //overloading stream insertion(extraction) operators
    friend ostream& operator<<(ostream& Stream, const Time& aTime);
    friend istream& operator>>(istream& Stream, Time& aTime);
    
    //class function(static, no object's function) to get a Time object means now time
    static Time Now();
    
    //data members'const references, read only
    const unsigned int& Hour;
    const unsigned int& Minute;
    const unsigned int& Second;
    
    //00:00:00
    static const Time MIN_TIME;
    //23:59:59
    static const Time MAX_TIME;
    
private:
    //data members
    unsigned int m_uHour;
    unsigned int m_uMinute;
    unsigned int m_uSecond;
};

#endif /* Time_hpp */
