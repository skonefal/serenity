# Serenity

Intel and Mesosphere are working on creating cutting-edge oversubscription
technologies for Mesos. Follow the [Mesos Oversubscription Architecture](https://docs.google.com/document/d/1pUnElxHy1uWfHY_FOvvRC73QaOGgdXE0OXN-gbxdXA0/edit), it
is a very flexible solution which drives the internal semantics in Mesos but
leaves all actual estimation and controller logic to module implementors.

We consider oversubscription as a series of estimates i.e. how much can safely
be oversubscribed and decisions i.e. how to protect production workloads. The
different substages of estimates and decision-making should be able to
influence each other. For example, dramatic corrections may have to involve
limiting or stopping current estimates.

We aim for a very flexible solution where both estimation and corrections are
done in a pipelined approach with shared knowledge between each stage, referred
to as Filters with a shared bus.

![Serenity pipeline](https://github.com/mesosphere/serenity/blob/master/docs/images/serenity_pipeline.png)

For more documentation, please refer to [docs](https://github.com/mesosphere/serenity/blob/master/docs/README.md).

# Installing

## Prerequisites

Building Mesos modules requires system-wide installation of google-protobuf,
glog, boost and picojson.

## Build Mesos with some unbundled dependencies

### Preparing Mesos source code

Start by pulling a recent version of [Apache Mesos](https://git-wip-us.apache.org/repos/asf/mesos.git):

```
git clone https://git-wip-us.apache.org/repos/asf/mesos.git ~/mesos
```

### Building and Installing Mesos

Due to the fact that modules will need to have access to a couple of libprocess
dependencies, Mesos itself should get built with unbundled dependencies to
reduce chances of problems introduced by varying versions (libmesos vs. module
library).

We recommend using the following configure options:

```
cd ~/mesos
mkdir build && cd build
../configure --with-glog=/usr/local --with-protobuf=/usr/local --with-boost=/usr/local
make
make install
```

<<<<<<< HEAD
Note that the `--prefix=$HOME/usr` is required only if you don't want to do a system-wide Mesos installation.

## Build Mesos Modules (deprecated)
=======
### Build Serenity
>>>>>>> master

Once Mesos is built and installed, clone the Serenity package.

The configuration phase needs to know some details about your Mesos build and installation
location:

<<<<<<< HEAD
The configuration phase needs to know some details about your Mesos installation
location, hence the following are used:
`--with-mesos=/path/to/mesos/installation`

## Example (deprecated)
=======
>>>>>>> master
```
./bootstrap
mkdir build && cd build
../configure --with-mesos-root=~/mesos --with-mesos-build-dir=~/mesos/build
make
```

At this point, the Module libraries are ready in `build/.libs`.

### Using Mesos Modules

See [Mesos Modules](http://mesos.apache.org/documentation/latest/modules/).

## Building Serenity with Cmake

Serenity now supports Cmake build system.

Build the serenity with those commands:
```
./setup.sh
cd build
cmake -DWITH_MESOS="/usr" ..
make
```
