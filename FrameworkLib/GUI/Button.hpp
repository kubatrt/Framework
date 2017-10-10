#pragma once

#include <functional>

#include "Widget.hpp"

namespace framework
{
namespace gui
{

typedef std::function<void(void)>	Callback;

enum class ButtonSize
{
    Small,
    Wide,
};


class Button : public Widget
{
    public:
        Button(ButtonSize s = ButtonSize::Wide);

        void setFunction(Callback func);
        void setText(const std::string& str);
        void setTexture (const sf::Texture& tex);

        void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
        void render(sf::RenderTarget& renderer) override;
        void setPosition(const sf::Vector2f& pos) override;
        sf::Vector2f getSize() const override;

    private:
        void updateText();

        sf::Vector2f m_position;

		Text m_text;
		Rectangle m_button;
		Callback m_function = [](){};
};

}
}
