# **ZTcURL**

ZTcURL is a Zero-Trust Networking Architecture-embedded command line client application that utilizes [curl](https://curl.se/)'s [libcurl()](https://curl.se/libcurl/) library and [OpenZiti-C SDK](https://github.com/openziti/ziti-sdk-c) to allow secure, authenticated access to [OpenZiti](https://openziti.io/) services.

![](https://github.com/LiodakisOdysseas/ZTcURL/blob/master/ZTcURL_Network_topology.jpg)
## **Build instructions**

```
git clone https://github.com/LiodakisOdysseas/ZTcURL.git
cd ZTcURL
. dependencies-setup.sh
mkdir build && cd build
cmake ..
make
```
Note: The [dependencies-setup.sh](https://github.com/LiodakisOdysseas/ZTcURL/blob/master/dependencies-setup.sh) bash script takes about 5 minutes to install all the necessary dependencies (or maybe a bit longer if snap is not installed on     the host). Building the application has so far been tested only on Ubuntu 24.04.1 LTS virtual machines created with [multipass](https://multipass.run/) or [Windows Subsystem for Linux](https://learn.microsoft.com/en-us/windows/wsl/). On other platforms, successful binary building cannot thus far be absolutely guaranteed.

## **Usage**
```
./ZTcURL 'https://open.ziti.service.intercept.address:port/path?query' path/to/<openziti_identity_file>.json
