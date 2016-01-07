  * **Back links**
    * [Main page of Screen Wiki](MainPage.md)

# Introduction #

In this part, I'll try to explain goals of different main parts of the Screen framework (contained in _Screen/Utils_) and how to use them.

# Main concepts #

## _Declaration.h_ : Automatic embedded call tracer and profiler ##

### Aims ###

the _Declaration.h_ provides tools for debugging Screen application. Its provides 2 type of information :
  * A call tracer through the CALL log messages. It indicates all begins and ends of constructors, destructors, methods and functions.
  * A embedded profiler, in order to provide performance information.

Warning : These tools degrades strongly performances of the application. In the case of the profiler, it can compute unexpected results.

Warning : Don't use call tracer or profiler for long time executions. It uses many resources (memory can explode :))

### Usage ###

First add the inclusion _Screen/Utils/Declaration.h_
Then you can use several macros :
  * **_SCREEN\_DECL\_CLASS(<class name>)_**. Must be placed in the class body. This macro doesn't process anything. It's only define a static method that returns the name of the class. _SCREEN\_DECL\_CONSTRUCTOR_, _SCREEN\_DECL\_DESTRUCTOR_ and _SCREEN\_DECL\_METHOD_ need to have _SCREEN\_DECL\_CLASS_ defined in the class to be used.
  * **_SCREEN\_DECL\_CONSTRUCTOR(<constructor name>)_**. Must be placed at the beginning of the constructor.
  * **_SCREEN\_DECL\_DESTRUCTOR(<destructor name>)_**. Must be placed at the beginning of the destructor.
  * **_SCREEN\_DECL\_METHOD(<method name>)_**. Must be placed at the beginning of the method.
  * **_SCREEN\_DECL\_STATIC\_METHOD(<method name>)_**. Must be placed at the beginning of the static method.
  * **_SCREEN\_DECL\_FUNCTION(<function name>)_**. Must be placed at the beginning of the function.

### Example ###

  * Color.h :
```
#ifndef SCREEN_COLOR_H
#define SCREEN_COLOR_H

#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		/*!  \class Color
		 *   \brief color definition
		 *   \author Ratouit Thomas
		 */

		class SCREEN_EXPORT Color {
			SCREEN_DECL_CLASS(Screen::Core::Color)
		public:
			Color(unsigned long color = 0xFF000000);
			Color(unsigned char b, unsigned char g, unsigned char r, unsigned char a = 0xFF);
			~Color();
				
			unsigned long convertABGR() const;
				
			unsigned char getAlpha() const;
			void setAlpha(unsigned char a);
			unsigned char getBlue() const;
			void setBlue(unsigned char b);
			unsigned char getGreen() const;
			void setGreen(unsigned char g);
			unsigned char getRed() const;
			void setRed(unsigned char r);
			void set(unsigned char b, unsigned char g, unsigned char r, unsigned char a);
			void set(unsigned char b, unsigned char g, unsigned char r);
		        
		private:
			unsigned long color; //ABGR
		};
	}
}

#endif

```

  * Color.cpp :
```
#include <Screen/Core/Color.h>

namespace Screen {
	namespace Core {
		Color::Color(unsigned long color)
			:color(color){
			SCREEN_DECL_CONSTRUCTOR(Color)
		}
		
		Color::Color(unsigned char b, unsigned char g, unsigned char r, unsigned char a){
			SCREEN_DECL_CONSTRUCTOR(Color)
			set(b,g,r,a);
		}
		
		Color::~Color(){
			SCREEN_DECL_DESTRUCTOR(~Color)
		}
		
		unsigned long Color::convertABGR() const{
			SCREEN_DECL_METHOD(convertABGR)
			return color;
		}
		
		unsigned char Color::getAlpha() const{
			SCREEN_DECL_METHOD(getAlpha)
			return static_cast<unsigned char>((color & 0xFF000000) >> 24);
		}
		
		void Color::setAlpha(unsigned char a){
			SCREEN_DECL_METHOD(setAlpha)
			color = (color & 0x00FFFFFF) | (a << 8);
		}
        
		unsigned char Color::getBlue() const{
			SCREEN_DECL_METHOD(getBlue)
			return static_cast<unsigned char>((color & 0x00FF0000) >> 16);
		}
        
		void Color::setBlue(unsigned char b){
			SCREEN_DECL_METHOD(setBlue)
			color = (color & 0xFF00FFFF) | (b << 16);
		}
        
		unsigned char Color::getGreen() const{
			SCREEN_DECL_METHOD(getGreen)
			return static_cast<unsigned char>((color & 0x0000FF00) >> 8);
		}
        
		void Color::setGreen(unsigned char g){
			SCREEN_DECL_METHOD(setGreen)
			color = (color & 0xFFFF00FF) | (g << 8);
		}
        
		unsigned char Color::getRed() const{
			SCREEN_DECL_METHOD(getRed)
			return static_cast<unsigned char>((color & 0x000000FF) >> 0);
		}
        
		void Color::setRed(unsigned char r){
			SCREEN_DECL_METHOD(setRed)
			color = (color & 0xFFFFFF00) | (r << 0);
		}

		void Color::set(unsigned char b, unsigned char g, unsigned char r, unsigned char a){
			SCREEN_DECL_METHOD(set)
			color = (a << 24) | (b << 16) | (g << 8) | (r << 0);
		}
        
		void Color::set(unsigned char b, unsigned char g, unsigned char r){
			SCREEN_DECL_METHOD(set)
			color = (color & 0xFF000000) | (b << 16) | (g << 8) | (r << 0);
		}
	}
}

```

### Outputs ###

The output depends in the implementation of the logger and profiler reporters. These outputs show the results with the defaults reporters :

log.txt
```
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22fba0]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22fba0]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22fba0]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22fba0]
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22fb10]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22fb10]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22fb10]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22fb10]
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22fb00]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22fb00]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22fb00]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22fb00]
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22faf0]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22faf0]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22faf0]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22faf0]
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22fae0]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22fae0]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22fae0]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22fae0]
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22fad0]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22fad0]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22fad0]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22fad0]
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22fac0]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22fac0]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22fac0]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22fac0]
[CALL] [begin][constructor = Screen::Core::Color::Color()][address = 0x22fab0]
[CALL] [end][constructor = Screen::Core::Color::Color()][address = 0x22fab0]
[CALL] [begin][method = Screen::Core::Color::convertABGR()][address = 0x22fab0]
[CALL] [end][method = Screen::Core::Color::convertABGR()][address = 0x22fab0]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22fab0]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22fab0]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22fac0]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22fac0]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22fad0]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22fad0]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22fae0]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22fae0]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22faf0]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22faf0]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22fb00]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22fb00]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22fb10]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22fb10]
[CALL] [begin][destructor = Screen::Core::Color::~Color()][address = 0x22fba0]
[CALL] [end][destructor = Screen::Core::Color::~Color()][address = 0x22fba0]

```

profiler.txt
```
constructor | Screen::Core::Color::Color() | 0x22fba0 | 36.7658 | 36.7681 | ended
method | Screen::Core::Color::convertABGR() | 0x22fba0 | 36.8382 | 36.8402 | ended
constructor | Screen::Core::Color::Color() | 0x22fb10 | 36.8631 | 36.8647 | ended
method | Screen::Core::Color::convertABGR() | 0x22fb10 | 36.886 | 36.8879 | ended
constructor | Screen::Core::Color::Color() | 0x22fb00 | 36.9094 | 36.9111 | ended
method | Screen::Core::Color::convertABGR() | 0x22fb00 | 36.9329 | 36.9349 | ended
constructor | Screen::Core::Color::Color() | 0x22faf0 | 36.9561 | 36.958 | ended
method | Screen::Core::Color::convertABGR() | 0x22faf0 | 36.9796 | 36.9812 | ended
constructor | Screen::Core::Color::Color() | 0x22fae0 | 37.0036 | 37.0053 | ended
method | Screen::Core::Color::convertABGR() | 0x22fae0 | 37.0312 | 37.0329 | ended
constructor | Screen::Core::Color::Color() | 0x22fad0 | 37.0561 | 37.0581 | ended
method | Screen::Core::Color::convertABGR() | 0x22fad0 | 37.0812 | 37.0832 | ended
constructor | Screen::Core::Color::Color() | 0x22fac0 | 37.1064 | 37.1081 | ended
method | Screen::Core::Color::convertABGR() | 0x22fac0 | 37.1313 | 37.1332 | ended
constructor | Screen::Core::Color::Color() | 0x22fab0 | 37.1567 | 37.1584 | ended
method | Screen::Core::Color::convertABGR() | 0x22fab0 | 37.1815 | 37.1835 | ended
destructor | Screen::Core::Color::~Color() | 0x22fab0 | 37.2067 | 37.2089 | ended
destructor | Screen::Core::Color::~Color() | 0x22fac0 | 37.2324 | 37.2341 | ended
destructor | Screen::Core::Color::~Color() | 0x22fad0 | 37.2578 | 37.2598 | ended
destructor | Screen::Core::Color::~Color() | 0x22fae0 | 37.283 | 37.2849 | ended
destructor | Screen::Core::Color::~Color() | 0x22faf0 | 37.3087 | 37.3103 | ended
destructor | Screen::Core::Color::~Color() | 0x22fb00 | 37.3352 | 37.3371 | ended
destructor | Screen::Core::Color::~Color() | 0x22fb10 | 37.3606 | 37.3623 | ended
destructor | Screen::Core::Color::~Color() | 0x22fba0 | 37.3858 | 37.3877 | ended
```

Outputs can be huge and you will want to ignore some logs.

You will see how to configure logger and profiler outputs in the next chapters.

## Unique shared logger for Screen ##

### Logger Design ###

The logger design is based on Strategy patterns :

![https://docs.google.com/uc?id=0B6E-trOwx6Z3ZjFkMjI2YzUtNjVjNS00Y2U2LTk0MDgtOTI4NTZlMDhmYzhi&hl=en&img=logger.png](https://docs.google.com/uc?id=0B6E-trOwx6Z3ZjFkMjI2YzUtNjVjNS00Y2U2LTk0MDgtOTI4NTZlMDhmYzhi&hl=en&img=logger.png)

In order to create your own log format, implement the LoggerReporter interface and attach the reporter to the logger by using the SCREEN\_ATTACH\_LOGGER\_REPORTER

Example :

```
SCREEN_ATTACH_LOGGER_REPORTER(new Screen::Utils::FileLoggerReporter("out.log"));
```

### Default logger reporters ###

Fro now, there are two different default logger reporters :
  * Screen::Utils::CoutLoggerReporter, that displays the output on the standard output,
```
SCREEN_ATTACH_LOGGER_REPORTER(new Screen::Utils::CoutLoggerReporter);
```
  * Screen::Utils::FileLoggerReporter, that writes the output into a given file.
```
SCREEN_ATTACH_LOGGER_REPORTER(new Screen::Utils::FileLoggerReporter("out.log"));
```

## Profiler ##

## Smart Pointers ##

## Resource Management ##

## Singleton ##

## Exceptions ##

# Secondary concepts #