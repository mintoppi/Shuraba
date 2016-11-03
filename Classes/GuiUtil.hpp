//
//  GuiUtil.hpp
//  FirstGame
//
//  Created by Tetsuya on 2016/11/02.
//
//

#ifndef GuiUtil_hpp
#define GuiUtil_hpp

#include <stdio.h>
#include "cocos2d.h"

class GuiUtilLayer : public cocos2d::LayerColor
{
public:
    GuiUtilLayer():_label(NULL) {};
    virtual ~GuiUtilLayer();
    bool init();
    void createGuit();
    void updateGame2(float dt);
    void addSprite(const std::string);
        void addSprite(const std::string, float);
    void addSprite(const std::string filename, cocos2d::Point point);
    CREATE_FUNC(GuiUtilLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, _label, Label);
};

class GuiUtilScene : public cocos2d::Scene
{
public:
    GuiUtilScene():_layer(NULL) {};
    ~GuiUtilScene();
    bool init();
    CREATE_FUNC(GuiUtilScene);
    
    CC_SYNTHESIZE_READONLY(GuiUtilLayer*, _layer, Layer);
};
#endif /* GuiUtil_hpp */
