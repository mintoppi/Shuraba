//
//  GuiUtil.hpp
//  FirstGame
//
//  Created by Tetsuya on 2016/11/02.
//
//

#ifndef GuiUtil_hpp
#define GuiUtil_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

/**
 * 関数ポインターの型名の宣言
 *   CCObject のメソッドであり、
 *   void 型を返し、
 *   CCObject* を引数として受け取る関数ポインターを、
 *   SEL_MySelector という型名で扱う
 */
typedef void (cocos2d::CCObject::* SEL_MySelector)(cocos2d::CCObject*);

/**
 * 関数ポインターを取得するマクロの宣言
 *   my_selector("関数名") と記述した場合に、
 *   指定した関数のポインターを SEL_MySelector 型のポインターとして扱う
 */
#define my_selector(_SELECTOR) (SEL_MySelector)(&_SELECTOR)

class GuiUtilLayer : public cocos2d::LayerColor
{
public:
    GuiUtilLayer():_label(NULL) {};
    virtual ~GuiUtilLayer();
    bool init();
    void createGuit();
    void updateGame2(float dt);
    bool setNode(Node* tNode);
    void addSprite(const std::string);
    void addSprite(const std::string, float);
    void addSprite(const std::string filename, cocos2d::Point point);
    void addSprite(const std::string filename, const std::string filename2, cocos2d::Point point, std::function<void(Ref*)> callback);
    CREATE_FUNC(GuiUtilLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, _label, Label);
    
};

class GuiUtilScene : public cocos2d::Scene
{
public:
    GuiUtilScene():_layer(NULL) {};
    ~GuiUtilScene();
    bool init();
    CREATE_FUNC(GuiUtilScene);
    
    CC_SYNTHESIZE_READONLY(GuiUtilLayer*, _layer, Layer);
};
#endif /* GuiUtil_hpp */
