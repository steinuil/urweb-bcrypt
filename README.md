# urweb-bcrypt
Ur/Web bindings to the [Openwall](http://www.openwall.com/crypt/) blowfish
hashing implementation. The library is included in the sources.

## Status
**WARNING:** At the moment of writing, attempting to use this library will
result in a segfault.

## Usage
The interface is the same as OpenBSD's [crypt\_checkpass](https://man.openbsd.org/crypt_checkpass.3).
Here's an example:

    val hashPassword pass =
      hash <- Bcrypt.hash pass;
      return <xml>Your hashed password is {[hash]}.</xml>

    val validate pass hash =
      valid <- Bcrypt.check pass hash;
      if valid then
        return <xml>Your password is valid.</xml>
      else
        return <xml>Invalid password!</xml>

## Building
Building the library requires `gcc` and `ar`.

    make

## Inclusion
You can include the library in your Ur/Web project by simply cloning the
repository in your source directory with git:

    git clone https://github.com/steinuil/urweb-bcrypt bcrypt

Then include the library with the `library` directive in your main `.urp` file:

    library bcrypt
