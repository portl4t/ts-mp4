
## Name
ts-mp4 - MP4 streaming media, implement as plugin of Apache TrafficServer

## Status
This module is under active development and is production ready.

## Description
This module provides streaming media server support for MP4 files. User can send a HTTP request to the server with `start` argument which is measured in seconds, and the server will respond with the stream such that its start position corresponds to the requested time, for example:

```c
http://v.foo.com/dota2.mp4?start=290.12
```

This allows performing a random seeking at any time. We can use flash player, vlc, mplayer or chrome to play the streaming media. 

We can write this in remap.config:

```c
map http://v.foo.com/ http://inner.foo.com/ @plugin=/usr/lib64/trafficserver/plugins/libtsmp4.so
```

## System Requirements
* linux 64bits
* trafficserver

## Build
**step1**: get ts-mp4

    git clone https://github.com/portl4t/ts-mp4.git
    cd ts-mp4/src

**step2**: build, requires linux(64bits is recommended)

    make

**step3**: modify remap.config and restart the trafficserver

