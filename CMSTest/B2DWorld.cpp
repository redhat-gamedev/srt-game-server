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
    gravity = new b2Vec2(0.0f, -9.81f);    
    world = new b2World(*gravity);
    
    // As per https://developer.valvesoftware.com/wiki/Source_Multiplayer_Networking
    // resulting in 15ms per timeStep or tick
	timeStep = 1.0f / 66.0f;
    
	velocityIterations = 6;
	positionIterations = 2;
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
	groundBodyDef.position.Set(0.0f, -10.0f);
    
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
    groundBody = world->CreateBody(&groundBodyDef);
    
	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);
    
	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 40.0f);
    body = world->CreateBody(&bodyDef);
    
	// Define another box shape for our dynamic body.
	dynamicBox.SetAsBox(1.0f, 1.0f);
    
	// Define the dynamic body fixture.
	fixtureDef.shape = &dynamicBox;
    
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.3f;
	body->CreateFixture(&fixtureDef);
}

void B2DWorld::Update(std::string& strText)
{
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world->Step(timeStep, velocityIterations, positionIterations);
    
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
