#include "Observer2.hpp"

#include <algorithm>

namespace KM
{

void Subject::registerObserver(ObservedPtr object)
{
    //list.push_back( std::move(object));
}

void Subject::unregisterObserver(ObservedPtr object)
{
    list.erase(std::remove(list.begin(), list.end(), object), list.end());
}

void Subject::notify(int value)
{
    for (std::vector<ObservedPtr>::const_iterator it = list.begin(); it != list.end(); ++it)
    {
        if (*it != nullptr)
            (*it)->notify(); // value
    }
}

}