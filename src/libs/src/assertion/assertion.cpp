#include "assertion/assertion.h"
#include "CppUTest/Utest.h"

Assertion::Assertion() {

}


void Assertion::check(bool expression, AssertionInformation assert_info) {
    if (not expression) {
        _crash(assert_info);
    }
}


void Assertion::set_test_behavior() {
    _test_in_progress = true;
}


void Assertion::set_target_type(TargetType target_type) {
    _target_type = target_type;
}


void Assertion::_crash(AssertionInformation& assert_info) {
    bool test_in_progress = _is_test_in_progress(assert_info);
    if (not test_in_progress) {
        switch (_target_type) {
            case Assertion::TargetType::Host:
                this->_host_abord();
                break;

            case Assertion::TargetType::Device:
                this->_device_abord();
                break;
        }
    }
}


bool Assertion::_is_test_in_progress(AssertionInformation& assert_info) {
    if (_test_in_progress) {
        UtestShell::getCurrent()->fail( assert_info.message,
                                        assert_info.fileName,
                                        assert_info.lineNumber);
        return true;
    }
    return false;
}