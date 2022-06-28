#include "assertion/assertion.h"
#include "CppUTest/Utest.h"
#include <cstring>
#include <iostream>

/***************/
/* Constructor */
/***************/
Assertion::Assertion() {}
Assertion::~Assertion() {}

void Assertion::_host_abord(){}
void Assertion::_device_abord(){}


/*****************/
/* Public Method */
/*****************/
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


/******************/
/* Private Method */
/******************/
void Assertion::_crash(AssertionInformation& assert_info) {
    _log(assert_info.message);
    bool test_in_progress = _is_test_in_progress(assert_info);
    if (not test_in_progress) {
        switch (_target_type) {
            case Assertion::TargetType::Host:
                _host_abord();
                break;

            case Assertion::TargetType::Device:
                _device_abord();
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


/********************/
/* Protected Method */
/********************/
void Assertion::_log(const char* message) {
    int message_size = std::strlen(message);
    char balise[message_size + 6];
    char output_message[message_size + 4];

    balise[0] = '\0';
    output_message[0] = '\0';

    std::strcat(balise, "\n/");
    for (int i = 0; i < message_size + 2; i++) {
        std::strcat(balise, "*");
    }
    std::strcat(balise, "/\n");

    std::strcat(output_message, "/ ");
    std::strcat(output_message, message);
    std::strcat(output_message, " /");

    std::cout << balise << output_message << balise;
}
