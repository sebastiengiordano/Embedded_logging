#pragma once

#include <stdlib.h>
#include <assert.h>
#include <string>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ConsoleAppender.h"
#include "plog/Logger.h"
#include "plog/Severity.h"
// #include "logging/logging.h"

#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// logging::Log logger = logging::Log();

// static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
// static auto logger = plog::init(plog::debug, &consoleAppender);


// // Convenience structure that we can store items in
// //  to print out later when we add logging.
// typedef struct sAssertInfo {
//   uint32_t pc;
//   uint32_t lr;
//   uint32_t line;
//   // I don't suggest actually using these, but they
//   // are included for the examples.
//   char file[256];
//   char msg[256];
// } sAssertInfo;

// extern sAssertInfo g_assert_info;


// void __assert_func(const char *file,
//                    int line,
//                    const char *func,
//                    const char *failedexpr) {
//     snprintf(g_assert_info.msg, sizeof(g_assert_info.msg),
//             "ASSERT: %s at %s\n", failedexpr, func);
//     strncpy(g_assert_info.file, file, sizeof(g_assert_info.file));
//     g_assert_info.line = line;

//     __asm("bkpt 1");
// }


// void my_assert(const char *msg) {
//   strncpy(g_assert_info.msg, msg, sizeof(g_assert_info.msg));
//   __asm("bkpt 2");
// }


// #define MY_ASSERT(expr, msg) \
//     do {                                        \
//         if (!(expr)) {                          \
//         PLOG_FATAL << msg;                       \
//         /* my_assert(__FILENAME__, __LINE__); */     \
//         }                                       \
//     } while (0)


// template <class Handler, class Expr>
// void do_assert(std::true_type, const Expr& e, const source_location& loc, const char* expression) noexcept
// {
//     if (!e())
//     {
//         Handler::handle(loc, expression);
//         std::abort();
//     }
// }

// template <class Handler, class Expr>
// void do_assert(std::false_type, const Expr&, const source_location&, const char*) noexcept {}

// template <class Handler, class Expr>
// void do_assert(const Expr& e, const source_location& loc, const char* expression)
// {
//     do_assert<Handler>(Handler{}, e, loc, expression);
// }

// #define DEBUG_ASSERT(Expr, Handler) \
//     do_assert<Handler>([&] { return Expr; }, CUR_SOURCE_LOCATION, #Expr)

#define ASSERT_INFO(msg) {msg, __FILE__, __LINE__}

class Assertion {
	public:
		Assertion();
		~Assertion();

		typedef enum {
			Host,
			Device
		} TargetType;

		typedef struct {
			const char* message;
			const char* fileName;
			size_t lineNumber;
		} AssertionInformation;

		void check(bool expression, AssertionInformation assert_info);
		void set_test_behavior();
		void set_target_type(TargetType target_type);


	protected:
		virtual void _host_abord();
		virtual void _device_abord();


	private:
		void _crash(AssertionInformation& assert_info);
		bool _is_test_in_progress(AssertionInformation& assert_info);

		bool _test_in_progress = false;
		TargetType _target_type;
};
