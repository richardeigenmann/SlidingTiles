# Sliding Tiles

[![Build Status](https://travis-ci.org/richardeigenmann/SlidingTiles.svg?branch=master)](https://travis-ci.org/richardeigenmann/SlidingTiles)
[![codecov](https://codecov.io/gh/richardeigenmann/SlidingTiles/branch/master/graph/badge.svg)](https://codecov.io/gh/richardeigenmann/SlidingTiles)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7b1389d37d244865a6c12f7d028364fc)](https://www.codacy.com/app/richardeigenmann/SlidingTiles?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=richardeigenmann/SlidingTiles&amp;utm_campaign=Badge_Grade)

## Screenshot
![Screenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Screenshot.png)

## Description:
This program creates a window and places tiles in a grid.
The tiles can be slid around by dragging the mouse.
When the start and end tile match up in a path you win.


## Build and run
```bash
mkdir -p build
cd build
cmake .. 
# or cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang .. 
# or cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++-6 -DCMAKE_CC_COMPILER=/usr/bin/gcc .. 
make
./sliding-tiles
```

## Build and run on Visual Studio 2017

Currently broken because of broken UTF-8 support

This is a CMake project. That means that we let CMake create the solution files in the build directory from the CMakeLists.txt file

You need to install
* [CMake](https://cmake.org/download)
* [Python 2.x, not 3.x](https://www.python.org/downloads/release)
* [SFML](https://www.sfml-dev.org/download.php)
* [Visual Studio 2017](https://www.visualstudio.com/downloads)

On windows there is no standard place that SFML goes. So you need to tell CMake in the CMakeLists.txt file where it is. Edit this file and adjust the SFML_ROOT delcaration on line 6.

Then open the CMake GUI. It wants to know "Where is the source code:". Give it the sliding-tiles root directory.
It also wants to know the build directory. Create a build subdirectory and point the gui at that.

Click the Configure button. If you do this the first time it will ask you for the generator. Pick the Visual Sutdio 15 2017 Win64 generator. Be sure to pick a 64 bit generator if you downloaded the 64 bit SFML library! You could end up with an unhelpful linker error saying it doesn't like x86 in a x64 project.

![CMakeScreenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/cmake.png)

Then click Generate to create the sliding-tiles.sln solution file along with lots of other stuff in the sliding-tiles/build directory. Open this with Visual Studio 2017 by clicking "Open Project".

To build the software click Build > Build Solution from the menu. (Be sure not to have the game open or the build will fail to overwrite the exe file "LINK1168: Cannot open ... for writing".)

You should now have a sliding-tiles.exe file in the sliding-tiles/build/Debug directory. You can run it from that directory or start it with the debugger (green triangle or F5).

To run the unit tests. Right click in the Solution Explorer on "unit-tests" and pick "Set as StartUp project". Now you can run them without the debugger by pressing Ctrl-F5 or perhaps with the debugger by pressing F5 (but the terminal window closes on you then).

## Doxygen Documentation
```bash
mkdir -p build
cd build
doxygen ../Doxyfile
```

Then open the file in html/index.html in the browser


## Testing
```bash
mkdir -p build
cd build
cmake ..
make
make test
# or
./unit-tests
```

## Code Coverage
To generate code coverage reports from the unit tests run the below steps.
The CodeCoverage.cmake file used gcov from the gcc installation and lcov
which has to be installed separately to generate an html coverage report.

```bash
mkdir -p build
cd build
cmake ..
make
make sliding-tiles_coverage
# open the file coverage/index.html with a browser
```
## Notable Points:

### Segfault on textures
What's the difference between

```c++
sf::Texture & getTexture(const TileType & tileType) {
    return texturesMap[tileType];
};
```

And this?
```c++
sf::Texture getTexture(const TileType & tileType) {
    return texturesMap[tileType];
};
```

And what kind of difference could it possibly make to this code?
```c++
void TileView::render() {
    sf::Sprite sprite;
    sprite.setTexture(TexturesSingleton::getInstance().getTexture(tileType));
    sprite.setPosition(renderPosition.x, renderPosition.y);
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}
```

Turns out a huge difference: The difference is that easy-to-overlook little
ampersand in the return value declaration of the getTexture method.

Without the
ampersand the method returns a copy of the texture from the texturesMap (which
exists only once in the singleton). Whilst perhaps not optimally efficient
why should this be a problem? After all, the texture exists till the closing
brace in the render method. A few hundred segfaults later my suspicion is that
the draw method goes off into some asynchronous heaven and by the time it gets
round to picking up the texture the closing brace has come along and wiped the
texture off the stack and we get a segfault.

By adding the ampersand the getTexture method returns a reference to the texture
in the map. This is also on the stack but the texturesMap is a long living object
in the singleton so it does not go away and any delayed draw can happily access
it.


### Searching for a solution - A breadth first search!

For a human it is easy to see how to solve this puzzle:

![Solver1](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/solver1.png)
![Solver2](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/solver2.png)
![Solver3](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/solver3.png)

To solve programatically we can take a brute-force approach: Start with the puzzle
and figure out all possible moves that can be made by the tiles. In this puzzle
there is only one tile that can move (start and end tiles are fixed). It can
move in 4 directions.

If the tile moves to the right on the next move it can still move 3 ways. Note that
moving back is not desirable so we will only consider 3 potential moves.

If the tile moves to the right once more then it has no more future moves. In this
situation that is OK because the puzzle has been solved.

This making-a-move and then having multiple next moves can be expressed as a tree:

![Level1](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Level1.png)

We can visit each node and see if there are new moves (excluding the go back move):

![Level2](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Level2.png)

As we go n-deep the number of nodes increases. I'm sure there is some optimisation
that could be applied to prevent tiles moving round in circles. But we are on the
brute-force approach here...

![Level4](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Level4.png)

Which path is the fastest one that leads to a solved puzzle? Enter the breadth-first
search:

![Breadth-First-Search](https://upload.wikimedia.org/wikipedia/commons/5/5d/Breadth-First-Search-Algorithm.gif)

(From Wikipedia: https://en.wikipedia.org/wiki/Breadth-first_search )

Here is "my" code to find the shortest solution path:
```c++
bool PuzzleSolver::hasASolution(const MoveNode & node) {
    // inspired by https://gist.github.com/douglas-vaz/5072998
    std::queue<MoveNode> Q;
    Q.push(node);
    while (!Q.empty()) {
        MoveNode t = Q.front();
        Q.pop();
        gameBoard.loadGame(t.endingBoard);
        if (gameBoard.isSolved().size() > 0) {
            return true;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    return false;
}
```

I was impressed with the queue approach which avoids a recursive call. The method
places the root node on the queue and then reads nodes off the front of the queue.
If the endboard of the move isn't a solved puzzle the method looks for the
child moves and adds them at the end of the queue. This way first all the level 1
nodes are visited before the level 2 nodes are checked and so on.


## Rendering with a Rendering Singleton where Renderables register themselves

The SFML documentation suggests that you use this code to draw a window. Note
how the loop in the main method clears the canvas then draws the various objects
and then displays the window. This means that the main loop needs to know about
everything that is going on in the game and needs to keep track of it's state
so it can decide what to draw. For instance you would not want to draw the victory 
roll banner while the game is still playing.

```c++
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cute_image.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("nice_music.ogg"))
        return EXIT_FAILURE;
    // Play the music
    music.play();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
```

I didn't like my code after a few hundred lines. Can't we do better?

I chose to create an object that knows which objects can be rendered and then
calls them in the correct Z-order. Thus when the renderable objects are created
they register themselves with the renderer during object construction and 
de-register themselves when they get destructed.

So we need a class with a pure virtual function that the renderable objects can 
inherit and add their draw function to:

```c++
class Renderable {
public:
    /**
     * @brief Implementing classes must define the render method
     */
    virtual void render() = 0;

    /**
     * @brief an enum to hold the priority of the renderable. It can be
     * Background, Normal and OnTop. This is the order in which the
     * renderables will be drawn.
     */
    enum RenderPriority {
        Background,
        Normal,
        OnTop
    };


    /**
      * Inheriting classes can override this function to change the priority.
      * @return The RenderPriority enum value
      */
    virtual RenderPriority getRenderPriority() {
        return RenderPriority::Normal;
    }
};
```

Next we need the Rendering Singleton. We use the Observer pattern and kill off 
the default constructors so that you can only call the static getInstance() 
method which will create the exactly one instance and return it.

```c++
class RenderingSingleton {
public:
    /**
     * @brief Deleted to enforce singleton pattern
     */
    RenderingSingleton(RenderingSingleton const&) = delete;

    /**
     * @brief Deleted to enforce singleton pattern
     */
    void operator=(RenderingSingleton const&) = delete;

    /**
     * @brief returns the single instance of the RenderingSingleton
     */
    static RenderingSingleton& getInstance() {
        static RenderingSingleton instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
private:
    /**
     * @brief Private constructor for singleton
     */
    RenderingSingleton();
};
```

Next our RenderingSingleton needs to allow Renderables to register and deregister 
themselves. Following an example of the Observer pattern we use a std::map
to hold the references to the Renderables.

```c++
/**
 * @brief The map of Renderables
 */
std::map<Renderable * const, Renderable * const> renderables;

/**
 * Add a Renderable to the list of object to render
 * @param renderable The Renderable to add
 */
void add(Renderable& renderable) {
    renderables.insert(std::pair<Renderable * const, Renderable * const>(&renderable, &renderable));
}

/**
 * Removes a renderable from the list of objects to render
 * @param renderable The Renderable to remove
 */
void remove(Renderable& renderable) {
    renderables.erase(&renderable);
}
```

And finally our RenderingSingleton needs to call each registered Renderables to
ask it to render itself.

```c++
/**
 * Tell all renderables to render
 */
void renderAll() {
    for (auto& pair : renderables) {
        if (pair.second->getRenderPriority() == Renderable::RenderPriority::Background) {
            pair.second->render();
        }
    }
    for (auto& pair : renderables) {
        if (pair.second->getRenderPriority() == Renderable::RenderPriority::Normal) {
            pair.second->render();
        }
    }
    for (auto& pair : renderables) {
        if (pair.second->getRenderPriority() == Renderable::RenderPriority::OnTop) {
            pair.second->render();
        }
    }
    getRenderWindow()->display();
}
```

Now classes like Button can inherit from Renderable and can register themselves 
with the Rendering Singleton upon creation. The render() method is called by
the RenderingSingleton at the right time when the button needs to be drawn,

```c++
class Button : public Renderable ...

Button::Button() {
    RenderingSingleton::getInstance().add(*this);
}

~Button() {
    RenderingSingleton::getInstance().remove(*this);
}

void render() {
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}
```

Check out the whole implementation of the RenderingSingleton in the 
[renderingSingleton.h](renderingSingleton.h) and 
[renderingSingleton.cpp](renderingSingleton.cpp) files.


The same concept is used for the update cycle. Check out the whole implementation 
of the UpdatingSingleton in the 
[updatingSingleton.h](updatingSingleton.h) and 
[updatingSingleton.cpp](updatingSingleton.cpp) and [updatable.h](updatable.h) 
files.



## Messaging

The early versions of the game were built on the premise that the Game class
directed the flow of events. The Game class would order a puzzle to be loaded
and would tell the WinnerBlingBling class to celebrate the win. This approach is
fine for simple applications but there are drawbacks. If something changes 
you have to go back to the Game class and fix it there for instance.

A more modern design uses loose coupling where the various objects don't know or
care about the bigger picture. They just listen out for things they are concerned
with and react accordingly. I.e. the WinnerBlingBling class only needs to know
that the game was won and can start the merriment.

ZeroMQ is a fast versatile messaging library that lets us implement the pub-sub
publisher - subscriber pattern. This allows a publisher to broadcast messages
that the subscribers receive and can act upon.

I have chosen to use JSON as a format for my messages as the game already links
to Niels Lohmann's library and JSON is a nice versatile format. Obviously the 
serialisation and deserialisation comes at a cost so this approach might not work
in all cases.

The game probably has multiple places that need to send messages so I created
a PublishingSingleton ( [publishingSingleton.h](publishingSingleton.h) and 
[publishingSingleton.cpp](publishingSingleton.cpp) ) where any class can call the 
publish(const std::string & message) function.

In the receiving classes we need to connect to the socket and check if a message
was received:

```c++
// need the context and socket defined on the class
zmq::context_t context{1};
zmq::socket_t socket{context, ZMQ_SUB};

// This happens in the constructor:
socket.connect("tcp://localhost:64123");
socket.setsockopt(ZMQ_SUBSCRIBE, 0, 0);

// Here we receive the message:
 zmq::message_t reply;
 if (socket.recv(&reply, ZMQ_NOBLOCK)) {
    std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
    auto j = json::parse(message);
    std::string state = j["state"].get<std::string>();
    if (state == PublishingSingleton::GAME_WON) 
        ...
}
```



## Copyright information
This project is copyrighted by Richard Eigenmann, Zürich, 2016,2017. I have not yet
decided on a license. Please contact me with any questions.

The source includes a copy of JSON for Modern C++ from Niels Lohmann [GitHub](https://github.com/nlohmann/json) This is MIT licenced.

Trophy Clipart from http://www.clipartbest.com/clipart-aieonzEzT

The buttons were created by https://dabuttonfactory.com/

The Raleway font is a Google Font with Open Font License: https://fonts.google.com/specimen/Raleway

The tiles were drawn by Richard Eigenmann using Blender.