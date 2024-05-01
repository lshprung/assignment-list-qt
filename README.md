# Assignment List

A QT application for managing grouped tasks (or "entries"). Originally written using [PyQt5](https://github.com/lshprung/assignment-list-pyqt) before being rewritten in C++.

### Build Prerequisites

On Debian/Debian-based (Qt5):

```
# apt install cmake git g++ libqt5core5a libqt5gui5 libqt5sql5 libqt5sql5-sqlite libqt5svg5 libqt5widgets5 qtbase5-dev qttools5-dev
```

On Debian/Debian-based (Qt6):

```
# apt install cmake git g++ libqt6core6 libqt6gui6 libqt6sql6 libqt6sql6-sqlite libqt6svg6 libqt6uitools6 libqt6widgets6 qt6-base-dev qt6-tools-dev
```

On Fedora (Qt5):

```
# dnf install cmake gcc-c++ qt5-qtbase-devel qt5-qttools-static qt5-qtsvg-devel
```

On Fedora (Qt6):

```
# dnf install cmake gcc-c++ qt6-qtbase-devel qt6-qttools-devel qt6-qtsvg-devel
```

On Arch Linux (Qt5):

```
# pacman -S cmake gcc make qt5-base qt5-svg qt5-tools
```

On Arch Linux (Qt6):

```
# pacman -S cmake gcc make qt6-base qt6-svg qt6-tools
```

### Build Instructions

```
$ mkdir build
$ cd build
$ cmake ../
$ make
```

The above commands run from the project root will build the application.

The cmake command can be substituted with `cmake -DUSE_QT5=yes ../` to explicitly use Qt5 over Qt6 or `cmake -DUSE_QT6=yes ../` to explicitly use Qt6 over Qt5.

If using ninja instead of Makefiles, run `ninja` instead of `make`

### Installation

```
# make install
```

The above command will install the application, as well as a desktop entry (if on Linux)

Building installer packages using CPack is also supported for the following package formats:

- DEB (`cpack -G DEB`)
- RPM (`cpack -G RPM`)
- Windows Installer (`cpack -G NSIS`)

### Caveats

- Compiling on Windows currently requires the use of [MSYS2 MinGW](https://www.msys2.org/) to build correctly
