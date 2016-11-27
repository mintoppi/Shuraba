#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#define bg0_gif "家.png"
#define bg1_gif "花見.png"
#define bg2_gif "海.png"
#define bg2_2_gif "パラソル.png"
#define bg3_gif "日光.png"
#define bg4_gif "ゲレンデ.png"


#define sakura_png "桜.png"
#define hubuki_png "吹雪.png"
#define otiba_png "落ち葉.png"

#define seii_gif "TRUST.png"
#define LIFE_gif "LIFE.png"
#define TIME_gif "TIME.png"
#define PAUSE_gif "ポーズボタン.png"
#define info_gif "情報_02_3.jpg"

#define heart_jpeg "LIFEアイコン.png"
#define spade_jpeg "TRUSTアイコン.png"

#define settoku1_gif "答え１.png"
#define settoku2_gif "答え２.png"
#define settoku3_gif "答え３.png"
#define setsumon_png "設問.png"

#define yopparai1_png "酔っ払い-座１.png"
#define yopparai2_png "酔っ払い-座２.png"
#define yopparai3_png "酔っ払い-立.png"

#define player_png "人止前.png"

#define seikai_gif "正解２.png"
#define hazure_gif "はずれ２.png"
#define doujou_gif "同情_2.jpg"

#define LIFE_MAX 20
#define START_LIFE 10
#define SEII_MAX 20
#define START_SEII 0
#define LEVEL_TIME 30
#define cleartime 60.0
#define cleartime_mod 3


#define settoku_font "Hiragino Kaku Gothic Pro"


class HelloWorld : public cocos2d::LayerColor
{
public:
    HelloWorld();
    ~HelloWorld();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool,
    // instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene(int stage_no);
    
    // a selector callback
    virtual void menuCloseCallback(cocos2d::Object* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    void spriteMoveFinished(cocos2d::Node* sender);
    
    // draw output
    void DrawScene(void);
    
    // seii output
    void SeiiOutput(void);
    
    // life output
    void lifeOutput(void);
    
    // Info output
    void InfoOutput(void);
    
    // Info output
    void settokuOutput(int ch);
    
    void changeSettoku(float dt);
    
    // Anser output
    void AnserOutput(int);
    
    void gameLogic(float dt);
    
    void updateGame(float dt);
    
    void gameClear(void);
    
    void gameOver(void);
    
    void deleteTarget(cocos2d::Sprite* target);
    
    void removeDamage(float dt);
    
    void trap(int seasons);
    
    void TouchDispatcher();
    void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch* touches, cocos2d::Event *unused_event);
    bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event *unused_event);
    void onTouchCancelled(cocos2d::Touch* touches, cocos2d::Event *unused_event);
    
    void onEnter();
    void resetMotionStreak();
    void addMotionStreakPoint(cocos2d::CCPoint point);
    
    int h_num;
    int s_num;
    bool oni_flg;
    bool hou_flg;
    bool cuv_flg;
    bool bus_flg;
    bool cd_flg;
    bool lifeup_flg;
    bool touch_flg;
    bool pause_flg;
    
    float elapsedTime; //経過時間
    
    cocos2d::UserDefault* userDefault;
    
protected:
    cocos2d::Vector<cocos2d::Sprite*> _targets;
    cocos2d::Vector<cocos2d::Sprite*> _projectiles;
    cocos2d::Sprite *player, *settoku1, *settoku2, *settoku3, *setsumon;
    
    
    int _projectilesDestroyed;
    int wind_width;
    int wind_height;
    
    void addTarget();
    
    
};

#endif  // __HELLOWORLD_SCENE_H__
