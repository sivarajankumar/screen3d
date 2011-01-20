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

#ifndef SCREEN_THREAD_H
#define SCREEN_THREAD_H

#include <boost/thread.hpp>

namespace Screen {
    namespace Utils {

        /*!  \class NullMutexType
          *  \brief Empty type, do nothing. For single threading
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct NullMutexType {}
        ;

        /*!  \class NullScopeLock
          *  \brief mutex scope lock For single threading. Do nothing.
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct NullScopeLock {
            NullScopeLock(NullMutexType mutex) {}
            ~NullScopeLock() {}
            typedef NullMutexType MutexType;
        };

        /*!  \class SingleThreadingModel
          *  \brief Model for single thread object.
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct SingleThreadingModel {
            typedef struct NullScopeLock ScopeLockType;
            typedef NullScopeLock::MutexType MutexType;
        };

        /*!  \class MultipleThreadingModel
          *  \brief Model for single thread object.
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct MultipleThreadingModel {
            typedef boost::mutex::scoped_lock ScopeLockType;
            typedef boost::mutex MutexType;
        };
    }
}

#endif
