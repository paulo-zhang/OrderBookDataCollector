# OrderBookDataCollector
# Object Oriented Design With C++ 17

## Requirement
* Connect to Binance Websocket api(document: https://github.com/binance/binance-spot-api-docs/blob/master/web-socket-streams.md#how-to-manage-a-local-order-book-correctly)
* Receive order book data with realtime connection (Websocket);
* Save data to Redis & MongoDB asynchronously.

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

Install OpenSSL: 
`$sudo apt-get install libssl-dev`


Install boost: 
`$sudo apt-get install libboost-all-dev`


Clone nlohmann json, put nlohmann/single_include/nlohmann into ThirdParties:

`$git clone https://github.com/nlohmann/json`

`$cp -a json/single_include/nlohmann ~/Code/OrderBookDataCollector/ThirdParties`


Download asio-1.18.1, put asio-1.18.1/include into ThirdParties and change name to asio-1.18.1:

https://udomain.dl.sourceforge.net/project/asio/asio/1.18.1%20%28Stable%29/asio-1.18.1.tar.gz


Clone websocketpp, put websocketpp/websocketpp into ThirdParties:

`$git clone https://github.com/zaphoyd/websocketpp `

`$cp -a websocketpp/websocketpp ~/Code/OrderBookDataCollector/ThirdParties`


Install Redis plus plus support:

https://github.com/sewenew/redis-plus-plus#installation


Install MongoDB driver: 

Installing the current release of the MongoDB C Driver (libmongoc) and BSON library (libbson): 

http://mongoc.org/libmongoc/1.17.5/installing.html

Install mongocxx-driver: 

http://mongocxx.org/mongocxx-v3/installation/linux/#step-3-download-the-latest-version-of-the-mongocxx-driver


VS Code Command Pallete: 

`$CMake: Build`

`$CMake: Debug`


## OOD/OOP Explanation

### SOLID Principle
Single Responsibility: 
This is express everywhere in the code. Make sure every class does only highly related things, and one method does one thing only. If a method is over 50 lines, it may be too chubby, try make it slimmer by using more methods. If a class is bigger than 500 lines, we may need to review to class and consider deviding it into smaller ones. Make sure it is high cohesion within one class, and low coupling between any two classes(see Inversion of Control).

Open-Close Principle
This is not obvious in this project, but keep this in mind when you try to change the behaviour of a class.

Liskov Substitution Principle

Interface Segregation Principle

Dependency Inversion Principle (Inversion of Control (IoC))


### Dependency Injection (DI)



## Testability Explanation

### TDD

### GoogleTest



