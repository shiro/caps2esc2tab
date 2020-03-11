# caps2esc2tab

_Transforming the most useless keys **ever** in the most useful ones.

<sub>not enough keys on your keyboard? here's some modifiers!</sub>


## What is it?

A key remapping utility.

- `ESC` is `CAPSLOCK`
- `CAPSLOCK` is `ESC`
- `CAPSLOCK` is `CTRL` + `[KEY]`
- `CAPSLOCK` + `[h, j, k, l]` is `CTRL+ALT+SHIFT+META` + `[KEY]`
- `TAB` + `[KEY]` is `ALT+SHIFT+META` + `[KEY]`
- `RIGHT_ALT` + `[KEY]` is `ALT++META` + `[KEY]`

The mapping of the `ALT` keys can be toggled by pressing `F8`.  
with `SHIFT` + `LEFT_ALT` it is possible to pass through the `LEFT_ALT` key
without pausing the mapping.

## Why?

- Add a new modifier key
- Make keybindings more convenient

## Dependencies

- [Interception Tools][interception-tools]

## Building

```
$ git clone git@gitlab.com:interception/linux/plugins/caps2esc.git
$ cd caps2esc
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Execution

`caps2esc2tab` is an [_Interception Tools_][interception-tools] plugin. A suggested
`udevmon` job configuration is:

```yaml
- JOB: "intercept -g $DEVNODE | caps2esc2tab | uinput -d $DEVNODE"
  DEVICE:
    EVENTS:
      EV_KEY: [KEY_CAPSLOCK, KEY_ESC, KEY_TAB]

```

For more information about the [_Interception Tools_][interception-tools], check
the project's website.

## Installation

Currently manual installation **only**.

If someone wants to maintain this on aur, go ahead!

## Caveats

As always, there's always a caveat:

- `intercept -g` will "grab" the detected devices for exclusive access.
- If you tweak your key repeat settings, check whether they get reset.
  Please check [this report][key-repeat-fix] about the resolution.

## History

I forked the useful caps2esc key to add the tab functionality which I was
using, while being on Windows OS.

It's great for virtual monitor management as it's possible to use `tab` +
`[key]` to easily switch desktops.  
Furthermore it's even possible to combine `tab` with `caps lock` and `[key]` to
get another set of bindable keys!

## License

<a href="https://gitlab.com/interception/linux/plugins/caps2esc/blob/master/LICENSE.md">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/License_icon-mit-2.svg/120px-License_icon-mit-2.svg.png" alt="MIT">
</a>

Copyright © 2017 Francisco Lopes da Silva

[caps2esc-windows]: https://github.com/oblitum/Interception/blob/master/samples/caps2esc/caps2esc.cpp
[karabiner]: https://pqrs.org/osx/karabiner/
[xmodmap]: https://www.x.org/releases/X11R7.7/doc/man/man1/xmodmap.1.xhtml
[xcape]: https://github.com/alols/xcape
[x]: https://www.x.org
[interception]: https://github.com/oblitum/Interception
[interception-tools]: https://gitlab.com/interception/linux/tools
[key-repeat-fix]: https://github.com/oblitum/caps2esc/issues/1
