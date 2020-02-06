{ everything but the kitchen sink }
PROGRAM p1;
VAR x : INTEGER;
VAR y,z : REAL;
VAR s : STRING;
BEGIN
  x := +3;
  y := x * -2;
  z := (y / 3) - 4 + x;
  s := 'Hello World';



  IF (2 * x) > 20 THEN
    x := 0
  ELSE
    BEGIN
       y :=0;
       z := z + 1
    END;

  WHILE z < 0 DO
     BEGIN
        z := z - 2
     END;

  WHILE  y >= 0 DO y := y -1;
  WHILE  x<=1 DO x := X + 1;
  WHILE  0<>z DO z := 0;
  WHILE S='Hi' DO s:='Bye'
END.
{ comment at end of program }