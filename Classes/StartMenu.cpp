//
//  StartMenu.cpp
//  SimpleGame_addon
//
//  Created by Tetsuya on 2014/09/24.
//
//

#include "StartMenu.h"
#include "TitleMenu.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
//#include "curl.h"

using namespace cocos2d;

bool StartMenuScene::init()
{
	if( Scene::init() )
	{
		this->_layer = StartMenuLayer::create();
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

StartMenuScene::~StartMenuScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

Size winSize2;
void StartMenuLayer::menu(){
    
    winSize2 = CCDirector::getInstance()->getWinSize();

    //CCSprite *death;
    //death = CCSprite::create("ゲームオーバー1000.gif");
    
    Size screenSize = winSize2;
    
//    if (screenSize.height > 960)
//    {
//        death->setPosition(Point(320,620) );
//        this->addChild(death);
//    }else{
//        death->setPosition(Point(320,670) );
//        this->addChild(death);
//    }
    
    //sprintf(labels,"Score : %d\n BestScore : %d \n Update BEST SCORE!!", score, best_score);
    this->_label = CCLabelTTF::create("STAGE SELECT","Times New Roman", 64);
    this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
    _label->retain();
    _label->setColor( Color3B(0, 0, 600) );
    _label->setPosition( Point(winSize2.width/2, 800) );
    this->addChild(_label);
//
//    this->_label = CCLabelTTF::create("END","arial", 32);
//    this->_label->setHorizontalAlignment(kCCTextAlignmentRight);
//    _label->retain();
//    _label->setColor( ccc3(0, 0, 1000) );
//    _label->setPosition( Point(winSize2.width/2+70, 550) );
//    this->addChild(_label);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7);
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Opening.mp3", true);

    MenuItemFont::setFontName("AppleGothic");
    MenuItemLabel *label  = MenuItemFont::create("Modern her               HISCORE",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"home") );
    });
    MenuItemLabel *label2 = MenuItemFont::create("Spring Lover             HISCORE",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"spring") );
    });
    
    MenuItemLabel *label3 = MenuItemFont::create("Yes, Summerdays          HISCORE",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"summer") );
    });
    MenuItemLabel *label4 = MenuItemFont::create("Goodbye of Autumn day    HISCORE",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"autumn") );
    });
    MenuItemLabel *label5 = MenuItemFont::create("Winter, Again            HISCORE",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"winter") );
    });
    
    MenuItemLabel *label6 = MenuItemFont::create("HISCORE TOTAL",[](Ref *obj) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( TitleMenuScene::create() );
    });
    
    Menu *menu = Menu::create(label, label2, label3, label4, label5, label6, NULL);
    
    menu->setColor( Color3B(444, 0, 0) );
    
    menu->setPosition(320,500);
    
    //メニューを縦向きに並べます。
    menu->alignItemsVertically();
    
    
    this->addChild(menu);
    
//    //中心となる画像
//    CCSprite* m_sprite = CCSprite::create();
//    m_sprite->setTextureRect(CCRectMake(0, 0, 200, 200));
//    m_sprite->setColor(ccWHITE);
//    m_sprite->setOpacity(128);
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    m_sprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
//    this->addChild(m_sprite);
//    
//    //螺旋状に動く画像
//    CCSprite* m_sprite2 = CCSprite::create("CD.png");
//    m_sprite2->setAnchorPoint(ccp(0,0));
//    m_sprite2->setPosition(ccp(300,300));
//    m_sprite->addChild(m_sprite2, 0);
//    
//    //アニメーションを作成
//    CCActionInterval* actionRotate;
//    actionRotate = CCRotateBy::create(3, 360);
//    
//    CCActionInterval* actionScale;
//    actionScale = CCScaleTo::create(3, 0);
//    CCSpawn* actionSpan = CCSpawn::createWithTwoActions(actionRotate,actionScale);
//    m_sprite->runAction(actionSpan);
//    
//    //スプライトを作成
//    CCSize s = CCDirector::sharedDirector()->getVisibleSize();
//    CCSprite* pBar = CCSprite::create("bar.png");
//    
//    //タイマーにスプライトをセット
//    CCProgressTimer* pTimer = CCProgressTimer::create(pBar);
//    
//    //最初は0パーセント
//    pTimer->setPercentage(0);
//    
//    //タイマーの形（棒状に設定）
//    pTimer->setType(kCCProgressTimerTypeBar);
//    
//    //バーの伸びる方向（x方向に設定）
//    pTimer->setBarChangeRate(ccp(1, 0));
//    
//    //タイマーの基準点（左側に設定）
//    pTimer->setMidpoint(ccp(0, 0));
//    
//    //タイマーを配置
//    pTimer->setPosition(ccp(s.width*.5, s.height*.5));
//    pTimer->setTag(100);
//    addChild(pTimer);
//    
//    //パーセント表示用テキスト
//    CCLabelTTF* percentTxt = CCLabelTTF::create("0%", "Arial", 35);
//    percentTxt->setPosition(ccp(pTimer->getPositionX(), pTimer->getPositionY()+50));
//    percentTxt->setTag(200);
//    addChild(percentTxt);
    
    this->scheduleUpdate();
}

void StartMenuLayer::gameStartHome(char* stage)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"home") );
}

void StartMenuLayer::gameStartSpring(char* stage)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"spring") );
}

void StartMenuLayer::gameStartSummer(char* stage)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"summer") );
}

void StartMenuLayer::gameStartAutumn(char* stage)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)"autumn") );
}

void StartMenuLayer::gameStartWinter(char* stage)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CCDirector::getInstance()->replaceScene( HelloWorld::scene("winter") );

}

bool StartMenuLayer::init()
{
	if ( CCLayerColor::initWithColor(Color4B(255, 240, 245, 200)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

StartMenuLayer::~StartMenuLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}
