program FactorialConConstantes;

const
  NUMERO = 5;  { Definimos una constante para el número cuya factorial se va a calcular }

function factorial(x: Integer): Integer;
begin
  if x > 1 then
    factorial := x * factorial(x - 1)  { Llamada recursiva para calcular el factorial }
  else
    factorial := 1;  { Caso base: si x <= 1, el factorial es 1 }
end;

procedure Main;
var
  resultado: Integer;
begin
  resultado := factorial(NUMERO);  { Llamada a la función factorial con la constante NUMERO }
  writeln( resultado);  { Imprime el resultado del factorial }
end;


begin
  Main;  { Llamada al procedimiento main }
end.
