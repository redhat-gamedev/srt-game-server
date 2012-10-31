//
//  B2DWorld.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "B2DWorld.h"


// Constructor(s)
B2DWorld::B2DWorld()
{
    // Define the size of the world. Simulation will still work
	// if bodies reach the end of the world, but it will be slower.
	//b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);
    
	// Define the gravity vector.
	//b2Vec2
    gravity = new b2Vec2(0.0f, -9.81f);
    
	// Do we want to let bodies sleep?
	bool doSleep = true;
    
	// Construct a world object, which will hold and simulate the rigid bodies.
	//b2World world
    world = new b2World(worldAABB, *gravity, doSleep);
    
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	//float32
    timeStep = 1.0f / 60.0f;
	//int32
    iterations = 10;
}

// Destructor
B2DWorld::~B2DWorld()
{
    delete gravity;
    delete world;
}

// Method(s)
void B2DWorld::CreateBodiesAndShapes()
{
    // Define the ground body.
	//b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
    
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	//b2Body*
    groundBody = world->CreateBody(&groundBodyDef);
    
	// Define the ground box shape.
	//b2PolygonDef groundShapeDef;
    
	// The extents are the half-widths of the box.
	groundShapeDef.SetAsBox(50.0f, 10.0f);
    
	// Add the ground shape to the ground body.
	groundBody->CreateShape(&groundShapeDef);
    
	// Define the dynamic body. We set its position and call the body factory.
	//b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 40.0f);
	//b2Body*
    body = world->CreateBody(&bodyDef);
    
	// Define another box shape for our dynamic body.
	//b2PolygonDef shapeDef;
	shapeDef.SetAsBox(1.0f, 1.0f);
    
	// Set the box density to be non-zero, so it will be dynamic.
	shapeDef.density = 1.0f;
    shapeDef.restitution = 0.5f;
    
	// Override the default friction.
	shapeDef.friction = 0.3f;
    
	// Add the shape to the body.
	body->CreateShape(&shapeDef);
    
	// Now tell the dynamic body to compute it's mass properties base
	// on its shape.
	body->SetMassFromShapes();
}

void B2DWorld::Update(std::string& strText)
{
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(timeStep, iterations);
    
    // Now print the position and angle of the body.
    //b2Vec2
    position = body->GetPosition();
    //float32
    angle = body->GetAngle();
    
    memset(m_szBuf, 0, sizeof(m_szBuf));
    //sprintf(m_szBuf, "%4.2f %4.2f %4.2f", position.x, position.y, angle);
    sprintf(m_szBuf, "%4.2f", position.y);
    //printf("%s\n", m_szBuf);
    strText = m_szBuf;
    
}
