using namespace std;

#include <iostream>
#include <iomanip>
#include "Time.h"

Time::Time()
{ hour = min = sec = 0;
}

Time::Time(int h, int m, int s)
{ setTime(h, m, s);
}

void Time::setTime(int h, int m, int s)
{ hour = (h>=0 && h<24) ? h : 0;
  min = (m>=0 && m<60) ? m : 0;
  sec = (s>=0 && s<60) ? s : 0;
}

Time& Time::operator+=(unsigned int n) {
    sec += n;
    if (sec >= 60)
    { min += sec/60;
        sec %= 60;
        if (min >=60)
        { hour = (hour + min/60) % 24;
            min %= 60;
        }
    }
    return *this;
}

Time Time::operator+(unsigned int n) const
{ Time tCopy(*this);
  tCopy += n;
  return tCopy;
}

Time& Time::operator++()        // prefix version
{ *this += 1;
  return *this;
}

Time Time::operator++(int n)    // postfix version
{ Time tCopy(*this);
  *this += 1;
  return tCopy;
}

//Implementing 3 boolean functions
//This method returns true based on the smallest time Given.
bool Time::operator<(const Time& t) const {
    if (hour < t.hour) {
        return true;
    }else if (hour > t.hour) {
        return false;
    }else if (hour == t.hour) {
        if (min < t.min) {
            return true;
        }else if (min > t.min) {
            return false;
        }else if (min == t.min) {
            if (sec < t.sec) {
                return true;
            }else{
                return false;
            }
        }
    }else{
        return false;
    }
}


//This method uses both the operator< and operator== methods to implement operator<=
bool Time::operator<=(const Time& t) const {
    Time tCopy(*this);
    return tCopy < t || tCopy == t;
}

//This method returns true if all 6 components of the time are equal.
bool Time::operator==(const Time& t) const {
    return hour == t.hour & min == t.min & sec == t.sec;
}


ostream& operator<<(ostream &o, const Time &t)
{ o << setfill('0') << setw(2) <<  t.hour << ':' << setw(2) << t.min << ':' << setw(2) << t.sec;
  return o;
}

//Implementing 4 subtraction methods

//This method uses the defined method operator-= inorder to subtract a number from a time.
Time Time::operator-(unsigned int n) const {
    Time tCopy(*this);
    tCopy -= n;
    return tCopy;
}


//This method performs subtraction - It checks when seconds have dropped below 0 and then subtracts one from the minutes
//reseting the seconds back to 60; It then performs this check for the mins, subtracting one from hours and resetting mins
//back to 60
Time &Time::operator-=(unsigned int n) {
    sec -= n;
    while (sec<0){
        sec+=60;
        min-=1;
        if(min<0){
            min+=60;
            hour-=1;
        }
    }
    return *this;
}

//This method used the previously defined method operator-= to subtract only one from the time.
//prefix version
Time &Time::operator--() {
    *this -= 1;
    return *this;
}

//This method used the previously defined method operator-= to subtract only one from the time.
//postfix version
Time Time::operator--(int) {
    Time tCopy(*this);
    *this -= 1;
    return tCopy;
}

// implementing 3 friend bool functions

//This method works in much the same way as the less than one, however this is a friend function
bool operator>(const Time &t1, const Time &t2) {
    if (t1.hour > t2.hour) {
        return true;
    }else if (t1.hour < t2.hour) {
        return false;
    }else if (t1.hour == t2.hour) {
        if (t1.min > t2.min) {
            return true;
        }else if (t1.min < t2.min) {
            return false;
        }else if (t1.min == t2.min) {
            if (t1.sec > t2.sec) {
                return true;
            }else{
                return false;
            }
        }
    }else{
        return false;
    }
}

//This method uses the already defined opertator== and operator> to define operator>=
bool operator>=(const Time &t1, const Time &t2) {
    return t1 > t2 || t1 == t2;
}

//This method uses the already defined operator== to check if the two times are not equal.
bool operator!=(const Time &t1, const Time &t2) {
    return !(t1==t2);
}


//Implementing modulo operator

//This method calculates the modulo of two times.
unsigned int operator%(const Time &t1, const Time &t2) {
    int t1TotalSecs = (t1.hour*60*60) + (t1.min*60) + (t1.sec);
    int t2TotalSecs = (t2.hour*60*60) + (t2.min*60) + (t2.sec);
    int returnValue;
    //checking if t1TotalSecs is > than t2TotalSecs, If it is that means t2TotalSecs is on the next day, so add 1 day in seconds
    //to the variable then perform the subtraction.
    if (t1TotalSecs>t2TotalSecs){
        t2TotalSecs+=86400;
        returnValue = t2TotalSecs-t1TotalSecs;
    }else{
        returnValue = t2TotalSecs-t1TotalSecs;
    }
    return unsigned (returnValue);
}


