# urweb-bcrypt
Ur/Web bindings to the [Openwall](http://www.openwall.com/crypt/) blowfish
hashing implementation. The library is included in the sources.

## Status
The library is functional, but not very thoroughly tested.

## Usage
`urweb-bcrypt` provides a module `Bcrypt` with an interface similar to OpenBSD's
[password hashing functions](https://man.openbsd.org/crypt_checkpass.3).

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

If you plan on modifying this library and use GNU Make to build your project,
you might want to add a few targets to your main Makefile. This is roughly what
mine looks like:

    BCRYPT_SRC = bcrypt/lib.urp bcrypt/bcrypt.urs bcrypt/bcrypt.h bcrypt/bcrypt.c

    project.exe: ... $(BCRYPT_SRC) | bcrypt/bcrypt.a
      urweb project ...

    .PHONY: bcrypt/bcrypt.a
    bcrypt/bcrypt.a:
      @$(MAKE) -C bcrypt

    clean:
      ...
      @$(MAKE) -C bcrypt clean

## Example
A sample application using Bcrypt for user authentication.

    table users :
      { Nam  : string
      , Hash : string }
      PRIMARY KEY Nam

    fun signIn { Nam = name, Pass = password } =
      hash <- Bcrypt.hash password;
      dml (INSERT INTO users (Nam, Hash)
           VALUES ({[name]}, {[hash]}));
      return <xml>Successfully signed in!</xml>

    fun logIn { Nam = name, Pass = password } =
      { Hash = hash } <- oneRow1 (SELECT users.Hash FROM users
                                  WHERE users.Nam = {[name]});
      if Bcrypt.check password hash then
        return <xml>Successfully logged in!</xml>
      else
        return <xml>Invalid password.</xml>

    val main =
      return <xml><body><form>
        <h1>Sign in</h1>
        <textbox{#Nam}/><br/>
        <password{#Pass}/><br/>
        <submit value="Sign in!" action={signIn}/>
      </form>
      <form>
        <h1>Log in</h1>
        <textbox{#Nam}/><br/>
        <password{#Pass}/><br/>
        <submit value="Log in!" action={logIn}/>
      </form></body></xml>

# License
`urweb-bcrypt` is provided under the MIT license, see `LICENSE` for details.

Openwall bcrypt is placed in the public domain, and under a permissive license
in jurisdictions where public domain is not recognized.
See `bcrypt/crypt_blowfish.c` for details.
