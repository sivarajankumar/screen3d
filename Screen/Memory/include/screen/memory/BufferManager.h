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

#ifndef SCREEN_MEMORY_BUFFER_MANAGER_H
#define SCREEN_MEMORY_BUFFER_MANAGER_H

#include <screen/utils/Singleton.h>
#include <screen/utils/Declaration.h>
#include <screen/utils/SmartPtr.h>
#include <screen/memory/Export.h>
#include <screen/memory/BufferBase.h>
#include <screen/memory/Defaults.h>
#include <screen/memory/policies/BufferPolicyHandler.h>
#include <stack>
#include <set>

namespace screen {
	namespace memory {
		class SCREEN_MEMORY_EXPORT BufferManager : public screen::utils::UniqueSingleton<BufferManager>{
			SCREEN_DECL_CLASS(screen::memory::BufferManager);
			SINGLETON_DECL(UniqueSingleton,BufferManager);
			friend class Buffer;
		public:
			BufferManager();
			~BufferManager();

			void attachPolicyHandler(screen::memory::policies::BufferPolicyHandlerInterface* policy);

			BufferBase* getNewBufferBase(unsigned int size);
			void addToUnlocked(BufferBase* bufferBase);
			BufferBase* replaceBufferBase(BufferBase* oldBufferBase, unsigned int newSize);
			unsigned int garbage();

		private:
			static int calculateStackNumber(unsigned int size);
			static unsigned int calculateSizeFromStack(int stackNumber);
					
			template <unsigned int min, unsigned int max, unsigned int multiplier>
			struct _NumberOfStacks {
				enum{ result = _NumberOfStacks<min*multiplier, max, multiplier >::result+1 };
			};

			template <unsigned int value, unsigned int multiplier>
			struct _NumberOfStacks<value, value, multiplier> {
				enum{ result = 1 };
			};

			static const unsigned int numberOfStack = _NumberOfStacks<
					SCREEN_MEMORY_DEFAULT_MIN_SIZE,
					SCREEN_MEMORY_DEFAULT_MAX_SIZE,
					SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER >::result;

			std::map<void*,BufferBase> buffers[numberOfStack];
			std::stack<BufferBase*> unlockedBuffers[numberOfStack];
			std::map<void*,BufferBase> bigBuffers;

			screen::utils::SmartPtr<
				screen::memory::policies::BufferPolicyHandlerInterface,
				screen::utils::ScopePolicy> policy;
		};
	}
}

#endif
