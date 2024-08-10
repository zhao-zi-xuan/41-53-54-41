//
//  Time.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/5.
//

#include <stdexcept>
//three c++ stdlib for time types and functions
#include <ratio>
#include <chrono>
#include <ctime>

#include "Time.hpp"
using namespace std;

//static member, out class definition
//00:00:00
const Time Time::MIN_TIME = Time(0, 0, 0);
//23:59:59
const Time Time::MAX_TIME = Time(23,59, 59);

//constructor with parameters
Time::Time(unsigned int Hour, unsigned int Minute, unsigned int Second) : Hour(m_uHour), Minute(m_uMinute), Second(m_uSecond){
    Set(Hour, Minute, Second);
}

//copy constructor
Time::Time(const Time& aTime) : Hour(m_uHour), Minute(m_uMinute), Second(m_uSecond){
    Set(aTime.Hour, aTime.Minute, aTime.Second);
}

//default assigmnet operator
Time& Time::operator=(const Time& aTime) {
    //to avoid a = a;
    if (this != &aTime) {
        Set(aTime.Hour, aTime.Minute, aTime.Second);
    }
    return *this;
}

//destructor, not used
Time::~Time() {
}

//check values and set to privte members
void Time::Set(unsigned int Hour, unsigned int Minute, unsigned int Second) {
    SetHour(Hour);
    SetMinute(Minute);
    SetSecond(Second);
}

//check value and set to privte member, or, throw exception
void Time::SetHour(unsigned int Hour) {
    if (Hour >= 24) {
        throw invalid_argument("Hour should be 0~23.");
    }
    m_uHour = Hour;
}

//check value and set to privte member, or, throw exception
void Time::SetMinute(unsigned int Minute) {
    if (Minute >= 60) {
        throw invalid_argument("Minute should be 0~59.");
    }
    m_uMinute = Minute;
}

//check value and set to privte member, or, throw exception
void Time::SetSecond(unsigned int Second) {
    if (Second >= 60) {
        throw invalid_argument("Second should be 0~59.");
    }
    m_uSecond = Second;
}

//return the Seconds'count from 00:00:00, 00:00:00 is the first(1, not 0) second
unsigned int Time::InSeconds() const{
    return (m_uHour * 3600u + m_uMinute * 60u + m_uSecond) + 1;
}

//overlading relationship operators
bool Time::operator> (const Time& aTime) const {
    return InSeconds() > aTime.InSeconds();
}

bool Time::operator< (const Time& aTime) const {
    return InSeconds() < aTime.InSeconds();
}

bool Time::operator>=(const Time& aTime) const {
    return InSeconds() >= aTime.InSeconds();
}

bool Time::operator<=(const Time& aTime) const {
    return InSeconds() <= aTime.InSeconds();
}

bool Time::operator==(const Time& aTime) const {
    return (m_uHour == aTime.Hour) && (m_uMinute == aTime.Minute) && (m_uSecond == aTime.Second);
}

bool Time::operator!=(const Time& aTime) const {
    return (m_uHour != aTime.Hour) || (m_uMinute != aTime.Minute) || (m_uSecond != aTime.Second);
}

//overloading increment operators, to increase one second
//++23:59:50 is 00:00:00
Time& Time::operator++() {
    if (InSeconds() == Time(23, 59, 59).InSeconds()) {
        m_uHour = 0;
        m_uMinute = 0;
        m_uSecond = 0;
    }
    else {
        unsigned int NewInSeconds = InSeconds() + 1;
        //second
        m_uSecond = NewInSeconds % 60;
        //minute
        NewInSeconds /= 60;
        m_uMinute = NewInSeconds % 60;
        //hour
        m_uHour = NewInSeconds / 60;
    }
    return *this;
}

Time Time::operator++(int) {
    //call prefix operator++
    Time Res = *this;
    ++(*this);
    return Res;
}

//overloading decrement operators, to decrease one second
//--00:00:00 is 23:59:50
Time& Time::operator--() {
    if (InSeconds() == 0) {
        m_uHour = 23;
        m_uMinute = 59;
        m_uSecond = 59;
    }
    else {
        unsigned int NewInSeconds = InSeconds() - 1;
        //second
        m_uSecond = NewInSeconds % 60;
        //minute
        NewInSeconds /= 60;
        m_uMinute = NewInSeconds % 60;
        //hour
        m_uHour = NewInSeconds / 60;
    }
    return *this;
}

Time Time::operator--(int) {
    //call prefix operator--
    Time Res = *this;
    --(*this);
    return Res;
}

//return seconds'count between two time, 00:00:01-00:00:00 is 1, 00:00:00-00:00:01 is -1,
long long Time::operator-(const Time& aTime) const {
    return static_cast<long long>(InSeconds()) - static_cast<long long>(aTime.InSeconds());
}

//overloading stream insertion(extraction) operators
ostream& operator<<(ostream& Stream, const Time& aTime) {
    Stream << aTime.m_uHour << ':' << aTime.m_uMinute << ':' << aTime.m_uSecond;
    return Stream;
}

istream& operator>>(istream& Stream, Time& aTime) {
    char Temp;
    Stream >> aTime.m_uHour   >> Temp //jump first  ':'
           >> aTime.m_uMinute >> Temp //jump second ':'
           >> aTime.m_uSecond;
    return Stream;
}

//class function(static, no object's function) to get a Time object means now time;
Time Time::Now() {
    auto tp = chrono::system_clock::now();
    time_t cur_time = chrono::system_clock::to_time_t(tp);
    struct tm* pTimeInfo = localtime(&cur_time);
    return Time(pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
}
