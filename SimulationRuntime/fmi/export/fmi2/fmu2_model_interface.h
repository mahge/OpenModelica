/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES RECIPIENT'S ACCEPTANCE
 * OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

#ifndef __FMU2_MODEL_INTERFACE_H__
#define __FMU2_MODEL_INTERFACE_H__

#include "fmiFunctions.h"
#include "simulation_data.h"

#ifdef __cplusplus
extern "C" {
#endif

// macros used to define variables
#define pos(z) comp->isPositive[z]
#define copy(vr, value) setString(comp, vr, value)

// categories of logging supported by model.
// Value is the index in logCategories of a ModelInstance.
#define LOG_ALL       0
#define LOG_ERROR     1
#define LOG_FMI_CALL  2
#define LOG_EVENT     3

#define NUMBER_OF_CATEGORIES 4

typedef enum {
  modelInstantiated       = 1<<0,
  modelInitializationMode = 1<<1,
  modelInitialized        = 1<<2, // state just after fmiExitInitializationMode
  modelStepping           = 1<<3, // state after initialization
  modelTerminated         = 1<<4,
  modelError              = 1<<5
} ModelState;

typedef struct {
  fmiString instanceName;
  fmiType type;
  fmiString GUID;
  const fmiCallbackFunctions *functions;
  fmiBoolean loggingOn;
  fmiBoolean logCategories[NUMBER_OF_CATEGORIES];
  fmiComponentEnvironment componentEnvironment;
  ModelState state;
  fmiEventInfo eventInfo;

  DATA* fmuData;
  fmiBoolean toleranceDefined;
  fmiReal tolerance;
  fmiReal startTime;
  fmiBoolean stopTimeDefined;
  fmiReal stopTime;
} ModelInstance;

#ifdef __cplusplus
}
#endif

#endif
