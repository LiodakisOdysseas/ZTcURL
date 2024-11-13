# **ZTcURL**

ZTcURL is a Zero-Trust Networking Architecture-embedded command line client application that utilizes [curl](https://curl.se/)'s [libcurl()](https://curl.se/libcurl/) library and [OpenZiti-C SDK](https://github.com/openziti/ziti-sdk-c) to allow secure, authenticated access to [Fiware Orion Context Broker](https://github.com/telefonicaid/fiware-orion) instances through [OpenZiti](https://openziti.io/) overlay networks.

## **Build instructions**

Note: Building the application has so far been tested only on Ubuntu 24.04.1 LTS virtual machines created with [multipass](https://multipass.run/). Successful binary building on other platforms cannot thus far be guaranteed. The [dependencies-setup.sh](https://github.com/LiodakisOdysseas/ZTcURL/blob/master/dependencies-setup.sh) bash script takes about 5 minutes to install all the necessary dependencies (or maybe a bit longer if snap is not installed on the host). 
```
git clone https://github.com/LiodakisOdysseas/ZTcURL.git
cd ZTcURL
. dependencies-setup.sh
mkdir build && cd build
cmake ..
make
```

## **Usage**
```
./ZTcURL path-to/<openziti_identity_file.json>
