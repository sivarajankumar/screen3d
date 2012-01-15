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
 * \file screen/utils/ProfilerReporter.h
 * \brief Screen/Utils profile data output handling header file
 * \author
 *
 */

#ifndef SCREEN_PROFILER_REPORTER_H
#define SCREEN_PROFILER_REPORTER_H

#include <screen/utils/Export.h>
#include <fstream>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {
    	struct Profile;

        /**
         * \brief Interface for all profile reporters
         */
        class SCREEN_UTILS_EXPORT ProfilerReporter {
        public:
            /**
             * \brief Default constructor
             */
            ProfilerReporter();

            /**
             * \brief Destructor
             */
            virtual ~ProfilerReporter();

            /**
             * \brief Log profile data
             *
             * \param[in] iProfile the profile data to log
             */
            virtual void report(Profile* iProfile) = 0;
        };

        /**
         * \brief Standard output profile reporter
         *
         * Writes the profile data into the console
         */
        class SCREEN_UTILS_EXPORT CoutProfilerReporter : public ProfilerReporter {
        public:
            /**
             * \brief Log profile data
             *
             * \param[in] iProfile the profile data to log
             */
            void report(Profile* iProfile);
        };
        
        /**
         * \brief File output profile reporter
         *
         * Writes the profile data into a given file
         */
        class SCREEN_UTILS_EXPORT FileProfilerReporter : public ProfilerReporter {
        public:
            FileProfilerReporter(const char* iFile);
            /**
             * \brief Log profile data
             *
             * \param[in] iProfile the profile data to log
             */
            void report(Profile* iProfile);
        private:
            const char* _file; ///< File path
        };
    }
}
#endif
