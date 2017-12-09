# text-editor
Text editor made in C++ using SFML

This is a simple text editor made from scratch in C++. (Using SFML for window drawing)
Yes, thats it. Nothing fancy, nothing weird. Just a great learning experience.

![Simple example](https://raw.githubusercontent.com/JonSeijo/text-editor/master/img/super_example.gif)

The editor is functional, you can write text, delete it, select it (keyboard AND mouse support). It has some nice features like swapping text lines.

![Swapping lines](https://raw.githubusercontent.com/JonSeijo/text-editor/master/img/moving_lines.gif)

----

## Compiling instructions

The editor uses SFML library as graphics controller, so it is needed for compiling. IMPORTANT: Needs version +2.4 !!
See https://www.sfml-dev.org

A working Makefile is included, works great assuming you have sfml installed correctly.

```
make && ./editor
```

## Warnings!

Currently the editor does not support correctly viewing tabs characters ( \t ). Expect glitches when \t appears. Be careful with the data you save! This won't happen if you use the correct indentation method: spaces. Pressing the tab key will insert four spaces. The bug with \t will be fixed in future versions.


## F.A.Q.

![Swapping lines](https://raw.githubusercontent.com/JonSeijo/text-editor/master/img/but_why.gif)


## Notes

DejaVuSansMono.ttf
https://dejavu-fonts.github.io/

FreeMono.ttf
http://font.ubuntu.com/ufl/ubuntu-font-licence-1.0.txt

SFML 2.4
https://www.sfml-dev.org
