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
 * \file screen/memory/AllocBufferMap.cpp
 * \brief Screen memory allocation buffer map source file
 * \author
 *
 */

#include <screen/memory/AllocBufferMap.h>
#include <screen/memory/BufferBase.h>

namespace screen {
    namespace memory {
		SINGLETON_IMPL(UniqueSingleton,AllocBufferMap)
	
		void AllocBufferMap::addBufferBase(const void* iPtr, BufferBase* iBuf){
			_bufferBaseMap[iPtr] = iBuf;
    	}
    	
		BufferBase* AllocBufferMap::popBufferBase(const void* iPtr) const{
			std::map<const void*, BufferBase*>::const_iterator aIt = _bufferBaseMap.find(iPtr);
			if(aIt == _bufferBaseMap.end()){
				SCREEN_LOG_WARNING("Can't find buffer base for address " << iPtr);
    			return NULL;
    		}
    		else{
				BufferBase* aBuf = aIt->second;
    			
    			//optimisation tip : instead of cleaning map member, just set as NULL
				const_cast<BufferBase*&>(aIt->second) = NULL;
    			
				return aBuf;
    		}
    	}
    }
}
