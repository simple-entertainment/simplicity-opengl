/*
 This file is part of The Simplicity Engine.

 The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

 The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include <boost/smart_ptr.hpp>

#include "Component.h"

namespace simplicity
{
  /**
   * <p>
   * An entity.
   * </p>
   *
   * @author Gary Buyn
   */
  class Entity
  {
    public:
      /**
       * <p>
       * Creates an instance of <code>Entity</code>.
       * </p>
       */
      Entity();

      /**
       * <p>
       * Disposes of an instance of <code>Entity</code>.
       * </p>
       */
      virtual
      ~Entity();

      /**
       * <p>
       * Adds a component.
       * </p>
       *
       * @param component The component to add.
       */
      void
      addComponent(boost::shared_ptr<Component> component);

      /**
       * <p>
       * Retrieves the components.
       * </p>
       *
       * @return components The components.
       */
      std::vector<boost::shared_ptr<Component> >
      getComponents();

      /**
       * <p>
       * Removes a component.
       * </p>
       *
       * @param component The component to remove.
       */
      void
      removeComponent(const Component& component);

    private:
      /**
       * <p>
       * The components.
       * </p>
       */
      std::vector<boost::shared_ptr<Component> > components;
  };
}

#endif /* ENTITY_H_ */
