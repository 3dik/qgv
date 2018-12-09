Interactive Qt OGDF display
===============================

Features :
----------

* Layout independent, in other words: it's your (or [OGDF](http://www.ogdf.net/doku.php)'s) responsibility to layout the graph. This library just takes the resulted layout informations of the graph and tries to render it properly. This way, the user of the library has more flexibility in using OGDF for graph manipulation.
* Support edges : label on edge, simple arrow both direction
* Support Nodes : box shape
* Support subGraphs aka clusters
* Interactions with node and edge (context menu and double click)
* Zoom/move on graph
* Only 1 class to use

Installation :
--------------

On UNIX:
1. install OGDF
1. qmake -r
1. make

Compare the todo todo list. This library might also be buildable on other operating systems. With some tweaks, cmake might be supported too.

TODO :
------

* Support more attributes of OGDF
* Rebrand the project, see history
* Fix/clean up the broken build system. The non-unix builds are still assuming a graphviz codebase. The OGDF integration is probably buggy, Qt Creator might not be able to load the project. Maybe we should get rid off that Qt Creator stuff.

History :
---------

This is a fork of [qgv](https://github.com/3dik/qgv). Instead of Graphviz, we use OGDF. As distinguished from Graphviz, which often uses strings for customization, OGDF's "customization" API is strongly typed. Thus, we decided to redesign qgv's API in order to keep its flexibility. As a result, it's not a wrapper anymore. So the new design does not provide graph manipulation methods. It just renders the graph. Compare the feature list.

Good lecture on subject :
-------------------------

* Steve Dodier-Lazaro : <http://www.mupuf.org/blog/2010/07/08/how_to_use_graphviz_to_draw_graphs_in_a_qt_graphics_scene/>
* Arvin Schnell : <http://arvin.schnell-web.net/qgraph/>

Other similar projects (you must look before lose time with GraphViz) :
-----------------------
* Constraint-based diagram editor : https://github.com/mjwybrow/dunnart  (Probably best one ! Awesome work ...)
