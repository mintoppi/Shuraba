//
//  TitleMenu.cpp
//  FirstGame
//
//  Created by Tetsuya on 2016/10/30.
//
//

#include "TitleMenu.h"
#include "StartMenu.h"
#include "HelloWorldScene.h"
#include "ItemMenu.hpp"
#include "SimpleAudioEngine.h"
#include "GameManager.hpp"
#include "GuiUtil.hpp"

using namespace cocos2d;

bool TitleMenuScene::init()
{
    if( Scene::init() )
    {
        this->_layer = TitleMenuLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        this->_layer->menu();
        
        return true;
    }
    else
    {
        return false;
    }
}

TitleMenuScene::~TitleMenuScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

Size winSize2_2;
void TitleMenuLayer::menu(){
    
    winSize2_2 = Director::getInstance()->getWinSize();
    
    Size screenSize = winSize2_2;

    this->_label = CCLabelTTF::create("修羅場RUSH2","Times New Roman", 64);
    this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
    _label->retain();
    _label->setColor( Color3B(0, 0, 600) );
    _label->setPosition( Point(winSize2_2.width/2, 700) );
    this->addChild(_label);
    
    this->_label = CCLabelTTF::create("Game mode","Times New Roman", 48);
    this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
    _label->retain();
    _label->setColor( Color3B(0, 0, 600) );
    _label->setPosition( Point(winSize2_2.width/2, 700-90) );
    this->addChild(_label);
    
    
    MenuItemFont::setFontName("AppleGothic");
    
    MenuItemLabel *label1 = MenuItemFont::create("はじめから",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( HelloWorld::scene(0));
    });
    MenuItemLabel *label2 = MenuItemFont::create("続きから",[](Ref *obj) {
        GameManager gm = *GameManager::getInstance();
        int stage_no = gm.getStageNum();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( HelloWorld::scene(stage_no));
    });
    MenuItemLabel *label3 = MenuItemFont::create("ストイックモード",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( StartMenuScene::create() );
    });
    MenuItemLabel *label4 = MenuItemFont::create("アイテム",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( ItemMenuScene::create() );
    });
    MenuItemLabel *label5 = MenuItemFont::create("GUI",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( GuiUtilScene::create() );
    });
    
    Menu *menu = Menu::create(label1, label2, label3, label4, label5, NULL);
    
    menu->setColor( Color3B(444, 0, 0) );
    
    menu->setPosition(320,500-30);
    
    //メニューを縦向きに並べます。
    menu->alignItemsVertically();
    
    
    this->addChild(menu);
    
    
    
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //Director::getInstance()->replaceScene( TitleMenuScene::create() );

}

bool TitleMenuLayer::init()
{
    //if ( CCLayerColor::initWithColor( Color4B(255,255,255,255) ) )
    if ( LayerColor::initWithColor(Color4B(255, 240, 245, 200)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

TitleMenuLayer::~TitleMenuLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
