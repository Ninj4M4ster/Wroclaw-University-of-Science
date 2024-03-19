with Library; use Library;
with Text_IO; use Text_IO;

procedure main is
result: Natural;
begin
    result := gcmRecursive(15, 5);
    Put_Line(Natural'Image(result));
end main;