# Sliding Tiles

[![Build Status](https://travis-ci.org/richardeigenmann/SlidingTiles.svg?branch=master)](https://travis-ci.org/richardeigenmann/SlidingTiles)
[![codecov](https://codecov.io/gh/richardeigenmann/SlidingTiles/branch/master/graph/badge.svg)](https://codecov.io/gh/richardeigenmann/SlidingTiles)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7b1389d37d244865a6c12f7d028364fc)](https://www.codacy.com/app/richardeigenmann/SlidingTiles?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=richardeigenmann/SlidingTiles&amp;utm_campaign=Badge_Grade)
[![Coverity Badge](https://scan.coverity.com/projects/17624/badge.svg)](https://scan.coverity.com/projects/richardeigenmann-slidingtiles)

## Screenshot

![Screenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Screenshot.png)

## Description

This game places tiles in a grid. The blue one is a start tile and the red one is an end tile. The idea is to move the other tiles around one by one until a path is created from the start to the end.

## Keyboard shortcuts

* r - New Random Game: searches for a new game to play
* n - Next Game does a levelUp
* p - Prints the Game board
* d - Debug mode. Instructs all components to output debug information

## Objective for the author

Learn C++ game programming by building a nice little game. Along the way I have picked up and used a number of patterns, algorithms, frameworks and tools

### Patterns used in this app

* Singleton
* Observer
* Pub-Sub Messaging
* Actor
* RAII
* shared_ptr
* Unit Testing

### Algorithms

* Breadth-First-Search

### Frameworks

* CMake
* SFML
* ZeroMQ
* Google Test
* Doxygen
* TravisCI

### Features

* cross platform (sort of)
* Graphics & Sound
* Animation
* C++ 17
* Code Coverage
* Linting with clang-tidy
* Packaging with CPACK

## Build and run

### Prerequisites

Experimenting with the Windows Subsystem for Linux it transpires that the following steps need to be done (for an OpenSUSE installation)

```bash
git clone https://github.com/richardeigenmann/SlidingTiles.git
sudo zypper in cmake # for the build system
sudo zypper in sfml2-devel # to include and link SFML
sudo zypper in zeromq-devel # to include and link ZeroMQ
sudo zypper in gtest gmock gtest-devel # for the unit tests
sudo zypper in lcov # for code coverage
sudo zypper in rpm-build # for the make package target
```

```bash
cd SlidingTiles
mkdir -p build
cd build
cmake ..
# or cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ ..
# or cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++ ..
make -j$(nproc)
./sliding-tiles
```

## Explore the code with SourceTrail

See <https://sourcetrail.com>

```bash
export LANG=en_US.UTF-8
sourcetrail

# Project > New Project
# give it a name: SlidingTiles
# tell it where you want it to create it's working files
# Add Source Groups
# Pick C/C++ from Compilation Database
# select /dir/dir/SlidingTiles/build/compile_commands.json
# select the headers directory by clicking "Select from Compilation Database"
# Next > Next > Create > All files > Start > OK
# Files > main.cpp > explore!
```

## Build and run on Visual Studio 2019

Visual Studio now has support for CMake projects.

Prerequisites:

* [CMake](https://cmake.org/download)
* Git (https://git-scm.com/download/win)
* VCPKG (https://github.com/microsoft/vcpkg)

```bash
.\vcpkg.exe install sfml:x64-windows
.\vcpkg.exe install zeromq:x64-windows
.\vcpkg.exe install gtest:x64-windows
.\vcpkg integrate install
```

Open Visual Studio 2019.
File Open Filder.
Pick the folder of Sliding Tiles.
Next to the green triangle pick main.cpp
Click on the green triangle.


## Doxygen Documentation

```bash
mkdir -p build
cd build
doxygen ../Doxyfile
```

Then open the file in html/index.html in the browser
A manually compiled Doxygen build is available here: <https://richardeigenmann.github.io/SlidingTiles/doxygen/annotated.html>

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

## Linting with clang-tidy

```bash
mkdir -p build
cd build
cmake ..
make clang-tidy
```

## Notable Points

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

Without the ampersand the method returns a copy of the texture from the texturesMap (which
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

## Searching for a solution - A breadth first search

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

(From Wikipedia: <https://en.wikipedia.org/wiki/Breadth-first_search> )

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
    virtual void render() = 0;

    /**
     * @brief an enum to hold the priority of the renderable. It can be
     * Background, Normal and OnTop. This is the order in which the
     * renderables will be drawn.
     */
    enum class RenderPriority {
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

## Messaging with ZeroMQ

The early versions of the game were built on the premise that the Game class
directed the flow of events. The Game class would order a puzzle to be loaded
and would tell the WinnerBlingBling class to celebrate the win. This approach is
fine for simple applications but there are drawbacks. If something changes
you have to go back to the Game class and fix it there. A lot of code accumulates
there and you don't end up with a good "separation of concerns".

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
a ZmqSingleton ( [zmqSingleton.h](zmqSingleton.h) and
[zmqSingleton.cpp](zmqSingleton.cpp) ) where any class can call the
publish(const std::string & message) function.

ZeroMQ can transport the messages over various kinds of connection. Most common
certainly is the use of TCP sockets. But it also support In-Process connections.
For this to work, though, the zmq::context_t object must be shared. I chose to
use the ZmqSingleton as the carrier for the context object which is distributed
to any caller by means of a shared_ptr.

In the receiving classes we need to connect to the socket and check if a message
was received. The best place to review this is the DebugMessageListener class:
[debugMessageListener.h](debugMessageListener.h) and
[debugMessageListener.cpp](debugMessageListener.cpp)

```c++
// The constructor for a listener needs to bind to the ZeroMQ context and open
// a ZMQ_SUB socket which it can connect to as a tcp port, in process etc.
// It also extends the Updatable and registers there so that it gets update() callbacks.
DebugMessageListener::DebugMessageListener() {
    UpdatingSingleton::getInstance().add(*this);

    std::cout << "DebugMessageListener connecting to ZeroMQ socket: "
            << ZmqSingleton::RECEIVER_SOCKET << std::endl;
    contextPtr = ZmqSingleton::getInstance().getContext();
    socket = std::make_unique<zmq::socket_t>(*contextPtr, ZMQ_SUB);
    socket->connect(ZmqSingleton::RECEIVER_SOCKET);
    socket->setsockopt(ZMQ_SUBSCRIBE, 0, 0);
}


void DebugMessageListener::update(const float dt) {
    zmq::message_t reply;
    if (socket != nullptr && socket->recv(&reply, ZMQ_NOBLOCK)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        std::cout << "DebugMessageListener received: " << message << std::endl;
    }
}
```

The ZmqSingleton creates the context and socket as a private member variable:

```c++
std::shared_ptr<zmq::context_t> contextPtr = std::make_shared<zmq::context_t>(1);
zmq::socket_t socket{*contextPtr, ZMQ_PUB};
```

It makes the context available:

```c++
std::shared_ptr<zmq::context_t> & getContext() {
    return contextPtr;
}
```

And it facilitates publishing a message:

```c++
void ZmqSingleton::publish(const json & jsonMessage) {
    std::string message = jsonMessage.dump();
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.data(), message.size());
    socket.send(zmqMessage);
}
```

Which can be used when the game is won:

```c++
json jsonMessage{};
jsonMessage["state"] = ZmqSingleton::GAME_WON;
jsonMessage["victoryRollTime"] = VICTORY_ROLL_TIME;
jsonMessage["moves"] = moves;
jsonMessage["par"] = par;
for (const auto & solutionStep : solutionPath) {
    jsonMessage["solutionTiles"].push_back({solutionStep.x, solutionStep.y});
}
ZmqSingleton::getInstance().publish(jsonMessage);
```

## CPACK packaging to create rpm etc

```bash
cd build
make package
make package_source
```

These commands create the spec file in `build/_CPack_Packages/Linux/RPM/SPECS/sliding-tiles.spec` and then creates the rpm in `build/sliding-tiles--1.x86_64.rpm`

See this link for information about exporting your gpg key and usign it to sign the rpm. It doesn't work so well I find. <https://gist.github.com/fernandoaleman/1376720/aaff3a7a7ede636b6913f17d97e6fe39b5a79dc0>

```bash
# export your public key and import it into rpm
gpg --list-keys
gpg --export -a 'richard.eigenmann@gmail.com' > RPM-GPG-KEY-richi
sudo rpm --import RPM-GPG-KEY-richi # can generate error; doesn't seem to matter
# create a /root/.rpmmacros file
vi /root/.rpmmacros
#####
%_signature gpg
%_gpg_path /home/richi/.gnupg
%_gpg_name richard.eigenmann@gmail.com
%_gpgbin /usr/bin/gpg
#####
sudo rpm --addsign sliding-tiles--1.x86_64.rpm
# prompt for the password to the gpg store
sudo rpm -q --qf '%{SIGPGP:pgpsig} %{SIGGPG:pgpsig}\n' -p sliding-tiles--1.x86_64.rpm 
# warning: sliding-tiles--1.x86_64.rpm: Header V4 RSA/SHA256 Signature, key ID bb12f800: NOKEY
# RSA/SHA256, Tue Jul  2 23:35:59 2019, Key ID 8b118378bb12f800 (none)
```

## Testing the package on a openSUSE leap Docker container

see: <https://medium.com/@SaravSun/running-gui-applications-inside-docker-containers-83d65c0db110>
and <http://somatorio.org/en/post/running-gui-apps-with-docker>

```bash
xhost + # allow other computers to use your DISPLAY
docker run -it --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --volume /tmp/.X11-unix:/tmp/.X11-unix --volume /etc/localtime:/etc/localtime --device /dev/dri --device /dev/snd --device /dev/input --rm opensuse/leap
docker run -it --net=host --env="DISPLAY" -v /tmp/.X11-unix:/tmp/.X11-unix --device /dev/dri --device /dev/snd --device /dev/input --rm opensuse/leap

# on a different terminal find the container it
docker ps
# copy the package to the docker container
docker cp ..whereever/SlidingTiles/build/sliding-tiles--1.x86_64.rpm 8592395cb1de:/
# in the docker container:
zypper in sliding-tiles--1.x86_64.rpm
sliding-tiles

#TODO: No sound - in Debian Container there is!!

# On my Desktop -- doesn't work yet
zypper addrepo --refresh https://download.nvidia.com/opensuse/tumbleweed NVIDIA
zypper in x11-video-nvidiaG05
```

## Testing the package on a Debian Docker container

```bash
xhost + # allow other computers to use your DISPLAY
docker run -it --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --device /dev/dri --device /dev/snd --device /dev/input --rm debian:latest
docker run -it --net=host --env="DISPLAY" -v /tmp/.X11-unix:/tmp/.X11-unix --device /dev/dri --device /dev/snd --device /dev/input --rm debian:latest

apt-get update
apt-cache search x11-apps
apt-get install x11-apps

# on a different terminal find the container it
docker ps
# copy the package to the docker container
docker cp ..whereever/SlidingTiles/build/sliding-tiles--1.x86_64.deb c4844955c251:/
# in the docker container:
apt-get update
apt-get install ./sliding-tiles--1.x86_64.deb

sliding-tiles
```

## Copyright information

This project is copyrighted by Richard Eigenmann, Zürich, 2016,2020. I have not yet
decided on a license. Please contact me with any questions.

The source includes a copy of JSON for Modern C++ from Niels Lohmann [GitHub](https://github.com/nlohmann/json) This is MIT licenced.

Trophy Clipart from <http://www.clipartbest.com/clipart-aieonzEzT>

Undo Button from <http://www.clipartbest.com/clipart-nTX8LaxKc>

The buttons were created by <https://dabuttonfactory.com/>

The Raleway font is a Google Font with Open Font License: <https://fonts.google.com/specimen/Raleway>

The tiles were drawn by Richard Eigenmann using Blender.

The Over Par Clipart is from <https://pixabay.com/vectors/smiley-emoticon-smilies-emotion-150837/>
The license is <https://pixabay.com/service/license/>
