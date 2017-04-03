//
//  KFAGLSupport.h
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/6/17.
//  Copyright © 2017 Collin Lasley. All rights reserved.
//

#ifndef KFAGLSupport_h
#define KFAGLSupport_h

#include <Foundation/Foundation.h>
#include <CoreGraphics/CGGeometry.h>
#include <OpenGL/OpenGL.h>

#define degreesToRadians(angleDegrees) (angleDegrees * 3.14159265 / 180.0)

#define KFA_PAN_SPEED 0.2f
#define KFA_ZOOM_SPEED 0.1f
#define VERTEX_OFFSET 6
#define VERTEX_OFFSET_2D 4

typedef struct{
    signed int x, y, z;
}KFAPoint;

/************************************GET RID OF THIS GLOBAL ASAP! SHOVE IT INTO THE VOID POINTER!**************************/
extern KFAPoint rectCenter;

typedef struct{
    signed int r, g, b, a;
}KFAColorRGBA;

typedef enum : unsigned int {
    kfaGeometryTypeRectangle,
    kfaGeometryTypeLine
}KFAGeometryType;

typedef struct{
    KFAPoint startPoint;
    float length;
    float rotations[3];
}KFAGeometryLine;

typedef struct{
    KFAGeometryLine centerLine;
    KFAColorRGBA color;
    float width, height;
    void *drawData;
    size_t drawDataSize;
}KFAGeometryRectangularPrism;

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
    BOOL	forceUpdate;			/*YES Indicates VAR needs update*/
    BOOL	activated;				/*YES After first use*/
}VertexArrayType;

typedef enum : unsigned int {
    KFA_CAMERA_ROTATE_MAINTAINING_FOCUS,
    KFA_CAMERA_PAN_SUBJECT,
    KFA_CAMERA_ZOOM,
}KFACameraManipulationMode;

void OGL_SetOrthographicMatrix(double leftBound, double rightBound, double topBound, double bottomBound, double backZBound, double frontZBound);

void OGL_SetPerspective(float fovDegrees, CGRect windowRect, float nearZ, float farZ);

void OGL_TrainCameraToPosition(KFAPoint cameraPosition, KFAPoint subjectPosition);

void OGL_InitVertexArrays(void);

void OGL_AssignMemoryToVertexArray(void *data, KFAGeometryType type, long size, int vaID);

void OGL_UpdateVertexArrays(void);

void OGL_DisposeVertexArrays(void);

void OGL_DisposeVertexArray(int vaID);

void OGL_MarkVertexArrayRangeForUpdate(int startIndex, int endIndex);

void OGL_AdjustCamera(float adjustmentParameters[3], KFACameraManipulationMode manipulationMode);

void OGL_ApplyCameraTransformations(void);

#endif /* KFAGLSupport_h */
