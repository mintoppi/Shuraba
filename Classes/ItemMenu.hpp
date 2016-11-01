//
//  ItemMenu.hpp
//  FirstGame
//
//  Created by Tetsuya on 2016/11/01.
//
//

#ifndef ItemMenu_hpp
#define ItemMenu_hpp

#include <stdio.h>
#include "cocos2d.h"

class ItemMenuLayer : public cocos2d::LayerColor
{
public:
    ItemMenuLayer():_label(NULL) {};
    virtual ~ItemMenuLayer();
    bool init();
    void menu();
    void updateGame2(float dt);
    CREATE_FUNC(ItemMenuLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, _label, Label);
};

class ItemMenuScene : public cocos2d::Scene
{
public:
    ItemMenuScene():_layer(NULL) {};
    ~ItemMenuScene();
    bool init();
    CREATE_FUNC(ItemMenuScene);
    
    CC_SYNTHESIZE_READONLY(ItemMenuLayer*, _layer, Layer);
};

#endif /* ItemMenu_hpp */
