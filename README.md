# Wake on LAN C

Simply send "Magic Packets" to a given MAC address on the network.

## Building

This is currently written for and only relies on the standard C libraries in most Linux distros. 
You can use CMake to generate the appropriate build files. 
```
cmake .
make
```
As of now, there is no automated installation (it's on the todo list!)

## Usage

Simply run the binary that is built and it will prompt you for a MAC Address. Simple as.
```
$ ./wake-on-lan
```
It will ask you for the MAC address to send the packet to.

__NOTE: It's very likely that the name of the binary will change in the future!!__ I don't like typing more than
I need to, so I want the command to be shorter when I deploy this in my own environments. 

## Limitations

This is heavily WIP; as such, there are several current limitations that are in the process of being worked out:

* Currently hard coded to broadcast at the 192.168.0.0/24 address space
  * This will be ironed out, it will take some time as I want to ensure it is done properly and in an intuitive way
* The program itself is not cross platform (though any card that complies with the WoL standard should be woken). This is 
a long ways off from being resolved. 
* Must use either `:` or `-` for the seperators in the address. 