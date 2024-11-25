program SumatoriasConBucles;

type
  entero = Integer;

var
  num1, num2: entero;

{ Procedimiento que calcula la sumatoria usando un bucle for con incremento }
procedure sumatoriaForIncremento(inicio, fin: entero);
var
  suma, i: entero;
begin
  suma := 0;
  for i := inicio to fin do
    suma := suma + i;

  writeln(suma);
end;

{ Procedimiento que calcula la sumatoria usando un bucle for con rango descendente }
procedure sumatoriaForDecremento(inicio, fin: entero);
var
  suma, i: entero;
begin
  suma := 0;
  for i := inicio downto fin do
    suma := suma + i;

  writeln( suma);
end;

{ Procedimiento que calcula la sumatoria usando un bucle repeat }
procedure sumatoriaRepeat(inicio, fin: entero);
var
  suma, i: entero;
begin
  suma := 0;
  i := inicio;
  repeat
    suma := suma + i;
    i := i + 1;
  until i > fin;

  writeln(suma);
end;

begin
  { Definimos los valores de num1 y num2 }
  num1 := 1;  { Valor de inicio para las sumatorias }
  num2 := 5;  { Valor de fin para las sumatorias }
  { Llamamos a los procedimientos con los valores de num1 y num2 }
  sumatoriaForIncremento(num1, num2);   { Suma con FOR con incremento }
  sumatoriaForDecremento(num2, num1);   { Suma con FOR con decremento }
  sumatoriaRepeat(num1, num2);           { Suma con REPEAT }
end.

