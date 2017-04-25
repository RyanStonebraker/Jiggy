//// levelLoader.cpp
//// Ryan Stonebraker
//// 4/16/2017
//// loads shape information from text file
//
//#include "levelLoader.h"
//
//#include <fstream>
//#include <unordered_map>
//#include <string>
//#include <sstream>
//#include "JIGShape.h"
//#include "JIGRect.h"
//#include <stdexcept>
//#include "KFAGeometry.h"
//#include <vector>
//
//JIG::LoadLevel::LoadLevel(std::string fname) : _fname{fname} {
//    _getFromText();
//}
//
//void JIG::LoadLevel::_getFromText() {
//    // TODO ERROR CHECKING
//    std::ifstream reader(_fname);
//    
//    std::string shapeData;
//
//    int i = 0;
//    while (getline(reader, shapeData)) {
//        
//        std::istringstream shapeParser(shapeData);
//        
//        std::string shapeType;
//        shapeParser >> shapeType;
//        
//        KFAPoint shapeLoc{0, 0, 0};
//        shapeParser >> shapeLoc.x >> shapeLoc.y >> shapeLoc.z;
//        
//        float width = 0, height = 0;
//        shapeParser >> width >> height;
//        
//        float angle = 1;
//        shapeParser >> angle;
//        
////        std::unique_ptr<JIG::Shape> readShape = _createShape(shapeType, shapeLoc, width, height, angle);
//        
//        if (shapeType == "Rect")
//            _loadedShapes.push_back(_makeRect(shapeLoc, width, height, angle, JIGMakeColor(0.717f, 0.717f, 0.717f, 0.0f)));
//        _loadedShapes[i].submitForRender();
//        
//        // int x = readShape->getVertexArrayID()
//        ++i;
//    }
//    
//}
//
////std::unique_ptr<JIG::Shape> JIG::LoadLevel::_createShape(std::string shapeType, KFAPoint loc, float width, float height, float angle) {
////    if (shapeType == "Rect")
////        return std::unique_ptr<JIG::Shape> (new JIG::Rectangle(loc, width, height, angle, JIGMakeColor(0.717f, 0.717f, 0.717f, 0.0f)));
////    }
//
////void JIG::LoadLevel::renderLevel() const {
////    for (unsigned i = 0; i < _loadedShapes.size(); ++i) {
////        _loadedShapes[i]->submitForRender();
////    }
//
////}
