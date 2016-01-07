  * **Back links**
    * [Main page of Screen Wiki](MainPage.md)

# Introduction #

This document list all recommanted coding rules for Screen project's developpers.


# Naming conventions #

_This paragraph is not validated yet, it is a proposition. Maybe we could use this for ideas: [geosoft ccp style](http://geosoft.no/development/cppstyle.html)_

If not said, for all names composed of several word, each first character of the word is in upper case (ex: AClassName).

## Class names ##

Class name must start with a upper case.

## Struture name ##

See class names.

## Types ##

See class names.

Example: `TypeName`

## Methods ##

Methods names start with a lower case (except for static).

## Functions ##

Function names start with a upper case.

## Variables ##

Non static variables start with a lower case.

Class attributes, start with a `_`.

Methods or functions arguments start by the letter `i`, `o` or `io` depending if they are input, outputs or both.

Local variables start with the letter `a`.

Global variables start with the letter `g`. Should not be used

One letter variables (i, j, k ...) should not be used.


Examples:
```
int _attribute;
float _StaticAttribute;
void method(const int iArgument, int &oOutput, std::string& ioInputAndOutput);
void StaticMethod(const int iArgument, int &oOutput, std::string& ioInputAndOutput);
int aLocalVariable;
int gGlobalVariable;
```

## Static ##

All static (variables, methods, functions) starts by an upper case (if the variable starts with a non-alphabetic symbol, the first real letter of the name is in upper case).

## Macro ##

Macro names should be in upper case. If composed by several words, wordls should beseparated by `_`.

Example: `A_MACRO`

If you have an independant piece of code in a macro you should declare it like this:

```
do {                 \
<your code>          \
<your code again>    \
}while(0)      
```

## Enum ##

Enum should be like classes (or maybe change the end).

The content of the enum should be all in upper case. If composed of several words, the words should be separated by `_`.

Example:
```
MyEnum
{
  VALUE_1,
  VALUE_2
};
```

## Namespaces ##

Namespaces should all be in lower case.

# Code style #

## Indentation ##

### Tabulations ###

Tabulation policy: all tabs

Tabulation size: 4

### Indent ###

Indent 'public', 'protected', 'private' within class body: N

Indent declarations relatively to 'public', 'protected', 'private': Y

Indent statement within function body: Y

Indent statements within blocks: Y

Indent statements within 'switch' body: Y

Indent statements within 'case' body: Y

Indent 'break' statement: N

Indent declarations within 'namespace' definition: Y

Indent empty lines: Y


### Braces positions ###

Class declaration: open brace on the same line

Namespace declaration: open brace on the same line

Function declaration: open brace on the same line

Blocks (if, for, while, do ...): open brace on the same line

Block in 'switch' statement: open brace on the same line

Block in 'case' statement: open brace on the same line

Initializer List: (ex: int digits[.md](.md) = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };)


### Control statements ###

Insert new line before 'else' in an 'if' statement: yes

Insert new line before 'catch' in a 'try' statement: yes

Insert new line before 'while' in a 'do' statement: no


Keep simple 'if' statement on one line: yes

Keep 'else if' on one line: yes

### Line Wrapping ###

Policy : exemple wrap all elements, except first element if not
necessary

Indentation: exemple indent on column