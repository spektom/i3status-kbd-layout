i3status-kbd-layout
===================

Keyboard layout indication for [i3status](https://github.com/i3/i3status).

## Installing

Compile the `i3status-kbd-layout` program:

    mkdir build
    cd build
    cmake ..
    make

Copy it to some place in `$PATH`, for example:

    cp i3status-kbd-layout /usr/local/bin/

## Configuration

Add new `read_file` section to your `i3status` configuration:

    order += "read_file kbd_layout"

    ...

    read_file kbd_layout {
      path = "~/.i3status-kbd-layout"
    }

The above section lets `i3status` bar read new keyboard layout from that path, and show it.

Start `i3status-kbd-layout` when `i3wm` is started by adding the following line into `i3wm` configuration:

    exec --no-startup-id i3status-kbd-layout

