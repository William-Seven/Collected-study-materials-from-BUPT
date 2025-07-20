program main;
var a, b, c, d, e: integer;
begin
  a := 5;
  b := 5;
  c := 1;
  d := -2;
  e := (d * 1 div 2) + (a - b) - -(c + 3) mod 2;
  write(e);
  e := ((d mod 2 + 67) + -(a - b) - -((c + 2) mod 2));
  e := e + 3;
  write(e);
end.
