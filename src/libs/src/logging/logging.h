#pragma once

#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ConsoleAppender.h"

namespace logging {

    class Log {

        public:
            Log() {
                plog::init(plog::debug, &consoleAppender);
            }
            ~Log() {

            }

            static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;

    };

}
