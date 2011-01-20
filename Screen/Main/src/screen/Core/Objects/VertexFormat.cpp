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

#include <Screen/Core/Objects/VertexFormat.h>

namespace Screen {
	namespace Core {
		namespace Objects {
			using Screen::Core::VertexType;
			VertexUsageAndType::VertexUsageAndType(){
				SCREEN_DECL_CONSTRUCTOR(VertexUsageAndType)
			}
			
			VertexUsageAndType::~VertexUsageAndType(){
				SCREEN_DECL_DESTRUCTOR(VertexUsageAndType)
			}
			
			VertexUsage VertexUsageAndType::getUsage() const{
				SCREEN_DECL_METHOD(getUsage)
				return usage;
			}
			
			VertexType VertexUsageAndType::getType() const{
				SCREEN_DECL_METHOD(setUsage)
				return type;
			}
			
			VertexFormat::VertexFormat()
				:_lock(false){
				SCREEN_DECL_CONSTRUCTOR(VertexFormat)
			}
			
			VertexFormat::~VertexFormat(){
				SCREEN_DECL_DESTRUCTOR(~VertexFormat)
				//clean vertex usage and type list
				std::vector<const VertexUsageAndType *>::iterator i;
				for(i = vuatList.begin(); i != vuatList.end(); i++)
					delete (*i);
			}
			
			void VertexFormat::add(VertexUsage usage, VertexType type){
				SCREEN_DECL_METHOD(add)
				if(_lock){
					throw Screen::Utils::Exception("Vertex format modified after lock");
				}
				VertexUsageAndType* vuat = new VertexUsageAndType();
				vuat->usage = usage;
				vuat->type = type;
				vuatList.push_back(vuat);
			}
			
			void VertexFormat::lock(){
				SCREEN_DECL_METHOD(lock)
				_lock = true;
			}
			
			bool VertexFormat::isLocked() const{
				SCREEN_DECL_METHOD(isLocked)
				return _lock;
			}
			
			unsigned int VertexFormat::getSize() const{
				SCREEN_DECL_METHOD(getSize)
				static const unsigned int sizeTable[] = {
					sizeof(float), //VERTEX_TYPE_FLOAT1
					2*sizeof(float), //VERTEX_TYPE_FLOAT2
					3*sizeof(float), //VERTEX_TYPE_FLOAT3
					4*sizeof(float), //VERTEX_TYPE_FLOAT4
					sizeof(unsigned long) //VERTEX_TYPE_COLOR
				};
				unsigned int size = 0;
				for (const_iterator i = begin(); i != end(); ++i){
					size += sizeTable[(*i)->getType()];
				}
				return size;
			}
			
			VertexFormat::const_iterator VertexFormat::begin() const{
				SCREEN_DECL_METHOD(begin)
				return vuatList.begin();
			}
			
			VertexFormat::const_iterator VertexFormat::end() const{
				SCREEN_DECL_METHOD(end)
				return vuatList.end();
			}
		}
	}
}
