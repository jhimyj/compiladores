program MultiplicacionYDivisionConCondiciones;

type
    entero = Integer;
var
  num1, num2,multiplicacion : Integer;

begin
  { Pedimos al usuario los dos números enteros }
  num1 := 100;
  num2 :=-10;

  { Realizamos la multiplicación }
  multiplicacion := num1 * num2;

  if not (multiplicacion = 0)  then
    writeln(num1 div num2)  { División entera }

  else if not (num1 = 0) then
    writeln (num1)
  else writeln (num2);

end.