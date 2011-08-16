/*
 This file is part of The Simplicity Engine.

 The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

 The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SIMPLEOPENGLPICKINGENGINETEST_H_
#define SIMPLEOPENGLPICKINGENGINETEST_H_

#include <gtest/gtest.h>

#include <simplicity/opengl/picking/engine/SimpleOpenGLPickingEngine.h>

namespace simplicity
{
  namespace opengl
  {
    /**
     * <p>
     * Unit tests for the class {@link simplicity::opengl::SimpleOpenGLPickingEngine SimpleOpenGLPickingEngine}.
     * </p>
     *
     * @author Gary Buyn
     */
    class SimpleOpenGLPickingEngineTest : public testing::Test
    {
      protected:
        /**
         * An instance of the class being unit tested.
         */
        simplicity::opengl::SimpleOpenGLPickingEngine fTestObject;
    };
  }
}

#endif /* SIMPLEOPENGLPICKINGENGINETEST_H_ */
