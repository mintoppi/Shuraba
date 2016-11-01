//
//  ItemMenu.cpp
//  FirstGame
//
//  Created by Tetsuya on 2016/11/01.
//
//

#include "ItemMenu.hpp"

#include "StartMenu.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool ItemMenuScene::init()
{
    if( Scene::init() )
    {
        this->_layer = ItemMenuLayer::create();
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
    
    winSize2_3 = Director::getInstance()->getWinSize();
    
    Size screenSize = winSize2_3;
    
    this->_label = Label::create("アイテム","Times New Roman", 64);
    this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
    _label->retain();
    _label->setColor( Color3B(0, 0, 600) );
    _label->setPosition( Point(winSize2_3.width/2, 700) );
    this->addChild(_label);
}

bool ItemMenuLayer::init()
{
    //if ( CCLayerColor::initWithColor( Color4B(255,255,255,255) ) )
    if ( LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
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
