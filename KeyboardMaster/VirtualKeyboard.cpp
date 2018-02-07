#include "VirtualKeyboard.hpp"
#include "../FrameworkLib/ResourceManager/ResourceManager.hpp"


namespace km
{

namespace
{
constexpr float row_1st = 4;
constexpr float row_2nd = 55;
constexpr float row_3rd = 107;
constexpr float row_4th = 159;
constexpr float row_5th = 210;
constexpr float OUT_OF_RANGE = 200.0f;
}

VirtualKeyboard::VirtualKeyboard(sf::Vector2u windowSize)
{
    maskPositions[KeyCode::q] = sf::Vector2f(82, row_2nd);
    maskPositions[KeyCode::w] = sf::Vector2f(134, row_2nd);
    maskPositions[KeyCode::e] = sf::Vector2f(186, row_2nd);
    maskPositions[KeyCode::r] = sf::Vector2f(238, row_2nd);
    maskPositions[KeyCode::t] = sf::Vector2f(291, row_2nd);
    maskPositions[KeyCode::y] = sf::Vector2f(343, row_2nd);
    maskPositions[KeyCode::u] = sf::Vector2f(395, row_2nd);
    maskPositions[KeyCode::i] = sf::Vector2f(447, row_2nd);
    maskPositions[KeyCode::o] = sf::Vector2f(499, row_2nd);
    maskPositions[KeyCode::p] = sf::Vector2f(551, row_2nd);
    //...
    maskPositions[KeyCode::a] = sf::Vector2f(109, row_3rd);
    maskPositions[KeyCode::s] = sf::Vector2f(161, row_3rd);
    maskPositions[KeyCode::d] = sf::Vector2f(213, row_3rd);
    maskPositions[KeyCode::f] = sf::Vector2f(266, row_3rd);
    maskPositions[KeyCode::g] = sf::Vector2f(318, row_3rd);
    maskPositions[KeyCode::h] = sf::Vector2f(370, row_3rd);
    maskPositions[KeyCode::j] = sf::Vector2f(422, row_3rd);
    maskPositions[KeyCode::k] = sf::Vector2f(474, row_3rd);
    maskPositions[KeyCode::l] = sf::Vector2f(526, row_3rd);
    maskPositions[KeyCode::semicolon] = sf::Vector2f(578, row_3rd);
    maskPositions[KeyCode::apostrophe] = sf::Vector2f(631, row_3rd);
    maskPositions[KeyCode::z] = sf::Vector2f(134, row_4th);
    maskPositions[KeyCode::x] = sf::Vector2f(186, row_4th);
    maskPositions[KeyCode::c] = sf::Vector2f(238, row_4th);
    maskPositions[KeyCode::v] = sf::Vector2f(290, row_4th);
    maskPositions[KeyCode::b] = sf::Vector2f(343, row_4th);
    maskPositions[KeyCode::n] = sf::Vector2f(395, row_4th);
    maskPositions[KeyCode::m] = sf::Vector2f(447, row_4th);
    //...
    maskPositions[KeyCode::EOL] = sf::Vector2f(683, row_3rd);	// when EOL press "Enter"
    maskPositions[KeyCode::Space] = sf::Vector2f(238, row_5th);


    sf::Texture layoutTexture = fw::ResourceHolder::get().textures.get("kbl_48");
    layoutSprite_.setTexture(layoutTexture);
    layoutSprite_.setPosition(0.f, static_cast<float>(windowSize.y - layoutTexture.getSize().y));
    
    maskSprite_.setTexture(fw::ResourceHolder::get().textures.get("mask"));
    maskSprite_.setColor(sf::Color(255, 255, 255, 100));
}

void VirtualKeyboard::highlightLetter(int letterCode)
{
    auto search = maskPositions.find(letterCode);
    if (search != maskPositions.end())
    {
        sf::Vector2f pos = search->second;
        maskSprite_.setPosition(pos.x, pos.y + layoutSprite_.getPosition().y);
    }
    else
    {
        maskSprite_.setPosition(OUT_OF_RANGE, OUT_OF_RANGE);
    }
}

void VirtualKeyboard::update(sf::Time deltaTime)
{

}

void VirtualKeyboard::draw(sf::RenderTarget& renderer)
{
    renderer.draw(layoutSprite_);
    renderer.draw(maskSprite_);
}

}