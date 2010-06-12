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

#ifndef SCREEN_MEMORY_BUFFER_BASE_H
#define SCREEN_MEMORY_BUFFER_BASE_H

#include <Screen/Utils/Declaration.h>
#include <Screen/Memory/Export.h>

namespace Screen {
    namespace Memory {
		class SCREEN_MEMORY_EXPORT BufferBase {
        	SCREEN_DECL_CLASS(Screen::Memory::BufferBase)
        public:
			BufferBase();
            BufferBase(void* bufferPtr, unsigned int size);
			BufferBase(const BufferBase& bufferBase);
			const BufferBase& operator=(const BufferBase& bufferBase);
            ~BufferBase();

			const void* getBuffer() const;
			void* getBuffer();

			unsigned int getSize() const;
			void setSize(unsigned int size);

		private:
			void* bufferPtr;
			unsigned int size;
        };
    }
}

#endif
