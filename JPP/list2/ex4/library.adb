package body Library is
    -- This function iteratively calculates factorial of given number.
    -- 
    -- param arg Argument of factorial.
    -- return Factorial of given argument or 0, if factorial is not possible to calculate.
    function factorial(n : factorial_argument) return Natural is
    result: Natural := 1;
    it: Natural := 2;
    begin
        while it <= n loop
            result := result * it;
            it := it + 1;
        end loop;
        return result;
    end factorial;

    -- This function iteratively calculates the greatest common measure of two given numbers.
    -- 
    -- param a First number.
    -- param b Second number.
    -- return Greatest common measure of two given numbers.
    function gcm(a : Natural; b : Natural) return Natural is
    tmp: Natural;
    a_copy: Natural := a;
    b_copy: Natural := b;
    begin
        while b_copy /= 0 loop
            tmp := a_copy;
            a_copy := b_copy;
            b_copy := tmp mod b_copy;
        end loop;
        return a_copy;
    end gcm;

    -- This function iteratively finds the result of a diophantine equation of the following form:
    -- ax + by = c.
    -- 
    -- param a Value a in equation.
    -- param b Value b in equation.
    -- param c Value c in equation.
    -- return Structure holding result x and y of equation and error status. 
    --        If error status == 1 - two zeros for a and b were given and c is != 0. 
    --        If error status == 2 - there is no integral result available.
    function dioph(a : Integer; b : Integer; c : Integer) return dioph_result is
    a_copy: Integer := a;
    b_copy: Integer := b;
    c_copy: Integer := c;
    result: dioph_result;
    reversed: Boolean := false;
    a_p: Natural;
    b_p: Natural;
    d: Natural;
    tmp: Integer;
    s: Integer;
    x: Integer := 1;
    y: Integer := 0;
    div_result: Integer;
    div_rest: Integer := 1;
    x_temp: Integer := 0;
    y_temp: Integer := 1;
    helper_x_temp: Integer;
    helper_y_temp: Integer;
    begin
        a_p := Natural(if a_copy < 0 then a_copy * (-1) else a_copy);
        b_p := Natural(if b_copy < 0 then b_copy * (-1) else b_copy);
        d := gcm(a_p, b_p);
        if d = 0 then
            if c_copy /= 0 then
                result.error_status := 1;
            end if;
        elsif c_copy mod Integer(d) /= 0 then
            result.error_status := 2;
        else 
            if a_copy < b_copy then
                tmp := a_copy;
                a_copy := b_copy;
                b_copy := tmp;
                reversed := true;
            end if;
            if b_copy /= 0 then
                while div_rest /= 0 loop
                    div_result := a_copy / b_copy;
                    div_rest := a_copy mod b_copy;
                    a_copy := b_copy;
                    b_copy := div_rest;
                    
                    helper_x_temp := x_temp;
                    helper_y_temp := y_temp;
                    x_temp := x - div_result * x_temp;
                    y_temp := y - div_result * y_temp;
                    x := helper_x_temp;
                    y := helper_y_temp;
                end loop;
            end if;
            if reversed then
                result.x := y;
                result.y := x;
            else
                result.x := x;
                result.y := y;
            end if;
            s := c_copy / d;
            result.x := result.x * s;
            result.y := result.y * s;
        end if;
        return result;
    end dioph;

    -- This function recursively calculates factorial of given number.
    -- 
    -- param arg Argument of factorial.
    -- return Factorial of given argument or 0, if factorial is not possible to calculate.
    function factorialRecursive(n : factorial_argument) return Natural is
    begin
        if n <= 1 then
            return 1;
        end if;
        return n * factorialRecursive(n - 1);
    end factorialRecursive;

    -- This function recursively calculates the greatest common measure of two given numbers.
    -- 
    -- param a First number.
    -- param b Second number.
    -- return Greatest common measure of two given numbers.
    function gcmRecursive(a : Natural; b : Natural) return Natural is
    begin
        if b = 0 then
            return a;
        end if;
        return gcmRecursive(b, a mod b);
    end gcmRecursive;

    -- This is a helper function. It implements recursive extended euclides algorithm.
    -- It finds results of following equation: ax + by = gcm(a, b)
    -- 
    -- param a Value of a.
    -- param b Value of b.
    -- param x Current result of x.
    -- param y Current result of y.
    -- param x_temp Temporary value of x.
    -- param y_temp Temporary value of y.
    function recursiveExtendedEuclides(a : Integer; 
                                       b : Integer; 
                                       x : Integer; 
                                       y : Integer; 
                                       x_temp : Integer; 
                                       y_temp : Integer) return dioph_result is
    result: dioph_result;
    div_result: Natural;
    begin
        result.x := x;
        result.y := y;
        if b /= 0 then
            div_result := a / b;
            result := recursiveExtendedEuclides(b, a mod b, x_temp, y_temp, x - div_result * x_temp, y - div_result * y_temp);
        end if;
        return result;
    end recursiveExtendedEuclides;

    -- This function recursively finds the result of a diophantine equation of the following form:
    -- ax + by = c.
    -- 
    -- param a Value a in equation.
    -- param b Value b in equation.
    -- param c Value c in equation.
    -- return Structure holding result x and y of equation and error status. 
    --         If error status == 1 - two zeros for a and b were given and c is != 0. 
    --         If error status == 2 - there is no integral result available.
    function diophRecursive(a : Integer; b : Integer; c : Integer) return dioph_result is
    a_copy: Integer := a;
    b_copy: Integer := b;
    c_copy: Integer := c;
    result: dioph_result;
    reversed: Boolean := false;
    a_p: Natural;
    b_p: Natural;
    d: Natural;
    tmp: Integer;
    s: Integer;
    x: Integer := 1;
    y: Integer := 0;
    div_rest: Integer := 1;
    x_temp: Integer := 0;
    y_temp: Integer := 1;
    begin
        a_p := Natural(if a_copy < 0 then a_copy * (-1) else a_copy);
        b_p := Natural(if b_copy < 0 then b_copy * (-1) else b_copy);
        d := gcm(a_p, b_p);
        if d = 0 then
            if c_copy /= 0 then
                result.error_status := 1;
            end if;
        elsif c_copy mod Integer(d) /= 0 then
            result.error_status := 2;
        else 
            if a_copy < b_copy then
                tmp := a_copy;
                a_copy := b_copy;
                b_copy := tmp;
                reversed := true;
            end if;
            if b_copy /= 0 then
                result := recursiveExtendedEuclides(a_copy, b_copy, x, y, x_temp, y_temp);
            end if;
            if reversed then
                tmp := result.x;
                result.x := result.y;
                result.y := tmp;
            end if;
            s := c_copy / d;
            result.x := result.x * s;
            result.y := result.y * s;
        end if;
        return result;
    end diophRecursive;
end Library;