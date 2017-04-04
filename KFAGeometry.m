//
//  KFAGeometry.c
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/8/17.
//  Copyright © 2017 Collin Lasley. All rights reserved.
//

#include "KFAGeometry.h"
#include <OpenGL/glext.h>
#include <Opengl/gl.h>

static const float axisLinesData[] = {-1000.0f, 0.0f, 0.0f,
    1000.0f, 0.0f, 0.0f,
    0.0f, -1000.0f, 0.0f,
    0.0f, 1000.0f, 0.0f};

static float *axisLines;

static KFAGeometryRectangle *aRect;
static unsigned int nextVertexBuffer = 0;

void InitGeometry(void)
{
    axisLines = (float *)malloc(sizeof(KFAPoint)*4);
    memcpy(axisLines, &axisLinesData, sizeof(axisLinesData));
    OGL_AssignMemoryToVertexArray(axisLines, kfaGeometryTypeLine, sizeof(axisLinesData), nextVertexBuffer);
    nextVertexBuffer++;
    
    aRect = CreateNewRectangle((KFAPoint){0,0, 200}, 100.0f, 100.0f, 0.0f, (KFAColorRGBA){1.0f, 1.0f, 1.0f, 1.0f});
    SubmitRectangleForRender(aRect, -1);
}

void UpdateGeometry(BOOL switchColors, int horizontalVelocity, int verticalVelocity, float rotation)
{
    if (switchColors) {
        if (aRect->color.r < 1.0f) {
            aRect->color = (KFAColorRGBA){1.0f, 0.0f, 0.0f, 1.0f};
        }else{
            aRect->color = (KFAColorRGBA){0.0f, 0.0f, 1.0f, 1.0f};
        }
    }
    
    aRect->centerPoint.x += horizontalVelocity;
    aRect->centerPoint.y += verticalVelocity;
    
    aRect->rotation += rotation;
    
    SubmitRectangleForRender(aRect, 1);
}

void SubmitRectangleForRender(KFAGeometryRectangle *theRect, signed int vaID)
{
    if (theRect->drawDataSize != 0) {
        free(theRect->drawData);
        theRect->drawDataSize = 0;
    }
    theRect->drawDataSize = GeometricTypeToDataBlock(theRect, &(theRect->drawData), kfaGeometryTypeRectangle);
    
    if (vaID == -1){
        OGL_AssignMemoryToVertexArray(theRect->drawData, kfaGeometryTypeRectangle, theRect->drawDataSize, nextVertexBuffer);
        nextVertexBuffer++;
    }else{
        OGL_AssignMemoryToVertexArray(theRect->drawData, kfaGeometryTypeRectangle, theRect->drawDataSize, vaID);
    }
    rectCenter = theRect->centerPoint;
}


KFAGeometryRectangle* CreateNewRectangle(KFAPoint startPoint, float width, float height, float rotationAngle, KFAColorRGBA color)
{
    KFAGeometryRectangle *newRectangle = (KFAGeometryRectangle *)malloc(sizeof(KFAGeometryRectangle));
    
    newRectangle->centerPoint = startPoint;
    newRectangle->width = width;
    newRectangle->height = height;
    newRectangle->color = color;
    newRectangle->drawDataSize = 0;
    newRectangle->rotation = rotationAngle;
    
    return newRectangle;
}


size_t GeometricTypeToDataBlock(void *input, void **output, KFAGeometryType type)
{
    switch (type) {
        case kfaGeometryTypeLine:
        {
            ;
            KFAGeometryLine *theLine = (KFAGeometryLine *)input;
            long int dataSize = sizeof(KFAColorRGBA)+sizeof(float)*3+sizeof(KFAPoint)*2;
            float *objData = (float *)malloc(dataSize);
            
            objData[0] = 1.0f; objData[1] = 1.0f; objData[2] = 1.0f; objData[3] = 1.0f;
            objData[4] = theLine->rotations[0]; objData[5] = theLine->rotations[1]; objData[6] = theLine->rotations[2];
            
            objData[VERTEX_OFFSET+1] = theLine->startPoint.x;
            objData[VERTEX_OFFSET+2] = theLine->startPoint.y;
            objData[VERTEX_OFFSET+3] = theLine->startPoint.z;
            
            objData[VERTEX_OFFSET+4] = theLine->startPoint.x + theLine->length;
            objData[VERTEX_OFFSET+5] = theLine->startPoint.y;
            objData[VERTEX_OFFSET+6] = theLine->startPoint.z;
            
            *output = objData;
            return dataSize;
            break;
        }
        case kfaGeometryTypeRectangle:
        {
            KFAGeometryRectangle *theRect = (KFAGeometryRectangle *)input;
            /*Size for color, rotation transforms, and verticies*/
            long int dataSize = sizeof(KFAColorRGBA)+sizeof(float)+sizeof(KFAPoint)*4;
            float *objData = (float *)malloc(dataSize);
            
            objData[0] = theRect->color.r; objData[1] = theRect->color.g; objData[2] = theRect->color.b; objData[3] = theRect->color.a;
            objData[4] = theRect->rotation;
            
            objData[VERTEX_OFFSET_2D + 1] = theRect->centerPoint.x + (0.5f*theRect->width);
            objData[VERTEX_OFFSET_2D + 2] = theRect->centerPoint.y + (-0.5*theRect->height);
            objData[VERTEX_OFFSET_2D + 3] = theRect->centerPoint.z;
            
            objData[VERTEX_OFFSET_2D + 4] = theRect->centerPoint.x + (0.5f*theRect->width);
            objData[VERTEX_OFFSET_2D + 5] = theRect->centerPoint.y + (0.5*theRect->height);
            objData[VERTEX_OFFSET_2D + 6] = theRect->centerPoint.z;
            
            objData[VERTEX_OFFSET_2D + 7] = theRect->centerPoint.x + (-0.5f*theRect->width);
            objData[VERTEX_OFFSET_2D + 8] = theRect->centerPoint.y + (0.5*theRect->height);
            objData[VERTEX_OFFSET_2D + 9] = theRect->centerPoint.z;
            
            objData[VERTEX_OFFSET_2D + 10] = theRect->centerPoint.x + (-0.5f*theRect->width);
            objData[VERTEX_OFFSET_2D + 11] = theRect->centerPoint.y + (-0.5*theRect->height);
            objData[VERTEX_OFFSET_2D + 12] = theRect->centerPoint.z;
            
            *output = objData;
            return dataSize;
        }
            
            break;
        default:
            *output = NULL;
            break;
    }
    return 0L;
}
