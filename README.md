# Simple ARP Poisoning Detector

>Detects ARP Poisoning in local networks and displays ARP Cache.

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
    ###### Linux ARP Cache file with display option
    ```
    $ arp detector -lf -d
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