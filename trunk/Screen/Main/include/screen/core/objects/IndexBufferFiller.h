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

#ifndef SCREEN_INDEX_BUFFER_FILLER_H
#define SCREEN_INDEX_BUFFER_FILLER_H

#include <screen/utils/SmartPtr.h>
#include <screen/utils/Any.h>
#include <screen/core/Enums.h>
#include <screen/memory/TypedBuffer.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen{
	namespace core{
		namespace objects{
			class SCREEN_MAIN_EXPORT IndexBufferFiller{
				SCREEN_DECL_CLASS(screen::core::objects::IndexBufferFiller);

				friend class Setter;
			public:
				IndexBufferFiller();
				~IndexBufferFiller();

				void setAt(unsigned int i, unsigned int value);
				void getAt(unsigned int i, unsigned int& value) const;
				
				template <class T>
				const T* get() const;
				unsigned int getSize() const;
				unsigned int getIndexSize() const;

				typedef screen::utils::SmartPtr<IndexBufferFiller> SmartPtr;
			private:
				unsigned int stepSize;
				screen::utils::Any buffer;
			};
			
			template <class T>
			const T* IndexBufferFiller::get() const{
				SCREEN_DECL_METHOD(get);
				if(stepSize == 2)
				{
					const screen::memory::TypedBuffer<unsigned short>* shortBuffer =
							screen::utils::any_cast<screen::memory::TypedBuffer<unsigned short> >
							(&buffer);
#ifdef SCREEN_AUTHORIZE_LOG_DEBUG
					SCREEN_LOG_DEBUG("buffer");
					std::stringstream s;
					s << "|";
					const unsigned short* bufferContent = shortBuffer->getAt(0);
					size_t size = shortBuffer->size();
					for(int i=0; i<size; i++){
						s << bufferContent[i] << "|";
					}
					SCREEN_LOG_DEBUG(s.str());
#endif
					return reinterpret_cast<const T*>(shortBuffer->getAt(0));
				}
				else
				{
					const screen::memory::TypedBuffer<unsigned long>* longBuffer =
							screen::utils::any_cast<screen::memory::TypedBuffer<unsigned long> >
							(&buffer);
#ifdef SCREEN_AUTHORIZE_LOG_DEBUG
					SCREEN_LOG_DEBUG("buffer");
					std::stringstream s;
					s << "|";
					const unsigned long* bufferContent = longBuffer->getAt(0);
					size_t size = longBuffer->size();
					for(int i=0; i<size; i++){
						s << bufferContent[i] << "|";
					}
					SCREEN_LOG_DEBUG(s.str());
#endif
					return reinterpret_cast<const T*>(longBuffer->getAt(0));
				}
			}
		}
	}
}

#endif

