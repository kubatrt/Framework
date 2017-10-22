 #pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../FrameworkLib/Util/FPSCounter.hpp"
#include "../FrameworkLib/States/StateBase.hpp"
#include "../FrameworkLib/Utilities.hpp"

namespace framework
{

class Game
{
    public:
        Game();
        ~Game();
        Game(const Game&) = delete;
        Game& operator= (const Game&) = delete;
        Game(Game&&) = delete;
        Game&& operator= (Game&&) = delete;

        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& renderer);
        int run();

        template<typename T, typename... Args>
        void pushState(Args&&... args);
        void popState();

        const sf::RenderWindow& getWindow() const;

        void close();

    private:
        void handleEvent();
        void tryPop();

        StateBase& getCurrentState(); 

        sf::RenderWindow window_;
        std::vector<std::unique_ptr<StateBase>> states_;

        FPSCounter fpsCounter_;

        bool shouldPopState_;
};

template<typename T, typename... Args>
void Game::pushState(Args&&... args)
{
    states_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

}