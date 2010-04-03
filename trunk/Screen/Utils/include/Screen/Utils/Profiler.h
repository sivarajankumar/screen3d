/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2009 Ratouit Thomas                                    *
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

#ifndef SCREEN_PROFILER_H
#define SCREEN_PROFILER_H

#include <vector>
#include <Screen/Utils/Singleton.h>
#include <Screen/Utils/Policies.h>
#include <Screen/Utils/Export.h>

namespace Screen {
    namespace Utils {
        class ProfilerReporter;
        class Timer;

        struct SCREEN_UTILS_EXPORT Profile {
            std::string info;
            double beginning;
            double ending;
            bool ended;
        };

        class SCREEN_UTILS_EXPORT Profiler : public UniqueSingleton<Profiler> {
        	SINGLETON_DECL(UniqueSingleton,Profiler)
            friend class ProfileScope;
        public:
            void attachTimer(Screen::Utils::Timer* timer);
            void attachReporter(ProfilerReporter* reporter);
        private:
            void attachProfile(Profile* profile);
            Profiler();
            ~Profiler();

            Screen::Utils::Timer* timer;
            typedef std::vector<Profile*> ProfileSet;
            ProfileSet allProfiles;
            ProfilerReporter* reporter;
        };

        class SCREEN_UTILS_EXPORT ProfileScope {
        public:
            ProfileScope(const std::string& info);
            ~ProfileScope();
        private:
            Profile* profile;
        };
    }
}

# ifdef SCREEN_AUTHORIZE_PROFILE
#  define SCREEN_ATTACH_TIMER(t)    Screen::Utils::Profiler::instance()->attachTimer((t));
#  define SCREEN_ATTACH_PROFILE_REPORTER(r) Screen::Utils::Profiler::instance()->attachReporter((r));
#  define SCREEN_SCOPE_PROFILE(s)    Screen::Utils::ProfileScope _pScope((s));
# else
#  define SCREEN_ATTACH_TIMER(t)
#  define SCREEN_ATTACH_PROFILE_REPORTER(r)
#  define SCREEN_SCOPE_PROFILE(s)
# endif

#endif
