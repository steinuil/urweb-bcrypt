CC ?= gcc

bcrypt_version = 1.3
bcrypt_cflags = -W -Wall -Wbad-function-cast -Wcast-align -Wcast-qual -Wmissing-prototypes -Wstrict-prototypes -Wshadow -Wundef -Wpointer-arith -O2 -fomit-frame-pointer -funroll-loops
c = bcrypt

cc_flags = -Wall -Wextra -Wno-unused-parameter -Wno-implicit-fallthrough -std=gnu11
ur_include = -I$(shell urweb -print-cinclude)

b = build


bcrypt.a: $b/ow_gensalt.o $b/ow_blowfish.o $b/ow_crypt.o $b/bcrypt.o
	ar cr $@ $+


$b/bcrypt.o: bcrypt.c bcrypt.h $b/ow_crypt.h | $b
	$(CC) -c $(cc_flags) $< -o $@ -I$b $(ur_include)

$b/ow_blowfish.o: $c/crypt_blowfish.c $c/crypt_blowfish.h | $b
	$(CC) -c $(bcrypt_cflags) $< -o $@

$b/ow_gensalt.o: $c/crypt_gensalt.c $c/crypt_gensalt.h | $b
	$(CC) -c $(bcrypt_cflags) $< -o $@

$b/ow_crypt.o: $c/wrapper.c $c/ow-crypt.h $c/crypt_blowfish.h $c/crypt_gensalt.h $c/crypt.h | $b
	$(CC) -c $(bcrypt_cflags) $< -o $@

$b/ow_crypt.h: $c/ow-crypt.h | $b
	cp $< $@


$b:
	mkdir build

.SUFFIXES:

.PHONY: redownload
redownload:
	rm -rf $c
	curl --silent 'http://www.openwall.com/crypt/crypt_blowfish-$(bcrypt_version).tar.gz' | tar xzf -
	mv crypt_blowfish-$(bcrypt_version) $c

.PHONY: clean
clean: 
	rm -rf build bcrypt.a
