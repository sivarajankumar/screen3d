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
 * \file screen/memory/policies/CreateWithMalloc.cpp
 * \brief Memory allocation policy interface source file
 * \author
 *
 */

#include <screen/memory/policies/CreateWithMalloc.h>
#include <screen/memory/policies/BufferPolicyHandler.h>
#include <screen/utils/Exception.h>

namespace screen{
	namespace memory{
		namespace policies{
			CreateWithMalloc::CreateWithMalloc(BufferPolicyHandlerInterface* ioInterface)
				:_interface(ioInterface){
				SCREEN_DECL_CONSTRUCTOR(CreateWithMalloc);
			}

			void* CreateWithMalloc::createBuffer(size_t iBufferSize){
				SCREEN_DECL_METHOD(createBuffer);
				void* aBuffer = ::malloc(iBufferSize);
				if(aBuffer==NULL){
					_interface->garbage();
					aBuffer = ::malloc(iBufferSize);
					if(aBuffer==NULL){
						std::stringstream aSs;
						aSs << "Unable to allocate a buffer of size " << iBufferSize;
						throw screen::utils::Exception(aSs.str());
					}
				}
				return aBuffer;
			}
		}
	}
}
