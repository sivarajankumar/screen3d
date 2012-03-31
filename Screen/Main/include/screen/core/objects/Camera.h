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

#include <screen/utils/Declaration.h>

#include <screen/main/Export.h>

#include <glm/glm.hpp>

#include <iostream>

/**
 * Namespace all screen classes
 */
namespace screen {
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
				screen::core::Scene* getScene() const;

				/**
				 * \brief Check if the camera is active in its scene
				 * \return true if the camera is the active one in the scene
				 */
				bool isActive() const;

				/**
				 * Set the position of the camera
				 * \param[in] iVectorPosition position given as a vector
				 */
				void setPosition(const glm::vec3& iVectorPosition);

				/**
				 * Set the position of the camera
				 * \param[in] x
				 * \param[in] y
				 * \param[in] z
				 */
				void setPosition(const float x, const float y, const float z);

				/**
				 * Get the absolute position of the camera
				 * \return vector repesenting the position of the camera
				 */
				const glm::vec3& getPosition() const;

				/**
				 * Get camera projection
				 * \return camera projection matrix
				 */
				const glm::mat4x4 getProjection() const;

				/**
				 * Get camera view
				 * \return camera view matrix
				 */
				const glm::mat4x4 getView() const;

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

				glm::vec3 _position;				///< camera position
				// TODO find definition of those values
				glm::vec3 _center;					///< camera view center
				glm::vec3 _up;						///< camera view up
				float _fov;							///< camera field of view
				float _aspect;
				float _near;
				float _far;

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
				 * \brief assignment operator
				 */
				Camera& operator= (Camera &iSource);

				/**
				 * \brief const copy constructor
				 */
				Camera(const Camera& iSource);
				/**
				 * \brief copy constructor
				 */
				Camera(Camera& iSource);

		    };	
		}
	}
}

#endif
