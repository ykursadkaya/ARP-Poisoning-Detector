# Simple ARP Poisoning Detector

>Detects ARP Poisoning in local networks and displays ARP Cache.

Reads ARP Cache and checks if a MAC Address is same for two or more unique IPs in the same interface, commonly router and attacker have same MAC Address.

## Compile

Just compile with gcc or clang with no dependencies
```
$ gcc arp_detector.c -o arp_detector
```
or
```
$ clang arp_detector.c -o arp_detector
```

## Usage
`arp_detector` has two commands

```
$ arp_detector <OS> <display option> 
```

1. OS selection (necessary)
	* Linux ARP Cache File mode `-lf`
	* Linux "arp -an" command `-lc`
	* macOS "arp -an" command `-m`
	* Windows "arp -a" command `-w`
	##### macOS "arp -an" command detect-only, no display
	```
	$ arp_detector -m
	```
2. Display ARP Cache option (optional)
	* Print ARP Cache `-d`
	##### Linux ARP Cache file with display option
	```
	$ arp detector -lf -d
	```

Prints "ARP Poisoning detected!" alert on ARP Spoof detection, otherwise just prints ARP Cache or nothing depends on display option.

## Example

```
ykursadkaya@lubuntuVM:~/Desktop$ gcc arp_detector.c -o arp_detector
ykursadkaya@lubuntuVM:~/Desktop$ ./arp_detector -lf -d
10.0.2.1 at 52:54:00:12:35:00 on enp0s3
ykursadkaya@lubuntuVM:~/Desktop$ ./arp_detector -lf -d
10.0.2.4 at 08:00:27:be:0c:78 on enp0s3
10.0.2.1 at 08:00:27:be:0c:78 on enp0s3
ARP Poisoning detected!
ykursadkaya@lubuntuVM:~/Desktop$ ./arp_detector -lf -d
10.0.2.4 at 08:00:27:be:0c:78 on enp0s3
10.0.2.1 at 52:54:00:12:35:00 on enp0s3
ykursadkaya@lubuntuVM:~/Desktop$
```

## Help menu
```
$ arp_detector -h
```
```
OS selection:
	-l*	Linux systems
		-lc	Linux arp command
		-lf	Linux ARP cache file
	-m	macOS systems
	-w	Winows systems

Display option:
	-d	Display ARP Table
```

## Problems

Detector does not work properly on Windows systems but you can see ARP Cache with display option.