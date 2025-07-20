program main;
  
function func(p,x: integer): integer;
begin
  p := p - 1;
  func := p;
end;
end;

begin
  b := func(a);
  write(b);
end.