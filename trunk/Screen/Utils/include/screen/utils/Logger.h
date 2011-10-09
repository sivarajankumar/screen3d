/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2011 Ratouit Thomas                                    *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Lesser General Public License as published by  *
 * the Free Software Foundation; either version 3 of the License, or (at     *
 * your option) any later version.                                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser   *
 * General Public License for more details.                                  *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this program; if not, write to the Free Software Foundation,   *
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA, or go to   *
 * http://www.gnu.org/copyleft/lesser.txt.                                   *
 *****************************************************************************/

#ifndef SCREEN_LOGGER_H
#define SCREEN_LOGGER_H

#include <screen/utils/Singleton.h>
#include <screen/utils/Policies.h>
#include <screen/utils/Export.h>
#include <string>

namespace screen {
    namespace utils {
    	enum CallPosition{
    		CALL_BEGIN,
    		CALL_END
    	};
    	
    	enum CallType{
    		CALL_CONSTRUCTOR,
    		CALL_DESTRUCTOR,
    		CALL_METHOD,
    		CALL_STATIC_METHOD,
    		CALL_FUNCTION
    	};
    
        class LoggerReporter;

        class SCREEN_UTILS_EXPORT Logger : public UniqueSingleton<Logger> {
        	SINGLETON_DECL(UniqueSingleton,Logger)
        public:       	
            void attachReporter(LoggerReporter* reporter);
            void debug(const std::string& log);
            void info(const std::string& log);
            void warning(const std::string& log);
            void error(const std::string& log);
            void call(CallPosition pos,
            		  CallType type,
            		  const char* className,
            		  const std::string& functionName,
            		  const std::string& address);
        private:
            Logger();
            ~Logger();
            LoggerReporter* reporter;
        };
    }
}

# if defined(SCREEN_AUTHORIZE_LOG_DEBUG) || defined(SCREEN_AUTHORIZE_LOG_INFO) || defined(SCREEN_AUTHORIZE_LOG_WARNING) || defined(SCREEN_AUTHORIZE_LOG_ERROR)
#  define SCREEN_ATTACH_LOGGER_REPORTER(r) screen::utils::Logger::instance()->attachReporter((r));
# else
#  define SCREEN_ATTACH_LOGGER_REPORTER(r)
# endif

# if defined(SCREEN_AUTHORIZE_LOG_DEBUG)
#  define SCREEN_LOG_DEBUG(s)	{std::stringstream _ss; _ss << s; screen::utils::Logger::instance()->debug(_ss.str());}
# else
#  define SCREEN_LOG_DEBUG(s)
# endif

# if defined(SCREEN_AUTHORIZE_LOG_DEBUG) || defined(SCREEN_AUTHORIZE_LOG_INFO)
#  define SCREEN_LOG_INFO(s)	{std::stringstream _ss; _ss << s; screen::utils::Logger::instance()->info(_ss.str());}
# else
#  define SCREEN_LOG_INFO(s)
# endif

# if defined(SCREEN_AUTHORIZE_LOG_DEBUG) || defined(SCREEN_AUTHORIZE_LOG_INFO) || defined(SCREEN_AUTHORIZE_LOG_WARNING)
#  define SCREEN_LOG_WARNING(s)	{std::stringstream _ss; _ss << s; screen::utils::Logger::instance()->warning(_ss.str());}
# else
#  define SCREEN_LOG_WARNING(s)
# endif

# if defined(SCREEN_AUTHORIZE_LOG_DEBUG) || defined(SCREEN_AUTHORIZE_LOG_INFO) || defined(SCREEN_AUTHORIZE_LOG_WARNING) || defined(SCREEN_AUTHORIZE_LOG_ERROR)
#  define SCREEN_LOG_ERROR(s)	{std::stringstream _ss; _ss << s; screen::utils::Logger::instance()->error(_ss.str());}
# else
#  define SCREEN_LOG_ERROR(s)
# endif

# ifdef SCREEN_AUTHORIZE_LOG_CALL_TRACER
#  define SCREEN_LOG_CALL(p,t,c,f,a) screen::utils::Logger::instance()->call(p,t,c,f,a);
# endif

#endif
