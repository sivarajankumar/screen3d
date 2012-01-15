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
 * \file screen/utils/SingletonLazyInstance.h
 * \brief Screen/Utils singleton lazy instance handler header file
 * \author
 *
 */

#ifndef SCREEN_SINGLETON_LAZY_INSTANCE_MGR_H
#define SCREEN_SINGLETON_LAZY_INSTANCE_MGR_H

#include <screen/utils/Export.h>
#include <stack>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {
        class SingletonLazyInstanceInterface;
		
        /**
         * \brief Singleton lazy instance manager.
         *
         * It handles all singleton instance for UniqueSingleton model.
         * The current model only allow lazy instance destruction in the reverse order of the instanciation.
         * It ensure for example the Logger instance will be destroy at the last end if it is instanciated first.
         */
        class SCREEN_UTILS_EXPORT SingletonLazyInstanceManager{
			public:
                /**
                 * \brief Register a lazy instance
                 *
                 * \param[in,out] ioBase The lazy instance interface to register
                 */
				static void registerLazy(SingletonLazyInstanceInterface* ioBase);
			private:
                /**
                 * \brief Default constructor
                 */
				SingletonLazyInstanceManager();

                /**
                 * \brief Destructor
                 */
				~SingletonLazyInstanceManager();

                static SingletonLazyInstanceManager _Instance; ///< global instance for SingletonLazyInstanceManager
                std::stack<SingletonLazyInstanceInterface*> _stack; ///< lazy instance stack
		};
	}
}

#endif

