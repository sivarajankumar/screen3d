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

#include <screen/test/TestBuffer.h>
#include <screen/core/objects/BufferBase.h>
#include <screen/core/objects/Buffer.h>
#include <screen/core/objects/IndexBuffer.h>
#include <screen/core/objects/IndexBufferFiller.h>
#include <screen/core/objects/VertexBuffer.h>
#include <screen/core/objects/VertexBufferFiller.h>
#include <screen/core/objects/VertexFormat.h>
#include <screen/core/Enums.h>
#include <screen/test/utils/FakeRenderer.h>

CPPUNIT_TEST_SUITE_REGISTRATION(screen::test::TestBuffer);

#define BUFFER_SIZE 1000

struct Vertex1{
	float x, y, z;
	unsigned long Color;
	float tu, tv;
};

namespace screen {
	namespace test {
		class FakeBufferBase : public screen::core::objects::BufferBase {
		public:
			FakeBufferBase()
				:screen::core::objects::BufferBase(1000)
			{}
			
			void* lock(unsigned long offset, unsigned long size, screen::core::LockFlag flags){
				static unsigned char buffer[BUFFER_SIZE] = {'\0'};
				return buffer + offset;
			}
			void unlock(){
				
			}
		};
		
		class FakeBufferRenderer : public screen::test::utils::FakeRenderer{
		public:
			FakeBufferRenderer(){}		
			virtual ~FakeBufferRenderer(){}
			
			virtual screen::core::objects::BufferBase* createVB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const{
				return new FakeBufferBase;
			}
	        virtual screen::core::objects::BufferBase* createIB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const{
	        	return new FakeBufferBase;
	        }
	        virtual void setVB(const screen::core::objects::BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const screen::core::VertexFormat& vf){
	        	
	        }
	        virtual void setIB(const screen::core::objects::BufferBase* buffer, unsigned long stride){
	        	
	        }
		};
	
		void TestBuffer::testBuffer(){
			FakeBufferRenderer renderer;
		}
		void TestBuffer::testIndexBuffer(){
			FakeBufferRenderer renderer;
		}
		void TestBuffer::testVertexBuffer(){
			using namespace screen::core::objects;
			using namespace screen::core;
			
			FakeBufferRenderer renderer;
			
			//vertex format 1
			VertexFormat::SmartPtr vf1(new VertexFormat());
			vf1->add(VERTEX_USAGE_POSITION,VERTEX_TYPE_FLOAT3);
			vf1->add(VERTEX_USAGE_DIFFUSE,VERTEX_TYPE_COLOR);
			vf1->add(VERTEX_USAGE_TEXCOORD0,VERTEX_TYPE_FLOAT2);
			vf1->lock();
			
			//vertex format 2
			VertexFormat::SmartPtr vf2(new VertexFormat());
			vf2->add(VERTEX_USAGE_POSITION,VERTEX_TYPE_FLOAT3);
			vf2->add(VERTEX_USAGE_TEXCOORD0,VERTEX_TYPE_FLOAT2);
			vf2->lock();
			
			try{
				vf2->add(VERTEX_USAGE_DIFFUSE,VERTEX_TYPE_COLOR);
				CPPUNIT_FAIL("doesn't throw a exception");
			} catch(const screen::utils::Exception& e) {
				CPPUNIT_ASSERT(std::string(e.what()) == "[screen exception] Vertex format modified after lock");
			} catch(...) {
				CPPUNIT_FAIL("throws a bad exception");;
			}
			
			
			//vertices
            
			Vertex1 Vertices1[] =
			{
				{-1.0f, -1.0f,  1.0f, renderer.convertColor(0xFF0000FF), 0.0f, 1.0f},
				{-1.0f,  1.0f,  1.0f, renderer.convertColor(0xFFFF00FF), 0.0f, 0.0f},
				{ 1.0f,  1.0f,  1.0f, renderer.convertColor(0xFFFFFF00), 1.0f, 0.0f},
				{ 1.0f, -1.0f,  1.0f, renderer.convertColor(0xFFFF0000), 1.0f, 1.0f},
				{-1.0f, -1.0f, -1.0f, renderer.convertColor(0xFF00FFFF), 0.0f, 1.0f},
				{-1.0f,  1.0f, -1.0f, renderer.convertColor(0xFFFFFFFF), 0.0f, 0.0f},
				{ 1.0f,  1.0f, -1.0f, renderer.convertColor(0xFF00FF00), 1.0f, 0.0f},
				{ 1.0f, -1.0f, -1.0f, renderer.convertColor(0xFFFFC0C0), 1.0f, 1.0f}
			};
			
			VertexBuffer<Vertex1> vb1 = renderer.createVertexBuffer<Vertex1>(8,STATIC_DRAW,Vertices1,vf1);
			VertexBuffer<void> vb2 = renderer.createVertexBuffer<void>(8,STATIC_DRAW,Vertices1,vf1);
			try{
				VertexBuffer<Vertex1> vb3 = renderer.createVertexBuffer<Vertex1>(8,STATIC_DRAW,Vertices1,vf2);
				CPPUNIT_FAIL("doesn't throw a exception");
			} catch(const screen::utils::Exception& e) {
				std::stringstream ss;
				ss << "[screen exception] "
				   << "different size between vertex element type and vertex format size\n"
				   << "\t- Element type size = " << sizeof(Vertex1) << "\n"
				   << "\t- Vertex format size = " << vf2->getSize() << "\n";
				CPPUNIT_ASSERT(std::string(e.what()) == ss.str());
			} catch(...) {
				CPPUNIT_FAIL("throws a bad exception");
			}
			VertexBuffer<void> vb4 = renderer.createVertexBuffer<void>(8,STATIC_DRAW,Vertices1,vf2);
		}

		void TestBuffer::testIndexBufferFiller(){
			screen::core::objects::IndexBufferFiller indexBufferFiller;
			indexBufferFiller.setAt(0,42);
			indexBufferFiller.setAt(1,69);

			//basic tests

			unsigned int fourtyTwo = 0;
			indexBufferFiller.getAt(0,fourtyTwo);
			CPPUNIT_ASSERT(fourtyTwo == 42);

			unsigned int sexyNumber = 0;
			indexBufferFiller.getAt(1,sexyNumber);
			CPPUNIT_ASSERT(sexyNumber == 69);

			CPPUNIT_ASSERT(indexBufferFiller.getIndexSize() == 2);

			const unsigned short* shortBuffer = indexBufferFiller.get<unsigned short>();
			CPPUNIT_ASSERT(shortBuffer[0] == 42);
			CPPUNIT_ASSERT(shortBuffer[1] == 69);

			//short -> long convertion tests
			indexBufferFiller.setAt(4000,65536);

			unsigned int big = 0;
			indexBufferFiller.getAt(4000,big);
			CPPUNIT_ASSERT(big == 65536);

			CPPUNIT_ASSERT(indexBufferFiller.getIndexSize() == 4);

			const unsigned long* longBuffer = indexBufferFiller.get<unsigned long>();
			CPPUNIT_ASSERT(longBuffer[0] == 42);
			CPPUNIT_ASSERT(longBuffer[1] == 69);
			CPPUNIT_ASSERT(longBuffer[4000] == 65536);
		}

		void TestBuffer::testVertexBufferFiller(){
		}

	}
}
