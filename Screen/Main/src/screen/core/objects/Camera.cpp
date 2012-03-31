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
/**
 * \file Camera.cpp
 * \brief The camera from which the scene is rendered
 * \author pjdemaret
 *
 * This class is used to represent the camera object. The camera is the viewpoint from which the
 * 3D scene is rendered.
 */

//core includes
#include <screen/core/Scene.h>

//objects includes
#include <screen/core/objects/Camera.h>

//stl
#include <iostream>

//glm
#include <glm/gtc/matrix_transform.hpp>

namespace screen {
	namespace core {
		namespace objects {

			Camera::Camera(const std::string& iName, screen::core::Scene* iScene)
			: _name(iName), _scene(iScene),
			  _position(0.0f, 0.0f, 0.0f), _center(0.0f, 0.0f, 0.0f), _up(0.0f, 0.0f, 0.0f),
			  _fov(45.0f), _aspect(800.0f/600.0f),
			  _near(0.1f), _far(100.0f)
			{
				SCREEN_DECL_CONSTRUCTOR(Camera)
			}

			Camera::~Camera(){
				SCREEN_DECL_DESTRUCTOR(~Camera)
			}


			const std::string& Camera::getName() const{
				SCREEN_DECL_METHOD(getName)
				return _name;
			}

			inline
			screen::core::Scene* Camera::getScene() const{
				SCREEN_DECL_METHOD(getScene)
				return _scene;
			}

			inline
			bool Camera::isActive() const{
				SCREEN_DECL_METHOD(isActive)
				return (_scene->getActiveCamera() == this);
			}

			inline
			void Camera::setPosition(const glm::vec3& iVectorPosition){
				SCREEN_DECL_METHOD(setPosition)
				_position = iVectorPosition;
			}

			inline
			void Camera::setPosition(const float x, const float y, const float z){
				setPosition(glm::vec3(x,y,z));
			}

			inline
			const glm::vec3& Camera::getPosition() const{
				SCREEN_DECL_METHOD(getPosition)
				return _position;
			}

			inline
			const glm::mat4x4 Camera::getProjection() const{
				SCREEN_DECL_METHOD(getProjection)
				return glm::perspective(_fov, _aspect, _near, _far);
			}

			inline
			const glm::mat4x4 Camera::getView() const {
				SCREEN_DECL_METHOD(getView)
				return glm::lookAt(_position, _center, _up);
			}

		}
	}
}
