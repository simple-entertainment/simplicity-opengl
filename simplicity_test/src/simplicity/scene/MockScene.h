/*
 This file is part of The Simplicity Engine.

 The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

 The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MOCKSCENE_H_
#define MOCKSCENE_H_

#include <gmock/gmock.h>

#include <simplicity/scene/Scene.h>

namespace simplicity
{
  /**
   * <p>
   * A mock implementation of {@link simplicity::Scene Scene}.
   * </p>
   *
   * @author Gary Buyn
   */
  class MockScene : public Scene
  {
    public:
      MOCK_METHOD1(addCamera, void(boost::shared_ptr<Camera> camera));
      MOCK_METHOD1(addLight, void(boost::shared_ptr<Light> light));
      MOCK_CONST_METHOD0(getCameras, std::vector<boost::shared_ptr<Camera> >());
      MOCK_CONST_METHOD0(getLights, std::vector<boost::shared_ptr<Light> >());
      MOCK_CONST_METHOD0(getSceneGraph, boost::shared_ptr<SceneGraph>());
      MOCK_METHOD1(setCameras, void(std::vector<boost::shared_ptr<Camera> > cameras));
      MOCK_METHOD1(setLights, void(std::vector<boost::shared_ptr<Light> > const lights));
      MOCK_METHOD1(setSceneGraph, void(boost::shared_ptr<SceneGraph> sceneGraph));
  };
}

#endif /* MOCKSCENE_H_ */
