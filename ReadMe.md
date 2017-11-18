KeyboardMaster
==============
Visual Studio 2017


Framework project
=================
- FrameworkLib
-- Singleton
-- Observer
-- Utilities
-- States handling
-- Base game class
- FrameworkUT

Modules
=======
SoundPlayer
Rectangle
StackMenu
Animation

States
======
Simple states stack.

Games implementation as a whole could be done bin two ways:
- represented by set of 'States'
- A concrete 'Game' class implementation 
Game is a holder for concrete states which implements all the logic.

Object observer pattern implementation

KeyboardMaster will implement more than one game mechanics plus main menu functionality.
- 'Main Menu' - main menu with comments in cloud
- 'Course' - writing exercises
- 'Gallery' - reveal a picture by typing words, time
- 'Words Attack' - shot em up falling blocks, have no more lives!0
- 'Writing' - re-writing text without mistakes


Guidelines
==========
Because it's very important to be consistent.

Commit comments write as sentences.
Use camelCase.
Members function called 'on' like 'onCreated' should represent reaction on an event.
Class members should be 'named_' like this.
It's c++ so braces should be open/closed in new lines.
Game Objects - for these type of objects is acceptable to use public memebers variables.
Use structures for general pure data objects.
Remember aobut KISS, DRY, SOLID...

Settings - some of the classes needs to hold default settins. Is it strict related to objects, like default values for instances,
should be use 'static const' type. For general purpose constants to be used by one or more specific classes, constexpr variables
inside unnamed namespaces, so it is available only aroud compile unit.

TODO:
https://github.com/kubatrt/Framework/projects
