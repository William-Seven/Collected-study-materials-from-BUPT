program main;
var
  a: integer;
  b: integer;
  
function func(p: integer): integer;
begin
  p := p - 1;
  func := p;
end;

begin
  a := 10;
  b := func(a);

  write(b);
end.
