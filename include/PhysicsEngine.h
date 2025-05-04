#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <Box2D/Box2D.h>
#include <memory>

// Forward declarations
class Player;
class Ball;

class PhysicsEngine {
public:
    // Constructor & Destructor
    PhysicsEngine();
    ~PhysicsEngine();
    
    // Main update function
    void update(float deltaTime);
    
    // Body creation methods
    b2Body* createPlayerBody(float x, float y, bool isAttacker);
    b2Body* createBallBody(float x, float y);
    b2Body* createPitchBoundary();
    
private:
    b2Vec2 gravity;
    b2World world;
    
    // Contact listener for collision detection
    class ContactListener : public b2ContactListener {
    public:
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    };
    
    ContactListener contactListener;
};

#endif // PHYSICS_ENGINE_H