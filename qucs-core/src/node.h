/*
 * node.h - node class definitions
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
 * $Id: node.h,v 1.1 2003/12/20 19:03:25 ela Exp $
 *
 */

#ifndef __NODE_H__
#define __NODE_H__

class circuit;

class node : public object
{
 public:
  node ();
  node (char *);
  node (const node &);
  ~node ();
  void setNode (int);
  int getNode (void);
  void setPort (int);
  int getPort (void);
  void setCircuit (circuit *);
  circuit * getCircuit (void);

 private:
  int nNode;
  int port;
  circuit * _circuit;
};

#endif /* __NODE_H__ */