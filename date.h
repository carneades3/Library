using std::string;
using std::to_string;
using std::exception;
using std::ostream;
using std::istream;

namespace Chrono {
   
constexpr int FORBIDDEN_YEAR = 0;

inline string make_message(const string& MSG, const int X) {
   const string message = MSG + to_string(X); 
   return message;
}

inline bool is_valid_year(int y) {
   if (FORBIDDEN_YEAR == y)
      return false;
   return true;
}

inline bool is_valid_month(int m) {
   if (1 > m || 12 < m)
      return false;
   return true;
}

bool leapyear(int y);

inline unsigned int how_many_days(int year) {
   return leapyear(year) ? 366 : 365;
}

class Date {
public:
   class Invalid : public exception { 
      string msg {"Invalid date: "};
   public:
      Invalid(const string& message) { msg += message; }
      const char* what() {
         return msg.c_str();
      }
   };
   
   static const char* MONTH_NAMES[];
   enum Month {
      jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
   };
   
   Date(int yy, Month mm, int dd);
   Date();
   bool is_date();
   void validate();
   
   void add_day(int n);                // increase or decrease the Date by n days
   void add_month(int n);
   void add_year(int n);
   
   void set_previous_day();
   void set_next_day();
   void set_previous_month();
   void set_next_month();
   void set_previous_year();
   void set_next_year();
   
   int day()   const { return d; }
   Month month() const { return m; }
   int year()  const { return y; }
   
   bool operator==(const Date& other) const ;
   bool operator!=(const Date& other) const ;
   bool operator>(const Date& other) const ;
private:
   int y;
   Month m;
   int d;  
};

unsigned int day_in_year(const Date& date);

inline unsigned int days_to_end_year(const Date& date) {
   return how_many_days(date.year()) - day_in_year(date);
}

// prefix increment operator
inline Date::Month operator++(Date::Month& m)  {
   m = (m==Date::dec) ? Date::Month::jan : Date::Month(m+1);             // "wrap around"
   return m;
}

// prefix decrement operator
inline Date::Month operator--(Date::Month& m)  {
   m = (m==Date::jan) ? Date::Month::dec : Date::Month(m-1);             // "wrap around"
   return m;
}

inline ostream& operator<<(ostream& os, Date::Month m) {
   return os << Date::MONTH_NAMES[m - 1];
}

string to_string(const Date& d);
ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& date);

enum Day {
   sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

extern const char* DAY_NAMES[];

inline ostream& operator<<(ostream& os, Day day) {
   return os << DAY_NAMES[day];
}

Day day_of_week(const Date& other);
Date next_Sunday(const Date& date);
Date next_weekday(const Date& date);
Date next_workday(const Date& date);
unsigned int week_of_year(const Date& date);
Date get_today();

}
