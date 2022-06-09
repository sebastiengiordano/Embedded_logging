#include "CppUTest/TestHarness_c.h"
// #include "mockup/InputMock.h"
#include "assertion/assertion.h"


TEST_GROUP(Assertion) {
    // ActionObservableEuromair* action_observable_euromair;
    // InputEventObserver* input_event_observer;
    // TimeManager* time_manager;

    void setup() {
        // action_observable_euromair = new ActionObservableEuromair;
        // input_event_observer = new InputEventObserver;
        // action_observable_input = new InputMock(eInputId::LimitSwitchHigh);
        // event_observer_input = new InputMock(eInputId::LimitSwitchHigh);
        // time_manager = new TimeManager;

        // action_observable_euromair->add_observer(*input_event_observer);
        // action_observable_euromair->add_input(*action_observable_input);
        // input_event_observer->add_input(*event_observer_input);
    }

    void teardown() {
        // delete action_observable_euromair;
        // delete input_event_observer;
        // delete action_observable_input;
        // delete event_observer_input;
        // delete time_manager;
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(Assertion, assertion_failed) {
    
    // // Init test.
    // action_observable_input->add_action_type(action_type_long_duration);
    char* message = "My message";
    mock().expectOneCall("PLOG_FATAL").withParameter("msg", message);
    MY_ASSERT(0, *message);
    // action_observable_euromair->time_elapsed(time_manager->set_time(QUICK_DURATION));
    // // No event raised.
    // CHECK_EQUAL(true, input_event_observer->is_event_equal(event_observer_input, eEvent::Stop));
    // CHECK_EQUAL(true, input_event_observer->is_notification_counter_equal(event_observer_input, 0));

    // // Set action_observable_input to Activate state.
    // mock().expectOneCall("_read").onObject(action_observable_input).andReturnValue(1);
    // action_observable_euromair->time_elapsed(time_manager->set_time(QUICK_DURATION));
    // // No event raised.
    // CHECK_EQUAL(true, input_event_observer->is_event_equal(event_observer_input, eEvent::Stop));
    // CHECK_EQUAL(true, input_event_observer->is_notification_counter_equal(event_observer_input, 0));

}
