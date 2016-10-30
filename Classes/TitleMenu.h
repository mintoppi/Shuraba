//
//  TitleMenu.hpp
//  FirstGame
//
//  Created by Tetsuya on 2016/10/30.
//
//

#ifndef TitleMenu_h
#define TitleMenu_h

#include <stdio.h>
#include "cocos2d.h"

class TitleMenuLayer : public cocos2d::LayerColor
{
public:
    TitleMenuLayer():_label(NULL) {};
    virtual ~TitleMenuLayer();
    bool init();
    void menu();
    void gameStartHome(char* stage);
    void gameStartSpring(char* stage);
    void gameStartSummer(char* stage);
    void gameStartAutumn(char* stage);
    void gameStartWinter(char* stage);
    void updateGame2(float dt);
    CREATE_FUNC(TitleMenuLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
};

class TitleMenuScene : public cocos2d::Scene
{
public:
    TitleMenuScene():_layer(NULL) {};
    ~TitleMenuScene();
    bool init();
    CREATE_FUNC(TitleMenuScene);
    
    CC_SYNTHESIZE_READONLY(TitleMenuLayer*, _layer, Layer);
};

#endif /* TitleMenu_hpp */
