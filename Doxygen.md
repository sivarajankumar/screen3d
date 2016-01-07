  * **Back links**
    * [Main page of Screen Wiki](MainPage.md)

# Introduction #

Doxygen is an auto-documentation system for C++, C, Java, Objective-C, Python, IDL (Corba and Microsoft flavors), Fortran, VHDL, PHP, C#, and to some extent D.

In this documentation we will see how to use Doxygen for Screen project, but they are many other ways to use Doxygen we won't see. For more information you can consult [Doxygen official documentation](http://www.stack.nl/~dimitri/doxygen/manual.html).

# Standard commands #

I will now explain some of the commands we will use in Screen project. Many commands allow us to comment C++ elements (class, struct, functions, macro ...) in other files.

But we are not gonna use those features, so if you really need information about it consult Doxygen website.

Sometimes there is several ways to do the same thing, but i will just explain one, which must be used in Screen project.

All commands, can be written using \ or @. So \brief is the same as @brief.

## Block Documentation ##

There is four ways to create a comment block for Doxygen. We will use the double `*` C comments.

```
/**
 * ... Documentation ...
 */
```

Note that the stars inside the block (at the beginning the each lines) are useless.

Those blocks must be added before the element you need to comment (or at the beginning of file for file comment).

In those blocks, you will add commands, and a long description. Some commands work for an entire paragraph. Paragraph are separated by empty lines.

## Line Documentation ##

A line documentation will be done using a C++ triple / comment :
```
 ///  ... Documentation ...
```
As for blocks, line work for the code that follow the comment. But if your want to comment the element before, you must use '<' command :

```
int i = 0; ///< index i.
```
It is very useful to comment class variables, or function arguments.

## \file command ##

The \file command must be used in the block at the beginning of the file, and contains the file name.

## \brief command ##

The \brief command is used in all the bloc to set a brief description of the element following the comment.

## \author command ##

The \file command must be used in the block at the beginning of the file, and contains the author name. You can have several /author commands, if you have several authors.

## \param command ##

The \param command, define the parameters of a function. You must use it like this :
`\param[in-out-attribute] <parameter-name> { parameter description `}
The in out attribute define if the parameter is `[in]` `[out]` or `[in,out]`.


The existence of the parameter is checked and a warning is given if the documentation of this (or any other) parameter is missing or not present in the function declaration or definition.

Sample with memcpy:
```
/**
 Copies bytes from a source memory area to a destination memory area,
 where both areas may not overlap.
 \param[out] dest The memory area to copy to.
 \param[in]  src  The memory area to copy from.
 \param[in]  n    The number of bytes to copy
 */
void memcpy(void *dest, const void *src, size_t n);

```

## \tparam command ##

Starts a template parameter for a class or function template parameter with name \<template-parameter-name\>, followed by a description of the template parameter.
You must use it like this:
`\tparam <template-parameter-name> { description `}

## \return command ##

The \return command, describe the return value of a function.

## \bug command ##

The \bug command can be used to describe a known bug for this class or function. You can use several \bug commands in a block.

## \deprecated command ##

The \deprecated can be used to add a paragraph to precise if the commented element is deprecated.

## \sa or \see command ##

The \sa can be used to create a reference to another method, class or file. Same than \see command.

## \exception or \throws or \throw ##

The \exception <Exception object> {description} can be used to tell which exception can be thrown by the method. Same than \throws or \throw commands.

## Other commands ##

There are several other useful commands to use inside a comment block :

  * `\a` : to use a special font for the next word.
  * `\b` : to use bold font for the next word.
  * `\c` : to use a typewriter font for the next word.
  * `\e` or `\em` : to use italic font for the next word.
  * `\code` : to start a block of code (end with `\endcode`).
  * `\dot` : to start a block containing a valid description of a dot graph (end with `\enddot`). See Doxygen documentation for more information.
  * `\msc` : to start a block containing a valid description message sequence chart (end with `\endmsc`). See Doxygen documentation for more information.
  * `\verbatim` : to start a block where commands are not interpreted (end with `\endverbatim`).
  * `\f$` : to start an in-line LateX mathematics formula (end with `\f$`). See Latex Documentation.
  * `\f[` : to start an long LateX mathematics formula (end with `\f]`). See Latex Documentation.
  * `\image <format> <file> ["caption"] [<sizeindication>=<size>]` : to include an image.
  * `\n` : to add a new line.
  * `\\, \@, \&, \$, \#, \<, \>, \%, \"` : to display `\, @, &, $, #, <, >, %, "`.

## Unused commands : \class \fn \struct \def ... ##

We will not use \class, \fn .. commands, because in Screen project you will always define comment block just before the element definition.

# Sample #

```
#ifndef SAMPLE_H_
#define SAMPLE_H_

/**
 * \file Sample.h
 * \brief sample class for Doxygen comments
 * \author user
 *
 * This class is used to present some of the Doxygen ways to do comments for Screen 
 * (this is a long description). 
 */
#include <string>
#include <list>

/**
 * namspace for Doxygen presentation
 */
namespace doxygen{
  /**
   * \brief brief class description
   * \bug this class doesn't do anything
   *
   *  Long class description
   */
  class Sample{
  private:
    std::list<std::string> _list; ///< a list
    std::list<std::string>::iterator _listIt; ///< iterator on list
                                                

  public:
    /**
     *  \brief constructor
     *
     *  Sample class constructor
     *
     *  \param[in] list a list in parameters
     */
    Sample(std::list<std::string> iList);

    /**
     *  \brief Destructor
     *
     *  Sample class destructor
     */
    virtual ~Sample();

  public:
    /**
     *  \brief add to list
     *
     *  Method that add a \e thing to the list and return \e true if added
     *
     *  \param[in] iThing thing to add
     *  \return true if added
     */
    bool add2(std::string iThing);

    /**
     * \brief add to list
     *
     * Method that add a \e thing to the list
     *
     * \param[in] iThing thing to add
     *
     * \deprecated this method is deprecated
     */
     void add(std::string iThing);

  };
} 

#endif

```