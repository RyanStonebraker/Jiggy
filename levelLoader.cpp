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
#include <stdexcept>
#include "KFAGeometry.h"
#include <vector>
#include <memory>
#include <tuple>

JIG::LoadLevel::LoadLevel(std::string fname) : _fname{fname} {
    _getFromText();
}

void JIG::LoadLevel::_getFromText() {
//    KFAColorRGBA blue = JIGMakeColor(0.0f, 0.38f, 1.0f, 1.0f);
//    KFAColorRGBA red = JIGMakeColor(1.0f, 0.2f, 0.0f, 1.0f);
    KFAColorRGBA grey = JIGMakeColor(0.717f, 0.717f, 0.717f, 1.0f);

    
    // TODO ERROR CHECKING
    std::ifstream reader(this->_fname);
    
    std::string shapeData;

    for (unsigned i = 0; getline(reader, shapeData); ++i) {
        
        std::istringstream shapeParser(shapeData);
        
        std::string shapeType;
        shapeParser >> shapeType;
        
        KFAPoint shapeLoc{0, 0, 0};
        shapeParser >> shapeLoc.x >> shapeLoc.y >> shapeLoc.z;
        
        float width = 0, height = 0;
        shapeParser >> width >> height;
        
        float angle = 0;
        shapeParser >> angle;
        
        if (shapeType == "Rect") {
            _loadedShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(shapeLoc, width, height, angle, grey)));
            _loadedShapeInfo.push_back(std::make_tuple("Rect", shapeLoc, width, height, angle));
        }
        
    }
}

std::unique_ptr<JIG::Shape> & JIG::LoadLevel::operator[](int i) {
    return _loadedShapes[i];
}

void JIG::LoadLevel::renderLevel() const {
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

//KFAColorRGBA &color(int loc) {
//    
//}
//
//KFAColorRGBA color(int loc) const {
//    
//}

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
