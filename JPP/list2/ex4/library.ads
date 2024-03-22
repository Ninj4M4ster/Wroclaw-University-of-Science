with Interfaces.C; use Interfaces.C;

package Library is
    -- Structure for holding result of diophantine equation.
    type dioph_result is record
        x : Integer := 0;
        y: Integer := 0;
        error_status: Integer := 0;
    end record
        with Convention => C;

    -- Argument type of a factorial function.
    subtype factorial_argument is Natural range 0 .. 12;

    function factorial(n : factorial_argument) return Natural
        with 
            Export => True,
            Convention => C,
            External_Name => "factorial";
    function gcm(a : Natural; b : Natural) return Natural
        with 
            Export => True,
            Convention => C,
            External_Name => "gcm";
    function dioph(a : Integer; b : Integer; c : Integer) return dioph_result
        with 
            Export => True,
            Convention => C,
            External_Name => "dioph";
    function factorialRecursive(n : factorial_argument) return Natural
        with 
            Export => True,
            Convention => C,
            External_Name => "factorialRecursive";
    function gcmRecursive(a : Natural; b : Natural) return Natural
        with 
            Export => True,
            Convention => C,
            External_Name => "gcmRecursive";
    function diophRecursive(a : Integer; b : Integer; c : Integer) return dioph_result
        with 
            Export => True,
            Convention => C,
            External_Name => "diophRecursive";
private
    function recursiveExtendedEuclides(a : Integer; 
                                        b : Integer; 
                                        x : Integer; 
                                        y : Integer; 
                                        x_temp : Integer; 
                                        y_temp : Integer) return dioph_result;
end Library;