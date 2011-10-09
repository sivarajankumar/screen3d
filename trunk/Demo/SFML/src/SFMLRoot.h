/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2011 Ratouit Thomas                                    *
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

#ifndef SCREEN_SFML_ROOT_H
#define SCREEN_SFML_ROOT_H

#include <screen/core/objects/VertexBufferHandler.h>
#include <screen/core/objects/IndexBufferHandler.h>
#include <screen/core/objects/IndexBuffer.h>
#include <screen/core/objects/Texture.h>
#include <screen/core/Root.h>
#include <glm/glm.hpp>


class SFMLRoot : public screen::core::Root {
public:
	SFMLRoot();
	~SFMLRoot();
	void init();
	bool renderFrame();
private:
	struct Vertex
	{
		float x, y, z;
		unsigned long color;
		float tu, tv;
	};
	
	screen::core::objects::IndexBufferHandler ib1;
	screen::core::objects::VertexBufferHandler vb1;
	screen::core::objects::Texture texture;
	glm::vec3 cam;
	glm::mat4x4 view,proj,rotX,rotY,rotZ;
};

#endif
