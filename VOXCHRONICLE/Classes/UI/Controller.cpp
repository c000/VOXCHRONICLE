//
//  Controller.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include "SimpleAudioEngine.h"

#include "Controller.h"
#include "SkillTrigger.h"

using namespace cocos2d;

bool Controller::init() {
  if (!CCLayer::init()) {
    return false;
  }
  _triggers = CCArray::create();
  _triggers->retain();
  _enable = true;
  const int rotation[] = {0, 30, 60, 0, -30, -60};
  const int x[] = {95, 235, 310, 866, 727, 651};
  const int y[] = {298.5, 207, 62, 298.5, 208, 62};
  for (int i = 0; i < 6; ++i) {
    SkillTrigger* trigger = SkillTrigger::create("trigger_bg.png");
    trigger->setPosition(ccp(x[i] / 2.0, y[i] / 2.0));
    trigger->setRotation(rotation[i]);
    if (i < 3) trigger->setScaleX(-1);
    this->addChild(trigger);
    _triggers->addObject(trigger);
    this->setTouchEnabled(true);
  }
  return true;
}

Controller::Controller() {
}

Controller::~Controller() {
  _triggers->release();
}

void Controller::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Controller::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  if (!_enable) return false;
  const CCPoint triggerCenter = ccp(50, 60);
  const int triggerRadius = 40;
  CCObject* trigger = NULL;
  CCARRAY_FOREACH(_triggers, trigger) {
    CCPoint p = ((SkillTrigger*)trigger)->convertTouchToNodeSpace(pTouch);
    if (((SkillTrigger*)trigger)->getEnable() && ccpDistance(triggerCenter, p) < triggerRadius) {
      this->resetAllTriggers();
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("decide.caf");
      ((SkillTrigger*)trigger)->setPress(true);
      break;
    }
  }
  
  return true;
}

void Controller::resetAllTriggers() {
  CCObject* trigger = NULL;
  CCARRAY_FOREACH(_triggers, trigger) {
    ((SkillTrigger*)trigger)->setPress(false);
  }
}

int Controller::currentTriggerIndex() {
  int i = 0;
  CCObject* trigger = NULL;
  CCARRAY_FOREACH(_triggers, trigger) {
    if (((SkillTrigger*)trigger)->getPress() ){
      return i;
    }
    ++i;
  }
  return -1;
}

void Controller::updateSkills(CharacterManager* manager) {
  CCArray* allSkills = manager->getCurrentCharacter()->getSkills();
  int level = manager->getLevel();
  CCArray* skills = manager->getCurrentCharacter()->getSkills(level);
  for (int i = 0; i < _triggers->count(); ++i) {
    if (i >= allSkills->count()) break;
    Skill* skill = (Skill*)allSkills->objectAtIndex(i);
    SkillTrigger* trigger = (SkillTrigger*)_triggers->objectAtIndex(i);
    trigger->setSkill(skill);
    trigger->setEnable(skills->containsObject(skill));
  }
}

Skill* Controller::currentTriggerSkill() {
  int index = this->currentTriggerIndex();
  if (index >= 0) {
    return ((SkillTrigger*)_triggers->objectAtIndex(index))->getSkill();
  }
  return NULL;
}

void Controller::setEnable(bool enable) {
  _enable = enable;
}
