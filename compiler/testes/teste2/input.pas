program exemplo75 (input, output);
var m,n :  integer;
    c : boolean;
begin
    m := 3;
    n := 0;
    while m > 0 do
    begin
        while n < 5 do
        begin
            n := n + 1;
        end;
        m := m-1;
        n := m;
    end;
end.

