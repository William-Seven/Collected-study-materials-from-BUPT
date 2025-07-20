program main;
function ififElse: integer;
var
    a: integer;
    b: integer;
begin
    a := 5;
    b := 10;
    if (a = 5) then
        if (b = 10) then
            a := 25
        else
            a := a + 15;
    ififElse := a;
end;

begin
    write(ififElse);
end.
