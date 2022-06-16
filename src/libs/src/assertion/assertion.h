#pragma once

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ConsoleAppender.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/DebugOutputAppender.h"
#include "plog/Appenders/RollingFileAppender.h"
#include <plog/Formatters/TxtFormatter.h>
#include "plog/Logger.h"
#include "plog/Severity.h"



#define ASSERT_INFO(msg) {msg, __FILE__, __LINE__}


class Assertion {
	public:
		Assertion();
		~Assertion();

		typedef enum {
			Host,
			Device
		} TargetType;

		typedef enum {
			ConsoleAppender,
			ColorConsoleAppender
		} AppenderType;

		typedef struct {
			const char* message;
			const char* fileName;
			size_t lineNumber;
		} AssertionInformation;

		void check(bool expression, AssertionInformation assert_info);
		void set_test_behavior();
		void set_target_type(TargetType target_type);
		void set_logger(plog::Severity severity, AppenderType appender);


	protected:
		virtual void _host_abord();
		virtual void _device_abord();


	private:
		void _crash(AssertionInformation& assert_info);
		bool _is_test_in_progress(AssertionInformation& assert_info);
		void _set_appender(AppenderType appender);
		void _logging(const char* message);

		bool _test_in_progress = false;
		TargetType _target_type;
		plog::Severity _log_severity;
		plog::IAppender* _appender = NULL;
};
