# bugzilla
Bug report tracker.

![bugzilla main menu](res/mainmenu.png)

![bugzilla help](res/help.png)

## Description
Minimalistic bug report tracker and management system.

## Installation
Windows: See [Releases](https://github.com/DiamondBond/bugzilla/releases)

Linux: See [Install from source](#install-from-source)

## Install from source
Windows:
- Install [Dev-C++](https://sourceforge.net/projects/orwelldevcpp)
- Download this repo as a zip file
- Unzip somewhere
- Open bugzilla.cpp with Dev-C++
- Press F11 to compile & run

Linux:
```
git clone https://github.com/diamondbond/bugzilla
make all
# or `make release` if you want to build without -Ofast
```

## Usage
Windows: Double click the executable (bugzilla.exe)

Linux: 
```
./bugzilla.o
```

## Features
### Create a bug report
Creates a bug and files it for tracking.
### Update a bug report
Updates a bugs tracking information.
### Display a bug report
Generates a bug report from a bugs tracking information.
### List bug reports
Lists available bug reports. [TODO](#implement-list-bugs)
### Platform agnostic
Runs on Windows & Linux

## TODO
### Implement list_bugs()
List all the available bugs, this could be a glorified dir or ls
statement excluding the current running executable, further expanding
on this idea we could provide filesystem support to read files from a
users specified location, this might prove to be a nightmare to
implement, but who knows.
```
$USER selects "[L]ist Bug Reports" at menu and is presented with:
* bug1
* bug2
x bug3
* bug4
^ bug5
```
The symbol preceeding the bug report name provides some information at
a glance by representing the bug status.

## Inspiration
https://www.bugzilla.org
