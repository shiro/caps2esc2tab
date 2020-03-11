# Udev key-mods

Transforming the most useless keys **ever** in the most useful ones.

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

## Dependencies

- [Interception Tools][interception-tools]

## Building

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Execution

This program is an [_Interception Tools_][interception-tools] plugin. A suggested
`udevmon` job configuration is:

```yaml
- JOB: "intercept -g $DEVNODE | key-mods | uinput -d $DEVNODE"
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

## License

<a href="https://gitlab.com/interception/linux/plugins/caps2esc/blob/master/LICENSE.md">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/License_icon-mit-2.svg/120px-License_icon-mit-2.svg.png" alt="MIT">
</a>

[interception-tools]: https://gitlab.com/interception/linux/tools
