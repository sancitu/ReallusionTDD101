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

TEST( StatementsTest, Result_ByDefault_ReturnZero ) { ASSERT_EQ( 0, 0 ); }
