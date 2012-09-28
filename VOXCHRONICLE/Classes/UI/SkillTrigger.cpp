//
//  SkillTrigger.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include "SkillTrigger.h"

SkillTrigger* SkillTrigger::create(const char *pszFileName) {
  SkillTrigger *pobSprite = new SkillTrigger();
  if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
    pobSprite->autorelease();
    return pobSprite;
    }
  CC_SAFE_DELETE(pobSprite);
  return NULL;
}

SkillTrigger::SkillTrigger() : CCSprite() {
  _press = false;
}

SkillTrigger::~SkillTrigger() {
}

bool SkillTrigger::getPress() {
  return _press;
}

void SkillTrigger::setPress(bool press) {
  _press = press;
  if (press) {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("trigger_bg_selected.png");
    this->setTexture(texture);
  } else {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("trigger_bg.png");
    this->setTexture(texture);
  }
}

Skill* SkillTrigger::getSkill() {
  return _skill;
}

void SkillTrigger::setSkill(Skill* skill) {
  if (_skill) {
    _skill->release();
  }
  skill->retain();
  _skill = skill;
}