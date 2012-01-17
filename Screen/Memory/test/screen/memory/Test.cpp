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
			Buffer aBuf1;
			CPPUNIT_ASSERT(aBuf1.size()==0);
			CPPUNIT_ASSERT(aBuf1.getAt(0)==NULL);
			CPPUNIT_ASSERT(aBuf1.getAt(4000)==NULL);

			const char* aHello = "hello world !!";
			aBuf1.setAt(0,aHello,strlen(aHello)+1);

			CPPUNIT_ASSERT(aBuf1.size()==strlen(aHello)+1);
			CPPUNIT_ASSERT(aBuf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(strcmp(static_cast<const char*>(aBuf1.getAt(0)),aHello)==0);
			CPPUNIT_ASSERT(strcmp(static_cast<const char*>(aBuf1.getAt(2)),&aHello[2])==0);
		}

		void Test::testBufferImproveSize(){
			Buffer aBuf1;
			unsigned long aMagic = 42;

			//minimum border test
			aBuf1.setAt(0,&aMagic,sizeof(unsigned long));
			unsigned long aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(0)));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(aBuf1.size() == sizeof(unsigned long));
			CPPUNIT_ASSERT(aBuf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			//before next border
			aBuf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE-sizeof(unsigned long),&aMagic,sizeof(unsigned long));
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(0)));
			CPPUNIT_ASSERT(aRet == 42);
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(aBuf1.size() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);
			CPPUNIT_ASSERT(aBuf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			//after next border
			aBuf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE,&aMagic,sizeof(unsigned long));
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(0)));
			CPPUNIT_ASSERT(aRet == 42);
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(aRet == 42);
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE)));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(aBuf1.size() == SCREEN_MEMORY_DEFAULT_MIN_SIZE+sizeof(unsigned long));
			CPPUNIT_ASSERT(aBuf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);
		}

		void Test::testBigBuffer(){
			Buffer aBuf1;
			unsigned long aMagic = 42;
			//minimum border test
			aBuf1.setAt(0,&aMagic,sizeof(unsigned long));
			unsigned long aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(0)));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(aBuf1.size() == sizeof(unsigned long));
			CPPUNIT_ASSERT(aBuf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			//before next border
			aBuf1.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE-sizeof(unsigned long),&aMagic,sizeof(unsigned long));
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(0)));
			CPPUNIT_ASSERT(aRet == 42);
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(aBuf1.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE);
			CPPUNIT_ASSERT(aBuf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE);

			//after next border
			aBuf1.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE,&aMagic,sizeof(unsigned long));
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(0)));
			CPPUNIT_ASSERT(aRet == 42);
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE-sizeof(unsigned long))));
			CPPUNIT_ASSERT(aRet == 42);
			aRet = *(static_cast<const unsigned long*>(aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE)));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(aBuf1.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE+sizeof(unsigned long));
			CPPUNIT_ASSERT(aBuf1.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);

			//create buffer from void
			Buffer buf2;
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE,&aMagic,sizeof(unsigned long));
			aRet = *(static_cast<const unsigned long*>(buf2.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE)));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(buf2.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE+sizeof(unsigned long));
			CPPUNIT_ASSERT(buf2.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);

			//improve big buffer effective size
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,&aMagic,sizeof(unsigned long));
			aRet = *(static_cast<const unsigned long*>(buf2.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE)));
			CPPUNIT_ASSERT(aRet == 42);
			aRet = *(static_cast<const unsigned long*>(buf2.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER)));
			CPPUNIT_ASSERT(aRet == 42);
			CPPUNIT_ASSERT(buf2.size() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER+sizeof(unsigned long));
			CPPUNIT_ASSERT(buf2.effectiveSize() == SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER);
		}

		void Test::testGarbage(){
			unsigned long aMagic = 42;
			
			//first garbage in order to not be impacted by over tests
			BufferManager::Instance()->garbage();
			
			Buffer aBuf1;
			aBuf1.setAt(0,&aMagic,sizeof(unsigned long));
			aBuf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE,&aMagic,sizeof(unsigned long));

			CPPUNIT_ASSERT(BufferManager::Instance()->garbage()==SCREEN_MEMORY_DEFAULT_MIN_SIZE);

			Buffer buf2;
			buf2.setAt(0,&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE,&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,2),&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,3),&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,4),&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,5),&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE,&aMagic,sizeof(unsigned long));
			buf2.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,&aMagic,sizeof(unsigned long));

			unsigned int value = SCREEN_MEMORY_DEFAULT_MIN_SIZE+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,2)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,3)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,4)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,5)+
				SCREEN_MEMORY_DEFAULT_MIN_SIZE*power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,6);
			CPPUNIT_ASSERT(BufferManager::Instance()->garbage()==value);
		}

		void Test::testTypedBuffer(){
			TypedBuffer<long> aBuf1;
			CPPUNIT_ASSERT(aBuf1.size()==0);
			CPPUNIT_ASSERT(aBuf1.getAt(0)==NULL);
			CPPUNIT_ASSERT(aBuf1.getAt(4000)==NULL);

			//simple tests
			long aMagic = 42;
			aBuf1.setAt(0,&aMagic,1);

			CPPUNIT_ASSERT(aBuf1.size()==1);
			CPPUNIT_ASSERT(aBuf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*aBuf1.getAt(0)==42);
			
			long aTable[] = {1234, 5678};
			aBuf1.setAt(1,aTable,2);

			CPPUNIT_ASSERT(aBuf1.size()==3);
			CPPUNIT_ASSERT(aBuf1.effectiveSize()==SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long));
			CPPUNIT_ASSERT(aBuf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*aBuf1.getAt(0)==42);
			CPPUNIT_ASSERT(*aBuf1.getAt(1)==1234);
			CPPUNIT_ASSERT(*aBuf1.getAt(2)==5678);

			//improve effective size
			aBuf1.setAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long),&aMagic,1);
			CPPUNIT_ASSERT(aBuf1.size()==SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long)+1);
			CPPUNIT_ASSERT(aBuf1.effectiveSize()==SCREEN_MEMORY_DEFAULT_MIN_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER/sizeof(long));
			CPPUNIT_ASSERT(aBuf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*aBuf1.getAt(0)==42);
			CPPUNIT_ASSERT(*aBuf1.getAt(1)==1234);
			CPPUNIT_ASSERT(*aBuf1.getAt(2)==5678);
			CPPUNIT_ASSERT(*aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long))==42);

			//big buffer
			aBuf1.setAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE/sizeof(long),&aMagic,1);
			CPPUNIT_ASSERT(aBuf1.size()==SCREEN_MEMORY_DEFAULT_MAX_SIZE/sizeof(long)+1);
			CPPUNIT_ASSERT(aBuf1.effectiveSize()==SCREEN_MEMORY_DEFAULT_MAX_SIZE*SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER/sizeof(long));
			CPPUNIT_ASSERT(aBuf1.getAt(0)!=NULL);
			CPPUNIT_ASSERT(*aBuf1.getAt(0)==42);
			CPPUNIT_ASSERT(*aBuf1.getAt(1)==1234);
			CPPUNIT_ASSERT(*aBuf1.getAt(2)==5678);
			CPPUNIT_ASSERT(*aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MIN_SIZE/sizeof(long))==42);
			CPPUNIT_ASSERT(*aBuf1.getAt(SCREEN_MEMORY_DEFAULT_MAX_SIZE/sizeof(long))==42);
			
			BufferManager::Instance()->garbage();
		}
		
		void Test::testAllocator(){
			std::vector<long,screen::memory::Allocator<long> > aVec1;
			aVec1.push_back(42);
			CPPUNIT_ASSERT(aVec1[0]==42);
			CPPUNIT_ASSERT(aVec1.size()==1);
			BufferManager::Instance()->garbage();
		}
		
		template<class Alloc>
		void testOneVector(){
			std::vector<long,Alloc > aVec1;
			for(long aIt = 0; aIt<10000000; aIt++){
				aVec1.push_back(aIt);
			}
		}
		
		template<class Alloc>
		void testMultiVector(){
			std::vector<long,Alloc > aVec1[1000];
			for(int aIt = 0; aIt<1000; aIt++){
				for(long aIt2 = 0; aIt2<100000; aIt2++){
					aVec1[aIt].push_back(aIt2);
				}
			}
		}
		
		template<class Alloc>
		void testOneVectorManualSize(){
			int aSize = 20;
			std::vector<long,Alloc > aVec1(aSize);
			for(long aIt = 0; aIt<10000000; aIt++){
				if(aIt>=aSize){
					aSize*=2;
					aVec1.resize(aSize);
				}
				aVec1[aIt]=aIt;
			}
		}

		template<class Alloc>
		void testMultiVectorManualSize(){
			std::vector<long,Alloc > aVec1[1000];
			for(long aIt = 0; aIt<1000; aIt++){
				int aSize = 20;
				aVec1[aIt].resize(aSize);
				for(long aIt2 = 0; aIt2<100000; aIt2++){
					if(aIt2>=aSize){
						aSize*=2;
						aVec1[aIt].resize(aSize);
					}
					aVec1[aIt][aIt2] = aIt2;
				}
			}
		}
		
		void Test::testStressAllocator(){
			BufferManager::Instance()->garbage();
			screen::utils::Timer aTimer;
			
			double aStlOne = 0.0;
			double aStlMulti = 0.0;
			double aStlOneManual = 0.0;
			double aStlMultiManual = 0.0;
			double aPoolOne = 0.0;
			double aPoolMulti = 0.0;
			double aPoolOneManual = 0.0;
			double aPoolMultiManual = 0.0;
			double aFastPoolOne = 0.0;
			double aFastPoolMulti = 0.0;
			double aFastPoolOneManual = 0.0;
			double aFastPoolMultiManual = 0.0;
			double aScreenOne = 0.0;
			double aScreenMulti = 0.0;
			double aScreenOneManual = 0.0;
			double aScreenMultiManual = 0.0;
			
			//stl stress test
			{
				aTimer.reset();
				testOneVector<std::allocator<long> >();
				aStlOne = aTimer.getSeconds();
				
				aTimer.reset();
				testMultiVector<std::allocator<long> >();
				aStlMulti = aTimer.getSeconds();
				
				aTimer.reset();
				testOneVectorManualSize<std::allocator<long> >();
				aStlOneManual = aTimer.getSeconds();
				
				aTimer.reset();
				testMultiVectorManualSize<std::allocator<long> >();
				aStlMultiManual = aTimer.getSeconds();
			}
			//boost pool stress test
			{
				aTimer.reset();
				testOneVector<boost::pool_allocator<long> >();
				aPoolOne = aTimer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
				
				aTimer.reset();
				testMultiVector<boost::pool_allocator<long> >();
				aPoolMulti = aTimer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
				
				aTimer.reset();
				testOneVectorManualSize<boost::pool_allocator<long> >();
				aPoolOneManual = aTimer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
				
				aTimer.reset();
				testMultiVectorManualSize<boost::pool_allocator<long> >();
				aPoolMultiManual = aTimer.getSeconds();
				
				boost::singleton_pool<boost::pool_allocator_tag, sizeof(long)>::release_memory();
			}
			//boost fast pool stress test
			/*{
				aTimer.reset();
				testOneVector<boost::fast_pool_allocator>();
				aFastPoolOne = aTimer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
				
				aTimer.reset();
				testMultiVector<boost::fast_pool_allocator>();
				aFastPoolMulti = aTimer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
				
				aTimer.reset();
				testOneVectorManualSize<boost::fast_pool_allocator>();
				aFastPoolOneManual = aTimer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
				
				aTimer.reset();
				testMultiVectorManualSize<boost::fast_pool_allocator>();
				aFastPoolMultiManual = aTimer.getSeconds();
				
				boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(long)>::release_memory();
			}*/
			//screen memory stress test
			{
				aTimer.reset();
				testOneVector<screen::memory::Allocator<long> >();
				aScreenOne = aTimer.getSeconds();
				
				BufferManager::Instance()->garbage();
				
				aTimer.reset();
				testMultiVector<screen::memory::Allocator<long> >();
				aScreenMulti = aTimer.getSeconds();
				
				BufferManager::Instance()->garbage();

				aTimer.reset();
				testOneVectorManualSize<screen::memory::Allocator<long> >();
				aScreenOneManual = aTimer.getSeconds();
				
				BufferManager::Instance()->garbage();
				
				aTimer.reset();
				testMultiVectorManualSize<screen::memory::Allocator<long> >();
				aScreenMultiManual = aTimer.getSeconds();
				
				BufferManager::Instance()->garbage();
			}

			
			SCREEN_LOG_INFO("Stress Result : ");
			SCREEN_LOG_INFO("    * STL : [" << aStlOne << ", " << aStlMulti << ", " << aStlOneManual << ", " << aStlMultiManual << "]");
			SCREEN_LOG_INFO("    * Boost.pool : [" << aPoolOne << ", " << aPoolMulti << ", " << aPoolOneManual << ", " << aPoolMultiManual << "]");
			//SCREEN_LOG_INFO("    * Boost.fast_pool : [" << aFastPoolOne << ", " << aFastPoolMulti << ", " << aFastPoolOneManual << ", " << aFastPoolMultiManual << "]");
			SCREEN_LOG_INFO("    * Screen.Memory : [" << aScreenOne << ", " << aScreenMulti << ", " << aScreenOneManual << ", " << aScreenMultiManual << "]");
		}
	}
}
