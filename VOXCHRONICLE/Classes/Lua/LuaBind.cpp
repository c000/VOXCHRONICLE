//
//  LuaBind.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#include "LuaBind.h"
#include "LuaCocos2d.h"
#include "Skill.h"
#include "Enemy.h"
#include "CharacterManager.h"

static void tolua_reg_types (lua_State* tolua_S) {
  tolua_usertype(tolua_S, "Skill");
  tolua_usertype(tolua_S, "Enemy");
  tolua_usertype(tolua_S, "CharacterManager");
}

static int tolua_VC_Enemy_getRow(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  float tolua_ret = (float)  self->getRow();
  tolua_pushnumber(tolua_S, (float)tolua_ret);
  return 1;
}

static int tolua_VC_Enemy_moveRow(lua_State* tolua_S) {
  Enemy* self = (Enemy*)tolua_tousertype(tolua_S, 1, 0);
  float row = (float)tolua_tonumber(tolua_S, 2, 0);
  self->moveRow(row);
  return 0;
}

static int tolua_VC_Enemy_setRow(lua_State* tolua_S) {
  Enemy* self = (Enemy*)tolua_tousertype(tolua_S, 1, 0);
  float row = (float)tolua_tonumber(tolua_S, 2, 0);
  self->setRow(row);
  return 0;
}

static int tolua_VC_CharacterManager_setShield(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  bool shield = (bool)tolua_tonumber(tolua_S, 2, 0);
  self->setShield(shield);
  return 0;
}

static int tolua_VC_CharacterManager_changeCharacter(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  self->changeCharacter();
  return 0;
}

static int tolua_VC_CharacterManager_addTension(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int tension = (int)tolua_tonumber(tolua_S, 2, 0);
  self->addTension(tension);
  return 0;
}

static int tolua_VC_CharacterManager_getLevel(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int level = (int)self->getLevel();
  tolua_pushnumber(tolua_S, (int)level);
  return 1;
}

static int tolua_VC_CharacterManager_setLevel(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int level = (int)tolua_tonumber(tolua_S, 2, 0);
  self->setLevel(level);
  return 0;
}

static int tolua_VC_CharacterManager_cureHP(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int hp = (int)tolua_tonumber(tolua_S, 2, 0);
  int newHP = self->cureHP(hp);
  tolua_pushnumber(tolua_S, newHP);
  return 1;
}

TOLUA_API int tolua_voxchronicle_open(lua_State* tolua_S) {
  tolua_open(tolua_S);
  tolua_reg_types(tolua_S);
  tolua_module(tolua_S, NULL, 0);
  tolua_beginmodule(tolua_S, NULL);
  tolua_constant(tolua_S, "MAX_ROW", MAX_ROW);
  tolua_constant(tolua_S, "SkillRangeSingle", SkillRangeSingle);
  tolua_constant(tolua_S, "SkillRangeAll", SkillRangeAll);
  tolua_constant(tolua_S, "SkillRangeHorizontal", SkillRangeHorizontal);
  tolua_constant(tolua_S, "SkillRangeVertical", SkillRangeVertical);
  tolua_constant(tolua_S, "SkillRangeBack", SkillRangeBack);
  tolua_constant(tolua_S, "SkillRangeSelf", SkillRangeSelf);
  tolua_constant(tolua_S, "SkillTypeNone", SkillTypeNone);
  tolua_constant(tolua_S, "SkillTypeNormal", SkillTypeNormal);
  tolua_constant(tolua_S, "SkillTypePhysical", SkillTypePhysical);
  tolua_constant(tolua_S, "SkillTypeMagical", SkillTypeMagical);
  tolua_beginmodule(tolua_S, "Skill");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S, "Enemy", "Enemy", "CCSprite", NULL);
  tolua_beginmodule(tolua_S, "Enemy");
  tolua_function(tolua_S, "getRow", tolua_VC_Enemy_getRow);
  tolua_function(tolua_S, "moveRow", tolua_VC_Enemy_moveRow);
  tolua_function(tolua_S, "setRow", tolua_VC_Enemy_setRow);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S, "CharacterManager", "CharacterManager", "CCObject", NULL);
  tolua_beginmodule(tolua_S, "CharacterManager");
  tolua_function(tolua_S, "setShield", tolua_VC_CharacterManager_setShield);
  tolua_function(tolua_S, "addTension", tolua_VC_CharacterManager_addTension);
  tolua_function(tolua_S, "changeCharacter", tolua_VC_CharacterManager_changeCharacter);
  tolua_function(tolua_S, "setLevel", tolua_VC_CharacterManager_setLevel);
  tolua_function(tolua_S, "getLevel", tolua_VC_CharacterManager_getLevel);
  tolua_function(tolua_S, "cureHP", tolua_VC_CharacterManager_cureHP);
  tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  return 1;
}