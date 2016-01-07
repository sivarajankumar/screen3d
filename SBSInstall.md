  * **Back links**
    * [Main page of Screen Wiki](MainPage.md)
  * **Next session**
    * [Development environment](DevelopmentEnvironment.md)

# Introduction #

This part explains how you will install SBS, which is a mandatory part for all environment configuration tutorial (you can also create your dependencies by hand :s )

# Prerequisites #

To use SBS, you need some softwares on your machine :
  * [CMake](http://www.cmake.org/cmake/resources/software.html) (minimum version 2.6, version 2.8 recommended)
  * [Java](http://java.sun.com/javase/downloads/index.jsp) (version 1.6 or later)

Once those softwares are installed, you could choose to install SBS from pre-built installer to download or by compiling sources.
If you are not an SBS developer, I advice you to install it by installer

# Install from download #

## on Windows ##

Go to SBS site in download session, and choose the last installer :
http://code.google.com/p/sbs/downloads/list

Download it and execute it. Then just follow instructions.

That's it, SBS is installed. Now you could verify it works by going to First launch part.

## on Linux ##

For now there is no existing installer for linux. You could still install it from the sources

# Install from sources #

This part will allow you to have the benefits of latest snapshot versions of SBS.
For Screen developers, you would modify SBS and commit your changes.

First of all, you must install this software in addition for Java and CMake to compile SBS sources :
  * [Maven2 or Maven3](http://maven.apache.org/download.html)

Then, check out SBS trunk sources (on the repository, trunk/Tools/SBS/)

In your environment variables, add and set SBS\_ROOT to the SBS root folder (trunk/Tools/SBS), and add SBS\_ROOT and the root to maven in PATH variable. Maven also need a JAVA\_HOME environment variable, corresponding to your java JDK installation directory.

Then open a command terminal and go into SBS\_ROOT.

verify maven is well installed by writing :
```
mvn --version
```

then install SBS by writing (need and internet connection):
```
mvn install
```

# First launch #

First, open a new command terminal and write :
```
sbs help
```
You will see all commands available with SBS.

# Prepare SBS for Screen #

## Note about SBS paths ##

There are 2 main paths uses by SBS :
  * **SBS\_HOME**, in which you could find configuration files and the default repository . By default, if your user is "toto", your **SBS\_HOME** is :
    * Under linux, /user/toto/.sbs
    * Under Windows Vista/7, C:/Users/Toto/.sbs
    * Under Windows Xp, C:/Documents and Settings/Toto/.sbs
  * **SBS\_ROOT**, which is the SBS installation path

## screen.config ##

To use SBS you need one additional config file that contains several flags used by Screen.

Take **screen.config** file from SVN Screen root folder, and put it into your **SBS\_HOME** folder.

## Prepare your repository ##

Screen needs several external libraries to compile (boost, cppunit, ...)
Some build has been created and deployed as SBS components, that are only available as a simple additional repository reserved to some SBS developers (on a Dropbox shared folder).

We must find a way to easily share those resources; Please be patient

For those who have access to this Dropbox repository, you can resume this tutorial.

# Configure SBS repositories for SBS #

By default, SBS only knows one repository, set with REPOSITORY\_ROOT variable.
Your must configure SBS to take the Dropbox repository.
To do it, edit **SBS\_HOME**/repositories/repositories.xml file and add the repository  and filter definition. You shoud have something like :

```
<?xml version="1.0" encoding="UTF-8"?>
<repositories>
	<data>
		<repository id="1" type="local,snapshot,internal" path="${REPOSITORY_ROOT}" comment="main local repository" />
		<repository id="2" type="local,release,internal"  path="C:/.../Documents/My Dropbox/ScreenFrameWork/SBS-repository" comment="Screen dropbox repository" />
	</data>
	<filters>
		<!-- by default, a component is taken in the main local repository in order to obtain the latest snapshot version of the component.
		     if it is not into the main local repository, it would be found in another repository
		-->
		<filter id="1" component-name=".*" component-version=".*" compiler=".*" repository-id="1" />
		<filter id="2" component-name=".*" component-version=".*" compiler=".*" repository-id="2" />
	</filters>
</repositories>
```

From now, you shouldn't need anymore to touch SBS files. In the next session, you will choose your environment variable and launch last configuration commands.