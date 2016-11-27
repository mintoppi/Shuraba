//
//  GuiUtil.cpp
//  FirstGame
//
//  Created by Tetsuya on 2016/11/02.
//
//

#include "GuiUtil.hpp"
#include "StartMenu.h"
#include "HelloWorldScene.h"
#include "ScrollBarView.hpp"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool GuiUtilScene::init()
{
    if( Scene::init() )
    {
        this->_layer = GuiUtilLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        this->_layer->createGuit();
        
        return true;
    }
    else
    {
        return false;
    }
}

GuiUtilScene::~GuiUtilScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

int tTag=0;
int tagCount=1;
cocos2d::Vector<cocos2d::Sprite*> _targets;
Node* abc;
void GuiUtilLayer::addSprite(const std::string filename){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite* player = Sprite::create(filename);
    
    player->setPosition( Point(visibleSize.width/2,
                               player->getContentSize().height/2 + visibleSize.height/2) );
    player->setTag(tagCount);
    player->setName(filename);
    log("%s = %d", filename.c_str(), tagCount);
    abc->addChild(player);
    
    _targets.pushBack(player);
    tagCount++;
}

void GuiUtilLayer::addSprite(const std::string filename, float scale){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite* player = Sprite::create(filename);
    
    player->setPosition( Point(visibleSize.width/2,
                               player->getContentSize().height/2 + visibleSize.height/2) );
    player->setTag(tagCount);
    player->setName(filename);
    log("%s = %d", filename.c_str(), tagCount);
    player->setScale(scale);
    player->setPosition(player->getPositionX()-200,player->getPositionY()-300);
    FiniteTimeAction* actionMove = MoveBy::create( (float)6,
                                                  Point(player->getContentSize().width, 30) );
    FiniteTimeAction* actionMove2 = MoveBy::create( (float)3,
                                                  Point(-player->getContentSize().width, -30) );
    auto seq = CCSequence::create(actionMove, actionMove2, NULL);
    player->runAction( Repeat::create(EaseElasticInOut::create(seq),3) );
    abc->addChild(player);
    
    _targets.pushBack(player);
    tagCount++;
}


void GuiUtilLayer::addSprite(const std::string filename, Point point){
    
    Sprite* player = Sprite::create(filename);
    
    player->setPosition(point);
    player->setTag(tagCount);
    player->setName(filename);
    log("%s = %d", filename.c_str(), tagCount);
    abc->addChild(player);
    _targets.pushBack(player);
    tagCount++;
}

void GuiUtilLayer::addSprite(const std::string filename, Point point, float scale){
    
    Sprite* player = Sprite::create(filename);
    
    player->setPosition(point);
    player->setTag(tagCount);
    player->setName(filename);
    log("%s = %d", filename.c_str(), tagCount);
    player->setScale(scale);
    abc->addChild(player);
    _targets.pushBack(player);
    tagCount++;
}

void GuiUtilLayer::addSprite(const std::string filename, Point point, float scale, int zoder){
    
    Sprite* player = Sprite::create(filename);
    
    player->setPosition(point);
    player->setTag(tagCount);
    player->setName(filename);
    log("%s = %d", filename.c_str(), tagCount);
    player->setScale(scale);
    abc->addChild(player, zoder);
    _targets.pushBack(player);
    tagCount++;
}

void GuiUtilLayer::addSprite(const std::string filename, const std::string filename2, Point point, std::function<void(Ref*)> callback ){
    
    MenuItemImage *pCloseItem = MenuItemImage::create(filename,      // 通常状態の画像
                                                      filename2,    // 押下状態の画像
                                                      callback);  // 押下時のアクション
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(point);
    abc->addChild(pMenu, 1);
}

ParticleSystemQuad* particle2;
void GuiUtilLayer::createGuit(){
    if(abc == NULL) abc = this->getParent();
    
    const ccMenuCallback callback = [](Ref * pSender){
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene( StartMenuScene::create() );
    };
    
    //addSprite("kurenai.png");
    
//    addSprite("タッチ用-次の面をプレイ.png", "タッチ用-次の面をプレイ2.png", Point(162.259079,240.160095), callback);
//    
////    particle2 = ParticleSystemQuad::create("player-aura.plist");
////    
////    particle2->setPosition(320,530);
////    
////    this->addChild(particle2);
//    
//    addSprite("タッチ用-次の面をプレイ.png",Point(162.259079,240.160095));
//    addSprite("タッチ用-セーブ.png",Point(479.737946,240.161957));
//    addSprite("アイテムカラム.png",Point(323.993103,987.852844));
//    
//    addSprite("アイコン-愛.png",2.00);
//    addSprite("アイコン-根性.png",2.00);
//    addSprite("タッチ用-購入.png");
//    addSprite("アイコン-根性DX.png",2.00);
//    addSprite("アイコン-気合い.png",2.00);
//    addSprite("アイコン-気合いMAX.png",2.00);
//    addSprite("タッチ用-使用する(やめる).png");
//    addSprite("アイコン-強烈な愛.png",2.00);
//    addSprite("アイコン-永久根性.png",2.00);
//    addSprite("アイコン-被害妄想.png",2.00);
////    addSprite("タッチ用-セーブ.png");
//    addSprite("タッチ用-使用する.png");
//    addSprite("アイコン-へなちょこ.png",2.00);
//    addSprite("アイコン-永久気合い.png",2.00);
//    addSprite("アイコン-貧乏舌の心.png",2.00);
//    addSprite("アイコン-貧乏舌の魂.png",2.00);
//    addSprite("アイコン-猛烈な愛の嵐.png",2.00);
//    addSprite("アイコン-欲しがり屋さん.png",2.00);
//    addSprite("アイコン-話し合いで解決.png",2.00);
////    addSprite("タッチ用-次の面をプレイ.png");
//    addSprite("アイコン-超気合いウルトラMA.png",2.00);
//    addSprite("アイコン-全部受け止めてやる.png",2.00);
//    addSprite("アイコン-止まって見えるぜ.png",2.00);
//    addSprite("アイコン-ど根性スーパーDX.png",2.00);
//    addSprite("アイコン-ガチンコボディ.png",2.00);
//    addSprite("アイコン-こんなとこで死ねるか.png",2.00);
//    

    
//    addSprite("CD.png");
//    //addSprite("CloseNormal.png");
//    //addSprite("CloseSelected.png");
//    //addSprite("Default-568h@2x.png");
//    //addSprite("HelloWorld.png");
//    //addSprite("Icon-57.png");
//    //addSprite("LIFE.png");
//    //addSprite("LIFE_03-1.png");
//    //addSprite("LIFE_03.png");
//    addSprite("LIFEアイコン-a1.png");
//    addSprite("LIFEアイコン-a2.png");
//    addSprite("LIFEアイコン-a3.png");
//    addSprite("LIFEアイコン-d1.png");
//    addSprite("LIFEアイコン-d2.png");
//    addSprite("LIFEアイコン-d3.png");
//    addSprite("LIFEアイコン.png");
//    //addSprite("TIME.png");
//    //addSprite("TRUST.png");
//    addSprite("TRUSTアイコン-a1.png");
//    addSprite("TRUSTアイコン-a2.png");
//    addSprite("TRUSTアイコン-a3.png");
//    addSprite("TRUSTアイコン.png");
//    //addSprite("bar.png");
//    //addSprite("naifu.pnga");
//    //addSprite("naifu2.png");
//    //addSprite("家.png");
//    addSprite("本.png");
//    //addSprite("桜.png");
//    //addSprite("海.png");
//    addSprite("皿.png");
//    //addSprite("説明-1.png");
//    //addSprite("人死.png");
//    addSprite("包丁.png");
//    //addSprite("同情.png");
//    //addSprite("吹雪.png");
//    //addSprite("日光.png");
//    //addSprite("正解.png");
//    addSprite("花瓶.png");
//    //addSprite("花見.png");
//    //addSprite("設問.png");
//    //addSprite("説明.png");
//    addSprite("酒瓶.png");
//    //addSprite("説得1-1.png");
//    //addSprite("説得1-2.png");
//    //addSprite("説得1.png");
//    //addSprite("説得2-1.png");
//    //addSprite("説得2-2.png");
//    //addSprite("説得2.png");
//    //addSprite("説得3-1.png");
//    //addSprite("説得3-2.png");
//    //addSprite("説得3.png");
//    //addSprite("情報_02.png");
//    //addSprite("情報_02_2.png");
//    //addSprite("誠意_03-1.png");
//    //addSprite("背景_03.png");
//    //addSprite("誠意_03.png");
//    addSprite("私服_止１前.png");
//    addSprite("私服_止１右.png");
//    addSprite("私服_止１左.png");
//    addSprite("私服_止１後.png");
//    addSprite("私服_止２前.png");
//    addSprite("私服_止２右.png");
//    addSprite("私服_止２左.png");
//    addSprite("私服_止２後.png");
//    addSprite("私服_走１前.png");
//    addSprite("私服_走１右.png");
//    addSprite("私服_走１左.png");
//    addSprite("私服_走１後.png");
//    addSprite("私服_走２前.png");
//    addSprite("私服_走２右.png");
//    addSprite("私服_走２左.png");
//    addSprite("私服_走２後.png");
//    addSprite("私服_ダメージ.png");
//    //addSprite("クリア.png");
//    addSprite("スイカ.png");
//    //addSprite("タンス.png");
//    //addSprite("人止前.png");
//    //addSprite("人止右.png");
//    //addSprite("人止左.png");
//    //addSprite("人止後.png");
//    //addSprite("正解１.png");
//    //addSprite("正解２.png");
//    //addSprite("正解３.png");
//    addSprite("浮き輪.png");
//    addSprite("焼き鳥.png");
//    addSprite("空き缶.png");
//    //addSprite("答え１.png");
//    //addSprite("答え２.png");
//    //addSprite("答え３.png");
//    //addSprite("落ち葉.png");
//    addSprite("足あと.png");
//    //addSprite("クリア_2.png");
//    //addSprite("当たり_2.png");
//    addSprite("スーツ_止１前.png");
//    addSprite("スーツ_止１右.png");
//    addSprite("スーツ_止１左.png");
//    addSprite("スーツ_止１後.png");
//    addSprite("スーツ_止２前.png");
//    addSprite("スーツ_止２右.png");
//    addSprite("スーツ_止２左.png");
//    addSprite("スーツ_止２後.png");
//    addSprite("スーツ_走１前.png");
//    addSprite("スーツ_走１右.png");
//    addSprite("スーツ_走１左.png");
//    addSprite("スーツ_走１後.png");
//    addSprite("スーツ_走２前.png");
//    addSprite("スーツ_走２右.png");
//    addSprite("スーツ_走２左.png");
//    addSprite("スーツ_走２後.png");
//    addSprite("スーツ_ダメージ.png");
//    addSprite("ゴミ袋-1.png");
//    //addSprite("はずれ.png");
//    //addSprite("アイテム.png");
//    addSprite("ゴミ袋.png");
//    addSprite("コップ.png");
//    addSprite("ストック.png");
//    //addSprite("人走１前.png");
//    //addSprite("人走１右.png");
//    //addSprite("人走１左.png");
//    //addSprite("人走１後.png");
//    //addSprite("人走２前.png");
//    //addSprite("人走２右.png");
//    //addSprite("人走２左.png");
//    //addSprite("人走２後.png");
//    addSprite("はだか_止１前.png");
//    addSprite("はだか_止１右.png");
//    addSprite("はだか_止１左.png");
//    addSprite("はだか_止１後.png");
//    addSprite("はだか_止２前.png");
//    addSprite("はだか_止２右.png");
//    addSprite("はだか_止２左.png");
//    addSprite("はだか_止２後.png");
//    addSprite("はだか_走１前.png");
//    addSprite("はだか_走１右.png");
//    addSprite("はだか_走１左.png");
//    addSprite("はだか_走１後.png");
//    addSprite("はだか_走２前.png");
//    addSprite("はだか_走２右.png");
//    addSprite("はだか_走２左.png");
//    addSprite("はだか_走２後.png");
//    addSprite("海パン_止１前.png");
//    addSprite("海パン_止１右.png");
//    addSprite("海パン_止１左.png");
//    addSprite("海パン_止１後.png");
//    addSprite("海パン_止２前.png");
//    addSprite("海パン_止２右.png");
//    addSprite("海パン_止２左.png");
//    addSprite("海パン_止２後.png");
//    addSprite("海パン_走１前.png");
//    addSprite("海パン_走１右.png");
//    addSprite("海パン_走１左.png");
//    addSprite("海パン_走１後.png");
//    addSprite("海パン_走２前.png");
//    addSprite("海パン_走２右.png");
//    addSprite("海パン_走２左.png");
//    addSprite("海パン_走２後.png");
//    addSprite("はだか_ダメージ.png");
//    addSprite("海パン_ダメージ.png");
//    addSprite("おにぎり.png");
//    addSprite("はずれ１.png");
//    addSprite("はずれ２.png");
//    addSprite("はずれ３.png");
//    addSprite("クッション.png");
//    addSprite("スリッパ.png");
//    //addSprite("テーブル.png");
//    //addSprite("パラソル.png");
//    //addSprite("パンダ.png");
//    addSprite("ペナント.png");
//    addSprite("雪だるま.png");
//    //addSprite("雪玉（大）.png");
//    addSprite("雪玉（小）.png");
//    //addSprite("アイテム画面-下.png");
//    addSprite("みたらし団子.png");
//    //addSprite("ゲレンデ.png");
//    //addSprite("ダメージ.png");
//    addSprite("ニホンザル.png");
//    addSprite("思い出の写真.png");
//    addSprite("焼きもろこし.png");
//    addSprite("アイテムカラム.png");
//    addSprite("オードブル.png");
//    addSprite("スイカボール.png");
//    addSprite("ダメージ１.png");
//    addSprite("ダメージ２.png");
//    addSprite("ダメージ３.png");
//    addSprite("スノーボード.png");
    //addSprite("ゲームオーバー.png");
    //addSprite("バランスボール.png");
    //addSprite("ポーズボタン.png");
    //addSprite("ゲームオーバー1000.png");
    //addSprite("Title.png",0.6);
    //addSprite("Title2.png",0.6);
    
//    addSprite("Title.png",Point(320.998383,670.016418), 0.6, 1);
//    addSprite("Title2.png",Point(319.001678,547.855469), 0.6);
    
//    //画面サイズを取得
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    
//    //スクロールの表示範囲を画面いっぱいに設定
//    ScrollView* pScrollView = ScrollView::create(winSize);
//    this->addChild(pScrollView);
    
    //背景画像を選択して、表示する場所（座標）を設定
//    CCSprite* pImg = CCSprite::create("家.png");
//    pImg->setScale(2.0, 2.0);
//    pImg->setPosition(ccp(winSize.width*.5, winSize.height*.5));
//    
//    //背景画像をスクロールにセット
//    pScrollView->setContainer(pImg);
//    pScrollView->setContentSize(pImg->getContentSize());
//    pScrollView->setContentOffset(CCPointZero, false);
//    pScrollView->setMinScale(0.5f);
//    pScrollView->setMaxScale(2.0f);
//    
//    pScrollView->setBounceable(false);
    
    //Size size = Size(visibleSize.width + origin.x, visibleSize.height + origin.y);
//    Size size = Size(200, 200);
//    ScrollView* sc = ScrollView::create(size);
//    sc->setDirection(ScrollView::Direction::VERTICAL);
//    sc->setContainer(pImg);
//    sc->setContentSize(pImg->getContentSize());
//    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    
//    sc->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    this->addChild(sc);
//    
//    ScrollBarView *bar = ScrollBarView::create(sc, ScrollBarView::BarType::VERTICAL_IN);
    
    
    //this->addChild(m_scrollView);

    
    //addSprite("スーツ_止１前.png");
    //addSprite("おにぎり.png");

    //addSprite("スーツ_止１前.png",Point(96.366951,360.341949));
    //addSprite("おにぎり.png",Point(533.648865,508.099609));
    
    //addSprite("おにぎり.png",Point(329.982819,446.201080));
    //addSprite("スーツ_止１前.png",Point(316.006409,400.276917));
    
    //this->_label = Label::create("アイテム","Times New Roman", 64);
    //this->_label->setHorizontalAlignment(TextHAlignment::RIGHT);
    //_label->retain();
    //_label->setColor( Color3B(0, 0, 600) );
    //_label->setPosition( Point(winSize2_3.width/2, 700) );
    //this->addChild(_label);
    

    
    //player2 = Sprite::create("スーツ_止１前.png", Rect(0, 0, 43, 62) );
    
    //player2->setPosition( Point(515.000000, 154.000000) );
    //player2->setTag(2);
        
    //ParticleSystemQuad* particle = ParticleSystemQuad::create("HelloParticle.plist");
//    ParticleSystemQuad* particle = ParticleSystemQuad::create("particle_texture-2.plist");
//
//    particle->setPosition(320,0);
//    this->addChild(particle);
    
    //イベントリスナーを作成
    auto listener = EventListenerTouchOneByOne::create();

    //タッチ開始
    listener->onTouchBegan = [](Touch* touch, Event* event){
        //log("TouchBegan");
        
        Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
        if(_targets.size() > 0){
            for(auto jt = _targets.begin();jt != _targets.end(); jt++)
            {
                Sprite* target = (*jt);
                
                if (target->getBoundingBox().containsPoint(touchPoint))
                {
                    tTag = target->getTag();
                    log("touch %d",tTag);
                }
            }
        }
        return true;
    };
    
    //タッチ中
    listener->onTouchMoved = [](Touch* touch, Event* event){
        //log("TouchMoved");
        Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
        //log("X:%f、Y:%fをタッチしました", touchPoint.x, touchPoint.y);
        
        // 前回とのタッチ位置との差をベクトルで取得する
        Vec2 delta = touch->getDelta();
        
        //Sprite* target = (*jt);
        
        if(tTag > 0){
            if(_targets.size() > 0){
                for(auto jt = _targets.begin();jt != _targets.end(); jt++)
                {
                    Sprite* target = (*jt);
                    if(target->getTag() == tTag){
                        
                        // 現在のかわずたんの座標を取得する
                        Vec2 position = target->getPosition();
                        
                        // 現在座標　+ 移動量を新たな座標にする
                        Vec2 newPosition = position + delta;
                        
                        /////////////////////////////////////////
                        // キャラクターが画面から飛び出してしまうのを防ぐ
                        // 画面サイズを取り出す
                        auto winsiz = Director::getInstance()->getWinSize();
                        
                        
                        if (newPosition.x < 0) { //もし、新しい位置が左端より左だったら
                            
                            newPosition.x = 0;   //x座標を0にする
                            
                        } else if(newPosition.x > winsiz.width){ //もし、右端より右だったら
                            
                            newPosition.x = winsiz.width;   //x座標を画面の横幅にする
                        }
                        
                        if (newPosition.y < 0) { //もし、新しい位置が左端より左だったら
                            
                            newPosition.y = 0;   //y座標を0にする
                            
                        } else if(newPosition.y > winsiz.height){ //もし、右端より右だったら
                            
                            newPosition.y = winsiz.height;   //x座標を画面の縦幅にする
                        }
                        
                        // "player.png"
                        target->setPosition(newPosition);
                        
                        //タグのインスタンスを取得
                        //Node* player = this -> getChildByTag(1);
                        //player->setPosition( touchPoint.x, touchPoint.y );
                    }
                }
            }
        }
        
//        particle2->setPosition(touch->getLocation().x, touch->getLocation().y);
        
        return true;
    };
    
    //タッチ終了
    listener->onTouchEnded = [](Touch* touch, Event* event){
        log("TouchEnded");
        if(_targets.size() > 0){
            for(auto jt = _targets.begin();jt != _targets.end(); jt++)
            {
                Sprite* target = (*jt);
                if(target->getTag() == tTag){
                    Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
                    log("addSprite(\"%s\",Point(%f,%f));", target->getName().c_str(), target->getPositionX(), target->getPositionY());
                }
            }
        }
        tTag = 0;
        //particle2->setPosition(touch->getLocation().x, touch->getLocation().y);
    };
    
    //イベントリスナーを登録
    abc->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, abc);
    
    //this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
}

bool GuiUtilLayer::setNode(Node* tNode){
        abc = tNode;
}

bool GuiUtilLayer::init()
{
    if ( LayerColor::initWithColor(Color4B(0,0,0,0)))
    //if ( LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

GuiUtilLayer::~GuiUtilLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
