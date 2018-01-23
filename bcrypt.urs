val hash : string -> transaction string
  (* Hash a password.
   * Automatically generates a salt and embeds it in the returned hash. *)

val check : string -> string -> transaction bool
  (* [check password hash]
   * Check the validity of a password given its hash. *)
