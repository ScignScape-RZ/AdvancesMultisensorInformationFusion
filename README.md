
# Advances in Multisensor Information Fusion
## Data Set and Code Base 

This data set derives from _Advances in multisensor information fusion: A Markov–Kalman viscosity fuzzy statistical predictor for analysis of oxygen flow, diffusion, speed, temperature, and time metrics in CPAP_ by James A. Rodger.

There are several ways to use the code, including several "build strategies".  The quickest option is to use the "`build-quick.pro`" project file in the "`./cpp/projects/qt/qt-multiple/unibuild`" folder.  For most users the best option may be "`build-most.pro`" in the same folder (both versions can be built independently).  The "`quick`" version lacks PDF and TCP features (which is explained via a message box when trying to use these features).

A more complex option is "`build-all.pro`", which is only needed for users wishing to generate test scripts or use other advanced features related to "Runtime Reflection".  This part of dsC is more experimental and requires Embeddable Commmon Lisp (see below).  For developing new code or debugging the executables it may be necessary or easier to use the "`isobuild`" strategy, where each Qt project is built separately, rather than the "`unibuild`" options where projeects are built automatically in order.  Via "`isobuild`" developers can choose which projects to include more precisely.  For the equivalent of "`build-all.pro`" follow the build order listed in "`build-order.txt`".  Note that these comments are only applicable to a small set of users extending or exploring the code in detail.

---
**Downloading**

If you use "`git clone`", it is recommended to provide your own name to the folder where the data set is unpacked.  For example, create a folder called "`AdvancesMultisensorInformationFusion`" or something smaller ("`AMIF`", say) and _inside_ that folder execute "`git clone https://github.com/scignscape/AdvancesMultisensorInformationFusion.git ar`" -- notice the trailing "`ar`" (for "archive") where this repository will be unpacked.  Then the parent "`AMIF`" folder can be used for other files related to the project (or follow-up research) but isolated from the actual repo.

Be aware that using long folder names, rather than succinct names like "`AMIF/ar`", may occasionally cause problems (see "`TROUBLESHOOTING`").

---
**Qt**

The Qt libraries and Qt Creator IDE (Integrated Development Environment) are the only known dependencies for most of the project (the exception being specialized use-cases needing Embeddable Commmon Lisp).  Qt is easy to install from https://www.qt.io/ and is free for noncommercial use.  

Linux users are advised to download and link against a version of Qt different from the Qt libraries bundled with your Desktop Environment.  This is first because Qt versions for Linux desktops are often out-of-date relative to the versions needed by applications, and second because developers should minimize the risk of unintentionally altering the components needed for their Desktop Environment to run.  In effect, the "`qmake`" you use for this repository (and other Qt applications not built-in to your desktop) should live somewhere other than a "`/usr`" subfolder. 

For Windows users, installing Qt is a good way to ensure that you have a C++ development environment, with components like MinGW and g++.  It is recommended to use these tools -- which are based on cross-platform environments -- as opposed to using Microsoft-specific products like the VC++ compiler.

The code in this data set is designed to build and run within Qt Creator.  You do not need a separate build tool like cmake.  Upon loading your preferred project file (e.g., "`build-quick.pro`" or "`build-most.pro`"), you can automatically compile and run the code -- and start exploring the data set -- with Qt Creator's "`Run`" option.  You can use "`build-quick.pro`" to test that your compiler is working properly and quickly browse the data set and then load "`build-most.pro`".  (Note that if you choose "`build-all.pro`" the compile time is noticeably longer -- that's usually not a sign of any problem but see "`TROUBLESHOOTING`".) 

---
**XPDF**

This data set includes a slightly modified version of the open-source XPDF reader (see https://www.xpdfreader.com/).  Users are encouraged to also install the official XPDF Reader.  The version distributed in this repository has been modified to work primarily with this data set.

Users may want to edit the "`./cpp/src/external/xpdf/xpdf/aconf/aconf.h`" file.  If you have (or choose to install) an official XPDF Reader you may want to copy "`aconf.h`" from that code base ("`aconf.h`" will be generated during cmake; this data set provides a default "`aconf.h`" file to eliminate the need for cmake as a build tool for the data set over all).

---
**TROUBLESHOOTING**

1.  Except with "`build-quick.pro`", the build process will generate multiple executable files, some for testing or related documentation.  Most of the times users will want the executable called "`dsmain-console`" (the project named "`__run_dsmain-console`") which should run automatically.  However, any executable may be chosen by right-clicking on the project as listed on Qt Creator's Project Panel (usually on the left of the IDE) or by selecting that desired "Run Configuration" from the "Run Settings" section of the "Projects" tab (at the far-left of the IDE).  If the application does not seem to run properly, it may be because the wrong executable selection is chosen for the default Run Configuration, so the "`__run_dsmain-console`" option should be chosen from the drop-down list in "Run Settings".

2.  The dsC project organization uses Qt naming conventions to automatically configure an environment so typical users can easily build and launch the main ("`dsmain-console`") application and other executables.  This process will fail if a working Qt environment (called a Qt "`kit`") is not available _before_ the "`build-quick.pro`" or other project files are opened in the IDE.  It is recommended to double-check that you have a valid kit ("`Options`" -- "`Build & Run`" -- "`Kits`") and start a new, blank session (via the menubar "`File`" -- "`Sessions`" submenu) before starting to use this data set.

3.  Because of a quirk, Qt Creator will on some systems misidentify project files with unusually long paths, causing an endless loop during the build (because "`qmake`" will run repeatedly).  This is most likely a problem for users choosing the more complex "`build-all`" or "`isobuild`" strategies.  If you use these options, keep an eye on the "Compiler Output" window on Qt Creator and make sure "`qmake`" is not running multiple times on one file (this attention ceases to be necessary once the Compiler Output suggests that all of the "`qmake`" files are processed and the compiler has started to generate object files).  If you do encounter a loop, you may either rename the problemmatic "`.pro`" files -- this repo chooses to give projects relatively long, descriptive names -- or choose shorter names like "`SSQM/ar`" for the repo folder and its parent.  Alternatively, employ the "`isobuild`" approach where you can manually decide when to run "`qmake`".

4.  For "`build-all`", or "`isobuild`" using the more advanced Runtime Reflection features, be sure that Embeddable Common Lisp is installed on your computer in locations that match the paths described in "`find-ecl-sexpr.pri`" (see below).  If the needed ECL components are not found, the project may fail to build and/or run.  You may need to copy "`ecl.dll`" or "`ecl.so`" to the folder where the "`dsmain-console`" executable is deployed (something like "`./cpp/targets/qt/qt-multiple/targets-5-10-1-UNIBUILD-all`").

---
**ECL**

This code may optionally use ECL (Embeddable Common Lisp) and a C++ ECL wrapper called cl-cxx.  Both of these are easy to find and build: check 
https://common-lisp.net/project/ecl/ and https://github.com/juanjosegarciaripoll/cl-cxx.

You may need to edit the "`find-ecl-sexpr.pri`" file to point to 
the correct folder(s) where ECL includes and libs are located.

Note that this data set also includes code from the Sexpresso project, used here to clean up generated Lisp files: the code is copied here for convenience, but please see https://github.com/BitPuffin/sexpresso for the original.  (The Sexpresso project is minimally used here and it is hard to find much information about it; generic searches for "`Sexpresso`" tend to find, um, other kinds of content.)

---
**R/Z**

The R/Z project can be used for more advanced Runtime Reflection for datasets.  As it is still experimental, R/Z is not documented thoroughly.  Please inquire for more information.  

The simplest use-case for R/Z is to build Intermediate Representation files to pass to the main ("`dsmain-console`") application.  In this case the application does not need to embed an R/Z scripting environment in the application itself, just a simpler capability to process Intermediate Representation in the "Kauvir" format.  A more advanced use-case is to script main applications directly, which is outside the scope of this data set.

See "`./scripts/rz-kph/t1.rz`" for an example of a script to generate a "Kauvir" file that is not immediately executed but can be saved to pass to "`dsmain-console`" via the "`kauvir-phaon-tcp-console`" executable. 

To check the R/Z environment overall, test the R/Z compiler with "`rz-graph-dynamo-runtime-console`" or one of the other "rz-dynamo" executables.  The "`t1.rz`" file can have sample code like: 
```
,fnd ::: Fn_Doc*;
fnd \== default; 

,kenv ::: KCM_Env*;
kenv \= (envv "KCM_Env*");

fnd -> init kenv;

,test-fn ::: .(int)  $-> extern;

fnd -> read  "test-fn";

```

Other examples of sample code are in the "`scripts`" folder.  Multiple 
samples can be executed in sequence with the project/executable called "`rz-multi-console`".

So for example, after confirming that "`t1.rz`" runs properly, try "`rz-multi-console`" which (as coded) will run all scripts listed in the "`./scripts/rz/m1.txt`" file; "`m1.txt`" lists scripts to run in sequence (e.g. as an informal test suite). 

Testing multiple scripts can also be achieved by including them all in one script with "`<#...>`" notation, e.g. script "`t24.txt`" in "`./ar/scripts/rz`" has the two lines "`<#t23>`" and "`<#t25>`".

---
**COMMENTS**

R/Z and other advanced features will continue to evolve for this and other dsC data sets.  This repository will be updated accordingly.  Please check back!
