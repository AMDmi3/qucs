/*
 * input.cpp - input netlist class implementation
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
 * $Id: input.cpp,v 1.1 2003/12/20 19:03:20 ela Exp $
 *
 */

#if HAVE_CONFIG_H
# include <config.h>
#endif

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>

#include "logging.h"
#include "component.h"
#include "net.h"
#include "input.h"
#include "check_netlist.h"

// Constructor creates an unnamed instance of the input class.
input::input () : object () {
  fd = stdin;
  subnet = NULL;
}

// Constructor creates an named instance of the input class.
input::input (char * file) : object (file) {
  if ((fd = fopen (file, "r")) == NULL) {
    logprint (LOG_ERROR, "cannot open file `%s': %s\n", 
	      file, strerror (errno));
    fd = stdin;
  }
  subnet = NULL;
}

// Destructor deletes an input object.
input::~input () {
  if (fd != stdin) fclose (fd);
}

/* This function scans, parses and checks a netlist from the input
   file (specified by the constructor call) or stdin if there is no
   such file.  Afterwards the function builds the netlist
   representation and stores it into the given netlist object.  The
   function returns zero on success and non-zero otherwise. */
int input::netlist (net * netlist) {

  // tell the scanner to use the specified file
  netlist_in = getFile ();

  // save the netlist object
  subnet = netlist;

  logprint (LOG_STATUS, "parsing netlist...\n");
  if (netlist_parse () != 0)
    return -1;

  logprint (LOG_STATUS, "checking netlist...\n");
  if (netlist_checker () != 0)
    return -1;

#if DEBUG
  netlist_list ();
#endif /* DEBUG */

  logprint (LOG_STATUS, "creating netlist...\n");
  factory ();

  netlist_destroy ();
  return 0;
}

/* This function builds up the netlist representation from the checked
   netlist input.  It creates circuit components as necessary. */
void input::factory (void) {

  struct definition_t * def;
  struct node_t * nodes;
  struct pair_t * pairs;
  circuit * c;
  object * o;
  int i;

  // go through the list of input definitions
  for (def = definition_root; def != NULL; def = def->next) {

    // handle actions
    if (def->action) {
      if (!strcmp (def->type, "SP")) {
	o = subnet;
	for (pairs = def->pairs; pairs != NULL; pairs = pairs->next)
	  if (pairs->value->ident)
	    o->addProperty (pairs->key, pairs->value->ident);
	  else
	    o->addProperty (pairs->key, pairs->value->value);
      }
    }

    // handle component definitions
    else {
      c = createCircuit (def->type);
      o = (object *) c;
      c->setName (def->instance);

      // add appropriate nodes to circuit
      for (i = 1, nodes = def->nodes; nodes != NULL; nodes = nodes->next, i++)
	if (i <= c->getSize ())
	  c->setNode (i, nodes->node);

      // add the properties to circuit
      for (pairs = def->pairs; pairs != NULL; pairs = pairs->next)
	if (pairs->value->ident)
	  o->addProperty (pairs->key, pairs->value->ident);
	else
	  o->addProperty (pairs->key, pairs->value->value);

      // insert the circuit into the netlist object
      if (!strcmp (def->type, "Pac"))
	subnet->insertPort (c);
      else
	subnet->insertCircuit (c);
    }
  }
}

// The function creates components specified by the type of component. 
circuit * input::createCircuit (char * type) {
  if (!strcmp (type, "Pac"))
    return new pac ();
  else if (!strcmp (type, "R"))
    return new resistor ();
  else if (!strcmp (type, "C"))
    return new capacitor ();
  else if (!strcmp (type, "L"))
    return new inductor ();
  else if (!strcmp (type, "VCCS"))
    return new vccs ();
  else if (!strcmp (type, "CCCS"))
    return new cccs ();
  else if (!strcmp (type, "VCVS"))
    return new vcvs ();
  else if (!strcmp (type, "CCVS"))
    return new ccvs ();
  else if (!strcmp (type, "BiasT"))
    return new biastee ();
  else if (!strcmp (type, "DCFeed"))
    return new dcfeed ();
  else if (!strcmp (type, "DCBlock"))
    return new dcblock ();
  else if (!strcmp (type, "Circulator"))
    return new circulator ();
  else if (!strcmp (type, "Attenuator"))
    return new attenuator ();
  else if (!strcmp (type, "Isolator"))
    return new isolator ();
  else if (!strcmp (type, "Tr"))
    return new trafo ();
  else if (!strcmp (type, "sTr"))
    return new strafo ();
  else if (!strcmp (type, "Vdc"))
    return new vdc ();
  else if (!strcmp (type, "Idc"))
    return new idc ();
  else if (!strcmp (type, "Vac"))
    return new vac ();

  logprint (LOG_ERROR, "no such circuit type `%s'\n", type);
  return NULL;
}