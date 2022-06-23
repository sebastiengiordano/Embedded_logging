#define ASSERT_DISABLED

#include "CppUTest/TestHarness.h"
// #include "CppUTest/TestHarness_c.h"
#include "CppUTestExt/MockSupport.h"
#include "mockup/AssertionMock.h"


TEST_GROUP(AssertionDisabled) {

    void setup() {
        
    }

    void teardown() {
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(AssertionDisabled, assertion_not_raised) {
    
    // Init test.
    AssertionMock assertion = AssertionMock();
    assertion.set_target_type(Assertion::TargetType::Host);
    assertion.set_test_behavior();
    assertion.CHECK_ASSERT(false, ASSERT_INFO("Assertion shall not failed during test."));
}
