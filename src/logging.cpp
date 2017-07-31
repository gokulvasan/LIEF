/* Copyright 2017 R. Thomas
 * Copyright 2017 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "easylogging++.h"
#include "LIEF/logging.hpp"

INITIALIZE_EASYLOGGINGPP

static LIEF::Logger logger;

namespace LIEF {

Logger::~Logger(void) = default;

const char* to_string(LOGGING_LEVEL e) {
  const std::map<LOGGING_LEVEL, const char*> enumStrings {
    { LOGGING_LEVEL::LOG_GLOBAL,   "GLOBAL"  },
    { LOGGING_LEVEL::LOG_TRACE,    "TRACE"   },
    { LOGGING_LEVEL::LOG_DEBUG,    "DEBUG"   },
    { LOGGING_LEVEL::LOG_FATAL,    "FATAL"   },
    { LOGGING_LEVEL::LOG_ERROR,    "ERROR"   },
    { LOGGING_LEVEL::LOG_WARNING,  "WARNING" },
    { LOGGING_LEVEL::LOG_INFO,     "INFO"    },
    { LOGGING_LEVEL::LOG_VERBOSE,  "VERBOSE" },
    { LOGGING_LEVEL::LOG_UNKNOWN,  "UNKNOWN" },
  };
  auto   it  = enumStrings.find(e);
  return it == enumStrings.end() ? "UNDEFINED" : it->second;
}

Logger::Logger(void)
{
  el::Logger* default_logger = el::Loggers::getLogger("default");
  el::Configurations conf;
  conf.setToDefault();
  conf.parseFromText(logging_config);
  el::Loggers::setDefaultConfigurations(conf, true);

  el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
}


void Logger::disable(void) {
  el::Configurations c;

  c.parseFromText("* GLOBAL:\n ENABLED = false");
  el::Loggers::reconfigureAllLoggers(c);
}

void Logger::enable(void) {
  el::Configurations c;
  c.parseFromText("* GLOBAL:\n ENABLED = true\n");
  el::Loggers::reconfigureAllLoggers(c);

  el::Loggers::setLoggingLevel(el::Level::Global);
}


void Logger::set_verbose_level(uint32_t level) {
  el::Loggers::setVerboseLevel(level);
}


void Logger::set_level(LOGGING_LEVEL level) {
  el::Loggers::setLoggingLevel(static_cast<el::Level>(level));

  if (level == LOGGING_LEVEL::LOG_DEBUG) {
    set_verbose_level(3);
  }
 }

}



