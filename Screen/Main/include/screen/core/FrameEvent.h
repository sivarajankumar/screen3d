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

#ifndef SCREEN_FRAME_EVENT_H
#define SCREEN_FRAME_EVENT_H

namespace screen {
    namespace core {
        class FrameEvent {
        public:
            inline explicit FrameEvent()
                    :timeSinceLastFrame(0),timeSinceLastEvent(0) {}

            inline ~FrameEvent() {}

            inline double getTimeSinceLastFrame() const {
                return timeSinceLastFrame;
            }

            inline double getTimeSinceLastEvent() const {
                return timeSinceLastEvent;
            }

            inline void setTimeSinceLastFrame(double time) {
                timeSinceLastFrame=time;
            }

            inline void setTimeSinceLastEvent(double time) {
                timeSinceLastEvent=time;
            }
        private:
            double timeSinceLastFrame;
            double timeSinceLastEvent;
        };
    }
}

#endif
