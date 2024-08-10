//
//  Date.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/5.
//

#include <cstdint>
#include "Date.hpp"

//out class definition

//0001-01-01
const Date Date::MIN_DATE = Date(1, 1, 1);
//UINT32_MAX-12-31
const Date Date::MAX_DATE = Date(UINT32_MAX, 12, 31);

//day is each month
//DayInMonth[0][1~12], not leap year
//DayInMonth[1][1~12], leap year
const unsigned int Date::DaysInMonth[2][13] = {
    {0u, 31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u},
    {0u, 31u, 29u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u}
};

//YEAR 1582
//Pope Gregor VIII issued a decree on February 24, 1582, permanently erasing the period from October 5, 1582 to October 14, 1582. There have never been these 10 days in history. October 4, 1582 is Thursday, and its next day is Friday, October 15, 1582.
//Before this year, there was a leap year every four years; After that, people used the current method of calculating leap years
const unsigned int Date::GrigoreyYear = 1582u;

//constructor with parameters, and default values
Date::Date(unsigned int Year, unsigned int Month, unsigned int Day) : Year(m_uYear), Month(m_uMonth), Day(m_uDay), WeekDay(m_WeekDay) {
    Set(Year, Month, Day);
}

//copy constructor
Date::Date(const Date& aDate) : Year(m_uYear), Month(m_uMonth), Day(m_uDay) , WeekDay(m_WeekDay){
    Set(aDate.Year, aDate.Month, aDate.Day);
}

//default assigmnet operator
Date& Date::operator=(const Date& aDate) {
    //to avoid a = a
    if (this != &aDate) {
        Set(aDate.Year, aDate.Month, aDate.Day);
    }
    return *this;
}

//destructor, not used
Date::~Date() {
}

//check values and set to private members
void Date::Set(unsigned int Year, unsigned int Month, unsigned int Day) {
    //check first
    if (!IsValid(Year, Month, Day)) {
        throw invalid_argument("Is not valid date");
    }
    //assigment
    m_uYear  = Year;
    m_uMonth = Month;
    m_uDay   = Day;
    //caluate week day form days form AD
    //the 0001-01-01 is Saturday
    unsigned int Days = InDaysFromAD();
    m_WeekDay = (WeekDayType)((Days -  1u + 6u) % 7u);
}

//return if the year is leap, form AD
bool Date::IsLeapYear() const {
    //call static member function
    return IsLeapYear(m_uYear);
}

//return if the date is valid, form AD
bool Date::IsValid() const {
    //call static member function
    return IsValid(m_uYear, m_uMonth, m_uDay);
}

//return the days'count from 0001-01-01, 0001-01-01 is the first(1, not 0) day
unsigned int Date::InDaysFromAD() const {
    unsigned int LeapYearCount;
    //leap years'count before 1582, from AD
    if (Year < GrigoreyYear) {
        LeapYearCount = (Year - 1u) / 4u;
    }
    //leap years'count after 1582, from AD
    else {
        LeapYearCount =
              //count leap years form AD, with nowdays method
              (Year - 1u) / 4u - (Year - 1u) / 100u + (Year - 1u) / 400u
              //add leap years defferent before 1582
            + (GrigoreyYear - 1u) / 100u - (GrigoreyYear - 1u) / 400u;
    }
    
    //Days before this year
    unsigned int DaysFromAD = 365u * (Year - 1u) + LeapYearCount;
    //there are not the 10 days: 1582-10-5 ~ 1582-10-14
    if ((Year >  GrigoreyYear) ||
        (Year == GrigoreyYear && Month > 10u) ||
        (Year == GrigoreyYear && Month == 10u && (Day >= 15u))) {
        DaysFromAD -= 10u;
    }
    //add days before this month
    bool IsLeapYearValue = IsLeapYear();
    for (unsigned int i = 1; i < Month; i++) {
        DaysFromAD += DaysInMonth[IsLeapYearValue][i];
    }
    //add this day, and the days beforethis day
    DaysFromAD += Day;
    return DaysFromAD;
}

//overlading relationship operators
bool Date::operator> (const Date& aDate) const {
    return InDaysFromAD() > aDate.InDaysFromAD();
}

bool Date::operator< (const Date& aDate) const {
    return InDaysFromAD() < aDate.InDaysFromAD();
}

bool Date::operator>=(const Date& aDate) const {
    return InDaysFromAD() >= aDate.InDaysFromAD();
}

bool Date::operator<=(const Date& aDate) const {
    return InDaysFromAD() <= aDate.InDaysFromAD();
}

bool Date::operator==(const Date& aDate) const {
    return (m_uYear == aDate.Year) && (m_uMonth == aDate.Month) && (m_uDay == aDate.Day);
}

bool Date::operator!=(const Date& aDate) const {
    return (m_uYear != aDate.Year) || (m_uMonth != aDate.Month) || (m_uDay != aDate.Day);
}

//overloading increment operators, to increase one day
Date& Date::operator++() {
    //there are not the 10 days: 1582-10-5 ~ 1582-10-14
    if (m_uYear == GrigoreyYear && m_uMonth == 10 && m_uDay == 4){
        Set(GrigoreyYear, 10, 15);
    }
    else {
        unsigned int NewDay = m_uDay + 1;
        unsigned int NewMonth = m_uMonth;
        unsigned int NewYear = m_uYear;
        if (NewDay > DaysInMonth[IsLeapYear()][NewMonth]) {
            NewDay = 1;
            NewMonth++;
        }
        if (NewMonth > 12) {
            NewMonth = 1;
            NewYear++;
        }
        Set(NewYear, NewMonth, NewDay);
    }
    return *this;
}

Date Date::operator++(int) {
    //call prefix operator++
    Date Res{*this};
    ++(*this);
    return Res;
}

//overloading decrement operators, to decrease one day
Date& Date::operator--() {
    //there are not the 10 days: 1582-10-5 ~ 1582-10-14
    if (m_uYear == GrigoreyYear && m_uMonth == 10 && m_uDay == 15){
        Set(GrigoreyYear, 10, 4);
    }
    else {
        unsigned int NewDay = m_uDay;
        unsigned int NewMonth = m_uMonth;
        unsigned int NewYear = m_uYear;
        //XXXX-1-1
        if (NewDay == 1 && NewMonth == 1) {
            NewDay = 31;
            NewMonth = 31;
            NewYear--;
        }
        else if (NewDay == 1 && NewMonth != 1){
            NewDay = DaysInMonth[IsLeapYear()][NewMonth - 1];
            NewMonth--;
        }
        else {
            NewDay--;
        }
        Set(NewYear, NewMonth, NewDay);
    }
    return *this;
}

Date Date::operator--(int) {
    //call prefix operator--
    Date Res{*this};
    --(*this);
    return Res;
}

long long Date::operator-(const Date& aDate) const {
    return static_cast<long long>(InDaysFromAD()) -  static_cast<long long>(aDate.InDaysFromAD());
}

//overloading stream insertion(extraction) operators
ostream& operator<<(ostream& Stream, const Date& aDate) {
    Stream << aDate.m_uYear << '/' << aDate.m_uMonth << '/' << aDate.m_uDay << ' ';
    switch (aDate.WeekDay) {
        case Date::WeekDayType::MON ://MON = 1, TUES = 2, WED = 3, THUR = 4, FRI = 5, SAT = 6 , SUN
            Stream << "MON";
            break;
        case Date::WeekDayType::TUES :
            Stream << "TUES";
            break;
        case Date::WeekDayType::WED :
            Stream << "WED";
            break;
        case Date::WeekDayType::THUR :
            Stream << "THUR";
            break;
        case Date::WeekDayType::FRI :
            Stream << "FRI";
            break;
        case Date::WeekDayType::SAT :
            Stream << "SAT";
            break;
        case Date::WeekDayType::SUN :
            Stream << "SUN";
            break;
        default:
            break;
    }
    return Stream;
}

istream& operator>>(istream& Stream, Date& aDate) {
    char Temp;
    unsigned int Year;
    unsigned int Month;
    unsigned int Day;
    string WeekDayStr;
    Stream >> Year  >> Temp //jump first  '/'
           >> Month >> Temp //jump second '/'
           >> Day   >> Temp //jump third  '/'
           >> WeekDayStr;
    aDate.Set(Year, Month, Day);
    return Stream;
}

bool Date::IsLeapYear(unsigned int Year) {
    if (Year < GrigoreyYear) {
        return (Year % 4u == 0u);
    }
    else {
        return (Year % 4u == 0u && Year % 100u != 0u) || (Year % 400u == 0u);
    }
}

bool Date::IsValid(unsigned int Year, unsigned int Month, unsigned int Day) {
//1 0001-01-01 is the first day of AD, not 0000-01-01
//2 Pope Gregor VIII issued a decree on February 24, 1582, permanently erasing the period from October 5, 1582 to October 14, 1582. There have never been these 10 days in history. October 4, 1582 is Thursday, and its next day is Friday, October 15, 1582.
    if (Year < 1) {
        return false;
    }
    if (Month < 1 || Month > 12) {
        return false;
    }
    if (Day < 1 ) {
        return false;
    }
    if (Year == GrigoreyYear && Month == 10 && (Day >= 5 && Day <= 14)) {
        return false;
    }
    if (Day > DaysInMonth[IsLeapYear(Year)][Month]) {
        return false;
    }
    return true;
}

//class function(static, no object's function) to get a date object means today;
Date Date::Today() {
    auto tp = chrono::system_clock::now();
    time_t cur_time = chrono::system_clock::to_time_t(tp);
    struct tm* pTimeInfo = localtime(&cur_time);
    return Date(pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday);
}
