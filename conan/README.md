# Conan

Creating a new custom settings
    
https://github.com/conan-io/conan-center-index/issues/98#issuecomment-2511395866


Variables and cache variables

https://github.com/conan-io/conan-center-index/pull/22064#discussion_r1695188168


Conan upload package and dependencies:

https://github.com/conan-io/conan/issues/11960#issuecomment-1564052940

conan create ... --format=json > graph.json
conan list --graph=graph.json --graph-binaries=* --format=json > pkglist.json
conan upload --list=pkglist.json -r=myremote



# Autotools

Falla al cross buildear
https://www.gnu.org/software/autoconf/manual/autoconf-2.63/html_node/Runtime.html

OK, en estos casos cuando falla on ./configure, hay que seguir los pasos:
- inspeccionar config.log para ver por qué - si no queda, claro, buscar la linea en ./configure que ha fallado
- inspeccionar ./configure, sabemos que si detecta crossbuilding, falla sin más
- implica esto que no se puede cross compilar? no siempre:
    - a veces hace comprobaciones donde el resultado lo puedes pre-meter en la receta y consigues saltarte la comprobación y crossbuildear sin mas
    - a veces efectivamente no se puede cross compilar, pero lo mínimo es ir a upstream y ver qué tienen documentado, por ej
        - en un "INSTALL" or "BUILD" en las fuentes - menciona si esta soportado o no?
    - como has dicho antes, ./configure es autogenerado - pero autotools deberia ser lo suficientemente listo para saltarse algunos checks cuando crossbuildeas:
        - es posible que se haya generado con una version vieja de autotools, podemos probar autoreconf? (para regenerar ./configure)
        - esta puesto esto en el configure.ac ? o sea, que falle así? de donde viene .. etc


Posible seteo de los checks desde el generate:
https://github.com/zarvox/conan-center-index/blob/677e5dc289f85d80c5d7fffd668a6c0b2167a0bb/recipes/flex/all/conanfile.py#L67-L68

Mirar en repology que hacen otros gestores de paquetes


The self.cpp_info contains the C++ linkage and usage requirements: includedirs, libdirs, libnames, cxxflags. They are used by generators such as CMakeDeps to generate mydep-config.cmake files that contains CMake targets that use these variables or tomydep.pc file for pkg-config via PkgConfigDeps. For some build systems such as Autotools that use environment variables, the generators like AutotoolsDeps can generate environment script files with the equivalent information. This information is very important for libraries, and mostly useless for applications (tool_requires)
The self.buildenv_info are environment variables, they don't go to any build system specific file like mydep-config.cmake, they only go to environment files like conanbuild.sh/bat that need to be activated or sourced to define the environment variables in the consumer developer side if desired. This is very rarely needed for libraries, it is sometimes needed for applications (tool_requires) that need some extra env-vars to run.


cache_variables:
    https://github.com/conan-io/conan-center-index/pull/22064#discussion_r1695188168


# Android

Tiene que haber una version mejor explicada pero la he perdido

emulator -avd Pixel_8_API_VanillaIceCream -netdelay none -netspeed full

adb push test_package /data/local/tmp/test_package
adb push *.so /data/local/tmp/
adb shell ldd /data/local/tmp/test_package
adb shell ls /data/local/tmp/test_package
adb shell

If adb fails, find process id and kill it

lsof -n -i4TCP:5037 | grep LISTEN

# > in shell

cd /data/local/tmp/test_package
ls -la
export LD_LIBRARY_PATH=.
getprop ro.build.version.release # get the android API version
file test_package
./test_package
