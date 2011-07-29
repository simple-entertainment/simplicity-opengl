/*
 This file is part of The Simplicity Engine.

 The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

 The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TORUS_H_
#define TORUS_H_

#include "Shape.h"

namespace simplicity
{
  /**
   * <p>
   * A torus-shaped {@link simplicity::Model Model}.
   * </p>
   *
   * @author Gary Buyn
   */
  class Torus : public virtual Shape
  {
    public:
      /**
       * <p>
       * Creates an instance of <code>Torus</code>.
       * </p>
       */
      Torus();

      /**
       * <p>
       * Disposes of an instance of <code>Torus</code>.
       * </p>
       */
      virtual
      ~Torus();

      const TranslationVector<float>&
      getCenter() const;

      RGBAColourVector<float>&
      getColour() const;

      /**
       * <p>
       * Retrieves the inner radius. The default is 1.0.
       * </p>
       *
       * @return The inner radius.
       */
      float
      getInnerRadius() const;

      /**
       * <p>
       * Retrieves the outer radius. The default is 2.0.
       * </p>
       *
       * @return The outer radius.
       */
      float
      getOuterRadius() const;

      void
      setColour(boost::shared_ptr<RGBAColourVector<float> > colour);

      /**
       * <p>
       * Sets the inner radius. The default is 1.0.
       * </p>
       *
       * @param innerRadius The inner radius.
       */
      void
      setInnerRadius(const float innerRadius);

      /**
       * <p>
       * Sets the outer radius. The default is 2.0.
       * </p>
       *
       * @param outerRadius The outer radius.
       */
      void
      setOuterRadius(const float outerRadius);

    private:
      /**
       * <p>
       * The point at the center of this <code>Torus</code>.
       * </p>
       */
      boost::shared_ptr<TranslationVector<float> > fCenter;

      /**
       * <p>
       * The colour to render this <code>Torus</code> as.
       * </p>
       */
      boost::shared_ptr<RGBAColourVector<float> > fColour;

      /**
       * <p>
       * The inner radius.
       * </p>
       */
      float fInnerRadius;

      /**
       * <p>
       * The outer radius.
       * </p>
       */
      float fOuterRadius;
  };
}

#endif /* TORUS_H_ */
