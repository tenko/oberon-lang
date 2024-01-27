(*
  RUN: %oberon --run %s | filecheck %s
  D exponent symbol for LONGREAL not supported.
  This is needed due to difference in rounding when parsing constants.
*)
MODULE ConstLongReal1;

CONST
  min = -1.7976931348623158D308
  max = -2.2250738585072014D-308

PROCEDURE printf(format: STRING; ...): INTEGER; EXTERN;

PROCEDURE Test;
VAR
  val : LONGREAL;
BEGIN
  val := min;
  printf("%.9g\n", val);
  val := max;
  printf("%.9g\n", val)
END Test;

BEGIN
    Test()
END ConstLongReal1.
(*
    CHECK: -1.7976931348623158e308
    CHECK: -2.2250738585072014e-308
*)