#include <iostream>
#include <cstdlib>    // For rand() and srand()
#include <ctime>      // For time()
#include <limits>     // For numeric_limits

class NumberGame {
private:
    int secretNumber;
    int minRange;
    int maxRange;
    int attempts;
    int maxAttempts;
    bool gameWon;

public:
    // Constructor
    NumberGame(int min, int max, int maxTries) : 
        minRange(min), 
        maxRange(max), 
        maxAttempts(maxTries), 
        attempts(0), 
        gameWon(false) 
    {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(0)));
        
        // Generate the random number
        secretNumber = minRange + rand() % (maxRange - minRange + 1);
    }

    // Game initialization
    void printWelcome() const {
        std::cout << "====================================\n";
        std::cout << "   WELCOME TO THE GUESSING GAME!    \n";
        std::cout << "====================================\n";
        std::cout << "I'm thinking of a number between " << minRange << " and " << maxRange << ".\n";
        std::cout << "Can you guess it in " << maxAttempts << " tries?\n\n";
    }

    // Get a valid guess from the player
    int getPlayerGuess() {
        int guess;
        bool validInput = false;
        
        do {
            std::cout << "Enter your guess (attempt " << attempts + 1 << "/" << maxAttempts << "): ";
            std::cin >> guess;
            
            // Check if input is valid
            if (std::cin.fail()) {
                std::cin.clear();  // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
                std::cout << "Invalid input. Please enter a number.\n";
            } else if (guess < minRange || guess > maxRange) {
                std::cout << "Please enter a number between " << minRange << " and " << maxRange << ".\n";
            } else {
                validInput = true;
            }
        } while (!validInput);
        
        attempts++;
        return guess;
    }

    // Process the player's guess
    void processGuess(int guess) {
        if (guess < secretNumber) {
            std::cout << "Too low! Try a higher number.\n\n";
        } else if (guess > secretNumber) {
            std::cout << "Too high! Try a lower number.\n\n";
        } else {
            std::cout << "\n🎉 CONGRATULATIONS! 🎉\n";
            std::cout << "You guessed the number in " << attempts << " attempts!\n\n";
            gameWon = true;
        }
    }

    // Check if the game is over
    bool isGameOver() const {
        return gameWon || attempts >= maxAttempts;
    }

    // Display end game message
    void displayGameResult() const {
        if (!gameWon) {
            std::cout << "Game over! You've used all your attempts.\n";
            std::cout << "The secret number was: " << secretNumber << "\n\n";
        }
        
        std::cout << "Thanks for playing!\n";
    }

    // Main game loop
    void play() {
        printWelcome();
        
        while (!isGameOver()) {
            int guess = getPlayerGuess();
            processGuess(guess);
        }
        
        displayGameResult();
    }
};

int main() {
    // Game parameters
    const int MIN_NUMBER = 1;
    const int MAX_NUMBER = 100;
    const int MAX_ATTEMPTS = 7;
    
    // Create and start the game
    NumberGame game(MIN_NUMBER, MAX_NUMBER, MAX_ATTEMPTS);
    game.play();
    
    return 0;
}