program proc1 (input, output);
    var x, y: integer;
    procedure p;
        var z:integer;
        begin
            z:=x;
            x:=x-1;
            if (z>1)then 
            begin
                p;
            end
                else 
                begin
                    y:=1;
                end;
            y:=y*z;
        end;
    begin
        read(x);
        p;
        write (x,y);
end.