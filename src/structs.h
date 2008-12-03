/*
*      structs.h
*      Copyright © 2008 Martin Duquesnoy <xorg62@gmail.com>
*      All rights reserved.
*
*      Redistribution and use in source and binary forms, with or without
*      modification, are permitted provided that the following conditions are
*      met:
*
*      * Redistributions of source code must retain the above copyright
*        notice, this list of conditions and the following disclaimer.
*      * Redistributions in binary form must reproduce the above
*        copyright notice, this list of conditions and the following disclaimer
*        in the documentation and/or other materials provided with the
*        distribution.
*      * Neither the name of the  nor the names of its
*        contributors may be used to endorse or promote products derived from
*        this software without specific prior written permission.
*
*      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef STRUCTS_H
#define STRUCTS_H

#include "wmfs.h"

#define NBUTTON        8
#define MAXTAG         36
#define NUM_OF_LAYOUT  7

/* Typedef */
typedef const char* uicb_t;
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef unsigned short ushort;
typedef unsigned char  uchar;

/* Enum */
enum { CurNormal, CurResize, CurMove, CurLast };
enum { WMState, WMProtocols, WMName, WMDelete, WMLast };
enum { NetSupported, NetWMName, NetLast };
typedef enum { Top, Bottom, Right, Left, Center, PositionLast } Position;

/*
 *  BarWindow Structure
 * (titlebar, infobar..)
 */
typedef struct
{
     Window win;
     Drawable dr;
     struct
     {
          /* Border Window */
          Window left, right, top, bottom;
          /* Border color */
          uint dark, light;
     } border;
     uint color;
     XRectangle geo;
     Bool mapped;
} BarWindow;

/* Client Structure. */
typedef struct Client Client;
struct Client
{
     /* Client title */
     char *title;
     /* Tag num */
     int tag;
     /* Screen */
     int screen;
     /* Window attribute */
     XRectangle geo;
     XRectangle frame_geo;
     /* Old window attribute */
     XRectangle ogeo;
     /* For resizehint usage */
     int basew, baseh, incw, inch;
     int maxw, maxh, minw, minh;
     int minax, maxax, minay, maxay;
     /* Client composant {{{ */
     Window win;
     BarWindow *titlebar;
     Window frame, resize;
     /* Border */
     Window right, left, top, bottom;
     /* }}} */
     struct
     {
          uint frame;
          uint resizecorner;
     } colors;
     /* Client Layout Information */
     Bool max, tile, free, hide;
     Bool hint, lmax, unmapped;
     /* Struct in chains */
     Client *next;
     Client *prev;
};

/* Keybind Structure */
typedef struct
{
     uint mod;
     KeySym keysym;
     void (*func)(uicb_t);
     uicb_t cmd;
} Key;

/* Mouse Binding Struct */
typedef struct
{
     int tag;
     uint button;
     void (*func)(uicb_t);
     uicb_t cmd;
} MouseBinding;

/* InfoBar Struct */
typedef struct
{
     BarWindow *bar;
     BarWindow *layout_button;
     BarWindow *tags[MAXTAG];
     XRectangle geo;
     char statustext[1024];
} InfoBar;

/* Layout Structure */
typedef struct
{
     char *symbol;
     void (*func)(void);
} Layout;

/* Tag Structure */
typedef struct
{
     char *name;
     float mwfact;
     int nmaster;
     Bool resizehint;
     Layout layout;
} Tag;

/* Alias struct */
typedef struct
{
     char *name;
     char *content;
} Alias;

/* Configuration structure */
typedef struct
{
     /* Misc option */
     char *font;
     bool raisefocus;
     bool raiseswitch;
     bool bartop;
     struct
     {
          /*
           * Only the colors will be use for text
           * are 'char*' (for xprint -> XftColorAllocName)
           */
          uint bar;
          char *text;
          char *tagselfg;
          uint tagselbg;
          uint tag_occupied_bg;
          uint tagbord;
          char *layout_fg;
          uint layout_bg;
     } colors;
     struct
     {
          char *background_command;
          MouseBinding *mouse;
          int nmouse;
     } root;
     struct
     {
          Bool place_at_mouse;
          int borderheight;
          uint bordernormal;
          uint borderfocus;
          uint resizecorner_normal;
          uint resizecorner_focus;
          uint mod;
          MouseBinding *mouse;
          int nmouse;
     } client;
     struct
     {
          int height;
          char *fg;
          MouseBinding *mouse;
          int nmouse;
     } titlebar;
     Alias *alias;
     Tag tag[MAXTAG];
     Layout layout[NUM_OF_LAYOUT];
     int *ntag;
     bool tag_round;
     int nkeybind;
     int nbutton;
     int nlayout;
} Conf;

/* Config.c struct */
typedef struct
{
     char *name;
     void *func;
} func_name_list_t;

typedef struct
{
      char *name;
      KeySym keysym;
} key_name_list_t;

typedef struct
{
     char *name;
     uint button;
} name_to_uint_t;

#endif /* STRUCTS_H */
