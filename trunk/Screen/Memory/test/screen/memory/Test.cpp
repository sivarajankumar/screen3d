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

#include <screen/memory/Test.h>
#include <screen/memory/Buffer.h>
#include <screen/memory/BufferManager.h>
#include <screen/memory/TypedBuffer.h>
#include <screen/memory/Defaults.h>
#include <screen/math/Other.h>

CPPUNIT_TEST_SUITE_REGISTRATION(screen::memory::Test);

using screen::math::power;

namespace screen {
	namespace memory {
		void Test::testBufferCreation(){
			Buffer buf1;
			CPPUNIT_ASSERT(buf1.size()==0);
			CPPUNIT_ASSERT(buf1.getAt(0)==NULL);
			CPPUNIT_ASSERT(buf1.getAt(4000)==NULL);

			const char* hello = "hello world !!";
			buf1.setAt(0,hello,strlen(hello)+1);

			CPPUNIT_ASSERT(buf1.size()==strlen(hello)+1);
			CPPUNIT_ASSERT(buf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(strcmp(static_cast<const char*>(buf1.getAt(0)),hello)==0);
			CPPUNIT_ASSERT(strcmp(static_cast<const char*>(buf1.getAt(2)),&hello[2])==0);			
		}

		void Test::testBufferImproveSize(){
			Buffer buf1;
			unsigned long magic = 42;

			//minimum border test
			buf1.setAt(0,&magic,sizeof(unsigned long));
			unsigned long ret = *(static_cast<const unsigned long*>(buf1.getAt(0)));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf1.size() == sizeof(unsigned long));
			CPPUNIT_ASSERT(buf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			//before next border
			buf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE-sizeof(unsigned long),&magic,sizeof(unsigned long));
			ret = *(static_cast<const unsigned long*>(buf1.getAt(0)));
			CPPUNIT_ASSERT(ret == 42);
			ret = *(static_cast<const unsigned long*>(buf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf1.size() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);
			CPPUNIT_ASSERT(buf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			//after next border
			buf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE,&magic,sizeof(unsigned long));
			ret = *(static_cast<const unsigned long*>(buf1.getAt(0)));
			CPPUNIT_ASSERT(ret == 42);
			ret = *(static_cast<const unsigned long*>(buf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(ret == 42);
			ret = *(static_cast<const unsigned long*>(buf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE)));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf1.size() == SCREEN_MEMORY_DEFAULT_MIN_SIZE+sizeof(unsigned long));
			CPPUNIT_ASSERT(buf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);
		}

		void Test::testBigBuffer(){
			Buffer buf1;
			unsigned long magic = 42;
			//minimum border test
			buf1.setAt(0,&magic,sizeof(unsigned long));
			unsigned long ret = *(static_cast<const unsigned long*>(buf1.getAt(0)));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf1.size() == sizeof(unsigned long));
			CPPUNIT_ASSERT(buf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			//before next border
			buf1.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE-sizeof(unsigned long),&magic,sizeof(unsigned long));
			ret = *(static_cast<const unsigned long*>(buf1.getAt(0)));
			CPPUNIT_ASSERT(ret == 42);
			ret = *(static_cast<const unsigned long*>(buf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf1.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE);
			CPPUNIT_ASSERT(buf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE);

			//after next border
			buf1.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE,&magic,sizeof(unsigned long));
			ret = *(static_cast<const unsigned long*>(buf1.getAt(0)));
			CPPUNIT_ASSERT(ret == 42);
			ret = *(static_cast<const unsigned long*>(buf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(ret == 42);
			ret = *(static_cast<const unsigned long*>(buf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE)));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf1.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE+sizeof(unsigned long));
			CPPUNIT_ASSERT(buf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);

			//create buffer from void
			Buffer buf2;
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE,&magic,sizeof(unsigned long));
			ret = *(static_cast<const unsigned long*>(buf2.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE)));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf2.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE+sizeof(unsigned long));
			CPPUNIT_ASSERT(buf2.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);

			//improve big buffer effective size
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,&magic,sizeof(unsigned long));
			ret = *(static_cast<const unsigned long*>(buf2.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE)));
			CPPUNIT_ASSERT(ret == 42);
			ret = *(static_cast<const unsigned long*>(buf2.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER)));
			CPPUNIT_ASSERT(ret == 42);
			CPPUNIT_ASSERT(buf2.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER+sizeof(unsigned long));
			CPPUNIT_ASSERT(buf2.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);
		}

		void Test::testGarbage(){
			unsigned long magic = 42;
			
			//first garbage in order to not be impacted by over tests
			BufferManager::instance()->garbage();
			
			Buffer buf1;
			buf1.setAt(0,&magic,sizeof(unsigned long));
			buf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE,&magic,sizeof(unsigned long));

			CPPUNIT_ASSERT(BufferManager::instance()->garbage()==SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			Buffer buf2;
			buf2.setAt(0,&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE,&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,2),&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,3),&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,4),&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,5),&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE,&magic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,&magic,sizeof(unsigned long));

			unsigned int value = SCREEN_MEMORY_DEFAULT_MIN_SIZE+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,2)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,3)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,4)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,5)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,6);
			CPPUNIT_ASSERT(BufferManager::instance()->garbage()==value);
		}

		void Test::testTypedBuffer(){
			TypedBuffer<long> buf1;
			CPPUNIT_ASSERT(buf1.size()==0);
			CPPUNIT_ASSERT(buf1.getAt(0)==NULL);
			CPPUNIT_ASSERT(buf1.getAt(4000)==NULL);

			//simple tests
			long magic = 42;
			buf1.setAt(0,&magic,1);

			CPPUNIT_ASSERT(buf1.size()==1);
			CPPUNIT_ASSERT(buf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*buf1.getAt(0)==42);
			
			long table[] = {1234, 5678};
			buf1.setAt(1,table,2);

			CPPUNIT_ASSERT(buf1.size()==3);
			CPPUNIT_ASSERT(buf1.effectiveSize()==SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long));
			CPPUNIT_ASSERT(buf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*buf1.getAt(0)==42);
			CPPUNIT_ASSERT(*buf1.getAt(1)==1234);
			CPPUNIT_ASSERT(*buf1.getAt(2)==5678);

			//improve effective size
			buf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long),&magic,1);
			CPPUNIT_ASSERT(buf1.size()==SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long)+1);
			CPPUNIT_ASSERT(buf1.effectiveSize()==SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER/sizeof(long));
			CPPUNIT_ASSERT(buf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*buf1.getAt(0)==42);
			CPPUNIT_ASSERT(*buf1.getAt(1)==1234);
			CPPUNIT_ASSERT(*buf1.getAt(2)==5678);
			CPPUNIT_ASSERT(*buf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long))==42);

			//big buffer
			buf1.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE/sizeof(long),&magic,1);
			CPPUNIT_ASSERT(buf1.size()==SCREEN_MEMORY_DEFAULT_MAX_SIZE/sizeof(long)+1);
			CPPUNIT_ASSERT(buf1.effectiveSize()==SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER/sizeof(long));
			CPPUNIT_ASSERT(buf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*buf1.getAt(0)==42);
			CPPUNIT_ASSERT(*buf1.getAt(1)==1234);
			CPPUNIT_ASSERT(*buf1.getAt(2)==5678);
			CPPUNIT_ASSERT(*buf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long))==42);
			CPPUNIT_ASSERT(*buf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE/sizeof(long))==42);			
		}
	}
}
