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

#include <screen/utils/Profiler.h>
#include <screen/utils/ProfilerReporter.h>
#include <screen/utils/Exception.h>
#include <screen/utils/Timer.h>
#include <iostream>

SINGLETON_IMPL(UniqueSingleton,screen::utils::Profiler)

screen::utils::Profiler::Profiler()
        :UniqueSingleton<Profiler>(),timer(new screen::utils::Timer()),reporter(NULL) {}

screen::utils::Profiler::~Profiler() {
    if(reporter!=NULL){
		for (ProfileSet::const_iterator i = allProfiles.begin(); i != allProfiles.end(); ++i){
			Profile* profile = (*i);
            SCREEN_ASSERT(profile!=NULL);
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
	}
	delete timer;
}

void screen::utils::Profiler::attachTimer(screen::utils::Timer* timer) {
	delete this->timer;
    this->timer = timer;
}

void screen::utils::Profiler::attachReporter(screen::utils::ProfilerReporter* reporter) {
    delete this->reporter;
    this->reporter = reporter;
}

void screen::utils::Profiler::attachProfile(Profile* profile) {
    allProfiles.push_back(profile);
}

screen::utils::ProfileScope::ProfileScope(const std::string& info)
        :profile(new screen::utils::Profile()) {
    profile->info=info;
    profile->ended=false;
    profile->ending=0;
	Profiler::Instance()->attachProfile(profile);
	profile->beginning=Profiler::Instance()->timer->getMilliseconds();
}

screen::utils::ProfileScope::~ProfileScope() {
	profile->ending=Profiler::Instance()->timer->getMilliseconds();
    profile->ended=true;
}
