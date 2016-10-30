//
//  StartMenu.h
//  SimpleGame_addon
//
//  Created by Tetsuya on 2014/09/24.
//
//

#ifndef __SimpleGame_addon__StartMenu__
#define __SimpleGame_addon__StartMenu__

#include "cocos2d.h"

class StartMenuLayer : public cocos2d::LayerColor
{
public:
    StartMenuLayer():_label(NULL) {};
    virtual ~StartMenuLayer();
    bool init();
    void menu();
    void gameStartHome(char* stage);
    void gameStartSpring(char* stage);
    void gameStartSummer(char* stage);
    void gameStartAutumn(char* stage);
    void gameStartWinter(char* stage);
    void updateGame2(float dt);
    CREATE_FUNC(StartMenuLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
};

class StartMenuScene : public cocos2d::Scene
{
public:
    StartMenuScene():_layer(NULL) {};
    ~StartMenuScene();
    bool init();
    CREATE_FUNC(StartMenuScene);
    
    CC_SYNTHESIZE_READONLY(StartMenuLayer*, _layer, Layer);
};

#endif /* defined(__SimpleGame_addon__StartMenu__) */
