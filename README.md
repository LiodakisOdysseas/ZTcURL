# **ZTcURL**

ZTcURL is a Zero-Trust Networking Architecture-embeded cli client application for allowing secure access to Fiware Orion Context Broker instances through an OpenZiti overlay network.

## **Build instructions**
--------------------------
Note: Building the application has so far been tested only on Ubuntu 24.04.1 LTS virtual machines created with [multipass](https://multipass.run/). Successful binary building on other platforms cannot thus far be guaranteed.
```
git clone https://github.com/LiodakisOdysseas/ZTcURL.git
cd ZTcURL
. dependencies-setup.sh
mkdir build && cd build
cmake ..
make
```

## **Usage**
---
```
./ZTcURL <openziti_identity_file.json>
