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

#include <screen/memory/algorithms/Test.h>
#include <screen/memory/Buffer.h>
#include <screen/memory/BufferManager.h>
#include <screen/memory/TypedBuffer.h>
#include <screen/memory/Defaults.h>
#include <screen/memory/algorithms/BufferConverter.h>

CPPUNIT_TEST_SUITE_REGISTRATION(screen::memory::algorithms::Test);


namespace screen {
	namespace memory {
		namespace algorithms {
			void Test::testBufferConverter(){
				screen::memory::TypedBuffer<unsigned char> aCharBuffer;

				unsigned char aFourtyTwo = 42;
				unsigned char aSexyNumber = 69;
				aCharBuffer.setAt(0,&aFourtyTwo,1);
				aCharBuffer.setAt(1,&aSexyNumber,1);

				CPPUNIT_ASSERT(aCharBuffer.size() == 2);

				screen::memory::TypedBuffer<unsigned long> aLongBuffer;

				CPPUNIT_ASSERT(aLongBuffer.size() == 0);

				screen::memory::algorithms::TypedBufferConverter<
						unsigned char,
						unsigned long,
						screen::memory::algorithms::DefautTypedBufferConverterFunc
							<unsigned char, unsigned long> >
					aConverter;

				aConverter.convert(aCharBuffer,aLongBuffer);

				CPPUNIT_ASSERT(aLongBuffer.size() == 2);

				unsigned long* aLongTable = aLongBuffer.getAt(0);

				CPPUNIT_ASSERT(aLongTable[0] == 42);
				CPPUNIT_ASSERT(aLongTable[1] == 69);

				screen::memory::BufferManager::Instance()->garbage();
			}
		}
	}
}
