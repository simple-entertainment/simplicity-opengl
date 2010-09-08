/*
    This file is part of The Simplicity Engine.

    The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see <http://www.gnu.org/licenses/>.
 */
package com.se.simplicity.editor.test.handlers;

import static org.easymock.EasyMock.expect;
import static org.easymock.classextension.EasyMock.createMock;
import static org.easymock.classextension.EasyMock.replay;
import static org.easymock.classextension.EasyMock.verify;

import java.util.HashMap;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.expressions.IEvaluationContext;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.ISources;
import org.junit.Before;
import org.junit.Test;

import com.se.simplicity.editor.handlers.RotationHandler;
import com.se.simplicity.editor.internal.ContentProvider;
import com.se.simplicity.editor.internal.EditMode;
import com.se.simplicity.editor.ui.editors.SceneEditor;

/**
 * <p>
 * Unit tests for the class {@link com.se.simplicity.editor.handlers.RotationHandler RotationHandler}.
 * </p>
 * 
 * @author Gary Buyn
 */
public class RotationHandlerTest
{
    /**
     * An instance of the class being unit tested.
     */
    private RotationHandler testObject;

    /**
     * <p>
     * Setup to perform before each unit test.
     * </p>
     */
    @Before
    public void before()
    {
        testObject = new RotationHandler();
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.editor.handlers.RotationHandler#execute(ExecutionEvent) execute(ExecutionEvent)}.
     * </p>
     * 
     * @throws ExecutionException Thrown if the handler fails to execute.
     */
    @Test
    public void execute() throws ExecutionException
    {
        // Create dependencies.
        IEvaluationContext mockContext = createMock(IEvaluationContext.class);
        SceneEditor mockSceneEditor = createMock(SceneEditor.class);
        ContentProvider mockContentProvider = createMock(ContentProvider.class);

        ExecutionEvent mockEvent = new ExecutionEvent(null, new HashMap<String, String>(), null, mockContext);

        // Dictate correct behaviour.
        expect(mockContext.getVariable(ISources.ACTIVE_EDITOR_NAME)).andStubReturn(mockSceneEditor);
        expect(mockSceneEditor.getContentProvider()).andStubReturn(mockContentProvider);
        mockContentProvider.setEditMode(EditMode.ROTATION);
        replay(mockContext, mockSceneEditor, mockContentProvider);

        // Perform test.
        testObject.execute(mockEvent);

        // Verify test results.
        verify(mockContentProvider);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.editor.handlers.RotationHandler#execute(ExecutionEvent) execute(ExecutionEvent)} with the special
     * condition that a {@link com.se.simplicity.editor.ui.editors.SceneEditor SceneEditor} is not active.
     * </p>
     * 
     * @throws ExecutionException Thrown if the handler fails to execute.
     */
    @Test(expected = ExecutionException.class)
    public void executeSceneEditorNotActive() throws ExecutionException
    {
        // Create dependencies.
        IEvaluationContext mockContext = createMock(IEvaluationContext.class);
        IEditorPart mockSceneEditor = createMock(IEditorPart.class);

        ExecutionEvent mockEvent = new ExecutionEvent(null, new HashMap<String, String>(), null, mockContext);

        // Dictate correct behaviour.
        expect(mockContext.getVariable(ISources.ACTIVE_EDITOR_NAME)).andStubReturn(mockSceneEditor);
        replay(mockContext, mockSceneEditor);

        // Perform test.
        testObject.execute(mockEvent);
    }
}
