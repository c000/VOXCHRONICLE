#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "LogoScene.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
  // fixed me
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
  // end simple audio engine here, or it may crashed on win32
  SimpleAudioEngine::sharedEngine()->end();
  CCScriptEngineManager::purgeSharedManager();
}

bool AppDelegate::applicationDidFinishLaunching()
{
  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
  
  // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
  // pDirector->enableRetinaDisplay(true);
  
  // turn on display FPS
  pDirector->setDisplayStats(true);
  
  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);
  
  // create a scene. it's an autorelease object
  CCScene *pScene = LogoScene::scene();
  
  // run
  pDirector->runWithScene(pScene);
  
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
  CCDirector::sharedDirector()->stopAnimation();
  
  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
  CCDirector::sharedDirector()->startAnimation();
  
  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
