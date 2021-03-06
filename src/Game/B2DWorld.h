#ifndef __SRT__B2DWorld__
#define __SRT__B2DWorld__

//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "../Shared/Types.h"
#include <box2d/box2d.h>
#include <Poco/Mutex.h>
#include <string>
#include <list>


class B2DWorld
{
    friend class AB2DEntity;
    
// Class
protected:
    static Poco::Mutex      s_aMutex;

public:
    static b2World*        s_pb2World;
    
    
// Instance
private:
    
protected:
    class _Factory
    {
        friend class B2DWorld;
        
    protected:
        // Constructor(s)
        _Factory() {};
        
        // Destructor(s)
        ~_Factory() {};

    public:
        b2Body* CreateBody(const b2BodyDef* pb2BodyDef);
        void DestroyBody(b2Body* pb2Body);
        
        b2Joint* CreateJoint(const b2JointDef* pb2JointDef);
        void DestroyJoint(b2Joint* pb2Joint);
    };
    
    b2Vec2*         gravity;
        
    float32         timeStep;// = 1.0f / 60.0f;
	int32           velocityIterations;
    int32           positionIterations;
    
    // Constructor(s)
    B2DWorld();
    
    // Destructor
    ~B2DWorld();

public:
    // Singleton(s)
    static _Factory& Factory()
    {
        static _Factory aFactory;
        return aFactory;
    }
    
    static B2DWorld& Instance()
    {
        static B2DWorld aB2DWorld;
        return aB2DWorld;
    }

    // Method(s)
    void Step();
};


#endif /* defined(__SRT__B2DWorld__) */
