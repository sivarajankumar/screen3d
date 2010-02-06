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

#ifndef SCREEN_VERTEX_FORMAT_H
#define SCREEN_VERTEX_FORMAT_H

#include <Screen/Core/Enums.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Utils/Export.h>
#include <vector>

namespace Screen {
	namespace Core {
		namespace Objects {
			class SCREEN_EXPORT VertexUsageAndType{
				SCREEN_DECL_CLASS(Screen::Core::VertexUsageAndType)
				friend class VertexFormat;
			public:
				VertexUsage getUsage() const;
				VertexType getType() const;
			private:
				VertexUsageAndType();
				~VertexUsageAndType();
				VertexUsage usage;
				VertexType type;
			};
			
			/*!  \class VertexFormat
			 *   \brief 
			 *   \author Ratouit Thomas
			 *   \date 19 sept. 09
			 */
		
			class SCREEN_EXPORT VertexFormat {
				SCREEN_DECL_CLASS(Screen::Core::VertexFormat)
			public:
				typedef std::vector<const VertexUsageAndType *>::const_iterator const_iterator;
				
				VertexFormat();
				~VertexFormat();
				
				void add(VertexUsage usage, VertexType type);
				void lock();
				
				bool isLocked() const;
				
				unsigned int getSize() const;
				
				VertexFormat::const_iterator begin() const;
				VertexFormat::const_iterator end() const;
				
				typedef Screen::Utils::SmartPtr<VertexFormat> SmartPtr;
			private:
				std::vector<const VertexUsageAndType *> vuatList;
				bool _lock;
			};
		}
	}
}

#endif
