#include "PhysicsEngine.h"
#include <iostream>

PhysicsEngine::PhysicsEngine() : gravity(0.0f, 0.0f), world(gravity) {
    // Configure Box2D world
    world.SetAllowSleeping(true);
    world.SetContinuousPhysics(true);
    
    // Set up contact listener
    world.SetContactListener(&contactListener);
    
    std::cout << "Physics engine initialized" << std::endl;
}

PhysicsEngine::~PhysicsEngine() {
    std::cout << "Physics engine shutting down" << std::endl;
}

void PhysicsEngine::update(float deltaTime) {
    // Box2D recommended: fixed time step with multiple iterations
    world.Step(deltaTime, 8, 3);
}

b2Body* PhysicsEngine::createPlayerBody(float x, float y, bool isAttacker) {
    // Define the player body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    bodyDef.fixedRotation = true; // Players don't rotate like barrels
    
    b2Body* body = world.CreateBody(&bodyDef);
    
    // Create hitbox for the player (simplified as a circle)
    b2CircleShape shape;
    shape.m_radius = 0.5f; // 0.5 meter radius
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.1f; // Low bounce
    
    body->CreateFixture(&fixtureDef);
    
    return body;
}

b2Body* PhysicsEngine::createBallBody(float x, float y) {
    // Similar implementation as in the full code...
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    
    b2Body* body = world.CreateBody(&bodyDef);
    
    b2CircleShape shape;
    shape.m_radius = 0.12f;
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.7f;
    
    body->CreateFixture(&fixtureDef);
    
    return body;
}

b2Body* PhysicsEngine::createPitchBoundary() {
    // Create the pitch boundary as a static body
    // Similar implementation as in the full code...
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0.0f, 0.0f);
    
    b2Body* body = world.CreateBody(&bodyDef);
    
    // Create boundary shape (box)
    b2ChainShape shape;
    b2Vec2 vs[4];
    vs[0].Set(-35.0f, -20.0f);
    vs[1].Set(35.0f, -20.0f);
    vs[2].Set(35.0f, 20.0f);
    vs[3].Set(-35.0f, 20.0f);
    shape.CreateLoop(vs, 4);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.3f;
    
    body->CreateFixture(&fixtureDef);
    
    return body;
}

void PhysicsEngine::ContactListener::BeginContact(b2Contact* contact) {
    // Collision detection logic
    std::cout << "Contact detected" << std::endl;
}

void PhysicsEngine::ContactListener::EndContact(b2Contact* contact) {
    // End of collision logic
}