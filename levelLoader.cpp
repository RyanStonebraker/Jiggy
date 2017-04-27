// levelLoader.cpp
// Ryan Stonebraker
// Last Modified: 4/25/2017
// loads shape information from text file

#include "levelLoader.h"

#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include "JIGShape.h"
#include "JIGRect.h"
#include "JIGArcSlice.h"
#include <stdexcept>
#include "KFAGeometry.h"
#include <vector>
#include <memory>
#include <tuple>
#include <iostream>
#include "JIGMain.h"


JIG::LoadLevel::LoadLevel(std::string fname) : _fname{fname} {
     _getFromText();
}

void JIG::LoadLevel::_getFromText() {
    
    // TODO ERROR CHECKING
    std::ifstream reader(_fname);
    
    std::string shapeData;
    

    for (unsigned i = 0; getline(reader, shapeData); ++i) {
        std::istringstream shapeParser(shapeData);
        
        std::string shapeType;
        shapeParser >> shapeType;
        
        KFAPoint shapeLoc{0, 0, 0};
        shapeParser >> shapeLoc.x >> shapeLoc.y >> shapeLoc.z;
        
        
        if (shapeType == "Rect") {
            int width = 0, height = 0;
            shapeParser >> width >> height;
            
            float angle = 0;
            shapeParser >> angle;
            
            KFAColorRGBA shapeColor{0, 0, 0, 0};
            float r, g, b;
            shapeParser >> r >> g >> b >> shapeColor.a;
            shapeColor.r = r/255.0;
            shapeColor.g = g/255.0;
            shapeColor.b = b/255.0;
            
            _loadedShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(shapeLoc, width, height, angle, shapeColor)));
            _loadedShapeInfo.push_back(std::make_tuple("Rect", shapeLoc, width, height, angle, shapeColor));
        }
        
//        else if (shapeType == "Arc") {
//            float radius = 0;
//            shapeParser >> radius;
//            
//            float angle = 0;
//            shapeParser >> angle;
//            
//            float theta = 0;
//            shapeParser >> theta;
//            
//            KFAColorRGBA shapeColor{0, 0, 0, 0};
//            float r, g, b;
//            shapeParser >> r >> g >> b >> shapeColor.a;
//            shapeColor.r = r/255.0;
//            shapeColor.g = g/255.0;
//            shapeColor.b = b/255.0;
//            
//            _loadedShapes.push_back(std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(shapeLoc, radius, theta, angle, shapeColor)));
//            _loadedShapeInfo.push_back(std::make_tuple("Arc", shapeLoc, radius, theta, angle, shapeColor));
//        }
        
    }
    
//    KFAPoint shapeLoc{0, 0, 0};
//    _loadedShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(shapeLoc, 100.0f, 100.0f, 0.0f, JIGMakeColor(0.717f, 0.717f, 0.717f, 1.0f))));
}

std::unique_ptr<JIG::Shape> & JIG::LoadLevel::operator[](int i) {
    return _loadedShapes[i];
}

void JIG::LoadLevel::renderLevel() {
    for (unsigned i = 0; i < _loadedShapes.size(); ++i)
        _updatePtr(i);
    
    for (unsigned i = 0; i < _loadedShapes.size(); ++i) {
        _loadedShapes[i]->submitForRender();
    }

}

std::string JIG::LoadLevel::_getString(int loc) const {
    std::string shapeStr = std::get<JIG::LoadLevel::NAME>(_loadedShapeInfo[loc]) + " ";
    
    std::ostringstream holdPos;
    auto position = this->location(loc);
    holdPos << position.x;
    shapeStr += holdPos.str() + " ";
    
    holdPos.str("");
    holdPos.clear();
    
    holdPos << position.y;
    shapeStr += holdPos.str() + " ";
    
    holdPos.str("");
    holdPos.clear();
    
    holdPos << position.z;
    shapeStr += holdPos.str() + " ";
    
    std::ostringstream holdAng;
    holdAng << this->rotation(loc);
    
    shapeStr += holdAng.str();
    
    return shapeStr;
}

std::string JIG::LoadLevel::_getTotalString() const {
    std::string allShapesStr;
    for (unsigned i = 0; i < _loadedShapes.size(); ++i)
        allShapesStr += _getString(i) + '\n';
    return allShapesStr;
}

std::ostream &JIG::operator<<(std::ostream& out, LoadLevel& rhs) {
    return out << rhs._getTotalString();
}

void JIG::LoadLevel::updateFile() {
    this->updateFile(_fname);
}
void JIG::LoadLevel::updateFile(std::string fname) {
    std::ofstream writer (fname);
    writer << this->_getTotalString();
}

KFAPoint &JIG::LoadLevel::location(int loc) {
    return std::get<JIG::LoadLevel::POSITION>(_loadedShapeInfo[loc]);
}

KFAPoint JIG::LoadLevel::location(int loc) const {
    return std::get<JIG::LoadLevel::POSITION>(_loadedShapeInfo[loc]);
}

float &JIG::LoadLevel::rotation(int loc) {
    return std::get<JIG::LoadLevel::ANGLE>(_loadedShapeInfo[loc]);
}

float JIG::LoadLevel::rotation(int loc) const {
    return std::get<JIG::LoadLevel::ANGLE>(_loadedShapeInfo[loc]);
}

KFAColorRGBA &JIG::LoadLevel::color(int loc) {
    return std::get<JIG::LoadLevel::COLOR>(_loadedShapeInfo[loc]);
}

KFAColorRGBA JIG::LoadLevel::color (int loc) const {
    return std::get<JIG::LoadLevel::COLOR>(_loadedShapeInfo[loc]);
}

unsigned long JIG::LoadLevel::size () {
    return _loadedShapes.size();
}

void JIG::LoadLevel::_updatePtr(int i) {
        if (std::get<JIG::LoadLevel::NAME>(_loadedShapeInfo[i]) == "Rect")
            _loadedShapes[i] = std::make_unique<JIG::Rectangle>(JIG::Rectangle(std::get<JIG::LoadLevel::POSITION>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::WIDTH>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::HEIGHT>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::ANGLE>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::COLOR>(_loadedShapeInfo[i])));
    
//        else if (std::get<JIG::LoadLevel::NAME>(_loadedShapeInfo[i]) == "Arc")
//            _loadedShapes[i] = std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(std::get<JIG::LoadLevel::POSITION>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::WIDTH>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::HEIGHT>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::ANGLE>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::COLOR>(_loadedShapeInfo[i])));
}


void JIG::LoadLevel::sendToGlobal() {
    
    for (unsigned i = 0; i < _loadedShapes.size(); ++i) {
        if (i < global_LevelShapes.size()) {
            global_LevelShapes[i] = std::make_unique<JIG::Rectangle>(JIG::Rectangle(std::get<JIG::LoadLevel::POSITION>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::WIDTH>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::HEIGHT>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::ANGLE>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::COLOR>(_loadedShapeInfo[i])));
        }
        else {
            global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(std::get<JIG::LoadLevel::POSITION>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::WIDTH>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::HEIGHT>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::ANGLE>(_loadedShapeInfo[i]), std::get<JIG::LoadLevel::COLOR>(_loadedShapeInfo[i]))));
        }
    }
}

void JIG::LoadLevel::submitGlobal() {
    for (unsigned i = 0; i < global_LevelShapes.size(); ++i) {
        global_LevelShapes[i]->submitForRender();
    }
}

