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
/*
 *
 * @author Adeel Asghar <adeel.asghar@liu.se>
 *
 * RCS: $Id$
 *
 */

#ifndef TLMCOSIMULATIONDIALOG_H
#define TLMCOSIMULATIONDIALOG_H

#include "MainWindow.h"
#include "TLMCoSimulationOutputWidget.h"
#include "TLMCoSimulationOptions.h"

class MainWindow;
class TLMCoSimulationOutputWidget;

class TLMCoSimulationDialog : public QDialog
{
  Q_OBJECT
public:
  TLMCoSimulationDialog(MainWindow *pMainWindow);
  ~TLMCoSimulationDialog();
  void show(LibraryTreeNode *pLibraryTreeNode);
  void simulationProcessFinished(TLMCoSimulationOptions tlmCoSimulationOptions, QDateTime resultFileLastModifiedDateTime);
  bool isTLMCoSimulationRunning() {return mIsTLMCoSimulationRunning;}
  void setIsTLMCoSimulationRunning(bool isTLMCoSimulationRunning) {mIsTLMCoSimulationRunning = isTLMCoSimulationRunning;}
private:
  MainWindow *mpMainWindow;
  LibraryTreeNode *mpLibraryTreeNode;
  bool mIsTLMCoSimulationRunning;
  Label *mpHeadingLabel;
  QFrame *mpHorizontalLine;
  QGroupBox *mpTLMManagerGroupBox;
  Label *mpManagerProcessLabel;
  QLineEdit *mpManagerProcessTextBox;
  QPushButton *mpBrowseManagerProcessButton;
  Label *mpServerPortLabel;
  QLineEdit *mpServerPortTextBox;
  Label *mpMonitorPortLabel;
  QLineEdit *mpMonitorPortTextBox;
  QCheckBox *mpInterfaceRequestModeCheckBox;
  QCheckBox *mpManagerDebugModeCheckBox;
  QGroupBox *mpTLMMonitorGroupBox;
  Label *mpMonitorProcessLabel;
  QLineEdit *mpMonitorProcessTextBox;
  QPushButton *mpBrowseMonitorProcessButton;
  Label *mpNumberOfStepsLabel;
  QLineEdit *mpNumberOfStepsTextBox;
  Label *mpTimeStepSizeLabel;
  QLineEdit *mpTimeStepSizeTextBox;
  QCheckBox *mpMonitorDebugModeCheckBox;
  QPushButton *mpSimulateButton;
  QPushButton *mpCancelButton;
  QDialogButtonBox *mpButtonBox;
  TLMCoSimulationOutputWidget *mpTLMCoSimulationOutputWidget;

  bool validate();
  TLMCoSimulationOptions createTLMCoSimulationOptions();
private slots:
  void browseManagerProcess();
  void browseMonitorProcess();
  void simulate();
};

#endif // TLMCOSIMULATIONDIALOG_H
