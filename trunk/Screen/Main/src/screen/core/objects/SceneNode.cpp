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
 * \file SceneNode.cpp
 * \brief  Base class for all nodes of the scene tree
 * \author pjdemaret
 *
 * This class is the base class of all nodes of the scene tree.
 */

//core includes
#include <screen/core/Scene.h>

//objects includes
#include <screen/core/objects/SceneNode.h>

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

			SceneNode::SceneNode(const std::string& iName, screen::core::Scene& iScene, SceneNode* iParentNode/* = NULL*/)
				: _name(iName), _scene(&iScene), _parentNode(iParentNode),
				  _rightNeedsUpdate(true), _positionNeedsUpdate(true),
				  _orientationNeedsUpdate(true), _position(0.0, 0.0, 0.0),
				  _front(0.0, 0.0, 1.0), _up(0.0, 1.0, 0.0)
			{
				updateRight();
				positionNeedsUpdate();
				orientationNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			SceneNode::~SceneNode(){
				SCREEN_DECL_DESTRUCTOR(~SceneNode);
			}

			//-----------------------------------------------------------------------

			const std::string& SceneNode::getName() const{
				SCREEN_DECL_METHOD(getName);
				return _name;
			}

			//-----------------------------------------------------------------------

			inline
			const screen::core::Scene& SceneNode::getScene() const{
				SCREEN_DECL_METHOD(getScene);
				return accessScene();
			}

			//-----------------------------------------------------------------------

			inline
			screen::core::Scene& SceneNode::accessScene() const{
				SCREEN_DECL_METHOD(accessScene);
				if (_scene == NULL)
					throw screen::utils::Exception( __FILE__, __LINE__, "Trying to get a NULL scene from the the SceneNode (" + getName() + ")");
				return *_scene;
			}

			//-----------------------------------------------------------------------

			inline
			const bool SceneNode::hasParent() const {
				SCREEN_DECL_METHOD(hasParent);
				return (_parentNode != NULL);
			}


			//-----------------------------------------------------------------------

			inline
			const SceneNode& SceneNode::getParent() const {
				SCREEN_DECL_METHOD(getParent);
				return accessParent();
			}

			//-----------------------------------------------------------------------

			inline
			SceneNode& SceneNode::accessParent() const {
				SCREEN_DECL_METHOD(accessParent);
				if (_parentNode == NULL)
					throw screen::utils::Exception( __FILE__, __LINE__, "Trying to access NULL parent node on SceneNode (" + getName() + ")");

				return *_parentNode;
			}

			//-----------------------------------------------------------------------

			void SceneNode::attachNode(SceneNode& iParentNode) {
				SCREEN_DECL_METHOD(attachNode);
				if (&iParentNode.getScene() != &getScene())
					throw screen::utils::Exception( __FILE__, __LINE__, "Impossible to attach " + getName() + " to parent " + iParentNode.getName()
													+ " They are not part of the same scene");
				detachFromParent();
				_parentNode = &iParentNode;
				iParentNode._childList.push_back(this);
				positionNeedsUpdate();
				orientationNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::detachFromParent() {
				SCREEN_DECL_METHOD(detachFromParent);
				if (_parentNode) {
					_parentNode->_childList.remove(this);
					_parentNode = NULL;
					positionNeedsUpdate();
					orientationNeedsUpdate();
				}
			}

			//-----------------------------------------------------------------------

			void SceneNode::addChild(SceneNode& iChildNode) {
				SCREEN_DECL_METHOD(addChild);
				iChildNode.attachNode(*this);
				// TODO what to do with child relative position and orientation?
			}

			//-----------------------------------------------------------------------

			inline
			int SceneNode::getNbChilds() const {
				SCREEN_DECL_METHOD(getNbChilds);
				return _childList.size();
			}

			//-----------------------------------------------------------------------

			inline
			bool SceneNode::isLeaf() const {
				SCREEN_DECL_METHOD(isLeaf);
				return (_childList.size() == 0);
			}

			//-----------------------------------------------------------------------

			inline
			void SceneNode::setPosition(const glm::vec3& iVectorPosition){
				SCREEN_DECL_METHOD(setPosition);
				if (_parentNode) {
					_position = iVectorPosition - _parentNode->getPosition();
				} else {
					_position = iVectorPosition;
				}
				positionNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			inline
			void SceneNode::setPosition(const float x, const float y, const float z){
				setPosition(glm::vec3(x,y,z));
			}

			//-----------------------------------------------------------------------

			inline
			const glm::vec3& SceneNode::getPosition() const{
				SCREEN_DECL_METHOD(getPosition);
				updateAbsolutePosition();
				return _absPosition;
			}

			//-----------------------------------------------------------------------

			inline
			void SceneNode::setRelativePosition(const glm::vec3& iVectorPosition){
				SCREEN_DECL_METHOD(setRelativePosition);
				_position = iVectorPosition;
				positionNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			inline
			void SceneNode::setRelativePosition(const float x, const float y, const float z){
				setRelativePosition(glm::vec3(x,y,z));
			}

			//-----------------------------------------------------------------------

			inline
			const glm::vec3& SceneNode::getRelativePosition() const{
				SCREEN_DECL_METHOD(getPosition);
				return _position;
			}

			//-----------------------------------------------------------------------

			void SceneNode::move(const glm::vec3& iVectorMove, const TranformSpace iRelativeSpace/* = TSpace_ABSOLUTE*/){
				SCREEN_DECL_METHOD(move);
				switch (iRelativeSpace) {
				case TSpace_LOCAL:
					// Move on the 3 axis
					if (iVectorMove.x)
						_position += (iVectorMove.x * getRight());
					if (iVectorMove.y)
						_position += (iVectorMove.y * getUp());
					if (iVectorMove.z)
						_position += (iVectorMove.z * getDirection());
					break;
				case TSpace_PARENT:
					if (_parentNode) { // if not, use absolute space
						// Move on the 3 axis
						if (iVectorMove.x)
							_position += (iVectorMove.x * getRight());
						if (iVectorMove.y)
							_position += (iVectorMove.y * getUp());
						if (iVectorMove.z)
							_position += (iVectorMove.z * getDirection());
						break;
					}
				case TSpace_ABSOLUTE:
					_position += iVectorMove;
					break;
				default:
					throw screen::utils::Exception( __FILE__, __LINE__, "Unknown transform space given in move for node " + getName());
				}
				positionNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::translateZ(const float iDistance, const TranformSpace iRelativeSpace /*= TSpace_LOCAL*/){
				SCREEN_DECL_METHOD(translateZ);
				// Full implementation, for optimization (instead of using move code)
				switch (iRelativeSpace) {
				case TSpace_LOCAL:
					_position += (iDistance * getDirection());
					break;
				case TSpace_PARENT:
					if (_parentNode) {  // if not, use absolute space
						_position += (iDistance * _parentNode->getDirection());
						break;
					}
				case TSpace_ABSOLUTE:
					_position += (iDistance *glm::vec3(0,0,1));
					break;
				default:
					throw screen::utils::Exception( __FILE__, __LINE__, "Unknown transform space given in translateZ for node " + getName());
				}
				positionNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::translateY(const float iDistance, const TranformSpace iRelativeSpace/* = TSpace_LOCAL*/){
				SCREEN_DECL_METHOD(translateY);
				// Full implementation, for optimization (instead of using move code)
				switch (iRelativeSpace) {
				case TSpace_LOCAL:
					_position += (iDistance *  getUp());
					break;
				case TSpace_PARENT:
					if (_parentNode) {  // if not, use absolute space
						_position += (iDistance * _parentNode->getUp());
						break;
					}
				case TSpace_ABSOLUTE:
					_position += (iDistance *glm::vec3(0,1,0));
					break;
				default:
					throw screen::utils::Exception( __FILE__, __LINE__, "Unknown transform space given in translateY for node " + getName());
				}
				positionNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::translateX(const float iDistance, const TranformSpace iRelativeSpace/* = TSpace_LOCAL*/){
				SCREEN_DECL_METHOD(translateX);
				// Full implementation, for optimization (instead of using move code)
				switch (iRelativeSpace) {
				case TSpace_LOCAL:
					_position += (iDistance *  getRight());
					break;
				case TSpace_PARENT:
					if (_parentNode) {  // if not, use absolute space
						_position += (iDistance * _parentNode->getRight());
						break;
					}
				case TSpace_ABSOLUTE:
					_position += (iDistance *glm::vec3(1,0,0));
					break;
				default:
					throw screen::utils::Exception( __FILE__, __LINE__, "Unknown transform space given in translateX for node " + getName());
				}
				positionNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::translate(const float iDistance, const glm::vec3& iAxis, const TranformSpace iRelativeSpace/* = TSpace_LOCAL*/){
				SCREEN_DECL_METHOD(translate);
				move(iDistance * glm::normalize(iAxis), iRelativeSpace);
			}

			//-----------------------------------------------------------------------

			void SceneNode::setDirection(const glm::vec3& iVectorDirection, const TranformSpace iRelativeSpace/* = TSpace_ABSOLUTE*/){
				SCREEN_DECL_METHOD(setDirection);
				switch (iRelativeSpace) {
				case TSpace_LOCAL:
					// TODO
					break;
				case TSpace_PARENT:
					if (_parentNode) {  // if not, use absolute space
						// TODO
						break;
					}
				case TSpace_ABSOLUTE:
					_front = glm::normalize(iVectorDirection);
					_rightNeedsUpdate =  true;
					break;
				default:
					throw screen::utils::Exception( __FILE__, __LINE__, "Unknown transform space given in setDirection for node " + getName());
				}
				orientationNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::setDirection(const float x, const float y, const float z, const TranformSpace iRelativeSpace/* = TSpace_ABSOLUTE*/){
				setDirection( glm::vec3(x, y, z), iRelativeSpace);
			}

			//-----------------------------------------------------------------------

			const glm::vec3& SceneNode::getDirection() const{
				SCREEN_DECL_METHOD(getDirection);
				return _front;
			}

			//-----------------------------------------------------------------------

			inline
			const glm::vec3& SceneNode::getUp() const{
				SCREEN_DECL_METHOD(getUp);
				return _up;
			}

			//-----------------------------------------------------------------------

			inline
			const glm::vec3& SceneNode::getRight() const{
				SCREEN_DECL_METHOD(getRight);
				updateRight();
				return _right;
			}

			//-----------------------------------------------------------------------

			// rotation local z
			void SceneNode::roll(const screen::math::Degree& iAngle){
				SCREEN_DECL_METHOD(roll);
				rotate(getDirection(), iAngle);
			}

			// rotation local y
			void SceneNode::yaw(const screen::math::Degree& iAngle){
				SCREEN_DECL_METHOD(yaw);
				rotate(getUp(), iAngle);
			}

			// rotation local x
			void SceneNode::pitch(const screen::math::Degree& iAngle){
				SCREEN_DECL_METHOD(pitch);
				rotate(getRight(), iAngle);
			}

			//-----------------------------------------------------------------------

			void SceneNode::rotate(const glm::vec3& iAxis, const screen::math::Degree& iAngle, const TranformSpace iRelativeSpace/* = TSpace_LOCAL*/){
				SCREEN_DECL_METHOD(rotate);
				if (iAngle == screen::math::Degree(0) || iAngle == screen::math::Degree(360)) // TODO test with modulo 360 ?
					return;

				switch (iRelativeSpace) {
				case TSpace_LOCAL:
					// TODO
					break;
				case TSpace_PARENT:
					if (_parentNode) {  // if not, use absolute space
						// TODO
						break;
					}
				case TSpace_ABSOLUTE:
					_front = glm::normalize(glm::rotate(_front, iAngle.getValue(), iAxis));
					_up = glm::normalize(glm::rotate(_up, iAngle.getValue(), iAxis));
					_rightNeedsUpdate = true;
					break;
				default:
					throw screen::utils::Exception( __FILE__, __LINE__, "Unknown transform space given in rotate for node " + getName());
				}
				orientationNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::lookAt(const glm::vec3& iPoint){
				SCREEN_DECL_METHOD(lookAt);
				_front = iPoint - _position;
				_rightNeedsUpdate = true;
				orientationNeedsUpdate();
			}

			//-----------------------------------------------------------------------

			void SceneNode::lookAt(const float x, const float y, const float z){
				lookAt(glm::vec3(x, y, z));
			}

			//-----------------------------------------------------------------------

			void SceneNode::updateRight() const{
				SCREEN_DECL_METHOD(updateRight);
				if (_rightNeedsUpdate){
					_right = glm::normalize(glm::cross(_front, _up));
					_rightNeedsUpdate = false;
				}
			}

			//-----------------------------------------------------------------------

			void SceneNode::positionNeedsUpdate() const
			{
				SCREEN_DECL_METHOD(positionNeedsUpdate);
				// TODO possible optimization. If already to true nothing to do, childen should have been notified.
				// children attachement should be check to be sure
				_positionNeedsUpdate = true;
				std::list<SceneNode*>::const_iterator aIt;
				for(aIt = _childList.begin(); aIt != _childList.end(); ++aIt)
				{
					if (*aIt)
						(*aIt)->positionNeedsUpdate();
				}
			}

			//-----------------------------------------------------------------------

			void SceneNode::orientationNeedsUpdate() const
			{
				SCREEN_DECL_METHOD(orientationNeedsUpdate);
				// TODO possible optimization. If already to true nothing to do, childen should have been notified.
				// children attachement should be check to be sure
				_orientationNeedsUpdate = true;
				std::list<SceneNode*>::const_iterator aIt;
				for(aIt = _childList.begin(); aIt != _childList.end(); ++aIt)
				{
					if (*aIt)
						(*aIt)->orientationNeedsUpdate();
				}
			}

			//-----------------------------------------------------------------------

			void SceneNode::updateAbsolutePosition() const
			{
				SCREEN_DECL_METHOD(updateAbsolutePosition);
				// TODO
				if (_positionNeedsUpdate)
				{
					if (_parentNode)
						_parentNode->updateAbsolutePosition();
					// TODO update absolute position based on parents transformations
				}
			}

			//-----------------------------------------------------------------------

			void SceneNode::updateAbsoluteOrientation() const
			{
				SCREEN_DECL_METHOD(updateAbsoluteOrientation);
				// TODO
				if (_orientationNeedsUpdate)
				{
					if (_parentNode)
						_parentNode->updateAbsoluteOrientation();
					// TODO update absolute orientation based on parents transformations

				}
			}

			//-----------------------------------------------------------------------

		}
	}
}
