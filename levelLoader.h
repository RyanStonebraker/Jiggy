// levelLoader.h
// Ryan Stonebraker
// 4/16/2017
// header for cpp that loads shape information from text file

#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include "JIGMain.h"
#include "JIGShape.h"
#include "KFAGLSupport.h"
#include "KFAGeometry.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace JIG {
    class LoadLevel {
    public:
        LoadLevel(std::string); // takes file name // submit all shapes for rendering to get vtx array ids
        Shape &operator[](int) const; // identifier = vtx array id
        
        void updateFile() const;
        void updateFile(std::string);
        void renderLevel() const;
        KFAColorRGBA &color(int);
        KFAPoint &location(int);
        float &rotation(int);
        
    private:
        std::vector <JIG::Shape> _loadedShapes; // vAID, ptr to shape
        std::string _fname;
        std::unique_ptr<JIG::Shape> _makeRect (KFAPoint, );
        // std::unique_ptr<JIG::Shape> _createShape(std::string, KFAPoint, float, float, float);
        void _getFromText();
    };
    
//    extern KFAColorRGBA blue = JIGMakeColor(0.0f, 0.38f, 1.0f, 1.0f);
//    extern KFAColorRGBA red = JIGMakeColor(1.0f, 0.2f, 0.0f, 1.0f);
//    extern KFAColorRGBA grey = JIGMakeColor(0.717f, 0.717f, 0.717f);
    
    
} // namespace JIG

#endif
