program f;

function factorial(x: Integer): Integer;
begin
  if x > 1 then
    factorial := x * factorial(x - 1)  { Llamada recursiva para calcular el factorial }
  else
    factorial := 1;  { Caso base: si x <= 1, el factorial es 1 }
end;


var
  a, b: Integer;
begin
  a := 5;
  b := factorial(a);  { Llamada a la función factorial y almacenamiento del resultado }
  writeln(b);  { Imprime el valor de b (el resultado del factorial de a) }
end.
