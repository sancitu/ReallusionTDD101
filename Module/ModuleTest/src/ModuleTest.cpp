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

        double fDiff = std::difftime( uEnd, uBegin );
        double fDays = fDiff / SECONDS_OF_ONE_DAY;

        return fDays;
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
    ASSERT_EQ( kStatements.Result( "2019-01-28", "2019-01-29" ), 1 );
}
