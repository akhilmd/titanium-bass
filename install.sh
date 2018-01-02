#!/bin/sh

apt-get update
apt-get install gcc -y 
apt-get install g++ -y
apt-get install libboost-all-dev -y
apt-get install libreadline6 libreadline6-dev -y
apt-get install python3-pandas -y
# apt-get install clang # Optional and will be prompted


# TODO

# if ! [ -x "$(command -v gcc)" ]; then
  # echo 'Error: gcc is not installed.' >&2
# fi

# if ! [ -x "$(command -v g++)" ]; then
  # echo 'Error: g++ is not installed.' >&2
# fi

# if ! [ -x "$(dpkg -s libboost-dev | grep 'Version')" ]; then
  # echo 'Error: boost is not installed.' >&2
# fi

# if ! [ -x "$(python3 -m pip freeze | grep pandas)" ]; then
  # echo 'Error: pandas is not installed.' >&2
# fi

