#!/bin/bash

sudo snap install cmake --classic
sudo apt install g++ -y
sudo systemctl daemon-reload
sudo apt install git curl zip unzip tar pkg-config zlib1g-dev libssl-dev libprotobuf-c-dev libcurl4-openssl-dev libtool make -y
cd
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg install llhttp
export llhttp_DIR=$(sudo find $(sudo find / -path '*/vcpkg/installed') -name 'llhttp-config.cmake' -type f -exec dirname {} \; -quit)
echo "export llhttp_DIR=$(sudo find $(sudo find / -path '*/vcpkg/installed') -name 'llhttp-config.cmake' -type f -exec dirname {} \; -quit)" >> ~/.bashrc
cd
curl -O https://download.libsodium.org/libsodium/releases/LATEST.tar.gz
tar -xzf LATEST.tar.gz
cd libsodium-stable
./configure
make && make check
sudo make install
cd
git clone https://github.com/json-c/json-c.git
mkdir json-c-build
cd json-c-build
cmake ../json-c
make
make test
make USE_VALGRIND=0 test
sudo make install
cd
git clone https://github.com/libuv/libuv.git
cd libuv
sh autogen.sh
./configure
make
make check
sudo make install
cd $(sudo find / -path "*ZTcURL/.git" -print -quit) && cd ../ #changing back to repository's root directory
