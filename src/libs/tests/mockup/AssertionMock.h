#include "assertion/assertion.h"

class AssertionMock : public Assertion {

    protected:
		virtual void _host_abord() override final {
            mock().actualCall("_host_abord").onObject(this);
        }
		virtual void _device_abord() override final {
            mock().actualCall("_device_abord").onObject(this);
        }
};