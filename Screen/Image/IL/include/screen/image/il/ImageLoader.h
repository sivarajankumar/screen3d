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
/**
 * \file Screen/Image/IL/ImageLoader.h
 * \brief Image loader header file
 * \author
 *
 * Image loader classe using devIL
 */

#ifndef SCREEN_IMAGE_IL_LOADER_H
#define SCREEN_IMAGE_IL_LOADER_H

#include <screen/utils/Loader.h>
#include <screen/core/objects/Image.h>
#include <screen/utils/Declaration.h>
#include <screen/image/il/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all image classes
	 */
	namespace image {
		/**
		 * Namespace for all classes based on devIL
		 */
		namespace il{

			/**
			 * \brief Class used to load a image using devIL
			 */
			class SCREEN_IMAGE_IL_EXPORT ImageLoader : public screen::utils::Loader<screen::core::objects::Image> {

				SCREEN_DECL_CLASS(screen::image::il::ImageLoader)
				SCREEN_DECL_LOADER(screen::image::il::ImageLoader,screen::core::objects::Image)

			public:

				/**
				 * \brief Constructor
				 */
				ImageLoader();

				/**
				 * \brief Destructor
				 */
				~ImageLoader();

				/**
				 * \brief load an image from a file name
				 * \param[in] iFilename name of the image file to load
				 * \return returns a pointer of an image object, created from the file
				 */
				screen::core::objects::Image* loadFromFile(const std::string& iFilename) const;

			};
		}
	}
}

#endif
