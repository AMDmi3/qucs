/***************************************************************************
                          capacitor.cpp  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2003 by Michael Margraf
    email                : margraf@mwt.ee.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "capacitor.h"


Capacitor::Capacitor()
{
  Description = "capacitor";

  Lines.append(new Line( -4,-11, -4, 11,QPen(QPen::darkBlue,4)));
  Lines.append(new Line(  4,-11,  4, 11,QPen(QPen::darkBlue,4)));
  Lines.append(new Line(-30,  0, -4,  0,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(  4,  0, 30,  0,QPen(QPen::darkBlue,2)));

  Ports.append(new Port(-30,  0));
  Ports.append(new Port( 30,  0));

  x1 = -30; y1 = -13;
  x2 =  30; y2 =  13;

  tx = x1+4;
  ty = y2+4;
  Sign  = "C";
  Model = "C";
  Name  = "C";

  Props.append(new Property("C", "1 pF", true, "capacitance in Farad"));
}

Capacitor::~Capacitor()
{
}

Capacitor* Capacitor::newOne()
{
  return new Capacitor();
}