#pragma once

#include <urweb.h>

uw_Basis_string uw_Bcrypt_hash(uw_context, uw_Basis_string password);
uw_Basis_bool uw_Bcrypt_check(uw_context, uw_Basis_string password, uw_Basis_string hash);
