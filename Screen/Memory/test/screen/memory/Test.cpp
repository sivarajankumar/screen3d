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
#include <screen/memory/Allocator.h>
#include <screen/math/Other.h>
#include <screen/utils/Timer.h>
#include <boost/pool/pool_alloc.hpp>
#include <vector>

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
			
			BufferManager::instance()->garbage();
		}
		
		void Test::testAllocator(){
			std::vector<long,screen::memory::Allocator<long> > vec1;
			vec1.push_back(42);
			CPPUNIT_ASSERT(vec1[0]==42);
			CPPUNIT_ASSERT(vec1.size()==1);			
			BufferManager::instance()->garbage();
		}
		
		template<template <class> class Alloc>
		void testOneVector(){
			std::vector<long,Alloc<long> > vec1;
			for(long i = 0; i<10000000; i++){
				vec1.push_back(i);
			}
		}
		
		template<template <class> class Alloc>
		void testMultiVector(){
			std::vector<long,Alloc<long> > vec1[1000];
			for(int i = 0; i<1000; i++){
				for(long j = 0; j<100000; j++){
					vec1[i].push_back(j);
				}
			}
		}
		
		template<template <class> class Alloc>
		void testOneVectorManualSize(){
			int size = 20;
			std::vector<long,Alloc<long> > vec1(size);
			for(long i = 0; i<10000000; i++){
				if(i>=size){
					size*=2;
					vec1.resize(size);
				}
				vec1[i]=i;
			}
		}
		
		template<template <class> class Alloc>
		void testMultiVectorManualSize(){
			std::vector<long,Alloc<long> > vec1[1000];
			for(long i = 0; i<1000; i++){
				int size = 20;
				vec1[i].resize(size);
				for(long j = 0; j<100000; j++){
					if(j>=size){
						size*=2;
						vec1[i].resize(size);
					}
					vec1[i][j] = j;
				}
			}
		}
		
		void Test::testStressAllocator(){
			BufferManager::instance()->garbage();
			screen::utils::Timer timer;
			
			double stlOne = 0.0;
			double stlMulti = 0.0;
			double stlOneManual = 0.0;
			double stlMultiManual = 0.0;
			double poolOne = 0.0;
			double poolMulti = 0.0;
			double poolOneManual = 0.0;
			double poolMultiManual = 0.0;
			double fastPoolOne = 0.0;
			double fastPoolMulti = 0.0;
			double fastPoolOneManual = 0.0;
			double fastPoolMultiManual = 0.0;
			double screenOne = 0.0;
			double screenMulti = 0.0;
			double screenOneManual = 0.0;
			double screenMultiManual = 0.0;
			
			//stl stress test
			{
				timer.reset();
				testOneVector<std::allocator>();
				stlOne = timer.getSeconds();
				
				timer.reset();
				testMultiVector<std::allocator>();
				stlMulti = timer.getSeconds();
				
				timer.reset();
				testOneVectorManualSize<std::allocator>();
				stlOneManual = timer.getSeconds();
				
				timer.reset();
				testMultiVectorManualSize<std::allocator>();
				stlMultiManual = timer.getSeconds();
			}
			//boost pool stress test
			{
				timer.reset();
				testOneVector<boost::pool_allocator>();
				poolOne = timer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
				
				timer.reset();
				testMultiVector<boost::pool_allocator>();
				poolMulti = timer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
				
				timer.reset();
				testOneVectorManualSize<boost::pool_allocator>();
				poolOneManual = timer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
				
				timer.reset();
				testMultiVectorManualSize<boost::pool_allocator>();
				poolMultiManual = timer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
			}
			//boost fast pool stress test
			/*{
				timer.reset();
				testOneVector<boost::fast_pool_allocator>();
				fastPoolOne = timer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
				
				timer.reset();
				testMultiVector<boost::fast_pool_allocator>();
				fastPoolMulti = timer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
				
				timer.reset();
				testOneVectorManualSize<boost::fast_pool_allocator>();
				fastPoolOneManual = timer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
				
				timer.reset();
				testMultiVectorManualSize<boost::fast_pool_allocator>();
				fastPoolMultiManual = timer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
			}*/
			//screen memory stress test
			{
				timer.reset();
				testOneVector<screen::memory::Allocator>();
				screenOne = timer.getSeconds();
				
				BufferManager::instance()->garbage();
				
				timer.reset();
				testMultiVector<screen::memory::Allocator>();
				screenMulti = timer.getSeconds();
				
				BufferManager::instance()->garbage();

				timer.reset();
				testOneVectorManualSize<screen::memory::Allocator>();
				screenOneManual = timer.getSeconds();
				
				BufferManager::instance()->garbage();
				
				timer.reset();
				testMultiVectorManualSize<screen::memory::Allocator>();
				screenMultiManual = timer.getSeconds();
				
				BufferManager::instance()->garbage();

			}

			
			SCREEN_LOG_INFO("Stress Result : ");
			SCREEN_LOG_INFO("    * STL : [" << stlOne << ", " << stlMulti << ", " << stlOneManual << ", " << stlMultiManual << "]");
			SCREEN_LOG_INFO("    * Boost.pool : [" << poolOne << ", " << poolMulti << ", " << poolOneManual << ", " << poolMultiManual << "]");
			//SCREEN_LOG_INFO("    * Boost.fast_pool : [" << fastPoolOne << ", " << fastPoolMulti << ", " << fastPoolOneManual << ", " << fastPoolMultiManual << "]");
			SCREEN_LOG_INFO("    * Screen.Memory : [" << screenOne << ", " << screenMulti << ", " << screenOneManual << ", " << screenMultiManual << "]");
		}
	}
}
