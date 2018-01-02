# Titanium Bass #

The project involved designing and building a command line tool for user interaction, an SQL parser and a physical level backend for data management.

### Prerequisites

* gcc version 5.4.0 or higher
* g++ version 6.3.0 or higher
* boost-1.65.1-2 or higher
* clang version 3.8.0-2ubuntu4 or higher [optional]
* GNU Readline and History
* Python3 Pandas-0.16.2 or higher 

### Installing

First install all the required packages. Ubuntu users can run install.sh as: [NOTE: It can take a considerably long time]

```
sudo ./install.sh
```

Compile the project on your local system by:

```
make clean
make
```

### Usage

Please see this [README](https://github.com/DarkFate13/Titanium-Bass/blob/master/examples/README.md) for raw usage

For python api: [STILL IN DEV PHASE]

```
./clt -p # To start listening
python3 titaniumLite/titaniumLite.py # To execute commands 
```

### Authors: ###

* **Durga Akhil Mundroy** - [akhilmd](https://github.com/akhilmd)
* **Ganesh K.** - [DarkFate13](https://github.com/DarkFate13)
* **Harsh Garg** - [HARSHGARG76](https://github.com/HARSHGARG76)


### Timeline: ###
* Week 1
	* Discussed project structure, tools and backend interface.
	* Made barebones project with fake implementation.
	* Implemented backend for points 1-5 in [outline.pdf](https://github.com/DarkFate13/Titanium-Bass/blob/master/outline.pdf).
* Week 2
	* Discussed structure and production rules for parser.
	* Implemented backend for points 6-10 in [outline.pdf](https://github.com/DarkFate13/Titanium-Bass/blob/master/outline.pdf).
* Week 3
	* Implemented backend for points 11-15 in [outline.pdf](https://github.com/DarkFate13/Titanium-Bass/blob/master/outline.pdf).
	* Implemented parser for points 1-9 in [outline.pdf](https://github.com/DarkFate13/Titanium-Bass/blob/master/outline.pdf).
* Week 4
	* Implemented backend for points 16-19 in [outline.pdf](https://github.com/DarkFate13/Titanium-Bass/blob/master/outline.pdf).
	* Implemented parser for points 10-19 in [outline.pdf](https://github.com/DarkFate13/Titanium-Bass/blob/master/outline.pdf).

### How to contribute to the project: ###

* Fork this repo.
* Create a branch in your Fork.
* Push changes to your branch.
* Once you want others to see and review your changes, create a pull request.
* We'll go through the pull request and merge them into the master project.