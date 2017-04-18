//
//  KFAGLSupport.c
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/6/17.
//  Copyright © 2017 Collin Lasley. All rights reserved.
//

#include <stdio.h>

#if __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <OpenGL/gl.h>
#elif _WIN32
	#include <math.h>
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/GLU.h>
	#include "glext.h"
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
	PFNGLGENBUFFERSPROC glGenBuffers = NULL;
	PFNGLBINDBUFFERPROC glBindBuffer = NULL;
	PFNGLBUFFERDATAPROC glBufferData = NULL;
	PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
#endif

#ifdef __OBJC__
    #import <GLKit/GLKit.h>
#endif

#include "KFAGLSupport.h"

#define NUM_VERTEX_ARRAYS 2

static VertexArrayType vertexBufferObjects[NUM_VERTEX_ARRAYS];

static float translationTransformations[3], scaleTransformations[3], rotationTransformations[3];

void OGL_InitWGL(void)
{
#if _WIN32
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
#endif
}

void OGL_SetOrthographicMatrix(double leftBound, double rightBound, double topBound, double bottomBound, double backZBound, double frontZBound)
{
#if __APPLE__
    glMultMatrixf(GLKMatrix4MakeOrtho(leftBound, rightBound, bottomBound, topBound, frontZBound, backZBound).m);
#elif _WIN32
	glOrtho(leftBound, rightBound, bottomBound, topBound, frontZBound, backZBound);
#endif
}

void OGL_TrainCameraToPosition(KFAPoint cameraPosition, KFAPoint subjectPosition)
{
#if __APPLE__
    glMultMatrixf(GLKMatrix4MakeLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, subjectPosition.x, subjectPosition.y, subjectPosition.z, 0.0f, 1.0f, 0.0f).m);
#elif _WIN32
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, subjectPosition.x, subjectPosition.y, subjectPosition.z, 0.0, 1.0, 0.0);
#endif
}

void OGL_InitVertexArrays(void)
{
    for (int i = 0; i < NUM_VERTEX_ARRAYS; i++) {
        vertexBufferObjects[i].arraySize= 0;
        vertexBufferObjects[i].dataBlockPtr = NULL;
        vertexBufferObjects[i].forceUpdate = false;
        vertexBufferObjects[i].activated = false;
        glGenBuffers(1, &vertexBufferObjects[i].vbo);
    }
    
    for (int i = 0; i < 3; i++) {
        translationTransformations[i] = 0.0f;
        scaleTransformations[i] = 1.0f;
        rotationTransformations[i] = 0.0f;
    }
}

unsigned int OGL_AssignMemoryToVertexArray(void *data, KFAGeometryType type, long size, int vaID)
{
    if (vaID >= NUM_VERTEX_ARRAYS) {
        printf("OGL_AssignMemoryToVertexArrayRange: vaID Passed > Number of VARs!");
        exit(1);
    }
    
    if (vaID == -1) {
        for (int i = 0; i < NUM_VERTEX_ARRAYS; i++) {
            if (!vertexBufferObjects[i].activated) {
                vaID = i;
                goto foundFreeVertexArray;
            }
        }
        printf("OGL_AssignMemoryToVertexArrayRange: out of vertex arrays!");
        exit(1);
    }
    
foundFreeVertexArray:
    
    vertexBufferObjects[vaID].arraySize = size;
    vertexBufferObjects[vaID].dataBlockPtr = data;
    vertexBufferObjects[vaID].type = type;
    vertexBufferObjects[vaID].forceUpdate = true;
    vertexBufferObjects[vaID].activated = true;
    
    return vaID;
}

void OGL_UpdateVertexArrays(void)
{
#if _MSC_VER
	#pragma warning( push )
	#pragma warning( disable : 4244)
#endif
    long int size;
    
    for (int i = 0; i < NUM_VERTEX_ARRAYS; i++) {
        size = vertexBufferObjects[i].arraySize;
        
        if (size == 0)
            continue;
        
        if (!vertexBufferObjects[i].activated)
            continue;
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[i].vbo);
        switch (vertexBufferObjects[i].type) {
            case kfaGeometryTypeLine:
                ;
                if (vertexBufferObjects[i].forceUpdate) {
                    /*Set up vertex data*/
                    
                    glPushMatrix();
                    glBufferData(GL_ARRAY_BUFFER, vertexBufferObjects[i].arraySize, vertexBufferObjects[i].dataBlockPtr, GL_STATIC_DRAW);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[i].vbo);
                    glVertexPointer(3, GL_FLOAT, 0, NULL);
                    glEnableClientState(GL_VERTEX_ARRAY);
                    
                    /*Set up color data*/
                    glColor3f(1.0f, 1.0f, 1.0f);
                    
                    glDrawArrays(GL_LINES, 0, 4);
                    //vertexBufferObjects[i].forceUpdate = NO;
                    glPopMatrix();
                }else{
                    glDrawArrays(GL_LINES, 0, 4);
                }
                break;
            case kfaGeometryTypeRectangle:
			{

				if (vertexBufferObjects[i].forceUpdate) {
					float *rectData = (float *)vertexBufferObjects[i].dataBlockPtr;
					/*Set up Vertex Data*/
					glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[i].vbo);
					glBufferData(GL_ARRAY_BUFFER, vertexBufferObjects[i].arraySize - sizeof(float)*(VERTEX_OFFSET_2D - 1), rectData + VERTEX_OFFSET_2D + 1, GL_STATIC_DRAW);

					glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[i].vbo);
					glVertexPointer(3, GL_FLOAT, 0, NULL);
					glEnableClientState(GL_VERTEX_ARRAY);

					/*Set up color data*/
					glColor4f(*(rectData), *(rectData + 1), *(rectData + 2), *(rectData + 3));

					/*Set up rotation Data*/
                    glTranslatef(*(rectData + 5), *(rectData + 6), *(rectData + 7));
                    glRotatef(*(rectData + 4), 0.0f, 0.0f, 1.0f);
                    glTranslatef(-(*(rectData + 5)), -(*(rectData + 6)), -(*(rectData + 7)));

					glDrawArrays(GL_QUADS, 0, 4);
					//vertexBufferObjects[i].forceUpdate = NO;
				}else{
					glDrawArrays(GL_QUADS, 0, 4);
				}
				break;
			}
            case kfaGeometryTypeArc:
            {
                const unsigned int numberSegments = 60;
                const float originAngle = 0.0f;
                
                if (vertexBufferObjects[i].forceUpdate) {
                    float *arcData = (float *)vertexBufferObjects[i].dataBlockPtr;
                    /*Set up Vertex Data*/
                    /*glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[i].vbo);
                    glBufferData(GL_ARRAY_BUFFER, vertexBufferObjects[i].arraySize - sizeof(float)*(VERTEX_OFFSET_2D - 1), arcData + VERTEX_OFFSET_2D + 1, GL_STATIC_DRAW);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[i].vbo);
                    glVertexPointer(3, GL_FLOAT, 0, NULL);
                    glEnableClientState(GL_VERTEX_ARRAY);*/
                    
                    /*Set up color data*/
                    glColor4f(*(arcData), *(arcData + 1), *(arcData + 2), *(arcData + 3));
                    
                    /*Set up rotation Data*/
                    glTranslatef(*(arcData + 5), *(arcData + 6), *(arcData + 7));
                    glRotatef(*(arcData + 4), 0.0f, 0.0f, 1.0f);
                    glTranslatef(-(*(arcData + 5)), -(*(arcData + 6)), -(*(arcData + 7)));
                    
                    /*Drawing, the old fashioned way*/
                    float theta = arcData[VERTEX_OFFSET_2D+2] / float(numberSegments - 1);
                    float tangetial_factor = tanf(theta);
                    float radial_factor = cosf(theta);
                    
                    float x = arcData[VERTEX_OFFSET_2D+1] * cosf(originAngle);//we now start at the start angle
                    float y = arcData[VERTEX_OFFSET_2D+1] * sinf(originAngle);
                    
                    glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
                    for(int ii = 0; ii < numberSegments; ii++)
                    {
                        glVertex3f(x + arcData[5], y + arcData[6], arcData[7]);
                        
                        float tx = -y; 
                        float ty = x; 
                        
                        x += tx * tangetial_factor; 
                        y += ty * tangetial_factor; 
                        
                        x *= radial_factor; 
                        y *= radial_factor;
                    } 
                    glEnd();
                    
                    //glDrawArrays(GL_QUADS, 0, 4);
                    //vertexBufferObjects[i].forceUpdate = NO;
                }else{
                    glDrawArrays(GL_QUADS, 0, 4);
                }
            }
                break;
            default:
                /*Error Junk*/
                break;
        }
    }
#if _MSC_VER
	#pragma warning( pop )
#endif
}

void OGL_DisposeVertexArrays(void)
{
    for (int i = 0; i < NUM_VERTEX_ARRAYS; i++) {
        OGL_DisposeVertexArray(i);
    }
}

void OGL_DisposeVertexArray(int vaID)
{
	if (vaID == -1)
		return;
    if (vertexBufferObjects[vaID].dataBlockPtr != NULL) {
        glDeleteBuffers(1, &vertexBufferObjects[vaID].vbo);
        free(vertexBufferObjects[vaID].dataBlockPtr);
        vertexBufferObjects[vaID].dataBlockPtr = NULL;
        vertexBufferObjects[vaID].forceUpdate = false;
        vertexBufferObjects[vaID].activated = false;
    }
}

void OGL_MarkVertexArrayRangeForUpdate(int startIndex, int endIndex)
{
    for (int i = startIndex; i <= endIndex; i++) {
        vertexBufferObjects[i].forceUpdate = true;
    }
}

void OGL_AdjustCamera(float adjustmentParameters[3], KFACameraManipulationMode manipulationMode)
{
    switch (manipulationMode) {
        case KFA_CAMERA_ROTATE_MAINTAINING_FOCUS:
            /*Code*/
            break;
        case KFA_CAMERA_PAN_SUBJECT:
            translationTransformations[0] += adjustmentParameters[0];
            translationTransformations[1] += adjustmentParameters[1];
            translationTransformations[2] += adjustmentParameters[2];
            break;
        case KFA_CAMERA_ZOOM:
            if (scaleTransformations[0] < 0.5) {
                scaleTransformations[0] = 0.5; scaleTransformations[1] = 0.5; scaleTransformations[2] = 0.5;
                return;
            }
            scaleTransformations[0] += adjustmentParameters[0];
            scaleTransformations[1] += adjustmentParameters[1];
            scaleTransformations[2] += adjustmentParameters[2];
            break;
        default:
            break;
    }
}

void OGL_ApplyCameraTransformations(void)
{
    glTranslatef(translationTransformations[0], translationTransformations[1], translationTransformations[2]);
    glScalef(scaleTransformations[0], scaleTransformations[1], scaleTransformations[2]);
}
