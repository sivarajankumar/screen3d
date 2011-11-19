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
/**
 * \file screen/memory/policies/BasicStackHandler.h
 * \brief Buffer stack selector header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_POLICIES_STACK_SELECTOR_H
#define SCREEN_MEMORY_POLICIES_STACK_SELECTOR_H

#include <screen/utils/Declaration.h>
#include <screen/memory/Defaults.h>
#include <screen/memory/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all memory classes
	 */
	namespace memory {
		/**
		 * Namespace for all policies classes
		 */
		namespace policies{
			class BufferPolicyHandlerInterface;

			/**
			 * \brief Class to compute stack number from expected buffer size and real buffer size from stack number.
			 *
			 * The main role of this class is to hidden stack number computing from other processes.
			 * Buffers have 2 size, the expected size and the real size (see BufferBase.h)
			 *
			 */
			class SCREEN_MEMORY_EXPORT BasicStackSelector{
				SCREEN_DECL_CLASS(screen::memory::policies::BasicStackSelector);
			public:

				/**
				 * \brief Constructor with common buffer policy interface.
				 *
				 * \param[in,out] ioInterface Common buffer policy interface
				 */
				BasicStackSelector(BufferPolicyHandlerInterface* ioInterface);

				/**
				 * \brief Compute stack number from expected buffer size
				 *
				 * \param[in] iSize expected buffer size
				 * \return Returns stack number
				 */
				int calculateStackNumber(unsigned int iSize);

				/**
				 * \brief Compute real buffer size from stack number
				 *
				 * \param[in] iStackNumber stack number
				 * \return Returns real buffer size
				 */
				unsigned int calculateSizeFromStack(int iStackNumber);

				/**
				 * \brief Class to compute number of stack at compile time.
				 *
				 * \tparam iMin Minimum buffer size
				 * \tparam iMax Maximum buffer size
				 * \tparam iMultiplier Multiplier for buffer size
				 *
				 */
				template <unsigned int iMin, unsigned int iMax, unsigned int iMultiplier>
				struct NumberOfStacks {
					enum{ RESULT = NumberOfStacks<iMin*iMultiplier, iMax, iMultiplier >::RESULT+1 };
				};

				/**
				 * \brief Class to compute number of stack at compile time.
				 *
				 * \tparam iValue Buffer size
				 * \tparam iMultiplier Multiplier for buffer size
				 *
				 */
				template <unsigned int iValue, unsigned int iMultiplier>
				struct NumberOfStacks<iValue, iValue, iMultiplier> {
					enum{ RESULT = 1 };
				};

				enum {
					MIN_BUFFER_SIZE = SCREEN_MEMORY_DEFAULT_MIN_SIZE, ///< minimum buffer size
					MAX_BUFFER_SIZE = SCREEN_MEMORY_DEFAULT_MAX_SIZE, ///< maximum buffer size
					NUMBER_OF_STACKS = NumberOfStacks<
						SCREEN_MEMORY_DEFAULT_MIN_SIZE,
						SCREEN_MEMORY_DEFAULT_MAX_SIZE,
						SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER >::RESULT ///< number of stacks in stack handler
				};
			private:
				BufferPolicyHandlerInterface* _interface; ///< common buffer policy interface
			};
		}
	}
}

#endif
