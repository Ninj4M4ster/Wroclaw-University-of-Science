package Library is
    -- Structure for holding result of diophantine equation.
    type dioph_result is record
        x : Integer := 0;
        y: Integer := 0;
        error_status: Integer := 0;
    end record;

    -- Argument type of a factorial function.
    subtype factorial_argument is Natural range 0 .. 12 ;

    function factorial(n : factorial_argument) return Natural;
    function gcm(a : Natural; b : Natural) return Natural;
    function dioph(a : Integer; b : Integer; c : Integer) return dioph_result;
    function factorialRecursive(n : factorial_argument) return Natural;
    function gcmRecursive(a : Natural; b : Natural) return Natural;
    function diophRecursive(a : Integer; b : Integer; c : Integer) return dioph_result;
private
    function recursiveExtendedEuclides(a : Integer; 
                                        b : Integer; 
                                        x : Integer; 
                                        y : Integer; 
                                        x_temp : Integer; 
                                        y_temp : Integer) return dioph_result;
end Library;