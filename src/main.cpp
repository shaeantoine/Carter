#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "PhysicsEngine.h"
#include "Renderer.h"
#include "GameState.h"
#include "InputHandler.h"

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float TIMESTEP = 1.0f / 60.0f;  // Fixed timestep for physics

int main() {
    // Print startup message
    std::cout << "Starting Carter..." << std::endl;

    // Initialize window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Carter");
    window.setFramerateLimit(60);
    
    // Create core systems using smart pointers
    auto physicsEngine = std::make_shared<PhysicsEngine>();
    auto gameState = std::make_shared<GameState>();
    auto renderer = std::make_shared<Renderer>(window);
    auto inputHandler = std::make_shared<InputHandler>(window);
    
    // Initialize game state
    gameState->initialize(physicsEngine);
    
    // Setup timing variables
    sf::Clock clock;
    float accumulator = 0.0f;
    
    // Main game loop
    while (window.isOpen()) {
        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            inputHandler->handleEvent(event);
        }
        
        // Process input
        inputHandler->update(gameState);
        
        // Fixed timestep for physics
        while (accumulator >= TIMESTEP) {
            physicsEngine->update(TIMESTEP);
            gameState->update(TIMESTEP);
            accumulator -= TIMESTEP;
        }
        
        // Render the game
        window.clear(sf::Color(34, 139, 34));  // Green color for the pitch
        renderer->render(gameState);
        window.display();
    }
    
    std::cout << "Carter shutting down..." << std::endl;
    return 0;
}