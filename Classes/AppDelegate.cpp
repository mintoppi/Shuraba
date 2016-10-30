#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "StartMenu.h"
#include "TitleMenu.h"

USING_NS_CC;


AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director *pDirector = Director::getInstance();
    
    //pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    
    Size screenSize = Director::getInstance()->getWinSize();
    
    //Size screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    //CCLOG("+++++++screenSize %f, %f",screenSize.height, screenSize.width);
    //Size designSize = Size(640, 1136);
    std::vector<std::string> searchPaths;
    
    //searchPaths.push_back("hd");
    //searchPaths.push_back("sd");
    
    /*if (screenSize.height > 960)
    {
        CCLOG("hd");
        searchPaths.push_back("hd");
        //pDirector->setContentScaleFactor(640.0f/designSize.height);
    }
    else
    {
        CCLOG("sd");
        searchPaths.push_back("sd");
        //pDirector->setContentScaleFactor(320.0f/designSize.height);
    }*/
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    //this->CCEGLView::setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
    
    // turn on display FPS
    pDirector->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
    //Scene *pScene = StartMenuScene::create();
    Scene *pScene = TitleMenuScene::create();
    //StartScene *startScene = StartScene::create();
    
    
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
