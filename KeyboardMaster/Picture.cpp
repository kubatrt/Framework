#include "Picture.hpp"

namespace km
{

Picture::Picture(sf::Texture texture, uint width, uint height, uint rows, uint cols)
    : dictionary_("D:/Workspace/Projects/Framework/Debug/data/words_01")  // data/words_01
    , complete_(false)
{
    std::cout << "Picture Width: " << width << " Height: " << height << std::endl;

    //texture_ = texture;
    // res/textures/obraz_1.png
    texture_.loadFromFile("D:/Workspace/Projects/Framework/Debug/res/textures/obraz_1.png");
    sprite_.setTexture(texture_);
    sprite_.setPosition(sf::Vector2f(0, 0));
    
    elementsInRow_ = rows;
    elementsInCol_ = cols;
    elementsTotal_ = elementsInRow_ * elementsInCol_;

    int picElemWidth = texture_.getSize().x / elementsInRow_;
    int picElemHeight = texture_.getSize().y / elementsInCol_;

    int index = 0;
    for (uint y = 0; y < elementsInCol_; ++y)
    {
        for (uint x = 0; x < elementsInRow_; ++x)
        {
            std::wstring word = dictionary_.getRandomWord();
            std::wcout << "Random word: " << word << std::endl;
            int picElemPositionX = x * picElemWidth;
            int picElemPositionY = y * picElemHeight;

            auto picElem = std::make_shared<PictureElement>(texture_, sf::IntRect(x * picElemWidth, y * picElemHeight, picElemWidth, picElemHeight),
                  index, word, sf::Vector2f(static_cast<float>(picElemPositionX), static_cast<float>(picElemPositionY)));
            elementsSPtr_.push_back(picElem);
            
            indexesLeft.insert(index);
            index++;
        }
    }

    init();
}

void Picture::typedWord(std::wstring typedWord)
{
    std::wcout << "Index: " << activeIndex_ << std::endl;
    if (elementsSPtr_.at(activeIndex_)->getWord() == typedWord)
    {
        elementsCorrect_++;
        elementsSPtr_.at(activeIndex_)->reveal();
    }
    else
    {
        elementsSPtr_.at(activeIndex_)->miss();
    }
    
    if(indexesLeft.size() == 0)
        complete_ = true;

    if (activeIndex_ < elementsTotal_ - 1)
    {
        activeIndex_++; // just next TODO: randomize
        elementsSPtr_.at(activeIndex_)->setActive();
        indexesLeft.erase(activeIndex_);

    }
    std::wcout << "Index end: " << activeIndex_ << std::endl;
}

bool Picture::isComplete()
{
    return complete_;
}

void Picture::init()
{
    elementsCorrect_ = 0;
    activeIndex_ = 0; // random
    elementsSPtr_.at(activeIndex_)->setActive();
    indexesLeft.erase(activeIndex_);
    
    std::wcout << "Init" << std::endl;
}

void Picture::update(sf::Time deltaTime)
{
    for (auto &element : elementsSPtr_)
    {
        element->update(deltaTime);
    }
}


void Picture::draw(sf::RenderTarget& renderer)
{
    for (auto &element : elementsSPtr_)
    {
        element->draw(renderer);
    }

    //renderer.draw(sprite_);
}

}