program LogicosYWhile;

var
  a, b, c: Boolean;
  contador: Integer;

begin
  { Inicializamos las variables booleanas }
  a := true;
  b := false;
  c := true;

  { Imprimir los resultados de las operaciones lógicas }
  writeln(a and not b);  { Operación AND }
  writeln(a or b);    { Operación OR }
  writeln(a and c);  { Operación AND }
  writeln(b or c);    { Operación OR }

  { Usamos un bucle while para realizar una acción varias veces }
  contador := 1;

  while contador <= 5 do
  begin
    writeln(contador);
    contador := contador + 1;
  end;
end.
