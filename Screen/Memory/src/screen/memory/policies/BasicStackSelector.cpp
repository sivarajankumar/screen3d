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
 * \file screen/memory/policies/BasicStackHandler.cpp
 * \brief Buffer stack selector source file
 * \author
 *
 */

#include <screen/memory/policies/BasicStackSelector.h>
#include <screen/memory/policies/BufferPolicyHandler.h>
#include <screen/math/Other.h>
#include <screen/utils/Exception.h>

namespace screen{
	namespace memory{
		namespace policies{
			BasicStackSelector::BasicStackSelector(BufferPolicyHandlerInterface* ioInterface)
				:_interface(ioInterface){
				SCREEN_DECL_CONSTRUCTOR(StackSelector);
			}

			int BasicStackSelector::calculateStackNumber(unsigned int iSize){
				SCREEN_DECL_METHOD(calculateStackNumber);
				unsigned int aTmp = iSize;
				unsigned int aRet = SCREEN_MEMORY_DEFAULT_MIN_SIZE;
				unsigned int aNumber = 0;

				while (aTmp > SCREEN_MEMORY_DEFAULT_MIN_SIZE){
					aTmp /= SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER;
					aRet *= SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER;
					++aNumber;
				}

				return aRet >= iSize ? aNumber : aNumber+1;
			}

			unsigned int BasicStackSelector::calculateSizeFromStack(int iStackNumber){
				SCREEN_DECL_METHOD(calculateSizeFromStack);
				return SCREEN_MEMORY_DEFAULT_MIN_SIZE*screen::math::power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,iStackNumber);
			}
		}
	}
}
