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

// maths
#include <screen/math/Angles.h>

//stl
#include <iostream>

//glm
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/core/func_geometric.hpp>

namespace screen {
	namespace core {
		namespace objects {

			//-----------------------------------------------------------------------

			Camera::Camera(const std::string& iName, screen::core::Scene& iScene)
			: SceneNode(iName, iScene, NULL),
			  _fov(45.0f), _aspectRatio(4.0f/3.0f),
			  _near(0.1f), _far(100.0f), _projectionNeedsUpdate(true),
			  _viewNeedsUpdate(true)
			{
				SCREEN_DECL_CONSTRUCTOR(Camera);
				updateProjection();
				updateView();
			}

			//-----------------------------------------------------------------------

			Camera::~Camera(){
				SCREEN_DECL_DESTRUCTOR(~Camera);
			}

			//-----------------------------------------------------------------------

			inline
			bool Camera::isActive() const{
				SCREEN_DECL_METHOD(isActive);
				return (&_scene->getActiveCamera() == this);
			}

			//-----------------------------------------------------------------------

			inline
			void Camera::setPosition(const glm::vec3& iVectorPosition){
				SCREEN_DECL_METHOD(setPosition);
				SceneNode::setPosition(iVectorPosition);
				_viewNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::move(const glm::vec3& iVectorMove){
				SCREEN_DECL_METHOD(move);
				_position += iVectorMove;
				_viewNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::translateZ(const float iDistance){
				SCREEN_DECL_METHOD(translateZ);
				_position += (iDistance * getDirection());
				_viewNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::translateY(const float iDistance){
				SCREEN_DECL_METHOD(translateY);
				_position += (iDistance * getUp());
				_viewNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::translateX(const float iDistance){
				SCREEN_DECL_METHOD(translateX);
				_position += (iDistance * getRight());
				_viewNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::translate(const float iDistance, const glm::vec3& iAxis){
				SCREEN_DECL_METHOD(translate);
				_position += (iDistance * glm::normalize(iAxis));
				_viewNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::setDirection(const glm::vec3& iVectorDirection){
				SCREEN_DECL_METHOD(setDirection);
				_eye = glm::normalize(iVectorDirection);
				_viewNeedsUpdate = true;
				_rightNeedsUpdate =  true;
			}

			//-----------------------------------------------------------------------

			void Camera::setDirection(const float x, const float y, const float z){
				setDirection( glm::vec3(x, y, z));
			}

			//-----------------------------------------------------------------------

			const glm::vec3& Camera::getDirection() const{
				SCREEN_DECL_METHOD(getDirection);
				return _eye;
			}

			//-----------------------------------------------------------------------

			inline
			const glm::vec3& Camera::getUp() const{
				SCREEN_DECL_METHOD(getUp);
				return _up;
			}

			//-----------------------------------------------------------------------

			inline
			const glm::vec3& Camera::getRight() const{
				SCREEN_DECL_METHOD(getRight);
				updateRight();
				return _right;
			}

			//-----------------------------------------------------------------------

			// rotation local z
			void Camera::roll(const screen::math::Degree& iAngle){
				SCREEN_DECL_METHOD(roll);
				rotate(getDirection(), iAngle);
			}

			//-----------------------------------------------------------------------

			// rotation local y
			void Camera::yaw(const screen::math::Degree& iAngle){
				SCREEN_DECL_METHOD(yaw);
				rotate(getUp(), iAngle);
			}

			// rotation local x
			void Camera::pitch(const screen::math::Degree& iAngle){
				SCREEN_DECL_METHOD(pitch);
				rotate(getRight(), iAngle);
			}

			//-----------------------------------------------------------------------

			void Camera::rotate(const glm::vec3& iAxis, const screen::math::Degree& iAngle){
				SCREEN_DECL_METHOD(rotate);
				_eye = glm::normalize(glm::rotate(_eye, iAngle.getValue(), iAxis));
				_up = glm::normalize(glm::rotate(_up, iAngle.getValue(), iAxis));
				_viewNeedsUpdate = true;
				_rightNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::lookAt(const glm::vec3& iPoint){
				SCREEN_DECL_METHOD(lookAt);
				_eye = iPoint - _position;
				_viewNeedsUpdate = true;
				_rightNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			void Camera::lookAt(const float x, const float y, const float z){
				lookAt(glm::vec3(x, y, z));
			}

			//-----------------------------------------------------------------------

			const glm::mat4x4& Camera::getView() const {
				SCREEN_DECL_METHOD(getView);
				updateView();
				return _view;
			}

			//-----------------------------------------------------------------------

			inline
			float Camera::getAspectRatio() const{
				SCREEN_DECL_METHOD(getAspectRatio);
				return _aspectRatio;
			}

			//-----------------------------------------------------------------------

			inline
			void Camera::setAspectRatio(const float iAspectRatio){
				SCREEN_DECL_METHOD(setAspectRatio);
				_aspectRatio = iAspectRatio;
				_projectionNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			inline
			float  Camera::getNearClipDistance() const{
				SCREEN_DECL_METHOD(getNearClipDistance);
				return _near;
			}

			//-----------------------------------------------------------------------

			inline
			void  Camera::setNearClipDistance(const float iNear){
				SCREEN_DECL_METHOD(setNearClipDistance);
				_near = iNear;
				_projectionNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			inline
			float  Camera::getFarClipDistance() const{
				SCREEN_DECL_METHOD(getFarClipDistance);
				return _far;
			}

			//-----------------------------------------------------------------------

			inline
			void  Camera::setFarClipDistance(const float iFar){
				SCREEN_DECL_METHOD(setFarClipDistance);
				_far = iFar;
				_projectionNeedsUpdate = true;
			}

			//-----------------------------------------------------------------------

			const glm::mat4x4& Camera::getProjection() const{
				SCREEN_DECL_METHOD(getProjection);
				updateProjection();
				return _projection;
			}

			//-----------------------------------------------------------------------

			void Camera::updateProjection() const {
				SCREEN_DECL_METHOD(updateProjection);
				if (_projectionNeedsUpdate){
					_projection = glm::perspective(_fov, _aspectRatio, _near, _far);
					_projectionNeedsUpdate = false;
				}
			}

			//-----------------------------------------------------------------------

			void Camera::updateView() const{
				SCREEN_DECL_METHOD(updateView);
				if (_viewNeedsUpdate){
					_view = glm::lookAt(_eye, _position, _up);
					_viewNeedsUpdate = false;
				}
			}

			//-----------------------------------------------------------------------

			void Camera::updateRight() const{
				SCREEN_DECL_METHOD(updateRight);
				if (_rightNeedsUpdate){
					_right = glm::normalize(glm::cross(_eye, _up));
					_rightNeedsUpdate = false;
				}
			}

			//-----------------------------------------------------------------------

		}
	}
}
