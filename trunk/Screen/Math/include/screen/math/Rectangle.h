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
 * \file Rectangle.h
 * \brief Rectangle header file for screen::math
 * \author Ratouit Thomas
 * \date 29 nov. 09
 *
 * Rectangle definition and mathematical operations on rectangles
 */

#ifndef SCREEN_RECTANGLE_H
#define SCREEN_RECTANGLE_H

#include <screen/math/Vector2i.h>
#include <screen/utils/Declaration.h>
#include <screen/math/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all math classes
	 */
	namespace math {

		/**
		 * \brief Possible intersections values
		 */
		enum RectangleIntersection{
			RECT_INT_IN,			///< The rectangle in totally inside
			RECT_INT_INTERSECT,		///< The rectangle intersect with the other (partially inside)
			RECT_INT_OUT			///< The rectangle is totally outside the other
	    };
	
		/**
		 *   \brief Rectangle class
		 */
		class SCREEN_MATH_EXPORT Rectangle {

			SCREEN_DECL_CLASS(screen::math::Rectangle)

		public:


			Rectangle(const Vector2i& leftTop = Vector2i(0, 0), const Vector2i& size = Vector2i(0, 0));
			Rectangle(int left, int top, int width, int height);
			~Rectangle();
			
			void set(int left, int top, int width, int height);
			void get(int& left, int& top, int& width, int& height) const;
			
			void set(const Vector2i& leftTop, const Vector2i& size);
			void get(Vector2i& leftTop, Vector2i& size) const;
			
			int getLeft() const;
			int getTop() const;
			int getWidth() const;
			int getHeight() const;
			int getRight() const;
			int getBottom() const;
			
			void setLeft(int left);
			void setTop(int top);
			void setWidth(int width);
			void setHeight(int height);
			void setRight(int right);
			void setBottom(int bottom);
			
			Vector2i getLeftTop() const;
			Vector2i getSize() const;
			Vector2i getRightBottom() const;
			
			void setLeftTop(const Vector2i& v);
			void setSize(const Vector2i& v);
			void setRightBottom(const Vector2i& v);
			
			bool operator ==(const Rectangle& rect) const;
			bool operator !=(const Rectangle& rect) const;
			
			screen::math::RectangleIntersection intersects(const Rectangle& rect) const;
		
		private:
			Vector2i leftTop;
			Vector2i size;

		};
	}
}

#endif
