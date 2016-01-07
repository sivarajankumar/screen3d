  * **Back links**
    * [Main page of Screen Wiki](MainPage.md)

# Introduction #

This page sums up the advancement of the different parts of Screen project.

# Advancement levels #

<font color='red'>empty</font> : Development no longer started.

<font color='purple'>in development</font> : Development in progress.

<font color='blue'>development complete</font> : Development complete. Not stable

<font color='green'>delivered</font> : Stable and delivered in a new pack.

# Screen/Utils pack #

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Any      | <font color='purple'>in development</font> | Screen/Utils | 0.1              | _N/A_             | must be tested |
| Debug call tracer | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | Must add attributes debug trace in version 0.2  |
| Exceptions | <font color='purple'>in development</font> | Screen/Utils | 0.1              | _N/A_             | simplest exception implemented, need improvements |
| File and paths management | <font color='purple'>in development</font> | Screen/Utils | 0.1              | _N/A_             | _N/A_       |
| Logger   | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | can process ERROR, WARNING, INFO and DEBUG logs |
| Memory allocation debugger | <font color='red'>empty</font> | Screen/Utils | 0.1              | _N/A_             | TODO :)     |
| Plug-in system (Windows) | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | based on dynamic library load |
| Plug-in system (Linux) | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | based on dynamic library load |
| Profiler | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | _N/A_       |
| Resource management | <font color='purple'>in development</font> | Screen/Utils | 0.1              | _N/A_             | need advance tests |
| Smart pointer | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | _N/A_       |
| Smart pointer policies | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | for 'classic' and resource based smart pointer |
| Singleton | <font color='blue'>development complete</font> | Screen/Utils | 0.1              | _N/A_             | _N/A_       |

# Screen/Main pack #

## Maths (_Screen::Math_) ##

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Generic and compile time sized vector | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Generic and compile time sized matrix | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Matrices | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Plane    | <font color='red'>empty</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Rectangles | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Vectors  | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |

## Core (_Screen::Core_) ##

  * **Vertices and Indices**

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Index Buffer | <font color='blue'>development complete</font> | Screen/Main | 0.1              | _N/A_             | 2 or 4 byte size index buffer |
| Index Buffer Filler | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | utility class to fill index buffers |
| Index Buffer Handler | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | concrete class to handle generic index buffers |
| Vertex Buffer | <font color='blue'>development complete</font> | Screen/Main | 0.1              | _N/A_             | vertex buffer with size compute at runtime or compile time |
| Vertex Format | <font color='blue'>development complete</font> | Screen/Main | 0.1              | _N/A_             | added lock system |
| Vertex Buffer Filler | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | utility class to fill vertex buffers |
| Vertex Buffer Handler | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | concrete class to handle generic vertex buffers |

  * **Color**

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Color    | <font color='blue'>development complete</font> | Screen/Main | 0.1              | _N/A_             | for vertex color |

  * **Textures**

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Texture  | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Texture management | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Pixel format and convertion | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Image    | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Image loading | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |
| Image management | <font color='purple'>in development</font> | Screen/Main | 0.1              | _N/A_             | _N/A_       |

# Screen/OpenGL pack #

  * **Vertices and Indices**

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Index Buffer | <font color='blue'>development complete</font> | Screen/OpenGL | 0.1              | _N/A_             | 2 or 4 byte size index buffer |
| Vertex Buffer | <font color='blue'>development complete</font> | Screen/OpenGL | 0.1              | _N/A_             | _N/A_       |
| Vertex Format | <font color='blue'>development complete</font> | Screen/OpenGL | 0.1              | _N/A_             | _N/A_       |

  * **Textures**

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Texture  | <font color='purple'>in development</font> | Screen/OpenGL | 0.1              | _N/A_             | doesn't work yet |

  * **Other**
| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Exceptions | <font color='purple'>in development</font> | Screen/OpenGL | 0.1              | _N/A_             | need additional exceptions |

# Screen/XML pack #

  * **General**

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Dom interface | <font color='blue'>development complete</font> | Screen/XML | 0.1              | _N/A_             | Screen specific DOM interface. |
| Dom implementation | <font color='purple'>in development</font> | Screen/XML | 0.1              | _N/A_             | Screen specific DOM implementation. |
| Parser interface | <font color='blue'>development complete</font> | Screen/XML | 0.1              | _N/A_             | _N/A_       |

  * **Xerces implementation**

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Xerces parser | <font color='purple'>in development</font> | Screen/XML | 0.1              | _N/A_             | _N/A_       |

# Screen/Fields pack #

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Field interface | <font color='purple'>in development</font> | Screen/Fields | 0.1              | _N/A_             | Common field interface to all fields |
| String Field | <font color='purple'>in development</font> | Screen/Fields | 0.1              | _N/A_             | _N/A_       |
| Template Sized String Field  | <font color='purple'>in development</font> | Screen/Fields | 0.1              | _N/A_             | _N/A_       |
| Boolean field | <font color='purple'>in development</font> | Screen/Fields | 0.1              | _N/A_             | _N/A_       |
| Integer field | <font color='purple'>in development</font> | Screen/Fields | 0.1              | _N/A_             | _N/A_       |
| Float field | <font color='purple'>in development</font> | Screen/Fields | 0.1              | _N/A_             | _N/A_       |

# Screen/Memory pack #

| **Name** | **Current state** | **Pack** | **Next version** | **Last delivery** | **Comment** |
|:---------|:------------------|:---------|:-----------------|:------------------|:------------|
| Memory manager | <font color='purple'>in development</font> | Screen/Memory | 0.1              | _N/A_             | Singleton for memory pools management |
| Memory buffers | <font color='purple'>in development</font> | Screen/Memory | 0.1              | _N/A_             | Handlers for memory pools |
| Memory policies | <font color='red'>empty</font> | Screen/Memory | 0.1              | _N/A_             | Policies for memory buffers (mainly for compute buffer size improvement) |