//
//  KFAGeometry.c
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/8/17.
//  Copyright © 2017 Collin Lasley. All rights reserved.
//

#include <vector>

#include "KFAGeometry.h"
#include "JIGRect.h"
#if __APPLE__
	#include <OpenGL/glext.h>
	#include <Opengl/gl.h>
#elif _WIN32
	#include <GL/GL.h>
#endif

extern std::vector<JIG::Shape>global_LevelShapes;

void InitGeometry(void)
{
    return;
    
#if 0
#if _MSC_VER
	KFAPoint initialPoint; initialPoint.x = 0; initialPoint.y = 0; initialPoint.z = 200;
	KFAColorRGBA initialColor; initialColor.r = 1.0f; initialColor.g = 1.0; initialColor.b = 1.0f; initialColor.a = 1.0f;
	aRect = CreateNewRectangle(initialPoint, 100.0f, 100.0f, 0.0f, initialColor);
#else
    aRect = CreateNewRectangle((KFAPoint){0,0, 200}, 100.0f, 100.0f, 0.0f, (KFAColorRGBA){1.0f, 1.0f, 1.0f, 1.0f});
#endif
    SubmitRectangleForRender(aRect, -1);
#endif
}

void UpdateGeometry(bool switchColors, int horizontalVelocity, int verticalVelocity, float rotation)
{
    
    
#if 0
    if (switchColors) {
        if (aRect->color.r < 1.0f) {
			/*Visual Studio has a subpar compiler*/
		#if _MSC_VER
			aRect->color.r = 1.0f; aRect->color.g = 0.0f; aRect->color.b = 0.0f;
		#else
            aRect->color = (KFAColorRGBA){1.0f, 0.0f, 0.0f, 1.0f};
		#endif
        }else{
		#if _MSC_VER
			aRect->color.r = 0.0f; aRect->color.g = 0.0f; aRect->color.b = 1.0f;
		#else
			aRect->color = (KFAColorRGBA) { 0.0f, 0.0f, 1.0f, 1.0f };
		#endif
        }
    }
    
    aRect->centerPoint.x += horizontalVelocity;
    aRect->centerPoint.y += verticalVelocity;
    
    aRect->rotation += rotation;
    
    SubmitRectangleForRender(aRect, 1);
#endif
}

void SubmitRectangleForRender(KFAGeometryRectangle *theRect, signed int vaID)
{
    if (theRect->drawDataSize != 0) {
        free(theRect->drawData);
        theRect->drawDataSize = 0;
    }
    theRect->drawDataSize = GeometricTypeToDataBlock(theRect, &(theRect->drawData), kfaGeometryTypeRectangle);
    
    if (vaID == -1){
        OGL_AssignMemoryToVertexArray(theRect->drawData, kfaGeometryTypeRectangle, theRect->drawDataSize, -1);
    }else{
        OGL_AssignMemoryToVertexArray(theRect->drawData, kfaGeometryTypeRectangle, theRect->drawDataSize, vaID);
    }
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

KFAPoint JIGMakePoint(signed int x, signed int y, signed int z)
{
    KFAPoint returnPoint;
    
    returnPoint.x = x;
    returnPoint.y = y;
    returnPoint.z = z;
    return returnPoint;
}

KFAColorRGBA JIGMakeColor(float r, float g, float b, float a)
{
    KFAColorRGBA returnColor;
    
    returnColor.r = r;
    returnColor.g = g;
    returnColor.b = b;
    returnColor.a = a;
    return returnColor;
}


size_t GeometricTypeToDataBlock(void *input, void **output, KFAGeometryType type)
{
#if _MSC_VER
	#pragma warning( push )
	#pragma warning( disable : 4244)
#endif
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
            long int dataSize = sizeof(KFAColorRGBA)+sizeof(float)+sizeof(KFAPoint)*4+sizeof(KFAPoint);
            float *objData = (float *)malloc(dataSize);
            
            objData[0] = theRect->color.r; objData[1] = theRect->color.g; objData[2] = theRect->color.b; objData[3] = theRect->color.a;
            objData[4] = theRect->rotation;
            objData[5] = theRect->centerPoint.x; objData[6] = theRect->centerPoint.y; objData[7] = theRect->centerPoint.z;
            
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
#if _MSC_VER
	#pragma warning( pop )
#endif
}
