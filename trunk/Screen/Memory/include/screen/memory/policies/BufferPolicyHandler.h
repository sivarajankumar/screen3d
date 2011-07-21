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

#ifndef SCREEN_MEMORY_POLICIES_BUFFER_POLICY_HANDLER_H
#define SCREEN_MEMORY_POLICIES_BUFFER_POLICY_HANDLER_H

#include <screen/utils/Declaration.h>
#include <screen/memory/BufferManager.h>
#include <screen/memory/policies/CreateWithMalloc.h>

namespace screen{
	namespace memory{
		namespace policies{
			class BufferPolicyHandlerInterface{
			public:
				virtual void* createBuffer(size_t bufferSize) = 0;
			};

			template <class CreationPolicy = screen::memory::policies::CreateWithMalloc>
			class BufferPolicyHandler : public BufferPolicyHandlerInterface{
			public:
				BufferPolicyHandler(screen::memory::BufferManager& bufferManager)
					:creationPolicy(bufferManager)
				{}

				void* createBuffer(size_t bufferSize){
					creationPolicy.createBuffer(bufferSize);
				}

			private:
				CreationPolicy creationPolicy;
			};
		}
	}
}

#endif
