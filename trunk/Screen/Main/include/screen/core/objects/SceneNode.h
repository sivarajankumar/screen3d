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
 * \file SceneNode.h
 * \brief Base class for all nodes of the scene tree
 * \author pjdemaret
 *
 * This class is the base class of all nodes of the scene tree.
 */

#ifndef SCREEN_SCENENODE_H
#define SCREEN_SCENENODE_H

//utils
#include <screen/utils/Declaration.h>

//main
#include <screen/main/Export.h>

// glm
#include <glm/glm.hpp>

// stl
#include <iostream>
#include <list>

/**
 * Namespace all screen classes
 */
namespace screen {

	namespace math {
		class Degree;
	}

	/**
	 * Namespace for the core classes of the engine
	 */
	namespace core {

		class Scene;

		/**
		 * Namespace for the objects of the engine
		 */
		namespace objects {

			/**
			 * \brief Enumeration corresponding to the space used for
			 * transformations
			 */
			enum TranformSpace
			{
				TSpace_LOCAL,		// Local Space
				TSpace_PARENT,		// Space of the parent node
				TSpace_ABSOLUTE		// Absolute Space
			};


			/**
			 * \brief SceneNode object
			 *
			 * Object describe a Node of the scene tree.
			 * The SceneNode must be attached to a scene.
			 * A node can have a parent node, and several child nodes. Position/rotation ect.. can be compute relatively
			 * to the global Space, the parent one or the local one
			 * Default relative position is (0,0,0). Default relative direction is (0,0,1). Default relative up is (0,1,0).
			 */
			class SCREEN_MAIN_EXPORT SceneNode {
				SCREEN_DECL_CLASS(screen::core::objects::SceneNode)
			public:

				friend class screen::core::Scene;

				/**
				 * \brief Get the name of the SceneNode
				 * \return Name of the SceneNode
				 */
				virtual const std::string& getName() const;

				/**
				 * \brief Get the scene holding the SceneNode
				 * \return scene holding the SceneNode
				 */
				const screen::core::Scene& getScene() const;

				/**
				 * \brief Access the scene holding the SceneNode
				 * \return scene holding the SceneNode
				 */
				screen::core::Scene& accessScene() const;

				/**
				 * \brief Check if this node has a parent node
				 * \return true if the node has a parent node
				 */
				const bool hasParent() const;

				/**
				 * \brief Get the parent node
				 * \exception screen::utils::Exception if there is no parent node
				 * \return scene holding the SceneNode
				 */
				const SceneNode& getParent() const;

				/**
				 * \brief Access the parent node
				 * \exception screen::utils::Exception if there is no parent node
				 * \return scene holding the SceneNode
				 */
				SceneNode& accessParent() const;

				/**
				 * \brief attach to a parent node
				 *
				 * If already attach to a node, it will first detach
				 * \exception screen::utils::Exception if the parent node is not attach to the same scene
				 */
				void attachNode(SceneNode& iParentNode);

				/**
				 * \brief detach from the parent node
				 * If no parent node is defined, do nothing
				 */
				void detachFromParent();

				/**
				 * \brief add a node as a child node
				 * If the child node is already attach to anoother parent, will first detach it
				 * \exception screen::utils::Exception if the child node is not attach to the same scene
				 */
				void addChild(SceneNode& iChildNode);

				/**
				 * \brief Get the number of childs of this node
				 * \return the number of childs of this node
				 */
				int getNbChilds() const;

				/**
				 * \brief Check if the node is a leaf of the scene tree: i.e. a node without childs
				 * \return true if the node has node childs
				 */
				bool isLeaf() const;

				/**
				 * \brief Set the absolute position of the SceneNode
				 * \param[in] iVectorPosition position given as a vector
				 */
				virtual void setPosition(const glm::vec3& iVectorPosition);

				/**
				 * \brief Set the absolute position of the SceneNode
				 * \param[in] x (horizontal)
				 * \param[in] y (up)
				 * \param[in] z (depth)
				 */
				virtual void setPosition(const float x, const float y, const float z);

				/**
				 * \brief Get the absolute position of the SceneNode
				 * \return vector repesenting the position of the SceneNode
				 */
				virtual const glm::vec3& getPosition() const;

				/**
				 * \brief Set the position of the SceneNode relatively to the parent Space
				 * \param[in] iVectorPosition position given as a vector
				 */
				virtual void setRelativePosition(const glm::vec3& iVectorPosition);

				/**
				 * \brief Set the position of the SceneNode relatively to the parent Space
				 * \param[in] x (horizontal)
				 * \param[in] y (up)
				 * \param[in] z (depth)
				 */
				virtual void setRelativePosition(const float x, const float y, const float z);

				/**
				 * \brief Get the position of the SceneNode relatively to the parent Space
				 * \return vector repesenting the position of the SceneNode
				 */
				virtual const glm::vec3& getRelativePosition() const;

				/**
				 * \brief Move the SceneNode by the given vector
				 * \param[in] iVectorMove vector used to move the SceneNode
				 * \param[in] iRelativeSpace space where the movement is done
				 */
				virtual void move(const glm::vec3& iVectorMove, const TranformSpace iRelativeSpace = TSpace_ABSOLUTE);

				/**
				 * \brief Move the SceneNode on its local z axis
				 * \param[in] iDistance distance of the SceneNode movement
				 * \param[in] iRelativeSpace space where the movement is done
				 */
				virtual void translateZ(const float iDistance, const TranformSpace iRelativeSpace = TSpace_LOCAL);

				/**
				 * \brief Move the SceneNode on its local y axis
				 * \param[in] iDistance distance of the SceneNode movement
				 * \param[in] iRelativeSpace space where the movement is done
				 */
				virtual void translateY(const float iDistance, const TranformSpace iRelativeSpace = TSpace_LOCAL);

				/**
				 * \brief Move the SceneNode on its local x axis
				 * \param[in] iDistance distance of the SceneNode movement
				 * \param[in] iRelativeSpace space where the movement is done
				 */
				virtual void translateX(const float iDistance, const TranformSpace iRelativeSpace = TSpace_LOCAL);

				/**
				 * \brief Move the SceneNode on an axis
				 * \param[in] iDistance distance of the SceneNode movement
				 * \param[in] iAxis axis on which the SceneNode is moving
				 * \param[in] iRelativeSpace space where the movement is done
				 */
				virtual void translate(const float iDistance, const glm::vec3& iAxis, const TranformSpace iRelativeSpace = TSpace_LOCAL);

				/**
				 * \brief Set the direction of the SceneNode
				 * \param[in] iVectorDirection position given as a vector
				 * \param[in] iRelativeSpace space where the movement is done
				 */
				virtual void setDirection(const glm::vec3& iVectorDirection, const TranformSpace iRelativeSpace = TSpace_ABSOLUTE);

				/**
				 * \brief Set the direction of the SceneNode
				 * \param[in] x (horizontal)
				 * \param[in] y (up)
				 * \param[in] z (depth)
				 * \param[in] iRelativeSpace space where the movement is done
				 */
				virtual void setDirection(const float x, const float y, const float z, const TranformSpace iRelativeSpace = TSpace_ABSOLUTE);

				/**
				 * \brief Get the absolute direction of the SceneNode
				 * \return vector repesenting the direction of the SceneNode (normalized)
				 */
				virtual const glm::vec3& getDirection() const;

				/**
				 * \brief Get the absolute up vector of the SceneNode
				 * \return vector repesenting the up vector of the SceneNode (normalized)
				 */
				virtual const glm::vec3& getUp() const;

				/**
				 * \brief Get the absolute right vector of the SceneNode
				 *
				 * This vector is computed when get is called
				 * \return vector representing the right vector of the SceneNode (normalized)
				 */
				virtual const glm::vec3& getRight() const;

				/**
				 * \brief Rotate anticlockwise arount its local z axis
				 * \param[in] iDegree angle in Degree
				 */
				virtual void roll(const screen::math::Degree& iAngle);

				/**
				 * \brief Rotate anticlockwise arount its local y axis
				 * \param[in] iDegree angle in Degree
				 */
				virtual void yaw(const screen::math::Degree& iAngle);

				/**
				 * \brief Rotate anticlockwise arount its local x axis
				 * \param[in] iDegree angle in Degree
				 */
				virtual void pitch(const screen::math::Degree& iAngle);

				/**
				 * \brief Rotate the SceneNode around a given axis
				 * \param[in] iAxis vector representing the axis (it's coordiantes are in the specified Space)
				 * \param[in] iDegree angle in Degree
				 */
				virtual void rotate(const glm::vec3& iAxis, const screen::math::Degree& iAngle, const TranformSpace iRelativeSpace = TSpace_LOCAL);

				/**
				 * \brief Make the SceneNode look at a point in space
				 *
				 * Make the SceneNode look at a point in space. Does not change the up vector of the SceneNode.
				 * \param[in] iPoint point ot look at (absolute position)
				 */
				virtual void lookAt(const glm::vec3& iPoint);

				/**
				 * \brief Make the SceneNode look at a point in space
				 *
				 * Make the SceneNode look at a point in space (position absolute). Does not change the up vector of the SceneNode.
				 * \param[in] x (horizontal)
				 * \param[in] y (up)
				 * \param[in] z (depth)
				 */
				virtual void lookAt(const float x, const float y, const float z);

				// TODO scale notion. Will probbaly need update everywhere

			protected:

				/**
				 * \brief Constructor with parent
				 *
				 * \param[in] iName name of the SceneNode
				 * \param[in] iScene scene where the SceneNode is attached
				 * \param[in] iParentNode parent scene node (default NULL)
				 */
				SceneNode(const std::string& iName, screen::core::Scene& iScene, SceneNode* iParentNode = NULL);

				/**
				 * Destructor
				 */
				virtual ~SceneNode();

				/**********************************************************************/

				// update are const in order to have const getter methods

				/**
				 * \brief Compute right vector
				 *
				 * Compute relative right vector if needed.
				 * Should be called before each access to the vector
				 */
				void updateRight() const;

				/**
				 * \brief Compute absolute position
				 *
				 * Compute absolute position if needed.
				 * Should be called before each access to the vector
				 */
				void updateAbsolutePosition() const;

				/**
				 * \brief Compute absolute orientation
				 *
				 * Compute absolute orientation vectors if needed.
				 * Should be called before each access one of the orientation vectors
				 */
				void updateAbsoluteOrientation() const;

				/**
				 * \brief signal to the node and its childs
				 * that the position needs to be updated
				 */
				void positionNeedsUpdate() const;

				/**
				 * \brief signal to the node and its childs
				 * that the orientation needs to be updated
				 */
				void orientationNeedsUpdate() const;

				/**********************************************************************/

				std::string _name;						///< Name of the SceneNode
				screen::core::Scene* _scene;			///< Scene rendered by the SceneNode
				SceneNode* _parentNode;					///< Parent node
				std::list<SceneNode*> _childList;		///< List of child nodes

			protected:

				// TODO bool _isOrientationInherited;			///< true if the orientation must be changed according to the parent orientation
				mutable bool _rightNeedsUpdate;			///< true if the right vector needs to be re-computed

			private:

				/* do not call directly, those values are not updated automatically, use the getters */
				mutable bool _positionNeedsUpdate;		///< true if the position needs to be updated (because of parent position)
				mutable bool _orientationNeedsUpdate;	///< true if the orientation (up, front, right) needs update (because of parent position)
				mutable glm::vec3 _position;			///< SceneNode relative position
				mutable glm::vec3 _front;				///< SceneNode relative front vector (normalized vector)
				mutable glm::vec3 _up;					///< SceneNode relative up vector (normalized vector)
				mutable glm::vec3 _right;				///< SceneNode relative right vector (normalized vector)
				mutable glm::vec3 _absPosition;			///< SceneNode absolute position
				mutable glm::vec3 _absFront;			///< SceneNode absolute front vector (normalized vector)
				mutable glm::vec3 _absUp;				///< SceneNode absolute up vector (normalized vector)
				mutable glm::vec3 _absRight;			///< SceneNode absolute right vector (normalized vector)


				// DO NOT USE
				/**
				 * \brief Default constructor
				 */
				SceneNode();

				/**
				 * \brief const assignment operator
				 */
				SceneNode& operator= (const SceneNode &iSource);

				/**
				 * \brief const copy constructor
				 */
				SceneNode(const SceneNode& iSource);

		    };	
		}
	}
}

#endif
