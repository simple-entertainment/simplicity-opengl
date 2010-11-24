/*
    This file is part of The Simplicity Engine.

    The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
package com.se.simplicity.scenegraph;

import java.util.List;

/**
 * <p>
 * A tree type graph of {@link com.se.simplicity.scenegraph.Node Node}s that represents a scene in a virtual universe. The <code>SceneGraph</code>
 * manages all the components within it. Methods of the <code>SceneGraph</code> should be called instead of calling methods on its components
 * directly. This ensures that the management of those components is not undermined.
 * </p>
 * 
 * @author Gary Buyn
 */
public interface SceneGraph
{
    /**
     * <p>
     * Adds a subgraph to the <code>SceneGraph</code>. The subgraph must be a tree type graph. The <code>SceneGraph</code> will determine where to add
     * the subgraph depending on the internal structure it maintains.
     * </p>
     * 
     * <p>
     * This method should be called instead of retrieving the root {@link com.se.simplicity.scenegraph.Node Node} of the <code>SceneGraph</code> and
     * manually adding a subgraph to maintain the integrity of the <code>SceneGraph</code>.
     * </p>
     * 
     * @param subgraphRoot The root <code>Node</code> of the subgraph to add.
     */
    void addSubgraph(Node subgraphRoot);

    /**
     * <p>
     * Adds a subgraph to the <code>SceneGraph</code>. The subgraph must be a tree type graph.
     * </p>
     * 
     * <p>
     * This method should be called instead of retrieving the root {@link com.se.simplicity.scenegraph.Node Node} of the <code>SceneGraph</code> and
     * manually adding a subgraph to maintain the integrity of the <code>SceneGraph</code>.
     * </p>
     * 
     * @param subgraphRoot The root <code>Node</code> of the subgraph to add.
     * @param parent The <code>Node</code> within the <code>SceneGraph</code> to add the subgraph under.
     */
    void addSubgraph(Node subgraphRoot, Node parent);

    /**
     * <p>
     * Retrieves the {@link com.se.simplicity.scenegraph.Node Node} with the given ID.
     * </p>
     * 
     * @param id The ID of the <code>Node</code> to retrieve.
     * 
     * @return The <code>Node</code> with the given ID.
     */
    Node getNode(int id);

    /**
     * Retrieves the root {@link com.se.simplicity.scenegraph.Node Node} of this <code>SceneGraph</code>.
     * 
     * @return The root <code>Node</code> of this <code>SceneGraph</code>.
     */
    Node getRoot();

    /**
     * <p>
     * Retrieves the root {@link com.se.simplicity.scenegraph.Node Node}s off all the subgraphs in this <code>SceneGraph</code>.
     * </p>
     * 
     * @return The root <code>Node</code>s off all the subgraphs in this <code>SceneGraph</code>.
     */
    List<Node> getSubgraphRoots();

    /**
     * <p>
     * Removes a subgraph from the <code>SceneGraph</code>.
     * </p>
     * 
     * <p>
     * This method should be called instead of retrieving the root {@link com.se.simplicity.scenegraph.Node Node} of the subgraph and manually
     * removing it from its parent to maintain the integrity of the <code>SceneGraph</code>.
     * </p>
     * 
     * @param subgraphRoot The root <code>Node</code> of the subgraph to remove.
     */
    void removeSubgraph(Node subgraphRoot);

    /**
     * <p>
     * Resets the IDs of all the {@link com.se.simplicity.scenegraph.Node Node}s in this <code>SceneGraph</code>.
     * </p>
     */
    void resetIDs();
}
