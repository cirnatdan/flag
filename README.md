**flag** is a frontend for [pkgsrc](), a portal package build system. The goal is to
have a tool similar to what `emerge` is for `Portage` or `yaourt` is for `AUR`.
It should work on most platforms supported by `pkgsrc`, including NetBSD, Linux,
macOS and others.

# Usage
**flag** wraps existing pkgsrc tools and make targets in convenient subcommands: 
* `flag search tmux` - search for package *tmux*, equivalent of `pkgfind tmux`
* `flag install tmux` - install package *tmux*, wrapper for `cd /usr/pkgsrc/misc/tmux && make install clean clean-depends`
* `flag remove tmux` - wrapper for `make deinstall`
* `flag options tmux` - wrapper for `make show-options`
* `flag dependencies tmux` - wrapper for `make show-depends` 

# Building
flag is developed on systems with an existing pkgsrc installation.
Requires at minimum NetBSD's [make](https://pkgsrc.se/devel/bmake) and a C compiler to build

## NetBSD
```
make
PREFIX=/usr/local make install
```

## Other OS
```
bmake
PREFIX=/usr/local bmake install
```

The $PREFIX value defaults to `/usr/local` and can be omitted 
