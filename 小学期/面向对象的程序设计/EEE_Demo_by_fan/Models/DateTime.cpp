//
//  DateTime.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/5.
//

#include <cstdint>
#include "DateTime.hpp"

//out class definition
//0001-01-01 00:00:00
const DateTime DateTime::MIN_DATETIME = DateTime(Date(1, 1, 1), Time(0, 0, 0));
//the end of universe
const DateTime DateTime::MAX_DATETIME = DateTime(Date(UINT32_MAX, 12, 31), Time(23, 59, 59));

//constructor with parameters, and default values
DateTime::DateTime(const Date& aDate, const Time& aTime):Date(aDate), Time(aTime){
}

//constructor with parameters
DateTime::DateTime(unsigned int Year, unsigned int Month, unsigned int Day, unsigned int Hour, unsigned int Minute, unsigned int Second) : Date(Year, Month, Day), Time(Hour, Minute, Second){
}

//overlading relationship operators
bool DateTime::operator  >(const DateTime& aDateTime) const{
    return (this->Date::operator>(aDateTime)) || (this->Date::operator==(aDateTime) && this->Time::operator>(aDateTime));
}

bool DateTime::operator  <(const DateTime& aDateTime) const{
    return (this->Date::operator<(aDateTime)) || (this->Date::operator==(aDateTime) && this->Time::operator<(aDateTime));
}

bool DateTime::operator >=(const DateTime& aDateTime) const {
    return operator>(aDateTime) || operator==(aDateTime);
}

bool DateTime::operator <=(const DateTime& aDateTime) const {
    return operator<(aDateTime) || operator==(aDateTime);
}

bool DateTime::operator ==(const DateTime& aDateTime) const {
    return (this->Date::operator==(aDateTime) && this->Time::operator==(aDateTime));
}

bool DateTime::operator !=(const DateTime& aDateTime) const {
    return !operator==(aDateTime);
}

//overloading increment operators, to increase one second
DateTime& DateTime::operator++() {
    this->Time::operator++();
    if (this->Time::Hour == 0 && this->Time::Minute == 0 && this->Time::Second == 0) {
        this->Date::operator++();
    }
    return *this;
}

DateTime DateTime::operator++(int){
    //call prefix operator++
    DateTime Res{*this};
    ++(*this);
    return Res;
}

//overloading decrement operators, to decrease one second
DateTime& DateTime::operator--() {
    this->Time::operator--();
    if (this->Time::Hour == 23 && this->Time::Minute == 59 && this->Time::Second == 59) {
        this->Date::operator--();
    }
    return *this;
}

DateTime DateTime::operator--(int) {
    //call prefix operator--
    DateTime Res{*this};
    --(*this);
    return Res;
}

//overloading stream insertion(extraction) operators
ostream& operator<<(ostream& Stream, const DateTime& aDateTime) {
    Stream << static_cast<const Date&>(aDateTime)
           << ' '
           << static_cast<const Time&>(aDateTime);
    return Stream;
}

istream& operator>>(istream& Stream, DateTime& aDateTime) {
    Stream >> static_cast<Date&>(aDateTime) //space is not need to jump
           >> static_cast<Time&>(aDateTime);
    return Stream;
}

//return seconds'count between two datetime
long long DateTime::operator-(const DateTime& aDateTime) const {
    return this->Date::operator-(aDateTime) * 3600 * 24 + this->Time::operator-(aDateTime);
}

//class function(static, no object's function) to get a DateTime object means today and now time;
DateTime DateTime::Now(){
    auto tp = chrono::system_clock::now();
    time_t cur_time = chrono::system_clock::to_time_t(tp);
    struct tm* pTimeInfo = localtime(&cur_time);
    return DateTime(pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday, pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
}

//class function(static, no object's function) to get a DateTimeRange object between two datetimes
DateTimeRange DateTime::Between(const DateTime& Begin, const DateTime& End){
    return make_pair(Begin, End);
}

//class function(static, no object's function) to get a DateTimeRange object From a datetime to the end of universe
DateTimeRange DateTime::From(const DateTime& Begin){
    return make_pair(Begin, DateTime::MAX_DATETIME);
}

//class function(static, no object's function) to get a DateTimeRange object From AD to a datetime
DateTimeRange DateTime::Until(const DateTime& End){
    return make_pair(DateTime::MIN_DATETIME, End);
}

//class function(static, no object's function) to get a DateTimeRange object From AD to to the end of universe
DateTimeRange DateTime::All(){
    return make_pair(DateTime::MIN_DATETIME, DateTime::MAX_DATETIME);

}
