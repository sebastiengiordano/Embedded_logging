#pragma once

#include <stdlib.h>

#define ASSERT_INFO(msg) {msg, __FILE__, __LINE__}

#if defined (ASSERT_DISABLED)
	#define CHECK_ASSERT(expression, assert_info) check(true, assert_info)
#else
	#define CHECK_ASSERT check
#endif

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
