/*
 * coax.cpp - coaxial class implementation
 * 
 * Copyright (C) 2001 Gopal Narayanan <gopal@astro.umass.edu>
 * Copyright (C) 2002 Claudio Girardi <claudio.girardi@ieee.org>
 * Copyright (C) 2005 Stefan Jahn <stefan@lkcc.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA, 02111-1307, USA
 *
 * $Id: coax.cpp,v 1.1 2005/03/13 14:46:35 margraf Exp $
 *
 */


/* 
 * coax.c - Puts up window for microstrip and 
 * performs the associated calculations
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "units.h"
#include "transline.h"
#include "coax.h"

coax::coax() : transline()
{
}

coax::~coax()
{
}

/*
 * get_coax_sub() - get and assign coax substrate parameters into coax
 * structure
 */
void coax::get_coax_sub ()
{
  er = getProperty ("Er");
  mur = getProperty ("Mur");
  tand = getProperty ("Tand");
  sigma = getProperty ("Sigma");
}

/*
 * get_coax_comp() - get and assign coax component parameters into
 * coax structure
 */
void coax::get_coax_comp ()
{
  f = getProperty ("Freq", UNIT_FREQ, FREQ_HZ);
}

/*
 * get_coax_elec() - get and assign coax electrical parameters into
 * coax structure
 */
void coax::get_coax_elec ()
{
  Z0 = getProperty ("Z0", UNIT_RES, RES_OHM);
  ang_l = getProperty ("Ang_l", UNIT_ANG, ANG_RAD);
}

/*
 * get_coax_phys() - get and assign coax physical parameters into coax
 * structure
 */
void coax::get_coax_phys ()
{
  din = getProperty ("din", UNIT_LENGTH, LENGTH_M);
  dout = getProperty ("dout", UNIT_LENGTH, LENGTH_M);
  l = getProperty ("L", UNIT_LENGTH, LENGTH_M);
}

double coax::alphad_coax ()
{
  double ad;
  ad = (M_PI/C0) * f * sqrt(er) * tand;
  ad = ad * 8.686;
  return ad;
}

double coax::alphac_coax ()
{
  double ac, Rs;
  Rs = sqrt((M_PI * f * mur* MU0)/sigma);
  ac = (0.5 * sqrt(er)) * (((1/din) + (1/dout))/log(dout/din)) * 
    (Rs/(120. * M_PI));
  ac = ac * 8.686;
  return ac;
}

/*
 * analyze() - analysis function
 */
void coax::analyze ()
{
  double lambda_g;

  /* Get and assign substrate parameters */
  get_coax_sub();

  /* Get and assign component parameters */
  get_coax_comp();
      
  /* Get and assign physical parameters */
  get_coax_phys();
 
  if (din != 0.0){
    Z0 = (60.0/sqrt(er))*log(dout/din);
  }

  lambda_g = (C0/(f))/sqrt(er * mur);
  /* calculate electrical angle */
  ang_l = (2.0 * M_PI * l)/lambda_g;    /* in radians */
     
  setProperty ("Z0", Z0, UNIT_RES, RES_OHM);
  setProperty ("Ang_l", ang_l, UNIT_ANG, ANG_RAD);

  show_results();
}


/*
 * synthesize() - synthesis function 
 */
void coax::synthesize ()
{
  double lambda_g;

  /* Get and assign substrate parameters */
  get_coax_sub();

  /* Get and assign component parameters */
  get_coax_comp();

  /* Get and assign electrical parameters */
  get_coax_elec ();

  /* Get and assign physical parameters */
  get_coax_phys();
      
  if (isSelected ("din")) {
    /* solve for din */
    din = dout / exp(Z0*sqrt(er)/60.0);
    setProperty ("din", din, UNIT_LENGTH, LENGTH_M);
  } else if (isSelected ("dout")) {
    /* solve for dout */
    dout = din * exp(Z0*sqrt(er)/60.0);
    setProperty ("dout", dout, UNIT_LENGTH, LENGTH_M);
  }

  lambda_g = (C0/(f))/sqrt(er * mur);
  /* calculate physical length */
  l = (lambda_g * ang_l)/(2.0 * M_PI);    /* in m */
  setProperty ("L", l, UNIT_LENGTH, LENGTH_M);

  show_results();
}

/*
 * show_results() - show results
 */
void coax::show_results()
{
  double fc;
  short m, n;

  atten_dielectric = alphad_coax () * l;
  atten_cond = alphac_coax () * l;

  setResult (0, atten_cond, "dB");
  setResult (1, atten_dielectric, "dB");
      
  n = 1;
  fc = C0 / (M_PI * (dout + din)/(double) n);
  setResult (2, "none");
  if (fc <= f) {
    char text[256], txt[256];
    strcpy (text, "TE(1,1) ");
    m = 2;
    fc = C0 / (2 * (dout - din)/(double) (m-1));
    while ((fc <= f) && (m<10)) {
      sprintf(txt, "TE(n,%d) ",m);
      strcat(text,txt);
      m++;
      fc = C0 / (2 * (dout - din)/(double) (m-1));
    }
    setResult (2, text);
  }

  setResult (3, "none");
  m = 1;
  fc = C0 / (2 * (dout - din)/(float) m);
  if (fc <= f) {
    char text[256], txt[256];
    strcpy (text, "");
    while ((fc <= f) && (m<10)) {
      sprintf(txt, "TM(n,%d) ",m);
      strcat(text,txt);
      m++;
      fc = C0 / (2 * (dout - din)/(double) m);
    }
    setResult (3, text);
  }
}