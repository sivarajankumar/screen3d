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
 * \file screen/memory/BufferManager.cpp
 * \brief Screen memory buffer manager source file
 * \author
 *
 */

#include <screen/memory/BufferManager.h>
#include <screen/utils/Exception.h>
#include <malloc.h>

namespace screen {
	namespace memory {
		SINGLETON_IMPL(UniqueSingleton,BufferManager);

		BufferManager::BufferManager(){
			SCREEN_DECL_CONSTRUCTOR(BufferManager);
			_policy = new screen::memory::policies::BufferPolicyHandler<>();
		}
		BufferManager::~BufferManager(){
			SCREEN_DECL_DESTRUCTOR(~BufferManager);
		}

		BufferBase* BufferManager::getNewBufferBase(unsigned int iSize){
			SCREEN_DECL_METHOD(getNewBufferBase);
			return _policy->getNewBufferBase(iSize);
		}

		void BufferManager::addToUnlocked(BufferBase* iBufferBase){
			SCREEN_DECL_METHOD(addToUnlocked);
			_policy->addToUnlocked(iBufferBase);
		}

		BufferBase* BufferManager::replaceBufferBase(BufferBase* iOldBufferBase, unsigned int iNewSize){
			SCREEN_DECL_METHOD(replaceBufferBase);
			return _policy->replaceBufferBase(iOldBufferBase,iNewSize);
		}

		unsigned int BufferManager::garbage(){
			SCREEN_DECL_METHOD(garbage);
			return _policy->garbage();
		}

		int BufferManager::calculateStackNumber(unsigned int iSize){
			SCREEN_DECL_METHOD(calculateStackNumber);
			return _policy->calculateStackNumber(iSize);
		}

		unsigned int BufferManager::calculateSizeFromStack(int iStackNumber){
			SCREEN_DECL_METHOD(calculateSizeFromStack);
			return _policy->calculateSizeFromStack(iStackNumber);
		}
	}
}
