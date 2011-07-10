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

#ifndef SCREEN_MEMORY_TEST_H
#define SCREEN_MEMORY_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace screen {
	namespace memory {
		class Test : public CppUnit::TestFixture {
			CPPUNIT_TEST_SUITE(Test);
			CPPUNIT_TEST(testBufferCreation);
			CPPUNIT_TEST(testBufferImproveSize);
			CPPUNIT_TEST(testBigBuffer);
			CPPUNIT_TEST(testGarbage);
			CPPUNIT_TEST(testTypedBuffer);
			CPPUNIT_TEST(testAllocator);
#ifdef SCREEN_MEMORY_RUN_STRESS_TEST
			CPPUNIT_TEST(testStressAllocator);
#endif
			CPPUNIT_TEST_SUITE_END();
		public:
			void testBufferCreation();
			void testBufferImproveSize();
			void testBigBuffer();
			void testGarbage();
			void testTypedBuffer();
			void testAllocator();
			void testStressAllocator();
		};
	}
}

#endif
