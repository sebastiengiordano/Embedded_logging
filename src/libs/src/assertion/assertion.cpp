#include "assertion/assertion.h"
#include "CppUTest/Utest.h"


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

void Assertion::set_logger(plog::Severity severity, Assertion::AppenderType appender) {
    _set_appender(appender);
    _log_severity = severity;
}


/******************/
/* Private Method */
/******************/
void Assertion::_crash(AssertionInformation& assert_info) {
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

void Assertion::_set_appender(Assertion::AppenderType appender) {
    switch (appender)
    {
        case Assertion::AppenderType::ConsoleAppender:
            _appender = new plog::ConsoleAppender<plog::TxtFormatter>;
            break;

        case Assertion::AppenderType::ColorConsoleAppender:
            _appender = new plog::ColorConsoleAppender<plog::TxtFormatter>;
            break;
        
        default:
            while (1);
    }
}

void Assertion::_logging(const char* message) {
    if (!_appender)
    {
        plog::init(_log_severity, _appender);
        // plog::PLOG(_log_severity) << message;
        plog::PLOG_FATAL << message;
    }
}
