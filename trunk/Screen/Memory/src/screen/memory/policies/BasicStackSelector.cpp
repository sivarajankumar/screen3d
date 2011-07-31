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

#include <screen/memory/policies/BasicStackSelector.h>
#include <screen/memory/policies/BufferPolicyHandler.h>
#include <screen/math/Other.h>
#include <screen/utils/Exception.h>

namespace screen{
	namespace memory{
		namespace policies{
			BasicStackSelector::BasicStackSelector(BufferPolicyHandlerInterface* interface)
				:interface(interface){
				SCREEN_DECL_CONSTRUCTOR(StackSelector);
			}

			int BasicStackSelector::calculateStackNumber(unsigned int size){
				SCREEN_DECL_METHOD(calculateStackNumber);
				unsigned int tmp = size;
				unsigned int ret = SCREEN_MEMORY_DEFAULT_MIN_SIZE;
				unsigned int number = 0;

				while (tmp > SCREEN_MEMORY_DEFAULT_MIN_SIZE){
					tmp /= SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER;
					ret *= SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER;
					++number;
				}

				return ret >= size ? number : number+1;
			}

			unsigned int BasicStackSelector::calculateSizeFromStack(int stackNumber){
				SCREEN_DECL_METHOD(calculateSizeFromStack);
				return SCREEN_MEMORY_DEFAULT_MIN_SIZE*screen::math::power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,stackNumber);
			}
		}
	}
}
