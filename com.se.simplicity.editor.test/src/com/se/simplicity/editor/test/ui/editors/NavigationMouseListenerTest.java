/*
    This file is part of The Simplicity Engine.

    The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
package com.se.simplicity.editor.test.ui.editors;

import static org.easymock.EasyMock.expect;
import static org.easymock.classextension.EasyMock.createMock;
import static org.easymock.classextension.EasyMock.replay;
import static org.easymock.classextension.EasyMock.reset;
import static org.easymock.classextension.EasyMock.verify;
import static org.junit.Assert.assertEquals;

import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.opengl.GLCanvas;
import org.eclipse.swt.widgets.Event;
import org.junit.Test;

import com.se.simplicity.editor.internal.ContentProvider;
import com.se.simplicity.editor.internal.Widget;
import com.se.simplicity.editor.ui.editors.NavigationMouseListener;
import com.se.simplicity.rendering.Camera;
import com.se.simplicity.scenegraph.Node;
import com.se.simplicity.vector.SimpleTransformationMatrixf44;
import com.se.simplicity.vector.TranslationVectorf;

/**
 * <p>
 * Unit tests for the class {@link com.se.simplicity.editor.ui.editors.NavigationMouseListener NavigationMouseListener}.
 * </p>
 * 
 * @author Gary Buyn
 */
public class NavigationMouseListenerTest
{
    /**
     * An instance of the class being unit tested.
     */
    private NavigationMouseListener testObject;

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.editor.ui.editors.NavigationMouseListener#mouseMove(MouseEvent) mouseMove(MouseEvent)}.
     * </p>
     */
    @Test
    public void mouseMove()
    {
        // Create dependencies.
        ContentProvider mockContentProvider = createMock(ContentProvider.class);
        Camera mockCamera = createMock(Camera.class);
        Node mockNode0 = createMock(Node.class);
        Node mockNode1 = createMock(Node.class);
        SimpleTransformationMatrixf44 matrix = new SimpleTransformationMatrixf44();

        Event event = new Event();
        event.widget = createMock(GLCanvas.class);
        MouseEvent mouseEvent = new MouseEvent(event);
        mouseEvent.button = 2;
        mouseEvent.x = 100;
        mouseEvent.y = 100;

        // Dictate correct behaviour.
        expect(mockContentProvider.getViewingCamera()).andStubReturn(mockCamera);
        expect(mockCamera.getNode()).andStubReturn(mockNode0);
        expect(mockNode0.getParent()).andStubReturn(mockNode1);
        expect(mockNode1.getTransformation()).andStubReturn(matrix);
        replay(mockContentProvider, mockCamera, mockNode0, mockNode1);

        // Initialise test environment.
        testObject = new NavigationMouseListener(mockContentProvider);
        testObject.mouseDown(mouseEvent);

        // Perform test.
        testObject.mouseMove(mouseEvent);
        mouseEvent.x = 110;
        mouseEvent.y = 110;
        testObject.mouseMove(mouseEvent);

        // Verify test results.
        assertEquals(Math.toRadians(-10.0f), matrix.getXAxisRotation(), 0.0001f);
        assertEquals(Math.toRadians(-10.0f), matrix.getYAxisRotation(), 0.0001f);
        assertEquals(0.0f, matrix.getZAxisRotation(), 0.0f);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.editor.ui.editors.NavigationMouseListener#mouseMove(MouseEvent) mouseMove(MouseEvent)} with the
     * special condition that button 2 on the mouse is not down.
     * </p>
     */
    @Test
    public void mouseMoveButton2NotDown()
    {
        // Create dependencies.
        ContentProvider mockContentProvider = createMock(ContentProvider.class);
        Camera mockCamera = createMock(Camera.class);
        Node mockNode0 = createMock(Node.class);
        Node mockNode1 = createMock(Node.class);
        SimpleTransformationMatrixf44 matrix = new SimpleTransformationMatrixf44();

        Event event = new Event();
        event.widget = createMock(GLCanvas.class);
        MouseEvent mouseEvent = new MouseEvent(event);
        mouseEvent.button = 2;
        mouseEvent.x = 100;
        mouseEvent.y = 100;

        // Dictate correct behaviour.
        expect(mockContentProvider.getViewingCamera()).andStubReturn(mockCamera);
        expect(mockCamera.getNode()).andStubReturn(mockNode0);
        expect(mockNode0.getParent()).andStubReturn(mockNode1);
        expect(mockNode1.getTransformation()).andStubReturn(matrix);
        replay(mockContentProvider, mockCamera, mockNode0, mockNode1);

        // Initialise test environment.
        testObject = new NavigationMouseListener(mockContentProvider);

        // Perform test.
        testObject.mouseMove(mouseEvent);
        mouseEvent.x = 110;
        mouseEvent.y = 110;
        testObject.mouseMove(mouseEvent);

        // Verify test results.
        assertEquals(0.0f, matrix.getXAxisRotation(), 0.0001f);
        assertEquals(0.0f, matrix.getYAxisRotation(), 0.0001f);
        assertEquals(0.0f, matrix.getZAxisRotation(), 0.0f);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.editor.ui.editors.NavigationMouseListener#mouseUp(MouseEvent) mouseUp(MouseEvent)}.
     * </p>
     */
    @Test
    public void mouseScrolled()
    {
        // Create dependencies.
        ContentProvider mockContentProvider = createMock(ContentProvider.class);
        Widget mockWidget = createMock(Widget.class);
        Camera mockCamera = createMock(Camera.class);
        Node mockNode = createMock(Node.class);
        SimpleTransformationMatrixf44 matrix = new SimpleTransformationMatrixf44();

        Event event = new Event();
        event.widget = createMock(GLCanvas.class);
        MouseEvent mouseEvent = new MouseEvent(event);
        mouseEvent.count = 1;

        // Dictate correct behaviour.
        expect(mockContentProvider.getViewingCamera()).andStubReturn(mockCamera);
        expect(mockContentProvider.getCurrentWidget()).andStubReturn(mockWidget);
        expect(mockCamera.getNode()).andStubReturn(mockNode);
        expect(mockNode.getTransformation()).andStubReturn(matrix);
        replay(mockContentProvider, mockCamera, mockNode);

        // Initialise test environment.
        testObject = new NavigationMouseListener(mockContentProvider);

        // Dictate expected results.
        mockWidget.updateView(mockCamera);
        replay(mockWidget);

        // Perform test 1.
        testObject.mouseScrolled(mouseEvent);

        // Verify test 1 results.
        verify(mockWidget);

        TranslationVectorf vector = matrix.getTranslation();

        assertEquals(0.0f, vector.getX(), 0.0f);
        assertEquals(0.0f, vector.getY(), 0.0f);
        assertEquals(-1.0f, vector.getZ(), 0.0f);

        // Modify dependencies.
        mouseEvent.count = -1;

        // Dictate expected results.
        reset(mockWidget);
        mockWidget.updateView(mockCamera);
        replay(mockWidget);

        // Perform test 2.
        testObject.mouseScrolled(mouseEvent);

        // Verify test 2 results.
        verify(mockWidget);

        vector = matrix.getTranslation();

        assertEquals(0.0f, vector.getX(), 0.0f);
        assertEquals(0.0f, vector.getY(), 0.0f);
        assertEquals(0.0f, vector.getZ(), 0.0f);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.editor.ui.editors.NavigationMouseListener#mouseUp(MouseEvent) mouseUp(MouseEvent)} with the
     * special condition that there is no current widget.
     * </p>
     */
    @Test
    public void mouseScrolledNoCurrentWidget()
    {
        // Create dependencies.
        ContentProvider mockContentProvider = createMock(ContentProvider.class);
        Camera mockCamera = createMock(Camera.class);
        Node mockNode = createMock(Node.class);
        SimpleTransformationMatrixf44 matrix = new SimpleTransformationMatrixf44();

        Event event = new Event();
        event.widget = createMock(GLCanvas.class);
        MouseEvent mouseEvent = new MouseEvent(event);
        mouseEvent.count = 1;

        // Dictate correct behaviour.
        expect(mockContentProvider.getViewingCamera()).andStubReturn(mockCamera);
        expect(mockContentProvider.getCurrentWidget()).andStubReturn(null);
        expect(mockCamera.getNode()).andStubReturn(mockNode);
        expect(mockNode.getTransformation()).andStubReturn(matrix);
        replay(mockContentProvider, mockCamera, mockNode);

        // Initialise test environment.
        testObject = new NavigationMouseListener(mockContentProvider);

        // Perform test 1.
        testObject.mouseScrolled(mouseEvent);

        // Verify test 1 results.
        // Just verifying that no errors occur...
    }
}
