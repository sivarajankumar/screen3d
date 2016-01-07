  * **Back links**
    * [Main page of Screen Wiki](MainPage.md)
    * [Development environment](DevelopmentEnvironment.md)

# Introduction #

This part intends to explain how Screen organizes its sources and its build system.

Screen is based on a plug-in architecture : each important pack of the Screen project is defined by a dynamic library (.dll/.so) that represents a plug-in.

This architecture allows to parallelize developments and to minimize dependencies. Furthermore, it permits deferred publication of different plug-ins and simplifies patches.

# Source architecture #

Screen source management is designed in a very strict but extensive way in order to structure developments and unify all development under common concepts.

All packs are designed in the same way :
  * a root folder of the pack, placed at root of the repository. it contains 3 things :
    * a **include** folder, that contains all pack headers
    * a **src** folder, that contains all pack sources
    * a **test** folder , that contains all pack tests
    * a **sbs.xml** file, that contains configurations of the pack

Note : in some cases, you can find/add header files into src folder. It's the case then you don't want users to access to this header files. For example, in Screen/XML, _XercesParser.h_ is in src because the library interface intends to be independant from the parsing library.

This schema sums up the design :
```
trunk
|
---> <pack name>
|    |
|    ---> sbs.xml
|    |
|    ---> include
|    |    |
|    |    --->Screen
|    |        |
|    |        ...
|    |
|    ---> src
|    |    |
|    |    --->Screen
|    |        |
|    |        ...
|    |
|    ---> test
|         |
|         --->Screen
|             |
|             ...
|
---> <another pack>
|    |
|    ...
|
...             
```

# SBS : Screen Build System #

**SBS is under development and is unstable. your configurations should not work with new versions of SBS due to compatibility break. Please be patient, a first release will come soon ;) .**

## Aims ##

SBS is build system using CMake. It generates CMakeLists.txt and CMakeCache.txt files, generates makefile with these files with CMake and compile the pack.

SBS uses 2 differents files in order to process :
  * a **sbs.xml** file
  * the **sbs.config** file, that contains all global configurations (paths, compiler choice, compiler options, ...). This file is placed in SBS root folder.

```
sbs.xml --------|
                |            |----> CMakeLists.txt -----|              |-----> makefile ----|
sbs.config -----|---> SBS ---|                          |---> cmake ---|                    |---> make ---> Pack (dll/exe/...)
                |            |----> CMakeCache.txt -----|              |---> IDE configs ---|
<env>.config----|
```

## Example ##

  * sbs.xml :

```
<?xml version="1.0" encoding="UTF-8"?>
<pack>
	<properties>
		<name>Screen/Main</name>
		<version>0.1.0</version>
		<buildtype>shared</buildtype>
	</properties>
	<main>
		<dependencies>
			<dependency name="Screen/Utils" version="0.1.0"/>
			<dependency name="boost" version="1.42">
				<libraries>
					<lib>boost_thread</lib>
				</libraries>
			</dependency>
			<dependency name="DevIL" version="1.7.8">
				<libraries>
					<lib>DevIL</lib>
				</libraries>
			</dependency>
		</dependencies>
		<flags>
			<flag flag="SCREEN_BUILD_SHARED_LIBRARY" config="all" />
		</flags>
	</main>
	<test>
		<dependencies>
			<dependency name="Screen/Main" version="0.1.0"/>
			<dependency name="Screen/Utils" version="0.1.0"/>
			<dependency name="boost" version="1.42">
				<libraries>
					<lib>boost_thread</lib>
				</libraries>
			</dependency>
			<dependency name="cppunit" version="1.12.1">
				<libraries>
					<lib>cppunit</lib>
				</libraries>
			</dependency>
		</dependencies>
	</test>
</pack>

```

  * screen.config :

```
#global configuration file for Screen

RELEASE_FLAGS = SCREEN_ASSERT SCREEN_AUTHORIZE_LOG_INFO
DEBUG_FLAGS = SCREEN_ASSERT SCREEN_AUTHORIZE_LOG_DEBUG
# SCREEN_AUTHORIZE_PROFILE SCREEN_AUTHORIZE_LOG_CALL_TRACER
```

  * wascana.config :

```
#Wascana specific configuration file for SBS

ENV_NAME = Wascana
TARGET_ENV = Eclipse CDT4 - Unix Makefiles
MAKE_PROGRAM = ${WASCANA_ROOT}/msys/bin/make.exe
C_COMPILER = ${WASCANA_ROOT}/mingw/bin/gcc.exe
CPP_COMPILER = ${WASCANA_ROOT}/mingw/bin/g++.exe

#DEFAULT_INCLUDE_PATH = /usr/include
#DEFAULT_LIB_PATH = /usr/lib
DEFAULT_LIB_NAME_PATTERN=${LIB_NAME}
DEFAULT_LIB_FULL_NAME_PATTERN=lib${LIB_NAME}.dll
#DEFAULT_LIB_FULL_NAME_PATTERN=lib${LIB_NAME}.so
```

  * thoratou.config

```
#personal specific configuration 

WASCANA_ROOT = C:/Wascana
REPOSITORY_ROOT = C:/lib/sbs-repo

```

## Commands ##

SBS divides is functionalities into phases. Each phase processes only a little part of the tool capabilities.

For now, there are only 6 available phases :
  * LOAD\_CONF (loads only general configuration file sbs.config)
  * LOAD\_XML (loads specified sbs.xml file)
  * CHECK (verifies all fields)
  * CHECK\_TEST (verifies all fields for tests)
  * GENERATE (generates cmake files, specific makefiles and environment)
  * GENERATE\_TEST (generates cmake files, specific makefiles and environment for tests)

To use these phases, you must use specific commands :

```
sbs <path-to-sbs.xml> <phase> [options]
```

example :

```
sbs . generate -e wascana -e thoratou
```
generates makefile and project for Wascana environment.

## Available phases ##

|  | LOAD\_CONF | LOAD\_XML | CHECK | CHECK\_TEST | GENERATE | GENERATE\_TEST |
|:-|:-----------|:----------|:------|:------------|:---------|:---------------|
| check | X          | X         | X     |             |          |                |
| check -t | X          | X         |       | X           |          |                |
| check -b | X          | X         | X     | X           |          |                |
| generate | X          | X         | X     |             | X        |                |
| generate -t | X          | X         |       | X           |          | X              |
| generate -b | X          | X         | X     | X           | X        | X              |

## Options ##

```
-e <env> : set specific environment configurations
-i <xml file> : select a specific input sbs file (default : sbs.xml)
-v : verbose (debug mode)
-d : debug compile
-t : apply to component tests
-b : apply to both the component itself and tests
```

# Local Repository Architecture #

  * Repository tree

```
<repository root>
|
---> <component> ex: Screen/Main
|    |
|    ---> <version> ex: 0.1.0
|         |
|         ---> component.xml (contains the description of the component)
|         |
|         ---> include (contains public includes of the component)
|         |
|         ---> lib
|              |
|              ---> <environment name> ex: Wascana
|                   |
|                   ---> Release (contains release libraries of the component)
|                        |
|                        --->library-description.xml (contains Release library descriptions)
|                   |
|                   ---> Debug (contains debug libraries of the component)
|                        |
|                        --->library-description.xml (contains Debug library descriptions)
|
---> <another component>
|    |
|    ...
|
...             
```
  * **For SBS generated libraries**

  * component.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<pack>
	<properties>
		<name>Screen/Main</name>
		<version>0.1.0</version>
		<buildtype>shared</buildtype>
	</properties>
	<main>
		<dependencies>
			<dependency>
				<includes>
					<path type="absolute">/home/thomas/Developments/Screen/trunk/Screen/Main/include</path>
				</includes>
				<libraries>
					<lib>Screen/Main</lib>
				</libraries>
			</dependency>
		</dependencies>
	</main>
	<imports>
		<import build="release" file="lib/${ENV_NAME}/Release/library-description.xml"/>
		<import build="debug" file="lib/${ENV_NAME}/Debug/library-description.xml"/>
	</imports>
</pack>

```

  * library-description.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<pack>
	<main>
		<dependencies>
			<dependency>
				<libraries>
					<path>.</path>
				</libraries>
			</dependency>
		</dependencies>
	</main>
	<descriptions>
		<library name="Screen/Main" path="." full-name="libScreenMain.so" compile-name="ScreenMain" type="shared" />
	</descriptions>
</pack>

```

  * **For external library pack**

  * component.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<pack>
	<properties>
		<name>boost</name>
		<version>1.42</version>
	</properties>
	<main>
		<dependencies>
			<dependency>
				<includes>
					<path>include</path>
				</includes>
			</dependency>
		</dependencies>
	</main>
	<imports>
		<import build="release" file="lib/${ENV_NAME}/Release/library-description.xml" />
		<import build="debug" file="lib/${ENV_NAME}/Debug/library-description.xml" />
	</imports>
</pack>

```

  * library-description.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<pack>
	<main>
		<dependencies>
			<dependency>
				<libraries>
					<path>.</path>
				</libraries>
			</dependency>
		</dependencies>
	</main>
	<descriptions>
		<library name="boost_date_time" type="shared" path="."  full-name="boost_date_time-mgw34-1_42.dll" compiler-name="boost_date_time-mgw34-1_42" />
		<library name="boost_date_time-mt" type="shared" path="."  full-name="boost_date_time-mgw34-mt-1_42.dll" compiler-name="boost_date_time-mgw34-mt-1_42" />
		<library name="boost_filesystem" type="shared" path="."  full-name="boost_filesystem-mgw34-1_42.dll" compiler-name="boost_filesystem-mgw34-1_42" />
		<library name="boost_filesystem-mt" type="shared" path="."  full-name="boost_filesystem-mgw34-mt-1_42.dll" compiler-name="boost_filesystem-mgw34-mt-1_42" />
		<library name="boost_iostreams" type="shared" path="."  full-name="boost_iostreams-mgw34-1_42.dll" compiler-name="boost_iostreams-mgw34-1_42" />
		<library name="boost_iostreams-mt" type="shared" path="."  full-name="boost_iostreams-mgw34-mt-1_42.dll" compiler-name="boost_iostreams-mgw34-mt-1_42" />
		<library name="boost_math_c99f" type="shared" path="."  full-name="boost_math_c99f-mgw34-1_42.dll" compiler-name="boost_math_c99f-mgw34-1_42" />
		<library name="boost_math_c99f-mt" type="shared" path="."  full-name="boost_math_c99f-mgw34-mt-1_42.dll" compiler-name="boost_math_c99f-mgw34-mt-1_42" />
		<library name="boost_math_c99l" type="shared" path="."  full-name="boost_math_c99l-mgw34-1_42.dll" compiler-name="boost_math_c99l-mgw34-1_42" />
		<library name="boost_math_c99l-mt" type="shared" path="."  full-name="boost_math_c99l-mgw34-mt-1_42.dll" compiler-name="boost_math_c99l-mgw34-mt-1_42" />
		<library name="boost_math_c99" type="shared" path="."  full-name="boost_math_c99-mgw34-1_42.dll" compiler-name="boost_math_c99-mgw34-1_42.dll" />
		<library name="boost_math_c99-mt" type="shared" path="."  full-name="boost_math_c99-mgw34-mt-1_42.dll" compiler-name="boost_math_c99-mgw34-mt-1_42" />
		<library name="boost_math_tr1f" type="shared" path="."  full-name="boost_math_tr1f-mgw34-1_42.dll" compiler-name="boost_math_tr1f-mgw34-1_42" />
		<library name="boost_math_tr1f-mt" type="shared" path="."  full-name="boost_math_tr1f-mgw34-mt-1_42.dll" compiler-name="boost_math_tr1f-mgw34-mt-1_42" />
		<library name="boost_math_tr1l" type="shared" path="."  full-name="boost_math_tr1l-mgw34-1_42.dll" compiler-name="boost_math_tr1l-mgw34-1_42" />
		<library name="boost_math_tr1l-mt" type="shared" path="."  full-name="boost_math_tr1l-mgw34-mt-1_42.dll" compiler-name="boost_math_tr1l-mgw34-mt-1_42" />
		<library name="boost_math_tr1" type="shared" path="."  full-name="boost_math_tr1-mgw34-1_42.dll" compiler-name="boost_math_tr1-mgw34-1_42" />
		<library name="boost_math_tr1-mt" type="shared" path="."  full-name="boost_math_tr1-mgw34-mt-1_42.dll" compiler-name="boost_math_tr1-mgw34-mt-1_42.dll" />
		<library name="boost_prg_exec_monitor" type="shared" path="."  full-name="boost_prg_exec_monitor-mgw34-1_42.dll" compiler-name="boost_prg_exec_monitor-mgw34-1_42" />
		<library name="boost_prg_exec_monitor-mt" type="shared" path="."  full-name="boost_prg_exec_monitor-mgw34-mt-1_42.dll" compiler-name="boost_prg_exec_monitor-mgw34-mt-1_42" />
		<library name="boost_program_options" type="shared" path="."  full-name="boost_program_options-mgw34-1_42.dll" compiler-name="boost_program_options-mgw34-1_42" />
		<library name="boost_program_options-mt" type="shared" path="."  full-name="boost_program_options-mgw34-mt-1_42.dll" compiler-name="boost_program_options-mgw34-mt-1_42" />
		<library name="boost_serialization" type="shared" path="."  full-name="boost_serialization-mgw34-1_42.dll" compiler-name="boost_serialization-mgw34-1_42" />
		<library name="boost_serialization-mt" type="shared" path="."  full-name="boost_serialization-mgw34-mt-1_42.dll" compiler-name="boost_serialization-mgw34-mt-1_42" />
		<library name="boost_signals" type="shared" path="."  full-name="boost_signals-mgw34-1_42.dll" compiler-name="boost_signals-mgw34-1_42" />
		<library name="boost_signals-mt" type="shared" path="."  full-name="boost_signals-mgw34-mt-1_42.dll" compiler-name="boost_signals-mgw34-mt-1_42" />
		<library name="boost_system" type="shared" path="."  full-name="boost_system-mgw34-1_42.dll" compiler-name="boost_system-mgw34-1_42" />
		<library name="boost_system-mt" type="shared" path="."  full-name="boost_system-mgw34-mt-1_42.dll" compiler-name="boost_system-mgw34-mt-1_42" />
		<library name="boost_thread" type="shared" path="."  full-name="boost_thread-mgw34-mt-1_42.dll" compiler-name="boost_thread-mgw34-mt-1_42" />
		<library name="boost_unit_test_framework" type="shared" path="."  full-name="boost_unit_test_framework-mgw34-1_42.dll" compiler-name="boost_unit_test_framework-mgw34-1_42" />
		<library name="boost_unit_test_framework-mt" type="shared" path="."  full-name="boost_unit_test_framework-mgw34-mt-1_42.dll" compiler-name="boost_unit_test_framework-mgw34-mt-1_42" />
		<library name="boost_wave" type="shared" path="."  full-name="boost_wave-mgw34-1_42.dll" compiler-name="boost_wave-mgw34-1_42" />
		<library name="boost_wave-mt" type="shared" path="."  full-name="boost_wave-mgw34-mt-1_42.dll" compiler-name="boost_wave-mgw34-mt-1_42" />
	</descriptions>
</pack>

```

**Note** : if component.xml doesn't exist on Linux, it doesn't return an error. It uses DEFAULT\_INCLUDE\_PATH, DEFAULT\_LIBRARY\_PATH, DEFAULT\_LIB\_NAME\_PATTERN and DEFAULT\_LIB\_FULL\_NAME\_PATTERN to retrieve paths and names. This last comportment is preferred on Linux

<a href='Hidden comment: 
|| *Generates makefiles* || ||
|| generate makefiles || sbs `<path-to-pack>` generate ||
|| *Compile* || ||
|| compile the Pack sources || sbs `<path-to-pack>` compile ||
|| compile the Pack tests || sbs `<path-to-pack>` compile -t ||
|| compile the Pack sources and tests || sbs `<path-to-pack>` compile -b ||
|| *Generates makefiles and compile* || ||
|| generate makefiles and compile the Pack sources || sbs `<path-to-pack>` build ||
|| generate makefiles and compile the Pack tests || sbs `<path-to-pack>` build -t ||
|| generate makefiles and compile the Pack sources and tests || sbs `<path-to-pack>` build -b ||
|| *Run tests* || ||
|| run tests || sbs `<path-to-pack>` test ||
'></a>