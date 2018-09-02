#include "controller_view.h"

controller_view::controller_view(): StartupV(new startup_view()), SpecializedV(0) {
  QObject::connect(StartupV, SIGNAL(type_FStartupTController(int)), this, SLOT(createSpecialized(int)));
  QObject::connect(StartupV, SIGNAL(type_FStartupTController(int)), this, SIGNAL(inviaTipo(int)));

  setCenterOfMonitor(StartupV);
  StartupV->show();
}

void controller_view::setCenterOfMonitor(QWidget* widget) const{
  QSize size = widget->sizeHint();
  QDesktopWidget* desktop = QApplication::desktop();
  int width = desktop->width();
  int height = desktop->height();
  int mw = size.width();
  int mh = size.height();
  int centerW = (width/2) - (mw/2);
  int centerH = (height/2) - (mh/2);
  widget->move(centerW, centerH);
}

void controller_view::createSpecialized(int i){

  switch(i){
    case 1:
      SpecializedV = new VRazionale();
      break;
    case 2:
      SpecializedV = new VComplesso();
      break;
    case 3:
      SpecializedV = new VTupla();
      break;
    case 4:
      SpecializedV = new VCircuito();
      break;
  }

  QObject::connect(SpecializedV, SIGNAL(back()), this, SLOT(createStartup()));
  QObject::connect(SpecializedV, SIGNAL(inviaQS(QString)), this, SIGNAL(inviaStringa(QString)));

  QObject::connect(SpecializedV, SIGNAL(inviaSORaz(int)), this, SIGNAL(SORaz(int)));
  QObject::connect(SpecializedV, SIGNAL(inviaSOComplesso(int)), this, SIGNAL(SOComplesso(int)));

  QObject::connect(SpecializedV, SIGNAL(specialized_view_inviaVolt(double)), this, SIGNAL(controller_view_inviaVolt(double)));
  QObject::connect(SpecializedV, SIGNAL(specialized_view_inviaFreq(double)), this, SIGNAL(controller_view_inviaFreq(double)));


  QObject::connect(this, SIGNAL(inviaResult(QString)), SpecializedV, SLOT(mostra_result(QString)));

  StartupV->close();
  delete StartupV;
  StartupV = 0;

  setCenterOfMonitor(SpecializedV);
  SpecializedV->show();
}


void controller_view::createStartup(){

  StartupV = new startup_view();
  QObject::connect(StartupV, SIGNAL(type_FStartupTController(int)), this, SLOT(createSpecialized(int)));
  QObject::connect(StartupV, SIGNAL(type_FStartupTController(int)), this, SIGNAL(inviaTipo(int)));

  SpecializedV->close();
  delete SpecializedV;
  SpecializedV = 0;

  setCenterOfMonitor(StartupV);
  StartupV->show();
}


controller_view::~controller_view(){

  if(StartupV)
    delete StartupV;

  if(SpecializedV)
    delete SpecializedV;

  std::cout << "SONO IL DISTRUTTORE DI CONTROLLER VIEW" << std::endl;

}