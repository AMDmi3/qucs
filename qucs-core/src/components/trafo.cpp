/*
 * trafo.cpp - trafo class implementation
 *
 * Copyright (C) 2003 Stefan Jahn <stefan@lkcc.org>
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this package; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.  
 *
 * $Id: trafo.cpp,v 1.1 2003/12/20 19:03:28 ela Exp $
 *
 */

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "complex.h"
#include "object.h"
#include "node.h"
#include "circuit.h"
#include "trafo.h"

trafo::trafo () : circuit (4) {
}

void trafo::calc (nr_double_t frequency) {

  nr_double_t t = getPropertyDouble ("T");

  complex z1 = (t * t) / (t * t + 1.0);
  complex z2 = t / (t * t + 1.0);
  complex z3 = 1 / (t * t + 1.0);

  setS (1, 1,  z1);
  setS (1, 2,  z2);
  setS (1, 3, -z2);
  setS (1, 4,  z3);
  setS (2, 1,  z2);
  setS (2, 2,  z3);
  setS (2, 3,  z1);
  setS (2, 4, -z2);
  setS (3, 1, -z2);
  setS (3, 2,  z1);
  setS (3, 3,  z3);
  setS (3, 4,  z2);
  setS (4, 1,  z3);
  setS (4, 2, -z2);
  setS (4, 3,  z2);
  setS (4, 4,  z1);
}