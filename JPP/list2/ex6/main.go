package main

/*
#include "lib.c"
*/
import "C"
import (
	"fmt"
)

func iterativeLibTest() {
	fmt.Println("Testing iterative functions")
	var tests_passed bool = true

	fmt.Println("Factorial test")
	var factorial_results = [22]uint64{
		1, 1, 2, 6, 24, 120, 720,
		5040, 40320, 362880, 3628800,
		39916800, 479001600, 6227020800,
		87178291200, 1307674368000, 20922789888000,
		355687428096000, 6402373705728000, 121645100408832000,
		2432902008176640000, 14197454024290336768}
	for i := 0; i < 22; i++ {
		if C.factorial(C.uint(i)) != C.ulonglong(factorial_results[i]) {
			fmt.Println("Bad result for n = ", i, ": got ", C.factorial(C.uint(i)), ", expected ", C.ulonglong(factorial_results[i]))
			tests_passed = false
		}
	}
	if C.factorial(23) != 0 {
		fmt.Println("Bad result for n = 23: got ", 23, " expected 0")
		tests_passed = false
	}
	if tests_passed {
		fmt.Println("Factorial tests passed.")
	}

	fmt.Println("Gcm test")
	tests_passed = true
	if C.gcm(1002, 1213) != 1 {
		fmt.Println("Bad result for a = 1002, b = 1213: got ", C.gcm(1002, 1213), " expected ", 1)
		tests_passed = false
	}
	if C.gcm(1002, 1152) != 6 {
		fmt.Println("Bad result for a = 1002, b = 1152: got ", C.gcm(1002, 1152), " expected ", 6)
		tests_passed = false
	}
	if C.gcm(69, 783255) != 3 {
		fmt.Println("Bad result for a = 69, b = 783255: got ", C.gcm(69, 783255), " expected ", 3)
		tests_passed = false
	}
	if C.gcm(28, 14) != 14 {
		fmt.Println("Bad result for a = 28, b = 14: got ", C.gcm(28, 14), " expected ", 14)
		tests_passed = false
	}
	if tests_passed {
		fmt.Println("Gcm tests passed.")
	}

	fmt.Println("Diophantive function tests")
	tests_passed = true
	var d_res = C.dioph(3, 5, 149)
	if d_res.x != 298 || d_res.y != -149 || d_res.error_status != 0 {
		fmt.Print("Bad result for a = 3, b = 5, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 298, -149, 0)
		tests_passed = false
	}
	d_res = C.dioph(15, 26, 149)
	if d_res.x != 1043 || d_res.y != -596 || d_res.error_status != 0 {
		fmt.Print("Bad result for a = 15, b = 26, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 1043, -596, 0)
		tests_passed = false
	}
	d_res = C.dioph(0, 26, 149)
	if d_res.x != 0 || d_res.y != 0 || d_res.error_status != 2 {
		fmt.Print("Bad result for a = 0, b = 26, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 0, 0, 2)
		tests_passed = false
	}
	d_res = C.dioph(0, 0, 149)
	if d_res.x != 0 || d_res.y != 0 || d_res.error_status != 1 {
		fmt.Print("Bad result for a = 0, b = 0, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 0, 0, 1)
		tests_passed = false
	}
	if tests_passed {
		fmt.Println("Diophantive function tests passed.")
	}
}

func recursiveLibTest() {
	fmt.Println("Testing recursive functions")
	var tests_passed bool = true

	fmt.Println("Factorial test")
	var factorial_results = [22]uint64{
		1, 1, 2, 6, 24, 120, 720,
		5040, 40320, 362880, 3628800,
		39916800, 479001600, 6227020800,
		87178291200, 1307674368000, 20922789888000,
		355687428096000, 6402373705728000, 121645100408832000,
		2432902008176640000, 14197454024290336768}
	for i := 0; i < 22; i++ {
		if C.factorialRecursive(C.uint(i)) != C.ulonglong(factorial_results[i]) {
			fmt.Println("Bad result for n = ", i, ": got ", C.factorialRecursive(C.uint(i)), ", expected ", C.ulonglong(factorial_results[i]))
			tests_passed = false
		}
	}
	if C.factorialRecursive(23) != 0 {
		fmt.Println("Bad result for n = 23: got ", 23, " expected 0")
		tests_passed = false
	}
	if tests_passed {
		fmt.Println("Factorial tests passed.")
	}

	fmt.Println("Gcm test")
	tests_passed = true
	if C.gcmRecursive(1002, 1213) != 1 {
		fmt.Println("Bad result for a = 1002, b = 1213: got ", C.gcmRecursive(1002, 1213), " expected ", 1)
		tests_passed = false
	}
	if C.gcmRecursive(1002, 1152) != 6 {
		fmt.Println("Bad result for a = 1002, b = 1152: got ", C.gcmRecursive(1002, 1152), " expected ", 6)
		tests_passed = false
	}
	if C.gcmRecursive(69, 783255) != 3 {
		fmt.Println("Bad result for a = 69, b = 783255: got ", C.gcmRecursive(69, 783255), " expected ", 3)
		tests_passed = false
	}
	if C.gcmRecursive(28, 14) != 14 {
		fmt.Println("Bad result for a = 28, b = 14: got ", C.gcmRecursive(28, 14), " expected ", 14)
		tests_passed = false
	}
	if tests_passed {
		fmt.Println("Gcm tests passed.")
	}

	fmt.Println("Diophantive function tests")
	tests_passed = true
	var d_res = C.diophRecursive(3, 5, 149)
	if d_res.x != 298 || d_res.y != -149 || d_res.error_status != 0 {
		fmt.Print("Bad result for a = 3, b = 5, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 298, -149, 0)
		tests_passed = false
	}
	d_res = C.diophRecursive(15, 26, 149)
	if d_res.x != 1043 || d_res.y != -596 || d_res.error_status != 0 {
		fmt.Print("Bad result for a = 15, b = 26, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 1043, -596, 0)
		tests_passed = false
	}
	d_res = C.diophRecursive(0, 26, 149)
	if d_res.x != 0 || d_res.y != 0 || d_res.error_status != 2 {
		fmt.Print("Bad result for a = 0, b = 26, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 0, 0, 2)
		tests_passed = false
	}
	d_res = C.diophRecursive(0, 0, 149)
	if d_res.x != 0 || d_res.y != 0 || d_res.error_status != 1 {
		fmt.Print("Bad result for a = 0, b = 0, c = 149: got x = ", d_res.x, " y = ", d_res.y, " err_status = ", d_res.error_status)
		fmt.Printf(", expected x = %d, y = %d, err_status = %d\n", 0, 0, 1)
		tests_passed = false
	}
	if tests_passed {
		fmt.Println("Diophantive function tests passed.")
	}
}

func main() {
	iterativeLibTest()
	recursiveLibTest()
}
