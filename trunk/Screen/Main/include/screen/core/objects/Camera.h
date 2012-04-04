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
 * \file Camera.h
 * \brief The camera from which the scene is rendered
 * \author pjdemaret
 *
 * This class is used to represent the camera object. The camera is the viewpoint from which the
 * 3D scene is rendered.
 */

#ifndef SCREEN_CAMERA_H
#define SCREEN_CAMERA_H

//utils
#include <screen/utils/Declaration.h>

//main
#include <screen/main/Export.h>

// glm
#include <glm/glm.hpp>

// stl
#include <iostream>

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
		/**
		 * Namespace for the objects of the engine
		 */

		class Scene;

		namespace objects {

			/**
			 * \brief Camera object
			 *
			 * Object describe the view from which a scene is rendered.
			 * The camera must be attached to a scene. A scene can have several cameras
			 * but only one camera can be active.
			 * Default aspect ratio is 4/3. Default near clip distance is 1. Default far clip distance is 100.
			 * Default fov is 45. Default position is (0,0,0). Default direction is (0,0,1). Default up is (0,1,0).
			 */
			class SCREEN_MAIN_EXPORT Camera {
				SCREEN_DECL_CLASS(screen::core::objects::Camera)
			public:

				friend class screen::core::Scene;

				/**
				 * \brief Get the name of the camera
				 * \return Name of the camera
				 */
		        const std::string& getName() const;

				/**
				 * \brief Get the scene holding the camera
				 * \return scene holding the camera
				 */
				const screen::core::Scene& getScene() const;

				/**
				 * \brief Access the scene holding the camera
				 * \return scene holding the camera
				 */
				screen::core::Scene& accessScene() const;

				/**
				 * \brief Check if the camera is active in its scene
				 * \return true if the camera is the active one in the scene
				 */
				bool isActive() const;

				/**
				 * \brief Set the position of the camera
				 * \param[in] iVectorPosition position given as a vector
				 */
				void setPosition(const glm::vec3& iVectorPosition);

				/**
				 * \brief Set the position of the camera
				 * \param[in] x (horizontal)
				 * \param[in] y (up)
				 * \param[in] z (depth)
				 */
				void setPosition(const float x, const float y, const float z);

				/**
				 * \brief Get the absolute position of the camera
				 * \return vector repesenting the position of the camera
				 */
				const glm::vec3& getPosition() const;

				/**
				 * \brief Move the camera by the given vector
				 * \param[in] iVectorMove vector used to move the camera
				 */
				void move(const glm::vec3& iVectorMove);

				/**
				 * \brief Move the camera on its local z axis
				 * \param[in] iDistance distance of the camera movement
				 */
				void translateZ(const float iDistance);

				/**
				 * \brief Move the camera on its local y axis
				 * \param[in] iDistance distance of the camera movement
				 */
				void translateY(const float iDistance);

				/**
				 * \brief Move the camera on its local x axis
				 * \param[in] iDistance distance of the camera movement
				 */
				void translateX(const float iDistance);

				/**
				 * \brief Move the camera on an axis
				 * \param[in] iDistance distance of the camera movement
				 * \param[in] iAxis axis on which the camera is moving
				 */
				void translate(const float iDistance, const glm::vec3& iAxis);

				/**
				 * \brief Set the direction of the camera
				 * \param[in] iVectorDirection position given as a vector
				 */
				void setDirection(const glm::vec3& iVectorDirection);

				/**
				 * \brief Set the direction of the camera
				 * \param[in] x (horizontal)
				 * \param[in] y (up)
				 * \param[in] z (depth)
				 */
				void setDirection(const float x, const float y, const float z);

				/**
				 * \brief Get the absolute direction of the camera
				 * \return vector repesenting the direction of the camera (normalized)
				 */
				const glm::vec3& getDirection() const;

				/**
				 * \brief Get the absolute up vector of the camera
				 * \return vector repesenting the up vector of the camera (normalized)
				 */
				const glm::vec3& getUp() const;

				/**
				 * \brief Get the absolute right vector of the camera
				 *
				 * This vector is computed when get is called
				 * \return vector representing the right vector of the camera (normalized)
				 */
				const glm::vec3& getRight();

				/**
				 * \brief Rotate anticlockwise arount its local z axis
				 * \param[in] iDegree angle in Degree
				 */
				void roll(const screen::math::Degree& iAngle);

				/**
				 * \brief Rotate anticlockwise arount its local y axis
				 * \param[in] iDegree angle in Degree
				 */
				void yaw(const screen::math::Degree& iAngle);

				/**
				 * \brief Rotate anticlockwise arount its local x axis
				 * \param[in] iDegree angle in Degree
				 */
				void pitch(const screen::math::Degree& iAngle);

				/**
				 * \brief Rotate the camera around a given axis
				 * \param[in] iAxis vector representing the axis
				 * \param[in] iDegree angle in Degree
				 */
				void rotate(const glm::vec3& iAxis, const screen::math::Degree& iAngle);

				/**
				 * \brief Make the camera look at a point in space
				 *
				 * Make the camera look at a point in space. Does not change the up vector of the camera.
				 * \param[in] iPoint point ot look at
				 */
				void lookAt(const glm::vec3& iPoint);

				/**
				 * \brief Make the camera look at a point in space
				 *
				 * Make the camera look at a point in space. Does not change the up vector of the camera.
				 * \param[in] x
				 * \param[in] y
				 * \param[in] z
				 */
				void lookAt(const float x, const float y, const float z);

				/**
				 * \brief Get camera view
				 *
				 * The matrix is computed when get is called
				 * \return camera view matrix
				 */
				const glm::mat4x4& getView();

				/**
				 * \brief Get the aspect ratio
				 * \return aspect ratio
				 */
				float getAspectRatio() const;

				/**
				 * \brief Set the aspect ratio
				 * \param[in] iAspectRatio aspect ratio
				 */
				void setAspectRatio(const float iAspectRatio);

				/**
				 * \brief Get near clip distance
				 * \return near clip distance
				 */
				float getNearClipDistance() const;

				/**
				 * \brief Set near clip distance
				 * \param[in] iNear near clip distance
				 */
				void setNearClipDistance(const float iNear);

				/**
				 * \brief Get far clip distance
				 * \return far clip distance
				 */
				float getFarClipDistance() const;

				/**
				 * \brief Set far clip distance
				 * \param[in] iFar far clip distance
				 */
				void setFarClipDistance(const float iFar);

				/**
				 * \brief Get camera projection
				 *
				 * The matrix is computed when get is called
				 * \return camera projection matrix
				 */
				const glm::mat4x4& getProjection();

			protected:

				/**
				 * \brief Constructor
				 *
				 * \param[in] iName name of the camera
				 * \param[in] iScene scene where the camera is attached
				 */
				Camera(const std::string& iName, screen::core::Scene* iScene);

				/**
				 * Destructor
				 */
				virtual ~Camera();

				/**********************************************************************/

				std::string _name;					///< Name of the camera
				screen::core::Scene* _scene;		///< Scene rendered by the camera

			private:

				/**
				 * \brief Update projection matrix
				 *
				 * Compute projection matrix. Should be called before each access to the
				 * matrix
				 */
				void updateProjection();

				/**
				 * \brief Compute view matrix
				 *
				 * Compute view matrix. hould be called before each access to the
				 * matrix
				 */
				void updateView();

				/**
				 * \brief Compute right vector
				 *
				 * Compute right vector. hould be called before each access to the
				 * vector
				 */
				void updateRight();

				/**********************************************************************/

			protected:

				glm::vec3 _position;				///< camera position, also used as the position of the eye (center)
				glm::vec3 _eye;						///< camera view eye, direction of the eye (view direction) (normalized vector)
				glm::vec3 _up;						///< camera view up, direction of the up vector (normalized vector)
				float _fov;							///< camera field of view
				float _aspectRatio;					///< camera	perspective's aspect ratio
				float _near;						///< camera perspective's near
				float _far;							///< camera perspective's far
				bool _projectionNeedsUpdate;		///< true if the projection matrix needs to be re-compute
				bool _viewNeedsUpdate;				///< true if the view matrix needs to be re-compute
				bool _rightNeedsUpdate;				///< true if the right vector needs to be re-compute

			private:

				/* do not call directly, those values are not updated automatically, use the getters */
				glm::vec3 _right;					///< camera right vector.
				glm::mat4x4 _projection;			///< camera projection transformation matrix
				glm::mat4x4 _view;					///< camera view matrix

				// DO NOT USE
				/**
				 * \brief Default constructor
				 */
				Camera();

				/**
				 * \brief const assignment operator
				 */
				Camera& operator= (const Camera &iSource);

				/**
				 * \brief const copy constructor
				 */
				Camera(const Camera& iSource);

		    };	
		}
	}
}

#endif
