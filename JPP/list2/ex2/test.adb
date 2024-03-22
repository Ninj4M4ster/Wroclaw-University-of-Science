with Library; use Library;
with Text_IO; use Text_IO;

package body test is
    procedure iterativeLibTest is
    test_passed: Boolean := true;
    factorial_results: array (factorial_argument) of Natural := (0 => 1, 1 => 1, 2 => 2, 3 => 6, 4 => 24,
    5 => 120, 6 => 720, 7 => 5040, 8 => 40320, 9 => 362880, 10 => 3628800, 11 => 39916800, 12 => 479001600);
    d_res: dioph_result;
    begin
        Put_Line("Iterative functions test");
        Put_Line("Factorial test");
        for i in 0..12 loop
            if factorial(factorial_argument(i)) /= factorial_results(i) then
                Put_Line("Bad result for n = " & Integer'Image(Integer(i)) & ", got " & Natural'Image(factorial(factorial_argument(i))) & ", expected " & Natural'Image(factorial_results(i)));
                test_passed := false;
            end if;
        end loop;

        if test_passed then
            Put_Line("Factorial test passed");
        end if;

        Put_Line("Gcm test");
        test_passed := true;
        if gcm(1002, 1213) /= 1 then
            Put_Line("Bad result for a = 1002, b = 1213: got " & Natural'Image(gcm(1002, 1213)) & ", expected 1");
            test_passed := false;
        end if;
        if gcm(1002, 1152) /= 6 then
            Put_Line("Bad result for a = 1002, b = 1152: got " & Natural'Image(gcm(1002, 1152)) & ", expected 6");
            test_passed := false;
        end if;
        if gcm(69, 783255) /= 3 then
            Put_Line("Bad result for a = 69, b = 783255: got " & Natural'Image(gcm(69, 783255)) & ", expected 3");
            test_passed := false;
        end if;
        if gcm(28, 14) /= 14 then
            Put_Line("Bad result for a = 28, b = 14: got " & Natural'Image(gcm(28, 14)) & ", expected 14");
            test_passed := false;
        end if;
        if test_passed = true then
            Put_Line("Gcm tests passed.");
        end if;

        Put_Line("Diophantive function tests");
        test_passed := true;
        d_res := dioph(3, 5, 149);
        if d_res.x /= 298 or d_res.y /= -149 or d_res.error_status /= 0 then
            Put("Bad result for a = 3, b = 5, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 298, y = -149, err_status = 0");
            test_passed := false;
        end if;
        d_res := dioph(15, 26, 149);
        if d_res.x /= 1043 or d_res.y /= -596 or d_res.error_status /= 0 then
            Put("Bad result for a = 15, b = 26, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 1043, y = -596, err_status = 0");
            test_passed := false;
        end if;
        d_res := dioph(0, 26, 149);
        if d_res.x /= 0 or d_res.y /= 0 or d_res.error_status /= 2 then
            Put("Bad result for a = 0, b = 26, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 0, y = 0, err_status = 2");
            test_passed := false;
        end if;
        d_res := dioph(0, 0, 149);
        if d_res.x /= 0 or d_res.y /= 0 or d_res.error_status /= 1 then
            Put("Bad result for a = 0, b = 0, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 0, y = 0, err_status = 1");
            test_passed := false;
        end if;
        if test_passed = true then
            Put_Line("Diophantive function tests passed.");
        end if;
    end;

    procedure recursiveLibTest is
    test_passed: Boolean := true;
    factorial_results: array (factorial_argument) of Natural := (0 => 1, 1 => 1, 2 => 2, 3 => 6, 4 => 24,
    5 => 120, 6 => 720, 7 => 5040, 8 => 40320, 9 => 362880, 10 => 3628800, 11 => 39916800, 12 => 479001600);
    d_res: dioph_result;
    begin
        Put_Line("Recursive functions test");
        Put_Line("Factorial test");
        for i in 0..12 loop
            if factorialRecursive(factorial_argument(i)) /= factorial_results(i) then
                Put_Line("Bad result for n = " & Integer'Image(Integer(i)) & ", got " & Natural'Image(factorialRecursive(factorial_argument(i))) & ", expected " & Natural'Image(factorial_results(i)));
                test_passed := false;
            end if;
        end loop;

        if test_passed then
            Put_Line("Factorial test passed");
        end if;

        Put_Line("Gcm test");
        test_passed := true;
        if gcmRecursive(1002, 1213) /= 1 then
            Put_Line("Bad result for a = 1002, b = 1213: got " & Natural'Image(gcmRecursive(1002, 1213)) & ", expected 1");
            test_passed := false;
        end if;
        if gcmRecursive(1002, 1152) /= 6 then
            Put_Line("Bad result for a = 1002, b = 1152: got " & Natural'Image(gcmRecursive(1002, 1152)) & ", expected 6");
            test_passed := false;
        end if;
        if gcmRecursive(69, 783255) /= 3 then
            Put_Line("Bad result for a = 69, b = 783255: got " & Natural'Image(gcmRecursive(69, 783255)) & ", expected 3");
            test_passed := false;
        end if;
        if gcmRecursive(28, 14) /= 14 then
            Put_Line("Bad result for a = 28, b = 14: got " & Natural'Image(gcmRecursive(28, 14)) & ", expected 14");
            test_passed := false;
        end if;
        if test_passed = true then
            Put_Line("Gcm tests passed.");
        end if;

        Put_Line("Diophantive function tests");
        test_passed := true;
        d_res := diophRecursive(3, 5, 149);
        if d_res.x /= 298 or d_res.y /= -149 or d_res.error_status /= 0 then
            Put("Bad result for a = 3, b = 5, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 298, y = -149, err_status = 0");
            test_passed := false;
        end if;
        d_res := diophRecursive(15, 26, 149);
        if d_res.x /= 1043 or d_res.y /= -596 or d_res.error_status /= 0 then
            Put("Bad result for a = 15, b = 26, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 1043, y = -596, err_status = 0");
            test_passed := false;
        end if;
        d_res := diophRecursive(0, 26, 149);
        if d_res.x /= 0 or d_res.y /= 0 or d_res.error_status /= 2 then
            Put("Bad result for a = 0, b = 26, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 0, y = 0, err_status = 2");
            test_passed := false;
        end if;
        d_res := diophRecursive(0, 0, 149);
        if d_res.x /= 0 or d_res.y /= 0 or d_res.error_status /= 1 then
            Put("Bad result for a = 0, b = 0, c = 149: got x = " & Integer'Image(d_res.x) &", y = " & Integer'Image(d_res.y) & ", err_status = " & Integer'Image(d_res.error_status));
            Put_Line(" expected x = 0, y = 0, err_status = 1");
            test_passed := false;
        end if;
        if test_passed = true then
            Put_Line("Diophantive function tests passed.");
        end if;
    end;

end test;