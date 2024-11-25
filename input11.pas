program SumatoriasConBucles;

type
  entero = Integer;

const
  MAXRANGO = 5;  { Definimos la constante que determina el rango de la sumatoria }

var
  num1: entero;

{ Procedimiento que calcula la sumatoria usando un bucle for con incremento }
procedure sumatoriaForIncremento(inicio, fin: entero);
var
  suma, i: entero;
begin
  suma := 0;
  for i := inicio to fin do
    suma := suma + i;

  writeln( suma);
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


  { Llamamos a los procedimientos con los valores de num1 y MAXRANGO }
  sumatoriaForIncremento(num1, MAXRANGO);   { Suma con FOR con incremento }
  sumatoriaForDecremento(MAXRANGO, num1);   { Suma con FOR con decremento }
  sumatoriaRepeat(num1, MAXRANGO);           { Suma con REPEAT }
end.
