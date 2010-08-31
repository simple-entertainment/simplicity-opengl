/*
    This file is part of The Simplicity Engine.

    The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
package com.se.simplicity.jogl.test.picking.engine;

import static org.easymock.EasyMock.expect;
import static org.easymock.classextension.EasyMock.createMock;
import static org.easymock.classextension.EasyMock.replay;
import static org.easymock.classextension.EasyMock.reset;
import static org.easymock.classextension.EasyMock.verify;
import static org.junit.Assert.assertEquals;

import java.awt.Dimension;

import javax.media.opengl.GL;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import com.se.simplicity.jogl.picking.SimpleJOGLPicker;
import com.se.simplicity.jogl.picking.engine.SimpleJOGLPickingEngine;
import com.se.simplicity.jogl.rendering.SimpleJOGLCamera;
import com.se.simplicity.jogl.test.mocks.MockGL;
import com.se.simplicity.picking.Pick;
import com.se.simplicity.picking.Picker;
import com.se.simplicity.picking.event.PickEvent;
import com.se.simplicity.picking.event.PickListener;
import com.se.simplicity.rendering.Camera;
import com.se.simplicity.rendering.engine.RenderingEngine;
import com.se.simplicity.scene.Scene;

/**
 * <p>
 * Unit tests for the class {@link com.se.simplicity.jogl.rendering.SimpleJOGLPickingEngine SimpleJOGLPickingEngine}.
 * </p>
 * 
 * @author Gary Buyn
 */
public class SimpleJOGLPickingEngineTest
{
    /**
     * An instance of the class being unit tested.
     */
    private SimpleJOGLPickingEngine testObject;

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLPickingEngine.advance advance()}.
     * </p>
     */
    @Test
    public void advance()
    {
        SimpleJOGLPicker mockPicker = createMock(SimpleJOGLPicker.class);
        Scene mockScene = createMock(Scene.class);
        Camera mockCamera = createMock(Camera.class);

        testObject.setPicker(mockPicker);
        testObject.setScene(mockScene);
        testObject.setCamera(mockCamera);
        testObject.pick(5, 10, 15, 20);
        testObject.pick(10, 20, 30, 40);

        reset(mockPicker);
        expect(mockPicker.pickScene(mockScene, mockCamera, testObject.getPicks().get(0))).andReturn(null);
        expect(mockPicker.pickScene(mockScene, mockCamera, testObject.getPicks().get(1))).andReturn(null);
        replay(mockPicker);

        testObject.advance();

        verify(mockPicker);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLPickingEngine.advance advance()} with the special condition that the
     * {@link com.se.simplicity.jogl.rendering.SimpleJOGLPickingEngine SimpleJOGLPickingEngine} being tested does not have any outstanding picks to
     * perform.
     * </p>
     */
    @Test
    public void advanceNoPicks()
    {
        SimpleJOGLPicker mockPicker = createMock(SimpleJOGLPicker.class);

        testObject.setPicker(mockPicker);

        reset(mockPicker);
        replay(mockPicker);

        testObject.advance();

        verify(mockPicker);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLPickingEngine.advance advance()} with the special condition that a
     * <code>RenderingEngine</code> is specified.
     * </p>
     */
    @Test
    public void advanceRenderer()
    {
        SimpleJOGLPicker mockPicker = createMock(SimpleJOGLPicker.class);
        RenderingEngine mockRenderingEngine = createMock(RenderingEngine.class);
        Scene mockScene = createMock(Scene.class);
        Camera mockCamera = createMock(Camera.class);

        expect(mockRenderingEngine.getScene()).andStubReturn(mockScene);
        expect(mockRenderingEngine.getCamera()).andStubReturn(mockCamera);
        replay(mockRenderingEngine);

        testObject.setPicker(mockPicker);
        testObject.setRenderingEngine(mockRenderingEngine);
        testObject.pick(5, 10, 15, 20);
        testObject.pick(10, 20, 30, 40);

        reset(mockPicker);
        expect(mockPicker.pickScene(mockScene, mockCamera, testObject.getPicks().get(0))).andReturn(null);
        expect(mockPicker.pickScene(mockScene, mockCamera, testObject.getPicks().get(1))).andReturn(null);
        replay(mockPicker);

        testObject.advance();

        verify(mockPicker);
    }

    /**
     * <p>
     * Setup to perform before each unit test.
     * </p>
     */
    @Before
    public void before()
    {
        testObject = new SimpleJOGLPickingEngine();
    }

    /**
     * Unit test the method {@link com.se.simplicity.jogl.picking.SimpleJOGLPickingEngine.convertPickCoordinatesFromViewportToSceneGraph
     * convertPickCoordinatesFromViewportToSceneGraph()}.
     */
    @Test
    public void convertPickCoordinatesFromViewportToSceneGraph()
    {
        // Create dependencies.
        Pick mockPick = createMock(Pick.class);
        SimpleJOGLCamera mockCamera = createMock(SimpleJOGLCamera.class);

        Dimension dimension = new Dimension();
        dimension.width = 200;
        dimension.height = 200;

        // Dictate correct behaviour.
        expect(mockPick.getX()).andStubReturn(100f);
        expect(mockPick.getY()).andStubReturn(100f);
        expect(mockPick.getWidth()).andStubReturn(2.0f);
        expect(mockPick.getHeight()).andStubReturn(2.0f);
        mockPick.setX(0.05f);
        mockPick.setY(0.05f * 0.75f);
        mockPick.setWidth(0.1f / 100);
        mockPick.setHeight((0.1f * 0.75f) / 100);
        expect(mockCamera.getFrameWidth()).andStubReturn(0.1f);
        expect(mockCamera.getFrameAspectRatio()).andStubReturn(0.75f);
        replay(mockPick, mockCamera);

        // Initialise test environment.
        testObject.setCamera(mockCamera);

        // Preform test.
        testObject.convertPickCoordinatesFromViewportToSceneGraph(dimension, mockPick);

        // Verify test results.
        verify(mockPick);
    }

    /**
     * Unit test the method {@link com.se.simplicity.jogl.picking.SimpleJOGLPickingEngine.firePickEvent firePickEvent()}.
     */
    @Test
    public void firePickEvent()
    {
        PickListener mockPickListener1 = createMock(PickListener.class);
        PickListener mockPickListener2 = createMock(PickListener.class);
        PickEvent mockPickEvent = createMock(PickEvent.class);

        testObject.addPickListener(mockPickListener1);
        testObject.addPickListener(mockPickListener2);

        reset(mockPickListener1, mockPickListener2);
        mockPickListener1.scenePicked(mockPickEvent);
        mockPickListener2.scenePicked(mockPickEvent);
        replay(mockPickListener1, mockPickListener2);

        testObject.firePickEvent(mockPickEvent);

        verify(mockPickListener1, mockPickListener2);
    }

    /**
     * Unit test the method {@link com.se.simplicity.jogl.picking.SimpleJOGLPickingEngine.pick pick()}.
     */
    @Test
    public void pick()
    {
        testObject.pick(5, 10, 15, 20);

        assertEquals(1, testObject.getPicks().size(), 0);

        Pick pick0 = testObject.getPicks().get(0);
        assertEquals(5, pick0.getX(), 0);
        assertEquals(10, pick0.getY(), 0);
        assertEquals(15, pick0.getWidth(), 0);
        assertEquals(20, pick0.getHeight(), 0);

        Pick mockPick = createMock(Pick.class);

        testObject.pick(mockPick);

        assertEquals(2, testObject.getPicks().size(), 0);
        assertEquals(mockPick, testObject.getPicks().get(1));
    }

    /**
     * Unit test the method {@link com.se.simplicity.jogl.picking.SimpleJOGLPickingEngine.pickViewport pickViewport()}.
     */
    @Test
    public void pickViewport()
    {
        // Create dependencies.
        SimpleJOGLCamera mockCamera = createMock(SimpleJOGLCamera.class);

        Dimension dimension = new Dimension();
        dimension.width = 200;
        dimension.height = 200;

        Pick pick = new Pick();
        pick.setX(50);
        pick.setY(150);
        pick.setWidth(2);
        pick.setHeight(2);

        // Dictate correct behaviour
        expect(mockCamera.getFrameWidth()).andStubReturn(0.1f);
        expect(mockCamera.getFrameAspectRatio()).andStubReturn(0.75f);
        replay(mockCamera);

        // Setup test environment.
        testObject.setCamera(mockCamera);

        // Perform test 1.
        testObject.pickViewport(dimension, 100, 100, 2, 2);

        // Verify test 1 results.
        assertEquals(1, testObject.getPicks().size(), 0);

        Pick pick0 = testObject.getPicks().get(0);
        assertEquals(0.05f, pick0.getX(), 0);
        assertEquals(0.0375f, pick0.getY(), 0);
        assertEquals(0.001f, pick0.getWidth(), 0);
        assertEquals(0.00075f, pick0.getHeight(), 0);

        // Perform test 2.
        testObject.pickViewport(dimension, pick);

        // Verify test 2 results.
        assertEquals(2, testObject.getPicks().size(), 0);

        Pick pick1 = testObject.getPicks().get(1);
        assertEquals(0.025f, pick1.getX(), 0);
        assertEquals(0.05625f, pick1.getY(), 0.0001f);
        assertEquals(0.001f, pick1.getWidth(), 0);
        assertEquals(0.00075f, pick1.getHeight(), 0);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.picking.engine.SimpleJOGLPickingEngine.run run()}.
     * </p>
     */
    @Test
    @Ignore("May need to use aspect to test")
    public void run()
    {}

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.picking.engine.SimpleJOGLPickingEngine#setGL(GL) setGL(GL)}.
     * </p>
     */
    @Test
    public void setGL()
    {
        MockGL mockGl = new MockGL();
        SimpleJOGLPicker mockPicker = createMock(SimpleJOGLPicker.class);

        testObject.setPicker(mockPicker);

        reset(mockPicker);
        mockPicker.setGL(mockGl);
        replay(mockPicker);

        testObject.setGL(mockGl);

        verify(mockPicker);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.picking.engine.SimpleJOGLPickingEngine#setPicker(Picker) setPicker(Picker)}.
     * </p>
     */
    @Test
    public void setPicker()
    {
        MockGL mockGl = new MockGL();
        SimpleJOGLPicker mockPicker = createMock(SimpleJOGLPicker.class);

        testObject.setGL(mockGl);

        mockPicker.setGL(mockGl);
        replay(mockPicker);

        testObject.setPicker(mockPicker);

        verify(mockPicker);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.picking.engine.SimpleJOGLPickingEngine#setRenderingEngine(RenderingEngine)
     * setRenderingEngine(RenderingEngine)}.
     * </p>
     */
    @Test
    public void setRenderingEngine()
    {
        // Create dependencies.
        RenderingEngine mockRenderingEngine = createMock(RenderingEngine.class);
        Scene mockScene = createMock(Scene.class);
        Camera mockCamera = createMock(Camera.class);

        // Dictate correct behaviour.
        expect(mockRenderingEngine.getScene()).andStubReturn(mockScene);
        expect(mockRenderingEngine.getCamera()).andStubReturn(mockCamera);
        replay(mockRenderingEngine);

        // Perform test.
        testObject.setRenderingEngine(mockRenderingEngine);

        // Verify test results.
        assertEquals(mockScene, testObject.getScene());
        assertEquals(mockCamera, testObject.getCamera());
    }
}
