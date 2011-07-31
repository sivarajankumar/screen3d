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

#ifndef SCREEN_MEMORY_POLICIES_STACK_SELECTOR_H
#define SCREEN_MEMORY_POLICIES_STACK_SELECTOR_H

#include <screen/utils/Declaration.h>
#include <screen/memory/Defaults.h>
#include <screen/memory/Export.h>

namespace screen{
	namespace memory{
		namespace policies{
			class BufferPolicyHandlerInterface;

			class SCREEN_MEMORY_EXPORT BasicStackSelector{
				SCREEN_DECL_CLASS(screen::memory::policies::BasicStackSelector);
			public:
				BasicStackSelector(BufferPolicyHandlerInterface* interface);
				int calculateStackNumber(unsigned int size);
				unsigned int calculateSizeFromStack(int stackNumber);

				template <unsigned int min, unsigned int max, unsigned int multiplier>
				struct _NumberOfStacks {
					enum{ result = _NumberOfStacks<min*multiplier, max, multiplier >::result+1 };
				};

				template <unsigned int value, unsigned int multiplier>
				struct _NumberOfStacks<value, value, multiplier> {
					enum{ result = 1 };
				};

				enum {
					minBufferSize = SCREEN_MEMORY_DEFAULT_MIN_SIZE,
					maxBufferSize = SCREEN_MEMORY_DEFAULT_MAX_SIZE,
					numberOfStacks = _NumberOfStacks<
						SCREEN_MEMORY_DEFAULT_MIN_SIZE,
						SCREEN_MEMORY_DEFAULT_MAX_SIZE,
						SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER >::result
				};
			private:
				BufferPolicyHandlerInterface* interface;
			};
		}
	}
}

#endif
