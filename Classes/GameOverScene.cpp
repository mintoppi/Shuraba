/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2010      Ray Wenderlich
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "StartMenu.h"
//#include "curl.h"

using namespace cocos2d;

//int scores=0;
//int BEST_SCORE = 0;
bool GameOverScene::init()
{
	if( CCScene::init() )
	{
        //scores = this->score;
        //BEST_SCORE = this->best_score;
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

GameOverScene::~GameOverScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

float elapsedTime;
int s_num;

void set(float a, int b){
    elapsedTime = a;
    s_num = b;
}

void GameOverScene::setScore(int heart, int trust, int time, int bonus, int score, int best_score){
    this->_layer->setScore(heart, trust, time, bonus, score,best_score);
}

bool se=false;
int nums;
bool c_flg = false;
char labels[200];
char labels2[200];
Size winSize;
int heart,trust, time2, bonus, score, best_score;
char* stage[25]={"home", "home", "home", "spring", "spring", "spring", "home", "home", "home", "summer", "summer", "summer", "home", "home", "home", "autumn", "autumn", "autumn", "home", "home", "home", "winter", "winter", "winter", "home"};
int stage_num=0;
void GameOverLayer::setScore(int l_heart, int l_trust, int l_time, int l_bonus, int l_score, int l_best_score){
    
    se=false;
    heart = l_heart;
    trust = l_trust;
    time2 = l_time;
    bonus = l_bonus;
    score = l_score;
    best_score = l_best_score;
    
    winSize = CCDirector::getInstance()->getWinSize();
    Sprite *death;
    if (score > CLEAR_SCORE) {
        //death = Sprite::create("ゲームオーバー.gif" );
        death = Sprite::create(clear_png);
    }else{
        death = Sprite::create("ゲームオーバー1000.jpg" );
    }
    
    Size screenSize = winSize;

    if (screenSize.height > 960)
    {
    death->setPosition(Point(320,620) );
    this->addChild(death);
    }else{
        death->setPosition(Point(320,670) );
        this->addChild(death);
    }
    
    //CCSpriteクラスで画像を設定します。
    auto sprite1 = Sprite::create(clear_png);
    
    //これをCCParallaxNodeクラスで利用します。
//    ParallaxNode *prallNode = ParallaxNode::create();
//    prallNode->setPosition(Point(0,0));
//    prallNode->addChild(sprite1, 1, Point(30,0), Point(320,470));
//    
//    this->addChild(prallNode,1);
//    //this->add

    clear_flg = true;
//    this->_layer->score =score;
//    this->_layer->best_score =best_score;
//    CCLog("+++++++Score : %d\n BestScore : %d \n Update BEST SCORE!!", score, best_score);

    //CCLog("Score : %d\n BestScore : %d \n Update BEST SCORE!!", scores, BEST_SCORE);
    if(clear_flg){
    if (best_score < score) {
        sprintf(labels, "Score : %d\n BestScore : %d \n Update BEST SCORE!!",score,score);
    }else{
        sprintf(labels, "LIFE\nTRUST\nTIME\nBONUS\nGet Score\nAll Score\nHIGH Score");
        sprintf(labels2, "%d\n%d\n%d:%02d\n%d\n%d\n%d\n%d",heart, trust, time2/60, time2%60, bonus, 0, 0, best_score);
    }

    
    //sprintf(labels,"Score : %d\n BestScore : %d \n Update BEST SCORE!!", score, best_score);
    this->_label = LabelTTF::create(labels,"arial", 32);
    this->_label->setHorizontalAlignment(cocos2d::TextHAlignment::RIGHT);
    _label->retain();
    _label->setColor( Color3B(0, 0, 1000) );
    _label->setPosition( Point(winSize.width/2-80, 550) );
    this->addChild(_label);
    
    this->_label = CCLabelTTF::create(labels2,"arial", 32);
    this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
    _label->retain();
    _label->setColor( Color3B(0, 0, 1000) );
    _label->setPosition( Point(winSize.width/2+70, 550) );
    this->addChild(_label);
        }
    
    MenuItemLabel *label = MenuItemFont::create("STAGE SELECT",[&](Ref *sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( StartMenuScene::create() );
    });
    
        stage_num = (stage_num + 1) % 25;
    MenuItemLabel *label2 = MenuItemFont::create("NextStage",[&](Ref *sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)stage[stage_num]) );
    });

    Menu *menu = Menu::create(label, label2, NULL);
    
    //後は同じ
    //Menu *menu = Menu::create(label, NULL);
    
    menu->setColor( Color3B(444, 0, 0) );
    
    menu->setPosition(320,300);
    
    //メニューを縦向きに並べます。
    menu->alignItemsVertically();
    
    this->addChild(menu);
    
    c_flg = true;
    
    
    if (score >= CLEAR_SCORE) {
        death = Sprite::create("ゲームオーバー1000.gif" );
        //ParticleSystemQuad* particle = ParticleSystemQuad::create("HelloParticle.plist");
        //particle->setPosition(320,0);
        //this->addChild(particle);
    }
}

int dt=0;
void GameOverLayer::update(float delta){
    
    dt++;
    int sound;
    if(clear_flg){
    if ((dt%6 == 0) && c_flg) {
        if(!se){
            se=true;
            sound = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SE-換算.mp3");
        }
        this->removeChild(_label);
        this->_label = CCLabelTTF::create(labels,"arial", 32);
        this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
        _label->retain();
        _label->setColor( Color3B(0, 0, 1000) );
        _label->setPosition( Point(winSize.width/2-80, 550) );
        this->addChild(_label);
        if (heart>0) {
            heart--;
            score = score + 20;
        }
        else if (trust>0) {
            trust--;
            score = score + 10;
        }
        else if (time2>0) {
            time2--;
            score = score + 5;
        }
        sprintf(labels2, "%d\n%d\n%d:%02d\n%d\n%d\n%d\n%d",heart, trust, time2/60, time2%60, bonus, score, score+bonus, best_score);
        this->_label = CCLabelTTF::create(labels2,"arial", 32);
        this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
        _label->retain();
        _label->setColor( Color3B(0, 0, 1000) );
        _label->setPosition( Point(winSize.width/2+70, 550) );
        this->addChild(_label);
        
        if (heart+trust+time2 == 0) {
            c_flg = false;
            se=false;
            CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(sound);
        }
        //sleep(5.0f);
    }
    }
    
}

bool GameOverLayer::init()
{
	if ( CCLayerColor::initWithColor( Color4B(255,255,255,255) ) )
	{
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("死.mp3");
        this->scheduleUpdate();
        
//        Size visibleSize = CCDirector::getInstance()->getVisibleSize();
//        CCPoint origin = CCDirector::getInstance()->getVisibleOrigin();
//        
//        MenuItemImage *pCloseItem = MenuItemImage::create(
//                                                              "CloseNormal.png",
//                                                              "CloseSelected.png",
//                                                              this,
//                                                              menu_selector(GameOverLayer::gameOverDone));
//        
//        pCloseItem->setPosition(Point(300,400));
//        
//        // create menu, it's an autorelease object
//        Menu* pMenu = Menu::create(pCloseItem, NULL);
//        pMenu->setPosition(CCPointZero);
//        this->addChild(pMenu, 1);
        

        
        // death bg
        
//        Sprite *death = Sprite::create("人死.gif", CCRectMake(0, 0, 89, 56) );
//        death->setPosition(Point(315, winSize.height/2+45) );
//        this->addChild(death);
//        
//        Sprite *death2 = Sprite::create("ダメージ.gif", CCRectMake(0, 0, 72, 73) );
//        death2->setPosition(Point(315, winSize.height/2+80) );
//        this->addChild(death2);
		
//		this->runAction( CCSequence::create(
//                                CCDelayTime::create(5),
//                                CCCallFunc::create(this, 
//                                callfunc_selector(GameOverLayer::gameOverDone)),
//                                NULL));
		
		return true;
	}
	else
	{
		return false;
	}
}

//static char errorBuffer[CURL_ERROR_SIZE];
static std::string buffer;

static int writer(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    int result = 0;
    
    if (buffer != NULL)
    {
        //バッファ追記
        buffer->append(data, size * nmemb);
        result = (int)(size * nmemb);
    }
    
    return result;
}

/*void GameOverLayer::httpConnection()
{
    CURL *curl;
    CURLcode result;
    
    //初期化
    curl = curl_easy_init();
    
    if (curl) {
        //curl設定
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        //curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.co.jp");
        curl_easy_setopt(curl, CURLOPT_URL, "http://www47.atpages.jp/mintoppi/WEB/action.php");
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        
        //リクエスト実行
        result = curl_easy_perform(curl);
        
        //ハンドラのクリーンアップ
        curl_easy_cleanup(curl);
        
        if (result == CURLE_OK) {
            //レスポンス表示
            log("%s", buffer.c_str());
        } else {
            //エラー表示
            log("%s", errorBuffer);
        }
    }
}*/


void GameOverLayer::gameOverDone()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CCDirector::getInstance()->replaceScene( StartMenuScene::create() );
}

void GameOverLayer::gameOverDone2()
{
    //httpConnection();
}

GameOverLayer::~GameOverLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}
