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

#include <screen/memory/AllocBufferMap.h>
#include <screen/memory/BufferBase.h>

namespace screen {
    namespace memory {
		SINGLETON_IMPL(UniqueSingleton,AllocBufferMap)
	
    	void AllocBufferMap::addBufferBase(const void* ptr, BufferBase* buf){
    		bufferBaseMap[ptr] = buf;
    	}
    	
    	BufferBase* AllocBufferMap::popBufferBase(const void* ptr) const{
    		std::map<const void*, BufferBase*>::const_iterator it = bufferBaseMap.find(ptr);
    		if(it == bufferBaseMap.end()){
    			SCREEN_LOG_WARNING("Can't find buffer base for address " << ptr);
    			return NULL;
    		}
    		else{
    			BufferBase* buf = it->second;
    			
    			//optimisation tip : instead of cleaning map member, just set as NULL
    			const_cast<BufferBase*&>(it->second) = NULL;
    			
    			return buf;
    		}
    	}
    }
}
