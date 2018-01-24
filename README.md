# urweb-bcrypt
Ur/Web bindings to the [Openwall](http://www.openwall.com/crypt/) blowfish
hashing implementation. The library is included in the sources.

## Status
The library is functional, but not very thoroughly tested.

## Usage
`urweb-bcrypt` provides a module `Bcrypt` with an interface similar to OpenBSD's
[password hashing functions](https://man.openbsd.org/crypt_checkpass.3).
Here's an example:

    fun hashPassword pass =
      hash <- Bcrypt.hash pass;
      return <xml>Your hashed password is {[hash]}.</xml>

    fun validate pass hash =
      if Bcrypt.check pass hash then
        return <xml>Your password is valid.</xml>
      else
        return <xml>Invalid password!</xml>

See `bcrypt.urs` for the type signatures.

## Building
Building the library requires GNU Make, `gcc` and `ar`. I haven't tested it
with Clang.

    make

## Inclusion
You can include the library in your Ur/Web project by simply cloning the
repository in your source directory with git:

    git clone https://github.com/steinuil/urweb-bcrypt bcrypt

Then include the library with the `library` directive in your main `.urp` file:

    library bcrypt

If you use GNU Make to build your project, you might want to add a few targets
to your main Makefile. This is roughly what mine looks like:

    BCRYPT_SRC = bcrypt/lib.urp bcrypt/bcrypt.urs bcrypt/bcrypt.h bcrypt/bcrypt.c

    project.exe: ... $(BCRYPT_SRC) | bcrypt/bcrypt.a
      urweb project ....

    .PHONY: bcrypt/bcrypt.a
    bcrypt/bcrypt.a:
      @$(MAKE) -C bcrypt

    clean:
      ...
      @$(MAKE) -C bcrypt clean
