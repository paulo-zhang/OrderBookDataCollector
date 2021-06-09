# OrderBookDataCollector
## A Complete Guide For Object Oriented Programming Using C++ 17 & VS Code CMake on Linux.
Continue updating ...

## Requirement
* Connect to Binance Websocket api(document: https://github.com/binance/binance-spot-api-docs/blob/master/web-socket-streams.md#how-to-manage-a-local-order-book-correctly)
* Receive order book data with real-time connection (Websocket);
* Save data to Redis & MongoDB asynchronously.

## OOP Explanation

### Coding convention

Java & C# are relatively new languages compared to C++ or C, and they are more 'OOP friendly'.

Here, I borrowed some good coding practice from Java/C#:

* Name variables clearly, use full words instead of abbreviations.

* Use Pascal naming convention for type definition names(class, struct, enum etc), method names, public variables; Use camel naming convention for private variables, parameters, local variables etc.

* Use nested namespaces, and make sure the namespaces are according to folder names.

* All classes, structs, enum (practically all function code) ..., must be written inside namespaces.

### Interfaces in C++

Unlike C#, there is no interface in C++, in order to achieve such abstraction I use pure virtual classes to declare interface like method signatures.

### SOLID Principles
Single Responsibility: 
Keep in mind the SOLID principles. Make sure every class does only highly related things, and one method does one thing only. If a method is over 50 lines, it may be too chubby, try make it slimmer by splitting into methods. If a class is bigger than 500 lines, we may need to review to class and consider dividing it into smaller ones. Make sure it is high cohesion within one class, and low coupling between any two classes(see Inversion of Control).

As we can see both MongoDB and Redis modules implement the same interface, the caller (Platform here) doesn't need to know about the concrete implementation, only call the method through interfaces. This is call 'Inversion of Control', depend on interfaces instead of concrete classes.

### Dependency Injection (DI)

Inject IDataFeedContext object to DataFeed implementation to allow call back notifications.

Inject IStorage objects & IDataFeed objects using service locator.

Inject serviceLocators into PlatformService, so it only depends on interfaces instead of concrete implementations.

(To be implemented) Test PlatformService with Mock dependencies.

## Class diagram

As we can see the main library PlatformService, which start all functions, has no dependent to any concrete storages or datafeeds. It only depends on interfaces (pure virtual classes) IStorage and IDataFeed, actually it doesn't even know the existence of RedisStorage, MongoDBStorage and BinanceDataFeed, which makes it totally testable. We can create a mock storage and a mock datafeed to test Platform.

![Class diagram](images/Class%20design.png)

## Testability Explanation

Testability is achieved by reducing the coupling among modules. 

The concept Inversion of Control (IoC) from SOLID is the best tool to reduce coupling.

When the dependencies are interfaces, we can easily inject mock implementations to test the modules (Example here will be Platform library ...).

### TDD

Writing test code before any implementation is possible once the interfaces are defined.

In this project, when we finish writing the interfaces in Common, we can start writing unit test code for some modules even before it's implemented.

### GoogleTest

A great unit test framework to test C++ projects.

https://github.com/google/googletest

## Finally, run the project

![Execution result](images/Execute%20results.png)

## Install Storage Support

### Install Docker

https://docs.docker.com/engine/install/ubuntu/

### Install Redis

`$sudo docker run -d -p 63790:6379 --name enjoy-redis redis:latest`


Install redis-cli(Optional): 

https://codewithhugo.com/install-just-redis-cli-on-ubuntu-debian-jessie/


### Install MongoDB

`$sudo docker run -d -p 27170-27172:27017-27019 --name mongodb mongo:latest`

## Compile Project

VS Code: https://code.visualstudio.com/docs/cpp/CMake-linux

Install OpenSSL: 
`$sudo apt-get install libssl-dev`


Install boost: 
`$sudo apt-get install libboost-all-dev`


Clone nlohmann json, put nlohmann/single_include/nlohmann into ThirdParties:

`$git clone https://github.com/nlohmann/json`

`$cp -a json/single_include/nlohmann ~/Code/OrderBookDataCollector/ThirdParties`


Download asio-1.18.1, put asio-1.18.1/include into ThirdParties and change name to asio-1.18.1:

`$wget https://udomain.dl.sourceforge.net/project/asio/asio/1.18.1%20%28Stable%29/asio-1.18.1.tar.gz`

`tar -xf asio-1.18.1.tar.gz`

`cp -a asio-1.18.1/include ~/Code/OrderBookDataCollector/ThirdParties`

`sudo mv ~/Code/OrderBookDataCollector/ThirdParties/include ~/Code/OrderBookDataCollector/ThirdParties/asio-1.18.1`

Clone websocketpp, put websocketpp/websocketpp into ThirdParties:

`$git clone https://github.com/zaphoyd/websocketpp`

`$cp -a websocketpp/websocketpp ~/Code/OrderBookDataCollector/ThirdParties`


Install Redis plus plus support:

`$sudo apt install cmake`

`$sudo apt-get install -y build-essential`

https://github.com/sewenew/redis-plus-plus#installation

`$git clone https://github.com/redis/hiredis.git`

`$cd hiredis && make && sudo make install && cd ..`


`$git clone https://github.com/sewenew/redis-plus-plus.git`

`$cd redis-plus-plus && mkdir build && cd build && cmake .. && make && sudo make install cd ../..`

Install MongoDB driver: 

Installing the current release of the MongoDB C Driver (libmongoc) and BSON library (libbson): 

http://mongoc.org/libmongoc/1.17.5/installing.html

Install mongocxx-driver: 

http://mongocxx.org/mongocxx-v3/installation/linux/#step-3-download-the-latest-version-of-the-mongocxx-driver

Include CPPServiceLocator:

`$git clone https://github.com/stevef51/CPPServiceLocator.git`

`$mv CPPServiceLocator ~/Code/OrderBookDataCollector/ThirdParties/`

VS Code Command Palette: 

`$CMake: Build`

`$CMake: Debug`


