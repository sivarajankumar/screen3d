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

#ifndef SCREEN_SFML_ROOT_H
#define SCREEN_SFML_ROOT_H

#include <Screen/Core/Objects/VertexBuffer.h>
#include <Screen/Core/Objects/IndexBuffer.h>
#include <Screen/Core/Objects/Texture.h>
#include <Screen/Core/Objects/VertexBufferFiller.h>
#include <Screen/Math/Vector3f.h>
#include <Screen/Math/Matrix4x4f.h>
#include <Screen/Core/Root.h>

class SFMLRoot : public Screen::Core::Root {
public:
	SFMLRoot();
	void init();
	bool renderFrame();
private:
	struct Vertex
	{
		float x, y, z;
		unsigned long color;
		float tu, tv;
	};
	
	Screen::Core::Objects::VertexBuffer<Vertex>::SmartPtr vb1;
	Screen::Core::Objects::VertexBufferFiller::SmartPtr vbf1;
	Screen::Core::Objects::IndexBuffer<unsigned short>::SmartPtr ib;
	Screen::Core::Objects::Texture texture;
	Screen::Math::Vector3f cam;
	Screen::Math::Matrix4x4f view,proj,rotX,rotY,rotZ;
};

#endif
