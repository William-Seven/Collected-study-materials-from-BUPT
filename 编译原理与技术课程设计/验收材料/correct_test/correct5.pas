program main;
var
arr: array[0..5] of integer;
sum, i: integer;
begin
    arr[0] := 1;
    arr[1] := 2;
    arr[2] := 33;
    arr[3] := 4;
    arr[4] := 5;
    arr[5] := 6;
    sum := 0;
    for i := 0 to 5 do
    begin
        sum := sum + arr[i];
    end;
    write(sum);
end.