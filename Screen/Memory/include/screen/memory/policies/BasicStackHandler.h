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

#ifndef SCREEN_MEMORY_POLICIES_BASIC_STACK_HANDLER_H
#define SCREEN_MEMORY_POLICIES_BASIC_STACK_HANDLER_H

#include <screen/utils/Declaration.h>
#include <screen/memory/BufferBase.h>
#include <screen/memory/Export.h>

namespace screen{
	namespace memory{
		namespace policies{
			class BufferPolicyHandlerInterface;

			template<class StackSelectorPolicy>
			class SCREEN_MEMORY_EXPORT BasicStackHandler{
				SCREEN_DECL_CLASS(screen::memory::policies::BasicStackHandler);
			public:
				BasicStackHandler(BufferPolicyHandlerInterface* interface);
				~BasicStackHandler();

				BufferBase* getNewBufferBase(unsigned int size);
				void addToUnlocked(BufferBase* bufferBase);
				BufferBase* replaceBufferBase(BufferBase* oldBufferBase, unsigned int newSize);
				unsigned int garbage();

				enum {
					minBufferSize = StackSelectorPolicy::minBufferSize,
					maxBufferSize = StackSelectorPolicy::maxBufferSize,
					numberOfStacks = StackSelectorPolicy::numberOfStacks
				};
			private:
				BufferPolicyHandlerInterface* interface;

				std::map<void*,BufferBase> buffers[numberOfStacks];
				std::stack<BufferBase*> unlockedBuffers[numberOfStacks];
				std::map<void*,BufferBase> bigBuffers;
			};
		}
	}
}

#endif
