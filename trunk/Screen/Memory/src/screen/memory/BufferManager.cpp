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

#include <screen/memory/BufferManager.h>
#include <screen/utils/Exception.h>
#include <malloc.h>

namespace screen {
	namespace memory {
		SINGLETON_IMPL(UniqueSingleton,BufferManager);

		BufferManager::BufferManager(){
			SCREEN_DECL_CONSTRUCTOR(BufferManager);
			policy = new screen::memory::policies::BufferPolicyHandler<>();
		}
		BufferManager::~BufferManager(){
			SCREEN_DECL_DESTRUCTOR(~BufferManager);
		}

		BufferBase* BufferManager::getNewBufferBase(unsigned int size){
			SCREEN_DECL_METHOD(getNewBufferBase);
			return policy->getNewBufferBase(size);
		}

		void BufferManager::addToUnlocked(BufferBase* bufferBase){
			SCREEN_DECL_METHOD(addToUnlocked);
			policy->addToUnlocked(bufferBase);
		}

		BufferBase* BufferManager::replaceBufferBase(BufferBase* oldBufferBase, unsigned int newSize){
			SCREEN_DECL_METHOD(replaceBufferBase);
			return policy->replaceBufferBase(oldBufferBase,newSize);
		}

		unsigned int BufferManager::garbage(){
			SCREEN_DECL_METHOD(garbage);
			return policy->garbage();
		}

		int BufferManager::calculateStackNumber(unsigned int size){
			SCREEN_DECL_METHOD(calculateStackNumber);
			return policy->calculateStackNumber(size);
		}

		unsigned int BufferManager::calculateSizeFromStack(int stackNumber){
			SCREEN_DECL_METHOD(calculateSizeFromStack);
			return policy->calculateSizeFromStack(stackNumber);
		}
	}
}
