#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "mockup/AssertionMock.h"


TEST_GROUP(Assertion) {

    AssertionMock* assertion;

    void setup() {
        assertion = new AssertionMock();
    }

    void teardown() {
        delete assertion;
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(Assertion, assertion_failed_during_test) {
    
    // Init test.
    assertion->set_target_type(Assertion::TargetType::Host);
    assertion->set_test_behavior();
    assertion->CHECK_ASSERT(false, ASSERT_INFO("Assertion failed during test."));
}

TEST(Assertion, assertion_failed_on_host) {
    
    // Init test.
    assertion->set_target_type(Assertion::TargetType::Host);
    mock().expectOneCall("_host_abord").onObject(assertion);
    assertion->CHECK_ASSERT(false, ASSERT_INFO("Assertion failed on host."));
}   

TEST(Assertion, assertion_failed_on_device) {
    
    // Init test.
    assertion->set_target_type(Assertion::TargetType::Device);
    mock().expectOneCall("_device_abord").onObject(assertion);
    assertion->CHECK_ASSERT(false, ASSERT_INFO("Assertion failed on device."));
}
