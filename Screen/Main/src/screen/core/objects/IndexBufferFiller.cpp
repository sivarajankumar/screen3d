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

#include <screen/core/objects/IndexBufferFiller.h>
#include <screen/core/objects/IndexBufferInterpreter.h>
#include <screen/memory/algorithms/BufferConverter.h>

namespace screen{
	namespace core{
		namespace objects{
			struct ShortToLongFunctor{
				SCREEN_DECL_CLASS(ShortToLongFunctor)

				void operator() (const unsigned short& input, unsigned long& output){
					SCREEN_DECL_METHOD(operator());
					output = input;
				}
			};

			struct Setter{
				SCREEN_DECL_CLASS(Setter)

						Setter(screen::core::objects::IndexBufferFiller& filler, unsigned int pos, unsigned int value)
					:filler(filler),pos(pos), value(value){}

				void operator()(screen::memory::TypedBuffer<unsigned short>& shortBuffer) const{
					SCREEN_DECL_METHOD(operator());
					if(value > 65535){
						SCREEN_LOG_INFO("Transform short index buffer into long one");
						//move from short buffer to long buffer
						screen::memory::TypedBuffer<unsigned long> newLongBuffer;
						screen::memory::algorithms::TypedBufferConverter<
								unsigned short,
								unsigned long,
								ShortToLongFunctor > converter;

						converter.convert(shortBuffer,newLongBuffer);

						//set the value in the new buffer
						unsigned long longValue = value;
						newLongBuffer.setAt(pos,&longValue,1);

						//set the new long buffer as filler buffer
						filler.buffer = newLongBuffer;
						//change step size for long buffer
						filler.stepSize = 4;
					}
					else
					{
						unsigned short shortValue = value;
						shortBuffer.setAt(pos,&shortValue,1);
					}
				}

				void operator()(screen::memory::TypedBuffer<unsigned long>& longBuffer){
					SCREEN_DECL_METHOD(operator());
					unsigned long longValue = value;
					longBuffer.setAt(pos,&longValue,1);
				}

				screen::core::objects::IndexBufferFiller& filler;
				unsigned int pos;
				unsigned int value;
			};

			struct Getter{
				SCREEN_DECL_CLASS(Getter)

				Getter(unsigned int pos, unsigned int &value):pos(pos), value(value){}

				void operator()(const screen::memory::TypedBuffer<unsigned short>& shortBuffer){
					SCREEN_DECL_METHOD(operator());
					const unsigned short* buffer = shortBuffer.getAt(pos);
					value = buffer[0];
				}

				void operator()(const screen::memory::TypedBuffer<unsigned long>& longBuffer){
					SCREEN_DECL_METHOD(operator());
					const unsigned long* buffer = longBuffer.getAt(pos);
					value = buffer[0];
				}

				unsigned int pos;
				unsigned int& value;
			};

			struct Sizer{
				SCREEN_DECL_CLASS(Sizer)

				Sizer(unsigned int &size):size(size){}

				void operator()(const screen::memory::TypedBuffer<unsigned short>& shortBuffer){
					SCREEN_DECL_METHOD(operator());
					size = shortBuffer.size();
				}

				void operator()(const screen::memory::TypedBuffer<unsigned long>& longBuffer){
					SCREEN_DECL_METHOD(operator());
					size = longBuffer.size();
				}

				unsigned int& size;
			};


			IndexBufferFiller::IndexBufferFiller()
				:stepSize(2),buffer(screen::memory::TypedBuffer<unsigned short>()){
				SCREEN_DECL_CONSTRUCTOR(IndexBufferFiller);
			}
			
			IndexBufferFiller::~IndexBufferFiller(){
				SCREEN_DECL_DESTRUCTOR(IndexBufferFiller);
			}
						
			void IndexBufferFiller::setAt(unsigned int i, unsigned int value){
				SCREEN_DECL_METHOD(setAt);

				IndexBufferInterpreter<Setter> setter(Setter(*this,i,value));
				setter(buffer);
			}
			
			void IndexBufferFiller::getAt(unsigned int i, unsigned int& value) const{
				SCREEN_DECL_METHOD(getAt);
				IndexBufferInterpreter<Getter> getter(Getter(i,value));
				getter(buffer);
			}
			
			unsigned int IndexBufferFiller::getSize() const{
				SCREEN_DECL_METHOD(getSize);
				unsigned int size = 0;
				IndexBufferInterpreter<Sizer> sizer(size);
				sizer(buffer);
				return size;
			}

			unsigned int IndexBufferFiller::getIndexSize() const{
				SCREEN_DECL_METHOD(getIndexSize);
				return stepSize;
			}
		}
	}
}
