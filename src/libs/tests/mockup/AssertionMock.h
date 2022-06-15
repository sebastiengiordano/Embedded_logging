#include "assertion/assertion.h"

class AssertionMock : public Assertion {

    protected:
		void _host_abord() {
            mock().actualCall("_host_abord").onObject(this);
        }
		void _device_abord() {
            mock().actualCall("_device_abord").onObject(this);
        }
};