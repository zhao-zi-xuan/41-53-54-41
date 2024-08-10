//
//  DateTime.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/5.
//

#ifndef DateTime_hpp
#define DateTime_hpp

#include "Date.hpp"
#include "Time.hpp"
#include <utility>
using namespace std;

//pre-declare
class DateTime;

//new type via using
//Datetime range is a pair of datetimes
using DateTimeRange = pair<DateTime, DateTime>;

class DateTime : public Date, public Time{
public:
    //constructor with parameters, and default values
    DateTime(const Date& aDate = Date(), const Time& aTime = Time());
    //constructor with parameters
    DateTime(unsigned int Year, unsigned int Month, unsigned int Day, unsigned int Hour, unsigned int Minute, unsigned int Second);
    
    //overlading relationship operators
    bool operator  >(const DateTime& aDateTime) const;
    bool operator  <(const DateTime& aDateTime) const;
    bool operator >=(const DateTime& aDateTime) const;
    bool operator <=(const DateTime& aDateTime) const;
    bool operator ==(const DateTime& aDateTime) const;
    bool operator !=(const DateTime& aDateTime) const;
    
    //overloading increment operators, to increase one second
    DateTime& operator++();
    DateTime  operator++(int);
    //overloading decrement operators, to decrease one second
    DateTime& operator--();
    DateTime  operator--(int);
    
    //return seconds'count between two datetime
    long long operator-(const DateTime& aDateTime) const;
 
    //overloading stream insertion(extraction) operators
    friend ostream& operator<<(ostream& Stream, const DateTime& aDateTime);
    friend istream& operator>>(istream& Stream, DateTime& aDateTime);

    //class function(static, no object's function) to get a DateTime object means today and now time;
    DateTime Now();
    
    //class function(static, no object's function) to get a DateTimeRange object between two datetimes
    static DateTimeRange Between(const DateTime& Begin, const DateTime& End);
    //class function(static, no object's function) to get a DateTimeRange object From a datetime to the end of universe
    static DateTimeRange From(const DateTime& Begin);
    //class function(static, no object's function) to get a DateTimeRange object From AD to a datetime
    static DateTimeRange Until(const DateTime& End);
    //class function(static, no object's function) to get a DateTimeRange object From AD to to the end of universe
    static DateTimeRange All();
    
    //0001-01-01 00:00:00
    static const DateTime MIN_DATETIME;
    //the end of universe
    static const DateTime MAX_DATETIME;
};

#endif /* DateTime_hpp */
