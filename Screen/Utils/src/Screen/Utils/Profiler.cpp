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

#include <Screen/Utils/Profiler.h>
#include <Screen/Utils/ProfilerReporter.h>
#include <Screen/Utils/Exception.h>
#include <Screen/Utils/Timer.h>
#include <iostream>

SINGLETON_IMPL(UniqueSingleton,Screen::Utils::Profiler)

Screen::Utils::Profiler::Profiler()
        :UniqueSingleton<Profiler>(),reporter(NULL) {}

Screen::Utils::Profiler::~Profiler() {
    if(reporter!=NULL){
		for (ProfileSet::const_iterator i = allProfiles.begin(); i != allProfiles.end(); ++i){
			Profile* profile = (*i);
			Assert(profile!=NULL);
			reporter->report(profile);
			delete profile;
		}
		delete reporter;
	}
	else{
		for (ProfileSet::const_iterator i = allProfiles.begin(); i != allProfiles.end(); ++i){
			Profile* profile = (*i);
			delete profile;
		}
		delete reporter;
	}
}

void Screen::Utils::Profiler::attachTimer(Screen::Utils::Timer* timer) {
    this->timer = timer;
}

void Screen::Utils::Profiler::attachReporter(Screen::Utils::ProfilerReporter* reporter) {
    if(this->reporter!=NULL)
        delete this->reporter;
    this->reporter = reporter;
}

void Screen::Utils::Profiler::attachProfile(Profile* profile) {
    allProfiles.push_back(profile);
}

Screen::Utils::ProfileScope::ProfileScope(const std::string& info)
        :profile(new Screen::Utils::Profile()) {
    profile->info=info;
    profile->ended=false;
    profile->ending=0;
    Profiler::instance()->attachProfile(profile);
    profile->beginning=Profiler::instance()->timer->getMilliseconds();
}

Screen::Utils::ProfileScope::~ProfileScope() {
    profile->ending=Profiler::instance()->timer->getMilliseconds();
    profile->ended=true;
}
