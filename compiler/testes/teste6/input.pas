program proc2 (input, output);
var x, y: integer;
    procedure p(t:integer);
    var z:integer;
    begin
        if (t>1)then
        begin
            p(t-1);
        end
        else
        begin
            y:=1;
        end;
        z:= y;
        y:=z*t;
    end;
    begin
        read(x);
        p(x);
        write (x,y);
    end.