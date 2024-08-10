//
//  Date.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/5.
//

#ifndef Date_hpp
#define Date_hpp

#include <ctime>
#include <iostream>
using namespace std;

class Date{
public:
    //constructor with parameters, and default values
    Date(unsigned int Year = 1900, unsigned int Month = 1, unsigned int Day = 1);
    //copy constructor
    Date(const Date& aDate);
    //default assigmnet operator
    Date& operator=(const Date& aDate);
    //destructor, not used
    ~Date();
    
    //check values and set to private members
    void Set(unsigned int Year, unsigned int Month, unsigned int Day);
    
    //return if the year is leap, form AD
    bool IsLeapYear() const;
    //return if the date is valid, form AD
    bool IsValid() const;
    
    //return the days'count from 0001-01-01, 0001-01-01 is the first(1, not 0) day
    unsigned int InDaysFromAD() const;
   
    //overlading relationship operators
    bool operator> (const Date& aDate) const;
    bool operator< (const Date& aDate) const;
    bool operator>=(const Date& aDate) const;
    bool operator<=(const Date& aDate) const;
    bool operator==(const Date& aDate) const;
    bool operator!=(const Date& aDate) const;
    
    //overloading increment operators, to increase one day
    Date& operator++();
    Date  operator++(int);
    //overloading decrement operators, to decrease one day
    Date& operator--();
    Date  operator--(int);
    
    //return days'count between two date, today-yesterday is 1, yesterday-today is -1
    long long operator-(const Date& aDate) const;
   
    //enum for week day
    enum class WeekDayType {MON = 1, TUES = 2, WED = 3, THUR = 4, FRI = 5, SAT = 6 , SUN = 0};
    
    //overloading stream insertion(extraction) operators
    friend ostream& operator<<(ostream& Stream, const Date& aDate);
    friend istream& operator>>(istream& Stream, Date& aDate);
    
    //class function(static, no object's function), return if an Year is leap, form AD
    static bool IsLeapYear(unsigned int Year);
    //class function(static, no object's function), return if a date is valid, form AD
    static bool IsValid(unsigned int Year, unsigned int Month, unsigned int Day);
    
    //class function(static, no object's function) to get a date object means today;
    static Date Today();
    
    //data members'const references, read only
    const unsigned int& Year;
    const unsigned int& Month;
    const unsigned int& Day;
    const WeekDayType& WeekDay;
    
    //0001-01-01
    static const Date MIN_DATE;
    //UINT32_MAX-12-31
    static const Date MAX_DATE;
    
private:
    //data members
    unsigned int m_uYear;
    unsigned int m_uMonth;
    unsigned int m_uDay;
    WeekDayType m_WeekDay;
    //day is each month
    //DayInMonth[0][1~12], not leap year
    //DayInMonth[1][1~12], leap year
    static const unsigned int DaysInMonth[2][13];
    //YEAR 1582
    //Pope Gregor VIII issued a decree on February 24, 1582, permanently erasing the period from October 5, 1582 to October 14, 1582. There have never been these 10 days in history. October 4, 1582 is Thursday, and its next day is Friday, October 15, 1582.
    //Before this year, there was a leap year every four years; After that, people used the current method of calculating leap years
    static const unsigned int GrigoreyYear;
};
#endif /* Date_hpp */
