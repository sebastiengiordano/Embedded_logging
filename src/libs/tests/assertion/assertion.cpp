#include "CppUTest/TestHarness.h"
// #include "CppUTest/TestHarness_c.h"
#include "CppUTestExt/MockSupport.h"
#include "mockup/AssertionMock.h"


TEST_GROUP(Assertion) {

    void setup() {
        
    }

    void teardown() {
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(Assertion, assertion_failed_during_test) {
    
    // // Init test.
    AssertionMock assertion = AssertionMock();
    assertion.set_target_type(Assertion::TargetType::Host);
    assertion.set_test_behavior();
    assertion.check(false, ASSERT_INFO("Assertion failed during test."));
}

TEST(Assertion, assertion_failed_on_host) {
    
    // // Init test.
    const char* message = "Assertion failed on host.";
    AssertionMock assertion = AssertionMock();
    assertion.set_target_type(Assertion::TargetType::Host);
    mock().expectOneCall("_host_abord").onObject(&assertion);
    assertion.check(false, ASSERT_INFO(message));
}

TEST(Assertion, assertion_failed_on_device) {
    
    // // Init test.
    AssertionMock assertion = AssertionMock();
    assertion.set_target_type(Assertion::TargetType::Device);
    mock().expectOneCall("_host_abord").onObject(&assertion);
    assertion.check(false, ASSERT_INFO("Assertion failed on device."));
}
