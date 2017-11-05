KeyboardMaster project
======================

Framework project
- FrameworkLib
-- Singleton
-- Observer
-- Utilities
-- States handling
-- Base game class
- FrameworkUT



Games implementation as a whole could be done bin two ways:
- represented by set of 'States'
- A concrete 'Game' class implementation 

Should be considered as KM will implement more than one game mechanics plus menu functionality
- Menu 
- 'Course' Game
- 'Gallery' Game
- 'Words Attack' Game


Guidelines:

Members function called 'on' like 'onCreated' should represent reaction on an event.

Game Objects - for these type of objects is acceptable to use public memebers variables.

Settings - some of the classes needs to hold default settins. Is it strict related to objects, like default values for instances,
should be use 'static const' type. For general purpose constants to be used by one or more specific classes, constexpr variables
inside unnamed namespaces, so it is available only aroud compile unit.

TODO:
https://github.com/kubatrt/Framework/projects