[dwm](https://dwm.suckless.org/)

- [Patches](https://dwm.suckless.org/patches)
    - dwm-actualfullscreen-20211013-cb3f58a.diff
    - dwm-bar-height-6.2.diff
    - dwm-bottomstack-20160719-56a31dc.diff
    - dwm-centerfirstwindow-6.2.diff
    - dwm-cool-autostart-6.2.diff
    - dwm-cyclelayouts-20180524-6.2.diff
    - dwm-deck-double-smartborders-6.2.diff
    - dwm-fibonacci-20200418-c82db69.diff
    - dwm-gridmode-5.8.2.diff
    - dwm-hide_vacant_tags-6.3.diff
    - dwm-leftstack-6.2.diff
    - dwm-movestack-20211115-a786211.diff
    - dwm-pertag-20200914-61bb8b2.diff
    - dwm-scratchpad-6.2.diff
    - dwm-sticky-20160911-ab9571b.diff
    - dwm-swallow-20201211-61bb8b2.diff
    - dwm-tatami-6.2.diff
    - dwm-tilewide-6.3.diff
    - shiftview.c

- supported layouts
    - multi-layer horizontal
    - multi-layer vertical
    - deck horizontal
    - deck vertical
    - bottom stack horizontal
    - bottom stack vertical
    - fibonacci dwindle
    - fibonacci sprial
    - grid
    - logarithmic sprial
    - tatami
    - center
    - center coner
    - tile left
    - tile right
    - floating
    - monocle

# dwm - dynamic window manager
dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements
In order to build dwm you need the Xlib header files.


## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    sh build.sh


## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can use dwmstats

    git clone https://github.com/zetatez/arch-dwmstatus.git
    cd arch-dwmstatus && sh build.sh

## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
