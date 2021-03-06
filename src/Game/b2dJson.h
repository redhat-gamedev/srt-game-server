/*
* Author: Chris Campbell - www.iforce2d.net
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2DJSON_H
#define B2DJSON_H

#include <stdio.h>
#include <map>
#include <string>
#include <box2d/box2d.h>
#include "json/json.h"

using namespace std;

class b2dJson
{
protected:
    bool m_useHumanReadableFloats;
    std::map<b2Body*,int> m_bodyIndexMap;
    std::map<b2Joint*,int> m_jointIndexMap;
    std::vector<b2Body*> m_bodies;
    std::vector<b2Joint*> m_joints;

    std::map<b2Body*,string> m_bodyToNameMap;
    std::map<b2Fixture*,string> m_fixtureToNameMap;
    std::map<b2Joint*,string> m_jointToNameMap;

public:
    //constructor
    b2dJson(bool useHumanReadableFloats = false);

    //writing functions
    std::string writeToString(b2World* world);
    void writeToFile(b2World* world, const char* filename);

    Json::Value b2j(b2World* world);
    Json::Value b2j(b2Body* body);
    Json::Value b2j(b2Fixture* fixture);
    Json::Value b2j(b2Joint* joint);

    void setBodyName(b2Body* body, const char* name);
    void setFixtureName(b2Fixture* fixture, const char* name);
    void setJointName(b2Joint* joint, const char* name);

    //reading functions
    b2World* readFromString(std::string str);
    b2World* readFromFile(const char* filename);

    b2World* j2b2World(Json::Value worldValue);
    b2Body* j2b2Body(b2World* world, Json::Value bodyValue);
    b2Fixture* j2b2Fixture(b2Body* body, Json::Value fixtureValue);
    b2Joint* j2b2Joint(b2World* world, Json::Value jointValue);

    int getBodiesByName(string name, vector<b2Body*>& bodies);
    int getFixturesByName(string name, vector<b2Fixture*>& fixtures);
    int getJointsByName(string name, vector<b2Joint*>& joints);

    b2Body* getBodyByName(string name);
    b2Fixture* getFixtureByName(string name);
    b2Joint* getJointByName(string name);

protected:
    //member helpers
    void vecToJson(const char* name, b2Vec2 vec, Json::Value& value, int index = -1);
    void floatToJson(const char* name, float f, Json::Value& value);
    int lookupBodyIndex( b2Body* body );
    int lookupJointIndex( b2Joint* joint );
    string getBodyName(b2Body* body);
    string getFixtureName(b2Fixture* fixture);
    string getJointName(b2Joint* joint);

    //static helpers
    static std::string floatToHex(float f);
    static float hexToFloat(std::string str);
    static float jsonToFloat(const char* name, Json::Value& value, float defaultValue = 0);
    static b2Vec2 jsonToVec(const char* name, Json::Value& value, int index = -1, b2Vec2 defaultValue = b2Vec2(0,0));
};

#endif // B2DJSON_H







