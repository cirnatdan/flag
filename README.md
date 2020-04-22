flag is a frontend for pkgsrc

# Building
flag is developed on systems with an existing pkgsrc installation.
Requires at minimum NetBSD's [make](https://pkgsrc.se/devel/bmake) and C compiler to build

```NetBSD
make
PREFIX=/usr/local make install
```

```Other OS
bmake
PREFIX=/usr/local bmake install
```

The $PREFIX value defaults to `/usr/local` and can be omitted 
