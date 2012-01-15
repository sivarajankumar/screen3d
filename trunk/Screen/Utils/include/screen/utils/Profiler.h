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
 * \file screen/utils/Profiler.h
 * \brief Screen/Utils profile log handling header file
 * \author
 *
 */

#ifndef SCREEN_PROFILER_H
#define SCREEN_PROFILER_H

#include <vector>
#include <screen/utils/Singleton.h>
#include <screen/utils/Policies.h>
#include <screen/utils/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {
        class ProfilerReporter;
        class Timer;

        /**
         * \brief Profile data
         */
        struct SCREEN_UTILS_EXPORT Profile {
            std::string _info; ///< Information string
            double _beginning; ///< Beginning time of scope profile
            double _ending; ///< Ending time of scope profile
            bool _ended; ///< Profile completed flags
        };

        /**
         * \brief Singleton for log message handling
         *
         * Must be used with declaration macros (i.e SCREEN_DECL_CONSTRUCTOR, ...)
         */
        class SCREEN_UTILS_EXPORT Profiler : public UniqueSingleton<Profiler> {
        	SINGLETON_DECL(UniqueSingleton,Profiler)
            friend class ProfileScope;
        public:
            /**
             * \brief Attach the timer
             *
             * Please attach the timer at beginning of main function
             *
             * \param[in] iTimer the timer instance
             */
            void attachTimer(screen::utils::Timer* iTimer);

            /**
             * \brief Attach a specific reporter
             *
             * Please attach the reporter you need at beginning of main function
             *
             * \param[in] iReporter The reporter to attach
             */
            void attachReporter(ProfilerReporter* iReporter);
        private:
            /**
             * \brief Attach a new profile to Profiler singleton
             *
             * \param[in] iProfile the profile to log
             */
            void attachProfile(Profile* iProfile);

            /**
             * \brief Default constructor
             */
            Profiler();

            /**
             * \brief Destructor
             */
            ~Profiler();

            screen::utils::Timer* _timer; ///< Timer instance
            typedef std::vector<Profile*> ProfileSet;
            ProfileSet _allProfiles; ///< Profile set
            ProfilerReporter* _reporter; ///< Reporter instance
        };

        /**
         * \brief Class to automatically handle profile scope destruction
         *
         * With this class, you will need only SCREEN_DECL_CONSTRUCTOR, ... to create a complete profile scope
         */
        class SCREEN_UTILS_EXPORT ProfileScope {
        public:
            /**
             * \brief Constructor
             *
             * \param[in] iInfo Profile information string
             */
            ProfileScope(const std::string& iInfo);


            /**
             * \brief Destructor
             */
            ~ProfileScope();
        private:
            Profile* _profile; ///< Profile instance
        };
    }
}

# ifdef USE_SCREEN_PROFILE
#  define SCREEN_ATTACH_TIMER(t)    screen::utils::Profiler::Instance()->attachTimer((t));
#  define SCREEN_ATTACH_PROFILE_REPORTER(r) screen::utils::Profiler::Instance()->attachReporter((r));
#  define SCREEN_SCOPE_PROFILE(s)    screen::utils::ProfileScope _pScope((s));
# else
#  define SCREEN_ATTACH_TIMER(t)
#  define SCREEN_ATTACH_PROFILE_REPORTER(r)
#  define SCREEN_SCOPE_PROFILE(s)
# endif

#endif
