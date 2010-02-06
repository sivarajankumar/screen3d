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

#include <Screen/Test/TestBuffer.h>
#include <Screen/Core/Objects/BufferBase.h>
#include <Screen/Core/Objects/Buffer.h>
#include <Screen/Core/Objects/IndexBuffer.h>
#include <Screen/Core/Objects/VertexBuffer.h>
#include <Screen/Core/Objects/VertexFormat.h>
#include <Screen/Core/Enums.h>
#include <Screen/Test/Utils/FakeRenderer.h>

CPPUNIT_TEST_SUITE_REGISTRATION(Screen::Test::TestBuffer);

#define BUFFER_SIZE 1000

struct Vertex1{
	float x, y, z;
	unsigned long Color;
	float tu, tv;
};

namespace Screen {
	namespace Test {
		class FakeBufferBase : public Screen::Core::Objects::BufferBase {
		public:
			FakeBufferBase()
				:Screen::Core::Objects::BufferBase(1000)
			{}
			
			void* lock(unsigned long offset, unsigned long size, Screen::Core::LockFlag flags){
				static unsigned char buffer[BUFFER_SIZE] = {'\0'};
				return buffer + offset;
			}
			void unlock(){
				
			}
		};
		
		class FakeBufferRenderer : public Screen::Test::Utils::FakeRenderer{
		public:
			FakeBufferRenderer(){}		
			virtual ~FakeBufferRenderer(){}
			
			virtual Screen::Core::Objects::BufferBase* createVB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const{
				return new FakeBufferBase;
			}
	        virtual Screen::Core::Objects::BufferBase* createIB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const{
	        	return new FakeBufferBase;
	        }
	        virtual void setVB(const Screen::Core::Objects::BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const Screen::Core::VertexFormat& vf){
	        	
	        }
	        virtual void setIB(const Screen::Core::Objects::BufferBase* buffer, unsigned long stride){
	        	
	        }
		};
	
		void TestBuffer::testBuffer(){
			FakeBufferRenderer renderer;
		}
		void TestBuffer::testIndexBuffer(){
			FakeBufferRenderer renderer;
		}
		void TestBuffer::testVertexBuffer(){
			using namespace Screen::Core::Objects;
			using namespace Screen::Core;
			
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
			} catch(const Screen::Utils::Exception& e) {
				CPPUNIT_ASSERT(std::string(e.what()) == "[Screen exception] Vertex format modified after lock");
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
			} catch(const Screen::Utils::Exception& e) {
				std::stringstream ss;
				ss << "[Screen exception] "
				   << "different size between vertex element type and vertex format size\n"
				   << "\t- Element type size = " << sizeof(Vertex1) << "\n"
				   << "\t- Vertex format size = " << vf2->getSize() << "\n";
				CPPUNIT_ASSERT(std::string(e.what()) == ss.str());
			} catch(...) {
				CPPUNIT_FAIL("throws a bad exception");
			}
			VertexBuffer<void> vb4 = renderer.createVertexBuffer<void>(8,STATIC_DRAW,Vertices1,vf2);
		}
	}
}
