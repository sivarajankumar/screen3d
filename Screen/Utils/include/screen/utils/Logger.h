/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2012 Ratouit Thomas                                    *
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
/**
 * \file screen/utils/Logger.h
 * \brief Screen/Utils log handling header file
 * \author
 *
 */

#ifndef SCREEN_LOGGER_H
#define SCREEN_LOGGER_H

#include <screen/utils/Singleton.h>
#include <screen/utils/Policies.h>
#include <screen/utils/Export.h>
#include <string>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        /**
         * \brief Call position (begin or end of scope)
         */
    	enum CallPosition{
    		CALL_BEGIN,
    		CALL_END
    	};
    	
        /**
         * \brief Call type (constructor, destructor; method, ...)
         */
        enum CallType{
    		CALL_CONSTRUCTOR,
    		CALL_DESTRUCTOR,
    		CALL_METHOD,
    		CALL_STATIC_METHOD,
    		CALL_FUNCTION
    	};
    
        class LoggerReporter;

        /**
         * \brief Singleton for log message handling
         *
         * Must be used with log macros (SCREEN_ATTACH_LOGGER_REPORTER,
         * SCREEN_LOG_DEBUG, SCREEN_LOG_INFO, SCREEN_LOG_WARNING, SCREEN_LOG_ERROR)
         */
        class SCREEN_UTILS_EXPORT Logger : public UniqueSingleton<Logger> {
        	SINGLETON_DECL(UniqueSingleton,Logger)
        public:
            /**
             * \brief Attach a specific reporter
             *
             * Please attach the reporter you need at beginning of main function
             *
             * \param[in] iReporter The reporter to attach
             */
            void attachReporter(LoggerReporter* iReporter);

            /**
             * \brief Log a debug message
             *
             * \param[in] iLog the debug message
             */
            void debug(const std::string& iLog);

            /**
             * \brief Log an info message
             *
             * \param[in] iLog the info message
             */
            void info(const std::string& iLog);

            /**
             * \brief Log a warning message
             *
             * \param[in] iLog the warning message
             */
            void warning(const std::string& iLog);

            /**
             * \brief Log an error message
             *
             * \param[in] iLog the error message
             */
            void error(const std::string& iLog);

            /**
             * \brief Log a call message
             *
             * \param[in] iPos The call position (begin or end)
             * \param[in] iType The call type
             * \param[in] iClassName The name of the class
             * \param[in] iFunctionName The function or method name
             * \param[in] iAddress The address of the traced instance
             */
            void call(CallPosition iPos,
                      CallType iType,
                      const char* iClassName,
                      const std::string& iFunctionName,
                      const std::string& iAddress);
        private:
            /**
             * \brief Default constructor
             */
            Logger();

            /**
             * \brief Destructor
             */
            ~Logger();

            LoggerReporter* _reporter; ///< reporter instance
        };

        /**
         * \brief Class to automatically handle log scope destruction
         *
         * With this class, you will need only SCREEN_DECL_CONSTRUCTOR, ... to create a complete log scope
         */
        class SCREEN_UTILS_EXPORT ScopeLog{
        public:
            /**
             * \brief Constructor
             *
             * Log begin scope call
             *
             * \param[in] iType Call type
             * \param[in] iClassName Class name
             * \param[in] iFunctionName Function or method name
             * \param[in] iAddress Instance address to trace
             */
            ScopeLog(screen::utils::CallType iType,
                     const char* iClassName,
                     const std::string& iFunctionName,
                     const std::string& iAddress);

            /**
             * \brief Destructor
             *
             * Log end scope call
             */
            ~ScopeLog();
        private:
            screen::utils::CallType _type; ///< Call type
            const char* _className; ///< Current class name
            std::string _functionName; ///< Function or method name
            std::string _address; ///< Cureent instance address
        };

    }
}

# if defined(USE_SCREEN_LOG_DEBUG) || defined(USE_SCREEN_LOG_INFO) || defined(USE_SCREEN_LOG_WARNING) || defined(USE_SCREEN_LOG_ERROR)
#  define SCREEN_ATTACH_LOGGER_REPORTER(r) screen::utils::Logger::Instance()->attachReporter((r));
# else
#  define SCREEN_ATTACH_LOGGER_REPORTER(r)
# endif

# if defined(USE_SCREEN_LOG_DEBUG)
#  define SCREEN_LOG_DEBUG(s)	do{std::stringstream _ss; _ss << s; screen::utils::Logger::Instance()->debug(_ss.str());} while(0)
# else
#  define SCREEN_LOG_DEBUG(s)
# endif

# if defined(USE_SCREEN_LOG_DEBUG) || defined(USE_SCREEN_LOG_INFO)
#  define SCREEN_LOG_INFO(s)	do {std::stringstream _ss; _ss << s; screen::utils::Logger::Instance()->info(_ss.str());} while(0)
# else
#  define SCREEN_LOG_INFO(s)
# endif

# if defined(USE_SCREEN_LOG_DEBUG) || defined(USE_SCREEN_LOG_INFO) || defined(USE_SCREEN_LOG_WARNING)
#  define SCREEN_LOG_WARNING(s)	do{std::stringstream _ss; _ss << s; screen::utils::Logger::Instance()->warning(_ss.str());} while(0)
# else
#  define SCREEN_LOG_WARNING(s)
# endif

# if defined(USE_SCREEN_LOG_DEBUG) || defined(USE_SCREEN_LOG_INFO) || defined(USE_SCREEN_LOG_WARNING) || defined(USE_SCREEN_LOG_ERROR)
#  define SCREEN_LOG_ERROR(s)	do{std::stringstream _ss; _ss << s; screen::utils::Logger::Instance()->error(_ss.str());} while(0)
# else
#  define SCREEN_LOG_ERROR(s)
# endif

# ifdef USE_SCREEN_LOG_CALL_TRACER
#  define SCREEN_LOG_CALL(p,t,c,f,a) screen::utils::Logger::Instance()->call(p,t,c,f,a);
#  define SCREEN_SCOPE_CALL(t,c,f,a) screen::utils::ScopeLog _scopeLog(t,c,f,a);
#else
#  define SCREEN_LOG_CALL(p,t,c,f,a)
#  define SCREEN_SCOPE_CALL(t,c,f,a)
# endif

#endif
