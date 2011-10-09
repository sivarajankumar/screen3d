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

#ifndef SCREEN_MEMORY_BUFFER_H
#define SCREEN_MEMORY_BUFFER_H

#include <screen/utils/Declaration.h>
#include <screen/memory/Export.h>

namespace screen {
    namespace memory {
		class BufferBase;
		
		class SCREEN_MEMORY_EXPORT Buffer {
        	SCREEN_DECL_CLASS(screen::memory::Buffer)
        public:
			typedef void* pointer;
			typedef const void* const_pointer;

			Buffer();
			Buffer(const Buffer& buffer);
			const Buffer& operator= (const Buffer& buffer);
            virtual ~Buffer();

			void setAt(unsigned int position,const void* buffer, unsigned int size);
			const void* getAt(unsigned int position) const;
			void* getAt(unsigned int position);
			unsigned int size() const;
			unsigned int effectiveSize() const;
			void allocate(unsigned int size);
				
			void unlock();
		protected:
			bool isLocked() const;
			void swap(const Buffer& buffer);

			BufferBase* bufferBase;
        };
    }
}

#endif
