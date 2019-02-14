// Module test code

#include <gmock/gmock.h>

#include "Module/Module.h"

using namespace testing;

// Classic Assertion:
//   Fatal assertion          Nonfatal assertion      Verifies
// ASSERT_EQ(val1, val2);   EXPECT_EQ(val1, val2);   val1 == val2
// ASSERT_NE(val1, val2);   EXPECT_NE(val1, val2);   val1 != val2
// ASSERT_LT(val1, val2);   EXPECT_LT(val1, val2);   val1 < val2
// ASSERT_LE(val1, val2);   EXPECT_LE(val1, val2);   val1 <= val2
// ASSERT_GT(val1, val2);   EXPECT_GT(val1, val2);   val1 > val2
// ASSERT_GE(val1, val2);   EXPECT_GE(val1, val2);   val1 >= val2
// 
// Test Case:
//   TEST( TestSuiteName, TestName ) {...}
//
// or using test fixture:
//   class TestSuiteName : public Test
//   {
//   protected:
//        virtual void SetUp() {}
// 	      CModule	m_kModule;    // your test module
//   };
//   TEST_F( TestSuiteName, TestName ) {...}

#define SECONDS_OF_ONE_DAY (24*3600)
std::map<std::string, int> g_Budget { std::make_pair( "2019-01", 310 ) };

class CStatements
{
public:
    int Result() { return 0; }
    int Result( char* szBegin, char* szEnd )
    {
        std::tm kBegin = {};
        std::istringstream ss( szBegin );
        ss >> std::get_time( &kBegin, "%Y-%m-%d" );
        time_t uBegin = std::mktime( &kBegin );

        ss.clear();
        ss.str( szEnd );

        std::tm kEnd ={};
        ss >> std::get_time( &kEnd, "%Y-%m-%d" );
        time_t uEnd = std::mktime( &kEnd );
        kEnd.tm_mday;
        double fDiff = std::difftime( uEnd, uBegin );
        double fDays = fDiff / SECONDS_OF_ONE_DAY;

        return (int) fDays + 1;
    }

    int Budget( char* szBegin, char* szEnd )
    {
        std::string strBudgetBegin;
        std::string strBudgetEnd;

        auto a = g_Budget.begin()->first;
        std::tm kBudgetBegin = {};
        std::istringstream ss( a + "-01" ); // first day
        ss >> std::get_time( &kBudgetBegin, "%Y-%m-%d" );

        // 01 => 0101 => 0201 => 0131
        auto b = g_Budget.rbegin()->first;
        std::tm kBudgetEndMonthFirstDay = {};
        std::istringstream ssb( b + "-01" ); // next to the last day
        ssb >> std::get_time( &kBudgetEndMonthFirstDay, "%Y-%m-%d" );
        
        struct tm kBudgetEnd;

        struct tm kNextMonthFirstDay;
        kNextMonthFirstDay.tm_hour = 0;
        kNextMonthFirstDay.tm_min = 0;
        kNextMonthFirstDay.tm_sec = 0;
        kNextMonthFirstDay.tm_mday = 1;

        if ( kBudgetEndMonthFirstDay.tm_mon == 11 )
        {
            kNextMonthFirstDay.tm_mon = 0;
            kNextMonthFirstDay.tm_year = kBudgetEndMonthFirstDay.tm_year + 1;
        }
        else
        {
            kNextMonthFirstDay.tm_mon = kBudgetEndMonthFirstDay.tm_mon + 1;
            kNextMonthFirstDay.tm_year = kBudgetEndMonthFirstDay.tm_year;
        }
        // Get the first day of the next month
        time_t uLastday = mktime( &kNextMonthFirstDay ) - SECONDS_OF_ONE_DAY;
        // Convert back to date and time
        localtime_s( &kBudgetEnd, &uLastday );

        std::string szYear = std::to_string( kBudgetEnd.tm_year );
        std::string szMonth = std::to_string( kBudgetEnd.tm_mon );
        std::string szDate = std::to_string( kBudgetEnd.tm_mday );
        strBudgetEnd = szYear + '-' + szMonth + '-' + szDate;
        char* szBudgetEnd = &strBudgetEnd[ 0 ];

        strBudgetBegin = b + "-01";
        char* szBudgetBegin = &strBudgetBegin[ 0 ];

        if ( Result( szBudgetBegin, szBegin ) > 0 && Result( szEnd, szBudgetEnd ) > 0 )
        {
            return 10 * Result( szBegin, szEnd );
        }
        else if ( Result( szBudgetBegin, szBegin ) <= 0 && Result( szEnd, szBudgetEnd ) <= 0 )
        {
            return 10 * Result( szBudgetBegin, szBudgetEnd );
        }
        else if ( Result( szEnd, szBudgetEnd ) <= 0 )
        {
            return 10 * Result( szBegin, szBudgetEnd );
        }
        else if ( Result( szBudgetBegin, szBegin ) <= 0 )
        {
            return 10 * Result( szBudgetBegin, szEnd );
        }
        else
        {
            return 0;
        }
    }
};

TEST( StatementsTest, Result_ByDefault_ReturnZero )
{
    CStatements kStatements;
    ASSERT_EQ( kStatements.Result(), 0 );
}

TEST( StatementsTest, Result_OneDay_ReturnOne )
{
    CStatements kStatements;
    ASSERT_EQ( kStatements.Result( "2019-01-28", "2019-01-28" ), 1 );
}

TEST( StatementsTest, Budget_OneDay_Return10 )
{
    CStatements kStatements;
    ASSERT_EQ( kStatements.Budget( "2019-01-28", "2019-01-28" ), 10 );
}

TEST( StatementsTest, Budget_TwoDays_Return20 )
{
    CStatements kStatements;
    ASSERT_EQ( kStatements.Budget( "2019-01-28", "2019-01-29" ), 20 );
}

TEST( StatementsTest, Budget_OutOfRangeLate1Day_Return40 )
{
    CStatements kStatements;
    ASSERT_EQ( kStatements.Budget( "2019-01-28", "2019-02-01" ), 40 );
}

TEST( StatementsTest, Budget_OutOfRangeEarly1Day_Return40 )
{
    CStatements kStatements;
    ASSERT_EQ( kStatements.Budget( "2018-12-31", "2019-01-04" ), 40 );
}

TEST( StatementsTest, Budget_OutOfRangeEarly1DayLate1Day_Return310 )
{
    CStatements kStatements;
    ASSERT_EQ( kStatements.Budget( "2018-12-31", "2019-02-01" ), 310 );
}