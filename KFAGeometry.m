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
    
    aRect = CreateNewRectangle((KFAPoint){0.0f,0.0f, 200.0f}, 100.0f, 100.0f, 0.0f, (KFAColorRGBA){1.0f, 1.0f, 1.0f, 1.0f});
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

KFAGeometryRectangularPrism* CreateNewRectangularPrism(KFAPoint startPoint, float length, float *angle, KFAColorRGBA color, float width, float height)
{
    KFAGeometryRectangularPrism *newRectPrism = malloc(sizeof(KFAGeometryRectangularPrism));
    
    newRectPrism->centerLine.startPoint = startPoint;
    newRectPrism->centerLine.length = length;
    newRectPrism->centerLine.rotations[0] = *angle;
    newRectPrism->centerLine.rotations[1] = *(angle+1);
    newRectPrism->centerLine.rotations[2] = *(angle+2);
    newRectPrism->color = color;
    newRectPrism->width = width;
    newRectPrism->height = height;
    
    return newRectPrism;
}


KFAGeometryRectangle* CreateNewRectangle(KFAPoint startPoint, float width, float height, float rotationAngle, KFAColorRGBA color)
{
    KFAGeometryRectangle *newRectangle = malloc(sizeof(KFAGeometryRectangle));
    
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
            float *objData = malloc(dataSize);
            
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
        case kfaGeometryTypeRectangularPrism:
        {
            ;
            KFAGeometryRectangularPrism *thePrism = (KFAGeometryRectangularPrism *)input;
            /*Size for color, rotation transforms, and 8 points to make the rectangular prism*/
            long int dataSize = sizeof(KFAColorRGBA)+sizeof(float)*3+sizeof(KFAPoint)*24;
            float *objData = malloc(dataSize);
            
            float x = ((float)dataSize/(sizeof(float)));
            
            objData[0] = thePrism->color.r; objData[1] = thePrism->color.g; objData[2] = thePrism->color.b; objData[3] = thePrism->color.a;
            objData[4] = thePrism->centerLine.rotations[0]; objData[5] = thePrism->centerLine.rotations[1]; objData[6] = thePrism->centerLine.rotations[2];
            
            /*These make the left rectangle*/
            objData[VERTEX_OFFSET+1] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+2] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+3] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+4] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+5] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+6] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+7] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+8] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+9] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+10] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+11] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+12] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            /*These make the top of the prism*/
            objData[VERTEX_OFFSET+13] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+14] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+15] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+16] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+17] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+18] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+19] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+20] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+21] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+22] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+23] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+24] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            /*These are for the bottom*/
            objData[VERTEX_OFFSET+25] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+26] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+27] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+28] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+29] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+30] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+31] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+32] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+33] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+34] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+35] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+36] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            /*These are for the front face*/
            objData[VERTEX_OFFSET+37] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+38] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+39] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+40] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+41] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+42] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+43] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+44] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+45] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+46] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+47] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+48] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            /*These are for the back face*/
            objData[VERTEX_OFFSET+49] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+50] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+51] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+52] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+53] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+54] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+55] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+56] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+57] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+58] = thePrism->centerLine.startPoint.x;
            objData[VERTEX_OFFSET+59] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+60] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            /*These make the right rectangle*/
            objData[VERTEX_OFFSET+61] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+62] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+63] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+64] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+65] = thePrism->centerLine.startPoint.y + (0.5f*thePrism->height);
            objData[VERTEX_OFFSET+66] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+67] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+68] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+69] = thePrism->centerLine.startPoint.z + (0.5f*thePrism->width);
            
            objData[VERTEX_OFFSET+70] = thePrism->centerLine.startPoint.x + thePrism->centerLine.length;
            objData[VERTEX_OFFSET+71] = thePrism->centerLine.startPoint.y + (-0.5f*thePrism->height);
            objData[VERTEX_OFFSET+72] = thePrism->centerLine.startPoint.z + (-0.5f*thePrism->width);
            
            *output = objData;
            return dataSize;
            
            break;
        }
        case kfaGeometryTypeRectangle:
        {
            KFAGeometryRectangle *theRect = (KFAGeometryRectangle *)input;
            /*Size for color, rotation transforms, and verticies*/
            long int dataSize = sizeof(KFAColorRGBA)+sizeof(float)+sizeof(KFAPoint)*4;
            float *objData = malloc(dataSize);
            
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
