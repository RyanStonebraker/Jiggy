//
//  KFAGLSupport.h
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/6/17.
//  Copyright © 2017 Collin Lasley. All rights reserved.
//

#ifndef KFAGLSupport_h
#define KFAGLSupport_h

#if __APPLE__
	#include <Foundation/Foundation.h>
	#include <CoreGraphics/CGGeometry.h>
	#include <OpenGL/OpenGL.h>
#elif _WIN32
	#include <windows.h>
	#include <GL/GL.h>
#endif

#define degreesToRadians(angleDegrees) (angleDegrees * 3.14159265 / 180.0)

#define KFA_PAN_SPEED 0.2f
#define KFA_ZOOM_SPEED 0.1f
#define VERTEX_OFFSET 6
#define VERTEX_OFFSET_2D 7

typedef struct{
    signed int x, y, z;
}KFAPoint;

typedef struct{
    float r, g, b, a;
}KFAColorRGBA;

typedef enum : unsigned int {
    kfaGeometryTypeRectangle,
    kfaGeometryTypeLine,
    kfaGeometryTypeArc
}KFAGeometryType;

typedef struct{
    KFAPoint startPoint;
    float length;
    float rotations[3];
}KFAGeometryLine;

typedef struct{
    KFAPoint centerPoint;
    KFAColorRGBA color;
    float width, height;
    void *drawData;
    size_t drawDataSize;
    float rotation;
}KFAGeometryRectangle;

typedef struct{
    long	arraySize;				/*Size of VAR block in bytes*/
    void	*dataBlockPtr;			/*Point to first byte of VAR memory*/
    KFAGeometryType type;
    GLuint  vbo;                    /*GL Vertex Buffer Object Ptr*/
    bool	forceUpdate;			/*YES Indicates VAR needs update*/
    bool	activated;				/*YES After first use*/
    signed int frameCount;
    KFAColorRGBA currentColor;
    KFAColorRGBA colorDelta;
}VertexArrayType;

typedef enum : unsigned int {
    KFA_CAMERA_ROTATE_MAINTAINING_FOCUS,
    KFA_CAMERA_PAN_SUBJECT,
    KFA_CAMERA_ZOOM,
}KFACameraManipulationMode;

void OGL_InitWGL(void);

void OGL_SetOrthographicMatrix(double leftBound, double rightBound, double topBound, double bottomBound, double backZBound, double frontZBound);

void OGL_TrainCameraToPosition(KFAPoint cameraPosition, KFAPoint subjectPosition);

void OGL_InitVertexArrays(void);

unsigned int OGL_AssignMemoryToVertexArray(void *data, KFAGeometryType type, long size, int vaID);

void OGL_UpdateVertexArrays(void);

void OGL_DisposeVertexArrays(void);

void OGL_DisposeVertexArray(int vaID);

void OGL_InterpolateColorForFrameCount(KFAColorRGBA *outputColor, unsigned int vertexArrayID);

void OGL_StartColorTransition(int vaID, KFAColorRGBA desiredColor);

void OGL_MarkVertexArrayRangeForUpdate(int startIndex, int endIndex);

void OGL_AdjustCamera(float adjustmentParameters[3], KFACameraManipulationMode manipulationMode);

void OGL_ApplyCameraTransformations(void);

#endif /* KFAGLSupport_h */
