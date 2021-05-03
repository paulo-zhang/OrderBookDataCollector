# OrderBookDataCollector

## Compile Project:

Install OpenSSL: $sudo apt-get install libssl-dev

Install boost: $sudo apt-get install libboost-all-dev

Clone nlohmann json, put nlohmann/single_include/nlohmann into ThirdParties:
https://github.com/nlohmann/json

Download asio-1.18.1, put asio-1.18.1/include into ThirdParties and change name to asio-1.18.1:
https://udomain.dl.sourceforge.net/project/asio/asio/1.18.1%20%28Stable%29/asio-1.18.1.tar.gz

Clone websocketpp, put websocketpp/websocketpp into ThirdParties:
https://github.com/zaphoyd/websocketpp 

VS Code Command Pallete: CMake:Build.

## Install storage support
### Install Docker
https://docs.docker.com/engine/install/ubuntu/

### Install Redis
$sudo docker run -d -p 63790:6379 --name enjoy-redis redis:latest

### Install MongoDB
$sudo docker run -d -p 27170-27172:27017-27019 --name mongodb mongo:latest
