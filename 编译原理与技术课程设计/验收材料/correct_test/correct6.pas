program main;
var ret: integer;

function ifWhile: integer;
var a,b: integer;
begin
  a := 0;
  b := 1;
  if (a = 5) then
  begin
    for b := 1 to 3 do
    begin
    end;
    b := b + 25;
    ifWhile := b;
  end
  else
    for a := 0 to 4 do
      b := b * 2;
  ifWhile := b;
end;

begin
  write(ifWhile());
end.