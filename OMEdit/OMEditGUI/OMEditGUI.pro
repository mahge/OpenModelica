#
 # This file is part of OpenModelica.
 #
 # Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 # c/o Linköpings universitet, Department of Computer and Information Science,
 # SE-58183 Linköping, Sweden.
 #
 # All rights reserved.
 #
 # THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 # THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 # ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES RECIPIENT'S ACCEPTANCE
 # OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 #
 # The OpenModelica software and the Open Source Modelica
 # Consortium (OSMC) Public License (OSMC-PL) are obtained
 # from OSMC, either from the above address,
 # from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 # http://www.openmodelica.org, and in the OpenModelica distribution.
 # GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 #
 # This program is distributed WITHOUT ANY WARRANTY; without
 # even the implied warranty of  MERCHANTABILITY or FITNESS
 # FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 # IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 #
 # See the full OSMC Public License conditions for more details.
 #
 #/

QT += network core gui webkit xml xmlpatterns svg opengl
greaterThan(QT_MAJOR_VERSION, 4) {
  QT += printsupport widgets webkitwidgets opengl
}

TRANSLATIONS = Resources/nls/OMEdit_de.ts \
  Resources/nls/OMEdit_es.ts \
  Resources/nls/OMEdit_fr.ts \
  Resources/nls/OMEdit_it.ts \
  Resources/nls/OMEdit_ja.ts \
  Resources/nls/OMEdit_ro.ts \
  Resources/nls/OMEdit_ru.ts \
  Resources/nls/OMEdit_sv.ts \
  Resources/nls/OMEdit_zh_CN.ts

TARGET = OMEdit
TEMPLATE = app

# This is very evil, lupdate just look for SOURCES variable and creates translations. This section is not compiled at all :)
evil_hack_to_fool_lupdate {
  SOURCES += ../../../OMPlot/OMPlotGUI/*.cpp
}

# Windows libraries and includes
win32 {
  OPENMODELICAHOME = $$(OPENMODELICAHOME)
  # define used for OpenModelica C-API
  DEFINES += IMPORT_INTO=1
  # win32 vs. win64
  contains(QT_ARCH, i386) { # 32-bit
    QMAKE_LFLAGS += -Wl,--stack,16777216,--enable-auto-import,--large-address-aware
  } else { # 64-bit
    QMAKE_LFLAGS += -Wl,--stack,33554432,--enable-auto-import
  }
  # release vs debug
  CONFIG(release, debug|release) { # release
    # required for backtrace
    # In order to get the stack trace in Windows we must add -g flag. Qt automatically adds the -O2 flag for optimization.
    # We should also unset the QMAKE_LFLAGS_RELEASE define because it is defined as QMAKE_LFLAGS_RELEASE = -Wl,-s in qmake.conf file for MinGW
    # -s will remove all symbol table and relocation information from the executable.
    QMAKE_CXXFLAGS += -g
    QMAKE_LFLAGS_RELEASE =
    # win32 vs. win64
    contains(QT_ARCH, i386) { # 32-bit
      LIBS += -L$$(OMDEV)/tools/msys/mingw32/lib/binutils -L$$(OMDEV)/tools/msys/mingw32/bin -L$$(OMDEV)/tools/msys/mingw32/lib -L$$(OPENMODELICAHOME)/../OMCompiler/3rdParty/FMIL/install/lib
    } else { # 64-bit
      LIBS += -L$$(OMDEV)/tools/msys/mingw64/lib/binutils -L$$(OMDEV)/tools/msys/mingw64/bin -L$$(OMDEV)/tools/msys/mingw64/lib -L$$(OPENMODELICAHOME)/../OMCompiler/3rdParty/FMIL/install/lib
    }
    LIBS += -limagehlp -lbfd -lintl -liberty -llibosg.dll -llibosgViewer.dll -llibOpenThreads.dll -llibosgDB.dll -llibosgGA.dll
  } else { # debug
    contains(QT_ARCH, i386) { # 32-bit
      LIBS += -L$$(OMDEV)/tools/msys/mingw32/lib -L$$(OPENMODELICAHOME)/../OMCompiler/3rdParty/FMIL/install/lib
    } else { # 64-bit
      LIBS += -L$$(OMDEV)/tools/msys/mingw64/lib -L$$(OPENMODELICAHOME)/../OMCompiler/3rdParty/FMIL/install/lib
    }
    LIBS += -llibosgd.dll -llibosgViewerd.dll -llibOpenThreadsd.dll -llibosgDBd.dll -llibosgGAd.dll
  }
  LIBS += -L../OMEditGUI/Debugger/Parser -lGDBMIParser \
    -L$$(OMBUILDDIR)/lib/omc -lomantlr3 -lOMPlot -lomqwt \
    -lOpenModelicaCompiler -lOpenModelicaRuntimeC -lfmilib -lModelicaExternalC -lomcgc -lpthread -llibfmilib -lshlwapi\
    -lws2_32

  INCLUDEPATH += $$(OMBUILDDIR)/include/omplot \
    $$(OMBUILDDIR)/include/omplot/qwt \
    $$(OMBUILDDIR)/include/omc/antlr3 $$(OMBUILDDIR)/include/omc/c

  RC_FILE = rc_omedit.rc
  CONFIG += osg
} else { # Unix libraries and includes
  include(OMEdit.config)
  # On unix we use backtrace of execinfo.h which requires -rdynamic
  # The symbol names may be unavailable without the use of special linker
  # options.  For systems using the GNU linker, it is necessary to use
  # the -rdynamic linker option.  Note that names of "static" functions
  # are not exposed, and won't be available in the backtrace.
  CONFIG(release, debug|release) {
    QMAKE_LFLAGS_RELEASE += -rdynamic
  }
}

SOURCES += main.cpp \
  Util/Helper.cpp \
  Util/Utilities.cpp \
  Util/StringHandler.cpp \
  MainWindow.cpp \
  $$OPENMODELICAHOME/include/omc/scripting-API/OpenModelicaScriptingAPIQt.cpp \
  OMC/OMCProxy.cpp \
  Modeling/MessagesWidget.cpp \
  Modeling/LibraryTreeWidget.cpp \
  Modeling/Commands.cpp \
  Modeling/CoOrdinateSystem.cpp \
  Modeling/ModelWidgetContainer.cpp \
  Modeling/ModelicaClassDialog.cpp \
  Options/OptionsDialog.cpp \
  Editors/BaseEditor.cpp \
  Editors/ModelicaEditor.cpp \
  Editors/TransformationsEditor.cpp \
  Editors/TextEditor.cpp \
  Editors/CEditor.cpp \
  Editors/MetaModelEditor.cpp \
  Editors/MetaModelicaEditor.cpp \
  Plotting/PlotWindowContainer.cpp \
  Component/Component.cpp \
  Annotations/ShapeAnnotation.cpp \
  Component/CornerItem.cpp \
  Annotations/LineAnnotation.cpp \
  Annotations/PolygonAnnotation.cpp \
  Annotations/RectangleAnnotation.cpp \
  Annotations/EllipseAnnotation.cpp \
  Annotations/TextAnnotation.cpp \
  Annotations/BitmapAnnotation.cpp \
  Component/ComponentProperties.cpp \
  Component/Transformation.cpp \
  Modeling/DocumentationWidget.cpp \
  Simulation/SimulationDialog.cpp \
  Simulation/SimulationOutputWidget.cpp \
  Simulation/SimulationProcessThread.cpp \
  Simulation/SimulationOutputHandler.cpp \
  TLM/FetchInterfaceDataDialog.cpp \
  TLM/FetchInterfaceDataThread.cpp \
  TLM/TLMCoSimulationDialog.cpp \
  TLM/TLMCoSimulationOutputWidget.cpp \
  TLM/TLMCoSimulationThread.cpp \
  FMI/ImportFMUDialog.cpp \
  FMI/ImportFMUModelDescriptionDialog.cpp \
  Plotting/VariablesWidget.cpp \
  Options/NotificationsDialog.cpp \
  Annotations/ShapePropertiesDialog.cpp \
  TransformationalDebugger/OMDumpXML.cpp \
  TransformationalDebugger/diff_match_patch.cpp \
  TransformationalDebugger/TransformationsWidget.cpp \
  Debugger/GDB/CommandFactory.cpp \
  Debugger/GDB/GDBAdapter.cpp \
  Debugger/StackFrames/StackFramesWidget.cpp \
  Debugger/Locals/LocalsWidget.cpp \
  Debugger/Locals/ModelicaValue.cpp \
  Debugger/Breakpoints/BreakpointMarker.cpp \
  Debugger/Breakpoints/BreakpointsWidget.cpp \
  Debugger/Breakpoints/BreakpointDialog.cpp \
  Debugger/DebuggerConfigurationsDialog.cpp \
  Debugger/Attach/AttachToProcessDialog.cpp \
  Debugger/Attach/ProcessListModel.cpp \
  CrashReport/backtrace.c \
  CrashReport/CrashReportDialog.cpp

HEADERS  += Util/Helper.h \
  Util/Utilities.h \
  Util/StringHandler.h \
  MainWindow.h \
  $$OPENMODELICAHOME/include/omc/scripting-API/OpenModelicaScriptingAPIQt.h \
  OMC/OMCProxy.h \
  Modeling/MessagesWidget.h \
  Modeling/LibraryTreeWidget.h \
  Modeling/Commands.h \
  Modeling/CoOrdinateSystem.h \
  Modeling/ModelWidgetContainer.h \
  Modeling/ModelicaClassDialog.h \
  Options/OptionsDialog.h \
  Editors/BaseEditor.h \
  Editors/ModelicaEditor.h \
  Editors/TransformationsEditor.h \
  Editors/TextEditor.h \
  Editors/CEditor.h \
  Editors/MetaModelEditor.h \
  Editors/MetaModelicaEditor.h \
  Plotting/PlotWindowContainer.h \
  Component/Component.h \
  Annotations/ShapeAnnotation.h \
  Component/CornerItem.h \
  Annotations/LineAnnotation.h \
  Annotations/PolygonAnnotation.h \
  Annotations/RectangleAnnotation.h \
  Annotations/EllipseAnnotation.h \
  Annotations/TextAnnotation.h \
  Annotations/BitmapAnnotation.h \
  Component/ComponentProperties.h \
  Component/Transformation.h \
  Modeling/DocumentationWidget.h \
  Simulation/SimulationOptions.h \
  Simulation/SimulationDialog.h \
  Simulation/SimulationOutputWidget.h \
  Simulation/SimulationProcessThread.h \
  Simulation/SimulationOutputHandler.h \
  TLM/FetchInterfaceDataDialog.h \
  TLM/FetchInterfaceDataThread.h \
  TLM/TLMCoSimulationOptions.h \
  TLM/TLMCoSimulationDialog.h \
  TLM/TLMCoSimulationOutputWidget.h \
  TLM/TLMCoSimulationThread.h \
  FMI/ImportFMUDialog.h \
  FMI/ImportFMUModelDescriptionDialog.h \
  Plotting/VariablesWidget.h \
  Options/NotificationsDialog.h \
  Annotations/ShapePropertiesDialog.h \
  TransformationalDebugger/OMDumpXML.cpp \
  TransformationalDebugger/diff_match_patch.h \
  TransformationalDebugger/TransformationsWidget.h \
  Debugger/GDB/CommandFactory.h \
  Debugger/GDB/GDBAdapter.h \
  Debugger/StackFrames/StackFramesWidget.h \
  Debugger/Locals/LocalsWidget.h \
  Debugger/Locals/ModelicaValue.h \
  Debugger/Breakpoints/BreakpointMarker.h \
  Debugger/Breakpoints/BreakpointsWidget.h \
  Debugger/Breakpoints/BreakpointDialog.h \
  Debugger/DebuggerConfigurationsDialog.h \
  Debugger/Attach/AttachToProcessDialog.h \
  Debugger/Attach/ProcessListModel.h \
  CrashReport/backtrace.h \
  CrashReport/CrashReportDialog.h

CONFIG(osg) {

SOURCES += Animation/AnimationWindow.cpp \
  Animation/ExtraShapes.cpp \
  Animation/Visualizer.cpp \
  Animation/VisualizerMAT.cpp \
  Animation/VisualizerCSV.cpp \
  Animation/VisualizerFMU.cpp \
  Animation/FMUWrapper.cpp \
  Animation/Shapes.cpp \
  Animation/TimeManager.cpp \
  ../../osgQt/GraphicsWindowQt.cpp \


HEADERS += Animation/AnimationWindow.h \
  Animation/AnimationUtil.h \
  Animation/ExtraShapes.h \
  Animation/Visualizer.h \
  Animation/VisualizerMAT.h \
  Animation/VisualizerCSV.h \
  Animation/VisualizerFMU.h \
  Animation/FMUWrapper.h \
  Animation/Shapes.h \
  Animation/TimeManager.h \
  Animation/rapidxml.hpp \
  ../../osgQt/OMEdit_GraphicsWindowQt.h \
  ../../osgQt/Export
}

LIBS += -lqjson
INCLUDEPATH += ../../qjson/build/include

INCLUDEPATH += $$OPENMODELICAHOME/include/omc/scripting-API \
  $$OPENMODELICAHOME/include/omc/c/util \
  $$OPENMODELICAHOME/../OMCompiler/3rdParty/FMIL/install/include

OTHER_FILES += Resources/css/stylesheet.qss \
  Resources/XMLSchema/tlmModelDescription.xsd \
  Debugger/Parser/GDBMIOutput.g \
  Debugger/Parser/GDBMIParser.h \
  Debugger/Parser/GDBMIParser.cpp \
  Debugger/Parser/main.cpp

# Please read the warnings. They are like vegetables; good for you even if you hate them.
CONFIG += warn_on
# Only disable the unused variable/function/parameter warning
win32 {
  QMAKE_CXXFLAGS += -Wno-clobbered -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter
}

RESOURCES += resource_omedit.qrc

DESTDIR = ../bin

UI_DIR = ../generatedfiles/ui

MOC_DIR = ../generatedfiles/moc

RCC_DIR = ../generatedfiles/rcc

ICON = Resources/icons/omedit.icns
