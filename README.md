dexpert
=======

current version: 0.1


A toolbox to manipulate DEX files. It's a C library that will be able to:
* parse a DEX file
* Rewrite a DEX file
* Manipulate very deeply the DEX elements

Why another DEX parser library you will ask ?
You're right, there are plenty of good libraries that are able to parse a DEX file. For example:
* The **AOSP** ([https://source.android.com/](https://source.android.com/))
* LIEF ([https://github.com/lief-project/LIEF](https://github.com/lief-project/LIEF))

**BUT** none of these libraries can rewrite a dex !! You can parse a DEX, manipulate him, but you can't rebuild a new one after your manipulations.
The goal of **DEXPERT** is to provide a good and powerful library that are able to rebuild a valid DEX file.

Rebuild a valid DEX file can be useful to:
* unpack obfuscated Android application (ex: DexGuard)
* develop your own packer to obfuscate your Android app.
* Patch all your favorite applications (to remove ads for example)


Compilation
-----------

To compile the `dexpert.a` library, you will need a basic compilation system (clang, gcc, ...). Not tested on Windows but it should works (it is only simple C files with no dependencies).

You can compile it using a toolchain for another architecture (To make it runnable on an Android device for exemple). You will have to:
* define the **CROSS** environnement variable to the path of the toolchain
* run the Makefile as usual

To compile the library, go in the src folder and `$ make`

Their are some examples you can compile:
`$ cd examples && make`

