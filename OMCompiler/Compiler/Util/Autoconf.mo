encapsulated package Autoconf

  constant Boolean haveBStatic = true;
  constant String bstatic = if haveBStatic then "-Wl,-Bstatic" else "";
  constant String bdynamic = if haveBStatic then "-Wl,-Bdynamic" else "";
  constant String configureCommandLine = "Configured 2020-11-21 14:57:36 using arguments:  '--disable-option-checking' '--prefix=/home/mahge/dev/OpenModelica/build' '--with-ombuilddir=/home/mahge/dev/OpenModelica/build' '--cache-file=/dev/null' '--srcdir=.'";
  constant String os = "linux";
  constant String make = "make";
  constant String exeExt = "";
  constant String dllExt = ".so";
  constant String ldflags_runtime = " -Wl,--no-as-needed -Wl,--disable-new-dtags -lOpenModelicaRuntimeC  -llapack -lblas   -lm -lomcgc -lpthread -rdynamic";
  constant String ldflags_runtime_sim = " -Wl,--no-as-needed -Wl,--disable-new-dtags -lSimulationRuntimeC  -llapack -lblas   -lm -lomcgc -lpthread -rdynamic -Wl,--no-undefined";
  constant String ldflags_runtime_fmu = " -Wl,--no-as-needed -Wl,--disable-new-dtags  -llapack -lblas   -lm -lpthread -rdynamic -Wl,--no-undefined";

  constant String platform = "Unix";
  constant String pathDelimiter = "/";
  constant String groupDelimiter = ":";

  constant String corbaLibs = "";
  constant String hwloc = if 0 == 1 then "-lhwloc" else "";
  constant list<String> systemLibs = {"-lomcruntime", "-lexpat", "-lsqlite3", "-llpsolve55_pic -lcolamd -lm -ldl ", corbaLibs, "-lomcgc", hwloc};

  constant String triple = "x86_64-linux-gnu";

annotation(__OpenModelica_Interface="util");
end Autoconf;
