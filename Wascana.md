  * **Prerequisites**
    * [Project/Pack oriented source management](ProjectOrientedSourceManagement.md)
    * [How to install SBS](SBSInstall.md)
  * **Back links**
    * [Development environment](DevelopmentEnvironment.md)

# Introduction #

Wascana is full environment based on Eclipse C++, MSYS and MingW compiler.
This environment provides easily configurable environment with advance features (makefiles, auto-indentation, auto-completion, debugger, ...).

# Wascana #

## Download Wascana ##

Download the installer at this link :

http://sourceforge.net/projects/wascana/files/Wascana%2C%20MinGW%20Edition/0.9.3/wascana-mingw-0.9.3.exe/download

## Install Wascana ##

Launch the installer _wascana-mingw-0.9.3.exe_

Continue until **Select Destination Location** window. Change the folder from **C:\Program Files\Wascana** to **C:\Wascana**.

We do this because there are some problems with spaces, notably during compilation of Xerces with MSYS.

Then continue and finish the installation.

## First launch ##

Launch Wascana.

The first thing Wascana asks is to choose a workspace. Enter a path in which you want the workspace to be placed. For all Screen developments, we will use this unique workspace.

Then validate the workspace and you arrive on the main Wascana window.

If it is not, select the C++ view.

In next parts, we configure all projects for Screen at once (we will have one project per component).

## Project creation ##

First, if you didn't do it, check-out Screen sources and install SBS : [How to install SBS](SBSInstall.md).

Then, in a command prompt, write :
```
sbs configure -g -e wascana -e screen -e user
```

In the same command prompt, go to Screen root file and write :
```
generate-screen-release.bat
```
or
```
generate-screen-debug.bat
```
It will prepare all projects for respectively release or debug mode

Now you must open every generated project one by one into you Wascana IDE.

It do it :

`File > New > Project`

Enter the name of the project (ScreenMain), uncheck **Use default location** and enter in the field the root of the pack (the folder that contains src folder, include folder, etc ...), and choose the right type of the project (for shared library in case of Screen/Main).

Finish the creation.

After this you will have a project that will have a project that contains 3 folders :
  * **src**
  * **include**
  * **test** (optional)

The folder **test** contains the test sources. The goal of this tests is to generate a executable using the shared library we want to create. So tests mustn't be in this project but in another. SBS automatically suppress the **test** folder from the project, so you don't have anything to do.

## Dependencies ##

SBS/Wascana environment doesn't compile needed dependencies by itself. You need to build external and Screen libraries.

_N.B._ : In SBS future evolutions, the latter will automatically search dependencies and build them. For external libraries, we will create specific packages.

## Builds ##

To build a project into Wascana, go into _Make_ tag, select your project and launch _all_
That's all ;)

## Launch ##

For now, you can't launch your project from Wascana.
To do this, go into the ${REPOSITORY\_ROOT}/Wascana/${your-build-type}, where _REPOSITORY\_ROOT_ is the path you must define in your specific sbs configuration file, and _your-build-type_ is _Release_ or _Debug_.

Then launch the executable of your pack.

## Configure test project ##

To configure a test project, use the option -t with the sbs command, and create a project with the root into the _test_ folder of the pack

# MSYS #