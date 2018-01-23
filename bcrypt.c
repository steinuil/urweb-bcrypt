#include <stdio.h>
#include <string.h>
#include <urweb.h>

#include "bcrypt.h"
#include "ow_crypt.h"


#define BCRYPT_HASH_SIZE (7 + 22 + 31 + 1)
#define BCRYPT_GENSALT_SIZE (7 + 22 + 1)


uw_Basis_string uw_Bcrypt_genSalt(uw_context ctx, uw_Basis_int cost) {
  size_t rand_size = 16;
  char rand_bytes[rand_size];
  { FILE *urand = fopen("/dev/urandom", "r");
    if (!urand) {
      uw_error(ctx, FATAL, "Failed to open /dev/urandom");
    }

    size_t read = fread(&rand_bytes, sizeof(char), rand_size, urand);
    if (!read || (read / sizeof(char)) < rand_size) {
      fclose(urand);
      uw_error(ctx, BOUNDED_RETRY, "Failed to read from /dev/urandom");
    }

    int ok = fclose(urand);
    if (ok != 0) {
      uw_error(ctx, BOUNDED_RETRY, "Failed to close /dev/urandom");
    }
  }

  char *out = uw_malloc(ctx, BCRYPT_GENSALT_SIZE);
  { char *ok = crypt_gensalt_rn("$2b$", cost, rand_bytes, rand_size, out, BCRYPT_GENSALT_SIZE);
    if (ok == NULL) {
      uw_error(ctx, BOUNDED_RETRY, "Failed to generate salt");
    }
  }

  return out;
}


uw_Basis_string uw_Bcrypt_hash(uw_context ctx, uw_Basis_string password) {
  char *salt = uw_Bcrypt_genSalt(ctx, 10);

  char *hash = uw_malloc(ctx, BCRYPT_HASH_SIZE);
  memset(hash, 0, BCRYPT_HASH_SIZE);

  { char *ok = crypt_rn(password, salt, hash, BCRYPT_HASH_SIZE);
    if (ok == NULL) {
      uw_error(ctx, BOUNDED_RETRY, "Failed to generate hash");
    }
  }

  return hash;
}

uw_Basis_bool uw_Bcrypt_check(uw_context ctx, uw_Basis_string password, uw_Basis_string hash) {
  char *other_hash = uw_malloc(ctx, BCRYPT_HASH_SIZE);
  memset(other_hash, 0, BCRYPT_HASH_SIZE);

  { char *ok = crypt_rn(password, hash, other_hash, BCRYPT_HASH_SIZE);
    if (ok == NULL) {
      uw_error(ctx, BOUNDED_RETRY, "Failed to generate hash");
    }
  }

  if (strcmp(hash, other_hash) == 0) {
    return uw_Basis_True;
  } else {
    return uw_Basis_False;
  }
}
