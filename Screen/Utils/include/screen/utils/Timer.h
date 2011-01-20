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

#ifndef SCREEN_TIMER_H
#define SCREEN_TIMER_H

#include <screen/utils/Declaration.h>

#ifdef WIN32
#include <windows.h>
#else
#include <ctime>
#endif

namespace screen {
    namespace utils {
        class Timer {
        public:
            inline explicit Timer() {
#ifdef WIN32
            	QueryPerformanceFrequency(&frequency);
#endif
                reset();
            }
            inline ~Timer() {}
            inline void reset() {
#ifdef WIN32
            	QueryPerformanceCounter(&start);
#else
                start = std::clock();
#endif
            }
#ifdef WIN32
            inline double getSeconds() const {
            	LARGE_INTEGER current;
            	QueryPerformanceCounter(&current);
                return (current.QuadPart - start.QuadPart) / static_cast<double>(frequency.QuadPart);
            }
            inline double getMilliseconds() const {
            	LARGE_INTEGER current;
            	QueryPerformanceCounter(&current);
                return ((current.QuadPart - start.QuadPart)*1000) / static_cast<double>(frequency.QuadPart);
            }
            inline double getMicroseconds() const {
            	LARGE_INTEGER current;
            	QueryPerformanceCounter(&current);
                return ((current.QuadPart - start.QuadPart)*1000000) / static_cast<double>(frequency.QuadPart);
            }
#else
            inline double getSeconds() const {
                return ((double) (std::clock()-start))/((double) CLOCKS_PER_SEC);
            }
            inline double getMilliseconds() const {
            	return (unsigned long) (((double) (std::clock()-start))* ((1000.0) / ((double) CLOCKS_PER_SEC)));
            }
            inline double getMicroseconds() const {
                return (unsigned long) (((double) (std::clock()-start))* ((1000000.0) / ((double) CLOCKS_PER_SEC)));
            }
#endif
        private:
#ifdef WIN32
        	LARGE_INTEGER frequency;
        	LARGE_INTEGER start;
#else
            unsigned long start;
#endif
        };
    }
}

#endif
