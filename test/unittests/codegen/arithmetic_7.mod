(*
  RUN: %oberon -I "%S;%inc" -L "%S;%lib" -l oberon --run %s | filecheck %s
*)
MODULE Arithmetic7;

IMPORT Out;

PROCEDURE Test;
VAR a, b, c : INTEGER;
BEGIN
  c := -3 * 5;
  Out.Int(c, 0);  Out.Ln;
  a := -3; b := 5;
  c := a * b;
  Out.Int(c, 0);  Out.Ln
END Test;

BEGIN
    Test
END Arithmetic7.
(*
    CHECK: -15
    CHECK: -15
*)