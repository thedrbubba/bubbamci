~~~
https://github.com/catchorg/Catch2/blob/devel/docs/test-fixtures.md#top
https://github.com/catchorg/Catch2/blob/devel/docs/test-cases-and-sections.md#top


We need a particle model and a RNG.
Event Handling.... two events at first, in this order. Boundary and then Collison.

~~~


# BubbaMake
This project is mainly meant as a demonstration of setup for a C++ cmake project (including header-only). Other libraries use and behaviors are show below. 

* [Boost](https://github.com/boostorg) (target: boost)                                `-DBMAKE_ENABLE_DEPENDENCY_BOOST:BOOL=ON/OFF`           [BMake/Dep/Boost_Find.cmake](./cmake_files/BMake/Dep/Boost_Find.cmake)
* [Catch](https://github.com/catchorg/Catch2) (target: catch)                         `-DBMAKE_ENABLE_DEPENDENCY_CATCH:BOOL=ON/OFF`           [BMake/Dep/Catch_Find.cmake](./cmake_files/BMake/Dep/Catch_Find.cmake)
* [MPark Variant](https://github.com/mpark/variant) (target: mpark\_variant)          `-DBMAKE_ENABLE_DEPENDENCY_MPARK_VARIANT:BOOL=ON/OFF`  [BMake/Dep/MParkV_Find.cmake](./cmake_files/BMake/Dep/MParkV_Find.cmake)

See [cmake_files/BMake/Options.cmake](./cmake_files/BMake/Options.cmake) for CMake options to use in the cmake commandline below. The `BDEPEND_ENABLE_DEPENDENCCY_<package>` are defined here, too. 

For example: `-DBMAKE_ENABLE_DEPENDENCY_BOOST:BOOL=OFF`

Usage:

~~~
git clone <repo address>/bubbamake.git bubbamake.git
cd bubbamake.git
mkdir build; cd build
cmake -DCMAKE_PREFIX_PATH=<boost package> ../   # This setups up the configuring for the make to do the work. Need an installed version of Boost. See next exampl if you do not have one.
make -j N                                       # This will actually executes the download, build, and install of the packages.
~~~

~~~
git clone <repo address>/bubbamake.git bubbamake.git
cd bubbamake.git
mkdir build; cd build
cmake -DBMAKE_ENABLE_DEPENDENCY_BOOST:BOOL=OFF ../
make -j N

If the package allows the tests to built automatically then it will be exercised.

If the package allows the tests to be executed automatically it will be exercised.

./GIT_REPO/bubbalastic.git
cd ./GIT_REPO/bubbaliastic.obj
cmake -D CMAKE_INSTALL_PREFIX=/home/drbubba/Packages/boost ../bubbalastics.git
~~~

---

`Boost` has to be found with CMake's `find_package`. You will need a `-DCMAKE_PREFIX_PATH` for the installed Boost library. At this time, Boost cannot be fetched like the other dependency packages. The only Boost library used in BubbaMake is `boost::assert`.


---

Notes: User beware that `installations` have not be worked out, yet. 

 
# bubbamci
