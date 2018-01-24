val hash : string -> transaction string
  (* Generate a 16-byte salt and hash the provided password with it, using
   * bcrypt version $2b$. The returned string contains both the salt and the
   * hashed password, and can directly be used in [check]. *)

val check : string -> string -> bool
  (* [check password hash]
   * Hash [password] using the salt included in [hash] and compare the two
   * hashes. *)
