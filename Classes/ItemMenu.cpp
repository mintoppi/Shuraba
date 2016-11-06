//
//  ItemMenu.cpp
//  FirstGame
//
//  Created by Tetsuya on 2016/11/01.
//
//

#include "ItemMenu.hpp"
#include "GuiUtil.hpp"
#include "StartMenu.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

GuiUtilLayer* gui;
bool ItemMenuScene::init()
{
    if( Scene::init() )
    {
        this->_layer = ItemMenuLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        
        return true;
    }
    else
    {
        return false;
    }
}

ItemMenuScene::~ItemMenuScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

Size winSize2_3;
void ItemMenuLayer::menu(){
    
    const ccMenuCallback callback = [](Ref * pSender){
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( StartMenuScene::create() );
    };
    gui->addSprite("タッチ用-次の面をプレイ.png", "タッチ用-次の面をプレイ2.png", Point(162.259079,240.160095), callback);

    gui->addSprite("タッチ用-セーブ.png",Point(479.737946,240.161957));
    gui->addSprite("アイテムカラム.png",Point(323.993103,987.852844));
    
    winSize2_3 = Director::getInstance()->getWinSize();
    
    Size screenSize = winSize2_3;
    
    this->_label = Label::create("アイテム","Times New Roman", 64);
    this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
    _label->retain();
    _label->setColor( Color3B(0, 0, 600) );
    _label->setPosition( Point(winSize2_3.width/2, 700) );
    this->addChild(_label);
    

    MenuItemLabel *label1 = MenuItemFont::create("ストイックモード",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( StartMenuScene::create() );
    });
    
    Menu *menu = Menu::create(label1, NULL);
    
    menu->setColor( Color3B(444, 0, 0) );
    
    menu->setPosition(320,500-30);
    
    //メニューを縦向きに並べます。
    menu->alignItemsVertically();
    
    this->addChild(menu);
}

bool ItemMenuLayer::init()
{

    if ( CCLayerColor::initWithColor( Color4B(0,0,0,0) ) )
    //if ( LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        gui = GuiUtilLayer::create();
        gui->setNode(this);
        menu();
        return true;
    }
    else
    {
        return false;
    }
}

ItemMenuLayer::~ItemMenuLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
