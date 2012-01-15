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

#ifndef SCREEN_MODEL_H
#define SCREEN_MODEL_H

#include <screen/utils/SmartPtr.h>
#include <screen/utils/Resource.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen{
	namespace core {
		namespace objects {
			/*!  \class Model
			 *   \brief 
			 *   \author Ratouit Thomas
			 *   \date 18 oct. 09
			 */
		
			class SCREEN_MAIN_EXPORT Model : public screen::utils::Resource<>{
				SCREEN_DECL_CLASS(screen::core::objects::Model)
			public:
				Model();
				~Model();
				
				typedef screen::utils::SmartPtr<Model, screen::utils::ResourceSmartPolicy> SmartPtr;
			private:
			};
		}
	}
}

#endif
