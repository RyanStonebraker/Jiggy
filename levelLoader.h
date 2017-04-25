// levelLoader.h
// Ryan Stonebraker
// Last Modified: 4/25/2017
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
#include <iostream>
#include <tuple>

namespace JIG {
    class LoadLevel {
    public:
        friend std::ostream &operator<<(std::ostream&, LoadLevel&);
        
        LoadLevel(std::string); // takes file name // submit all shapes for rendering to get vtx array ids
        std::unique_ptr<JIG::Shape> &operator[](int); // identifier = order in which loaded/vtx array id
        
        void updateFile();
        void updateFile(std::string);
        void renderLevel() const;
   
        KFAPoint &location(int);
        KFAPoint location(int) const;
        float &rotation(int);
        float rotation(int) const;
        
    private:
        enum {NAME, POSITION, WIDTH, HEIGHT, ANGLE};
        std::vector <std::unique_ptr<JIG::Shape>> _loadedShapes;
        std::vector <std::tuple<std::string, KFAPoint, int, int, float> > _loadedShapeInfo;
        std::string _fname;
        std::string _getString(int) const;
        std::string _getTotalString() const;
        
        void _getFromText();
    };
    
//    extern KFAColorRGBA blue = JIGMakeColor(0.0f, 0.38f, 1.0f, 1.0f);
//    extern KFAColorRGBA red = JIGMakeColor(1.0f, 0.2f, 0.0f, 1.0f);
//    extern KFAColorRGBA grey = JIGMakeColor(0.717f, 0.717f, 0.717f, 1.0f);
    
    
} // namespace JIG

#endif
