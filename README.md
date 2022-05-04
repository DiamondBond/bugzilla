# bugzilla
Bug report tracker.

![bugzilla main menu](res/img/mainmenu.png)

![bugzilla help](res/img/help.png)

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
### Platform agnostic
Runs on Windows & POSIX compliant systems.
### Create a bug report
Creates a bug report.
### List bug reports
Lists available bug reports.
### Display a bug report
Displays a bug report.
### Update a bug report
Updates a bug report.
### Remove a bug report
Deletes a bugs report.
### Built-in help
Offers help and info/docs.

## Inspiration
https://www.bugzilla.org
