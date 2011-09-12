/*
 This file is part of The Simplicity Engine.

 The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

 The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ENGINE_H_
#define ENGINE_H_

#include <boost/smart_ptr.hpp>

#include "../Entity.h"
#include "EngineInput.h"

namespace simplicity
{
  /**
   * <p>
   * A system that repeats a cycle of functionality. The cycles of functionality are atomic in the context of the <code>Engine</code>. In environments
   * where two or more <code>Engine</code>s are 'chained' together, the {@link simplicity::EngineInput EngineInput} can be used to pass
   * information from one <code>Engine</code> to the next.
   * </p>
   *
   * @author Gary Buyn
   */
  class Engine
  {
    public:
      /**
       * <p>
       * Disposes of an instance of <code>Engine</code> (included to allow polymorphic deletion).
       * </p>
       */
      virtual
      ~Engine()
      {
      }

      /**
       * <p>
       * Adds the given <code>Entity</code>s to the <code>Entity</code>s whose components are to be processed by this <code>Engine</code>.
       * </p>
       *
       * @param entities The <code>Entity</code>s whose components are to be processed by this <code>Engine</code>.
       */
      virtual void
      addEntities(std::vector<boost::shared_ptr<Entity> > entities) = 0;

      /**
       * <p>
       * Adds the given <code>Entity</code> to the <code>Entity</code>s whose components are to be processed by this <code>Engine</code>.
       * </p>
       *
       * @param entity The <code>Entity</code> whose components are to be processed by this <code>Engine</code>.
       */
      virtual void
      addEntity(boost::shared_ptr<Entity> entity) = 0;

      /**
       * <p>
       * Advances this <code>Engine</code> by one cycle.
       * </p>
       *
       * @param input The {@link com.se.simplicity.engine.EngineInput EngineInput} to process during this advancement.
       *
       * @throw SEEngineAdvancementException If this <code>Engine</code> fails to advance.
       *
       * @return The <code>EngineInput</code> for the next {@link com.se.simplicity.engine.Engine Engine} in the chain.
       */
      virtual boost::shared_ptr<EngineInput>
      advance(const boost::shared_ptr<EngineInput> input) = 0;

      /**
       * <p>
       * Destroys this <code>Engine</code>.
       * </p>
       */
      virtual void
      destroy() = 0;

      /**
       * <p>
       * Retrieves the preferred frequency (advancements per second) of this <code>Engine</code>.
       * </p>
       *
       * @return The preferred frequency (advancements per second) of this <code>Engine</code>.
       */
      virtual int
      getPreferredFrequency() const = 0;

      /**
       * <p>
       * Initialises this <code>Engine</code>.
       * </p>
       */
      virtual void
      init() = 0;

      /**
       * <p>
       * Resets this <code>Engine</code> to it's initial properties.
       * </p>
       */
      virtual void
      reset() = 0;

      /**
       * <p>
       * Sets the preferred frequency (advancements per second) of this <code>Engine</code>.
       * </p>
       *
       * @param preferredFrequency The preferred frequency (advancements per second) of this <code>Engine</code>.
       */
      virtual void
      setPreferredFrequency(const int preferredFrequency) = 0;
  };
}

#endif /* ENGINE_H_ */
