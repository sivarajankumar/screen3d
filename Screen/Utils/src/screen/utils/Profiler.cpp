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
 * \file screen/utils/Profiler.cpp
 * \brief Screen/Utils profile log handling source file
 * \author
 *
 */

#include <screen/utils/Profiler.h>
#include <screen/utils/ProfilerReporter.h>
#include <screen/utils/Exception.h>
#include <screen/utils/Timer.h>
#include <iostream>

SINGLETON_IMPL(UniqueSingleton,screen::utils::Profiler)

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        Profiler::Profiler()
                :UniqueSingleton<Profiler>(),_timer(new screen::utils::Timer()),_reporter(NULL) {}

        Profiler::~Profiler() {
            if(_reporter!=NULL){
                for (ProfileSet::const_iterator aIt = _allProfiles.begin(); aIt != _allProfiles.end(); ++aIt){
                    Profile* aProfile = (*aIt);
                    SCREEN_ASSERT(aProfile!=NULL);
                    _reporter->report(aProfile);
                    delete aProfile;
                    aProfile = NULL;
                }
                delete _reporter;
                _reporter = NULL;
            }
            else{
                for (ProfileSet::const_iterator aIt = _allProfiles.begin(); aIt != _allProfiles.end(); ++aIt){
                    Profile* aProfile = (*aIt);
                    delete aProfile;
                    aProfile = NULL;
                }
            }
            delete _timer;
            _timer = NULL;
        }

        void Profiler::attachTimer(screen::utils::Timer* iTimer) {
            delete _timer;
            _timer = iTimer;
        }

        void Profiler::attachReporter(ProfilerReporter* iReporter) {
            delete _reporter;
            _reporter = iReporter;
        }

        void Profiler::attachProfile(Profile* iProfile) {
            _allProfiles.push_back(iProfile);
        }

        ProfileScope::ProfileScope(const std::string& iInfo)
                :_profile(new screen::utils::Profile()) {
            _profile->_info=iInfo;
            _profile->_ended=false;
            _profile->_ending=0;
            Profiler::Instance()->attachProfile(_profile);
            _profile->_beginning = Profiler::Instance()->_timer->getMilliseconds();
        }

        ProfileScope::~ProfileScope() {
            _profile->_ending= Profiler::Instance()->_timer->getMilliseconds();
            _profile->_ended=true;
        }
    }
}
