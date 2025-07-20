program main;
var
  c: integer;
  d: integer;
  
function func(p,x,x: integer): integer;
begin
  p := p - 1;
  func := p;
end;

function func(p,x: integer): integer;
begin
  p := p - 1;
  func := p;
end;

begin
  b := func(a);
  write(b);
end.