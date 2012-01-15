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
 * \file Rectangle.cpp
 * \brief Rectangle code source file for screen::math
 * \author Ratouit Thomas
 * \date 29 nov. 09
 *
 * Rectangle definition and mathematical operations on rectangles
 */

#include <screen/math/Rectangle.h>

namespace screen {
	namespace math {
		Rectangle::Rectangle(const Vector2i& leftTop, const Vector2i& size)
			:leftTop(leftTop),size(size){
			SCREEN_DECL_CONSTRUCTOR(Rectangle)
		}
		
		Rectangle::Rectangle(int left, int top, int width, int height)
			:leftTop(left,top),size(width,height){
			SCREEN_DECL_CONSTRUCTOR(Rectangle)
		}

		
		Rectangle::~Rectangle(){
			SCREEN_DECL_DESTRUCTOR(~Rectangle)
		}
				
		void Rectangle::set(int left, int top, int width, int height){
			SCREEN_DECL_METHOD(set)
			leftTop.set(left,top);
			size.set(width,height);
		}
		void Rectangle::get(int& left, int& top, int& width, int& height) const{
			SCREEN_DECL_METHOD(get)
			leftTop.get(left,top);
			size.get(width,height);
		}
		
		void Rectangle::set(const Vector2i& leftTop, const Vector2i& size){
			SCREEN_DECL_METHOD(set)
			this->leftTop = leftTop;
			this->size = size;
		}
		void Rectangle::get(Vector2i& leftTop, Vector2i& size) const{
			SCREEN_DECL_METHOD(get)
			leftTop = this->leftTop;
			size = this->size;
		}
		
		int Rectangle::getLeft() const{
			SCREEN_DECL_METHOD(getLeft)
			return leftTop.getX();
		}
		int Rectangle::getTop() const{
			SCREEN_DECL_METHOD(getTop)
			return leftTop.getY();
		}
		int Rectangle::getWidth() const{
			SCREEN_DECL_METHOD(getWidth)
			return size.getX();
		}
		int Rectangle::getHeight() const{
			SCREEN_DECL_METHOD(getHeight)
			return size.getY();
		}
		int Rectangle::getRight() const{
			SCREEN_DECL_METHOD(getRight)
			return leftTop.getX() + size.getX();
		}
		int Rectangle::getBottom() const{
			SCREEN_DECL_METHOD(getBottom)
			return leftTop.getY() + size.getY();
		}
		
		void Rectangle::setLeft(int left){
			SCREEN_DECL_METHOD(setLeft)
			leftTop.setX(left);
		}
		void Rectangle::setTop(int top){
			SCREEN_DECL_METHOD(setTop)
			leftTop.setY(top);
		}
		void Rectangle::setWidth(int width){
			SCREEN_DECL_METHOD(setWidth)
			size.setX(width);
		}
		void Rectangle::setHeight(int height){
			SCREEN_DECL_METHOD(setHeight)
			size.setY(height);
		}
		void Rectangle::setRight(int right){
			SCREEN_DECL_METHOD(setRight)
			size.setX(right-leftTop.getX());
		}
		void Rectangle::setBottom(int bottom){
			SCREEN_DECL_METHOD(setBottom)
			size.setY(bottom-leftTop.getY());
		}
		
		Vector2i Rectangle::getLeftTop() const{
			SCREEN_DECL_METHOD(getLeftTop)
			return leftTop;
		}
		Vector2i Rectangle::getSize() const{
			SCREEN_DECL_METHOD(getSize)
			return size;
		}
		Vector2i Rectangle::getRightBottom() const{
			SCREEN_DECL_METHOD(getRightBottom)
			return size + leftTop;
		}
		
		void Rectangle::setLeftTop(const Vector2i& v){
			SCREEN_DECL_METHOD(setLeftTop)
			leftTop = v;
		}
		void Rectangle::setSize(const Vector2i& v){
			SCREEN_DECL_METHOD(setSize)
			size = v;
		}
		void Rectangle::setRightBottom(const Vector2i& v){
			SCREEN_DECL_METHOD(setRightBottom)
			size = v - leftTop;
		}
		
		bool Rectangle::operator ==(const Rectangle& rect) const{
		    return (leftTop == rect.leftTop) && (size == rect.size);
		}
		bool Rectangle::operator !=(const Rectangle& rect) const{
		    return !(*this == rect);
		}
		
		screen::math::RectangleIntersection Rectangle::intersects(const Rectangle& rect) const{
			using namespace std;

		    // Intersection rectangle
		    Vector2i intLeftTop(max(getLeft(), rect.getLeft()), max(getTop(), getTop()));
		    Vector2i intRightBottom(min(getRight(), rect.getRight()), min(getBottom(), rect.getBottom()));

		    if ((intLeftTop.getX() > intRightBottom.getX()) || (intLeftTop.getY() > intRightBottom.getY()))
		    	return screen::math::RECT_INT_OUT;
		    
		    Rectangle intersection(intLeftTop, intRightBottom);

		    if ((intersection == *this) || (intersection == rect))
		        return screen::math::RECT_INT_IN;
		    else
		        return screen::math::RECT_INT_INTERSECT;
		}
	}
}
