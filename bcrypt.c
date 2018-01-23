#include <stdio.h>
#include <urweb.h>

#include "bcrypt.h"
#include "ow_crypt.h"


#define BCRYPT_HASH_SIZE (7 + 22 + 31 + 1)
#define BCRYPT_GENSALT_SIZE (7 + 22 + 1)


uw_Basis_string uw_Bcrypt_hash(uw_context ctx, uw_Basis_string password) {
  char data[16];
  { FILE *urand = fopen("/dev/urandom", "r");
    fread(&data, sizeof(char), 16, urand);
    fclose(urand);
  }

  int hash_size = BCRYPT_HASH_SIZE;

  char *salt = crypt_gensalt_ra("$2b$", 10, data, BCRYPT_GENSALT_SIZE);
  char *hash = crypt_ra(password, salt, NULL, &hash_size);

  char *res = uw_malloc(ctx, hash_size);
  memcpy(res, hash, hash_size);

  if (salt) free(salt);
  if (hash) free(hash);

  return res;
}

uw_Basis_bool uw_Bcrypt_check(uw_context ctx, uw_Basis_string password, uw_Basis_string hash) {
  return uw_Basis_True;
}
