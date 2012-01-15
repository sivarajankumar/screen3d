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

#ifndef SCREEN_BUFFER_BASE_H
#define SCREEN_BUFFER_BASE_H

#include <screen/core/Enums.h>
#include <screen/main/Export.h>
#include <screen/utils/Declaration.h>
#include <screen/utils/SmartPtr.h>

namespace screen {
	namespace core {
		namespace objects {
			
			/** This class defines the API representation of a buffer of the render system 
			 @remarks
			 	Instances of BufferBase are creted by the 3D API 
			 */
			class SCREEN_MAIN_EXPORT BufferBase{
				SCREEN_DECL_CLASS(screen::core::Object::BufferBase)
				template <class T> friend class Buffer;
		    public :
		        virtual ~BufferBase();
		        
		        typedef screen::utils::SmartPtr<BufferBase> SmartPtr;
		    protected :

		        BufferBase(unsigned long count);
		        virtual void* lock(unsigned long offset, unsigned long size, screen::core::LockFlag flags) = 0;
		        virtual void unlock() = 0;
		        
		        unsigned long count; // buffer element number
		    };
		}
	}
}

#endif
