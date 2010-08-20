package com.se.simplicity.jogl.test.rendering;

import static org.easymock.EasyMock.expect;
import static org.easymock.classextension.EasyMock.createMock;
import static org.easymock.classextension.EasyMock.replay;
import static org.easymock.classextension.EasyMock.reset;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import javax.media.opengl.GL;

import org.junit.Before;
import org.junit.Test;

import com.se.simplicity.SEInvalidOperationException;
import com.se.simplicity.jogl.rendering.SimpleJOGLLight;
import com.se.simplicity.jogl.test.mocks.MockGL;
import com.se.simplicity.rendering.LightingMode;
import com.se.simplicity.scenegraph.Node;
import com.se.simplicity.vector.SimpleTransformationMatrixf44;
import com.se.simplicity.vector.SimpleTranslationVectorf4;

/**
 * <p>
 * Unit tests for the class {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight SimpleJOGLLight}.
 * </p>
 * 
 * @author simple
 */
public class SimpleJOGLLightTest
{
    /**
     * An instance of the class being unit tested.
     */
    private SimpleJOGLLight testObject;

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight.apply apply()}.
     * </p>
     */
    @Test
    public void apply()
    {
        MockGL mockGl = new MockGL();
        Node mockNode = createMock(Node.class);
        SimpleTransformationMatrixf44 matrix = new SimpleTransformationMatrixf44();

        testObject.setGL(mockGl);
        testObject.setNode(mockNode);
        testObject.init();

        mockGl.reset();
        reset(mockNode);
        expect(mockNode.getTransformation()).andStubReturn(matrix);
        expect(mockNode.getParent()).andStubReturn(null);
        replay(mockNode);

        testObject.apply();

        assertEquals(4, mockGl.getMethodCallCountIgnoreParams("glLightfv"), 0);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight.apply apply()} with the special condition that the
     * {@link com.se.simplicity.jogl.rendering.SimpleJOGLCamera SimpleJOGLLight} is not initialised.
     * </p>
     */
    @Test
    public void applyNotInitialised()
    {
        MockGL mockGl = new MockGL();
        Node mockNode = createMock(Node.class);
        SimpleTransformationMatrixf44 matrix = new SimpleTransformationMatrixf44();

        testObject.setGL(mockGl);
        testObject.setNode(mockNode);

        mockGl.reset();
        reset(mockNode);
        expect(mockNode.getTransformation()).andStubReturn(matrix);
        expect(mockNode.getParent()).andStubReturn(null);
        replay(mockNode);

        testObject.apply();

        assertEquals(3, mockGl.getMethodCallCountIgnoreParams("glEnable"), 0);
        assertEquals(4, mockGl.getMethodCallCountIgnoreParams("glLightfv"), 0);
    }

    /**
     * <p>
     * Setup to perform before each unit test.
     * </p>
     */
    @Before
    public final void before()
    {
        testObject = new SimpleJOGLLight();
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight.getTransformation getTransformation()}.
     * </p>
     * 
     * @throws SEInvalidOperationException Thrown by the setup of a helper object.
     */
    @Test
    public void getTransformation() throws SEInvalidOperationException
    {
        Node mockNode1 = createMock(Node.class);
        Node mockNode2 = createMock(Node.class);
        SimpleTransformationMatrixf44 matrix1 = new SimpleTransformationMatrixf44();
        matrix1.translate(new SimpleTranslationVectorf4(0.0f, 10.0f, 0.0f, 1.0f));
        SimpleTransformationMatrixf44 matrix2 = new SimpleTransformationMatrixf44();
        matrix2.rotate((float) (90.0f * Math.PI / 180), new SimpleTranslationVectorf4(1.0f, 0.0f, 0.0f, 1.0f));

        testObject.setNode(mockNode1);

        reset(mockNode1, mockNode2);
        expect(mockNode1.getTransformation()).andStubReturn(matrix1);
        expect(mockNode1.getParent()).andStubReturn(mockNode2);
        expect(mockNode2.getTransformation()).andStubReturn(matrix2);
        expect(mockNode2.getParent()).andStubReturn(null);
        replay(mockNode1, mockNode2);

        SimpleTransformationMatrixf44 matrix3 = new SimpleTransformationMatrixf44();
        matrix3.multiplyRight(matrix1);
        matrix3.multiplyRight(matrix2);
        matrix3.invert();

        assertEquals(matrix3, testObject.getTransformation());
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight.getTransformation getTransformation()} with the special condition
     * that the {@link com.se.simplicity.jogl.rendering.SimpleJOGLCamera SimpleJOGLLight} being tested does not have a <code>Node</code>.
     * </p>
     */
    @Test
    public void getTransformationNoNode()
    {
        assertNull(testObject.getTransformation());
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight.init init()}.
     * </p>
     */
    @Test
    public void init()
    {
        MockGL mockGl = new MockGL();

        testObject.setGL(mockGl);

        mockGl.reset();

        testObject.init();

        assertEquals(1, mockGl.getMethodCallCount("glEnable", new Object[] {GL.GL_LIGHTING}), 0);
        assertEquals(1, mockGl.getMethodCallCount("glEnable", new Object[] {GL.GL_COLOR_MATERIAL}), 0);
        assertEquals(1, mockGl.getMethodCallCount("glEnable", new Object[] {GL.GL_LIGHT0}), 0);
    }

    /**
     * <p>
     * Unit test the method {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight.init init()} with the special condition that the
     * {@link com.se.simplicity.jogl.rendering.SimpleJOGLLight SimpleJOGLLight} being tested is usng the solid lighting mode.
     * </p>
     */
    @Test
    public void initSolid()
    {
        MockGL mockGl = new MockGL();

        testObject.setGL(mockGl);
        testObject.setLightingMode(LightingMode.SOLID);

        mockGl.reset();

        testObject.init();

        assertEquals(1, mockGl.getMethodCallCount("glDisable", new Object[] {GL.GL_LIGHTING}), 0);
        assertEquals(1, mockGl.getMethodCallCount("glDisable", new Object[] {GL.GL_COLOR_MATERIAL}), 0);
        assertEquals(1, mockGl.getMethodCallCount("glDisable", new Object[] {GL.GL_LIGHT0}), 0);
    }
}
