package main

/**
 * @brief Structure for holding result of diophantine equation.
 */
type dioph_res struct {
	x            int64
	y            int64
	error_status uint8
}

/**
 * This function iteratively calculates factorial of given number.
 *
 * @param arg Argument of factorial.
 * @return Factorial of given argument or 0, if factorial is not possible to calculate.
 */
func factorial(n uint8) uint64 {
	var result uint64 = 1
	var it uint64 = 2
	for it <= (uint64)(n) && result*it > result {
		result *= it
		it++
	}
	if it <= (uint64)(n) {
		return 0
	}
	return result
}

/**
 * This function iteratively calculates the greatest common measure of two given numbers.
 *
 * @param a First number.
 * @param b Second number.
 * @return Greatest common measure of two given numbers.
 */
func gcm(a uint64, b uint64) uint64 {
	var help uint64
	for b != 0 {
		help = a
		a = b
		b = help % b
	}
	return a
}

/**
 * This function iteratively finds the result of a diophantine equation of the following form:
 * ax + by = c.
 *
 * @param a Value a in equation.
 * @param b Value b in equation.
 * @param c Value c in equation.
 * @return Structure holding result x and y of equation and error status.
 *         If error status == 1 - two zeros for a and b were given and c is != 0.
 *         If error status == 2 - there is no integral result available.
 */
func dioph(a int64, b int64, c int64) dioph_res {
	var result dioph_res = dioph_res{0, 0, 0}
	var reversed = false
	var a_p uint64
	var b_p uint64
	if a < 0 {
		a_p = (uint64)(a * -1)
	} else {
		a_p = (uint64)(a)
	}
	if b < 0 {
		b_p = (uint64)(b * -1)
	} else {
		b_p = (uint64)(b)
	}
	var d uint64 = gcm(a_p, b_p)
	if d == 0 { // a and b == 0
		if c != 0 {
			result.error_status = 1
		}
	} else if c%(int64)(d) != 0 { // no result available
		result.error_status = 2
	} else {
		if a < b {
			var p int64 = a
			a = b
			b = p
			reversed = true
		}
		var x int64 = 1
		var y int64 = 0
		if b != 0 {
			var div_result int64
			var div_rest int64 = 1
			var x_temp int64 = 0
			var y_temp int64 = 1
			for div_rest != 0 { // extended euklides algorithm
				div_result = a / b
				div_rest = a % b
				a = b
				b = div_rest

				var helper_x_temp int64 = x_temp
				var helper_y_temp int64 = y_temp
				x_temp = x - div_result*x_temp
				y_temp = y - div_result*y_temp
				x = helper_x_temp
				y = helper_y_temp
			}
		}
		if reversed {
			result.x = y
			result.y = x
		} else {
			result.x = x
			result.y = y
		}
		var s int64 = c / (int64)(d)
		result.x *= s
		result.y *= s
	}
	return result
}

/**
 * This function recursively calculates factorial of given number.
 *
 * @param arg Argument of factorial.
 * @return Factorial of given argument or 0, if factorial is not possible to calculate.
 */
func factorialRecursive(arg uint8) uint64 {
	if arg <= 1 {
		return 1
	}
	var current_result uint64 = factorialRecursive(arg - 1)
	if current_result*(uint64)(arg) <= current_result {
		return 0
	}
	return current_result * (uint64)(arg)
}

/**
 * This function recursively calculates the greatest common measure of two given numbers.
 *
 * @param a First number.
 * @param b Second number.
 * @return Greatest common measure of two given numbers.
 */
func gcmRecursive(a uint64, b uint64) uint64 {
	if b == 0 {
		return a
	}
	return gcmRecursive(b, a%b)
}

/**
 * This is a helper function. It implements recursive extended euclides algorithm.
 * It finds results of following equation: ax + by = gcm(a, b)
 *
 * @param a Value of a.
 * @param b Value of b.
 * @param x Current result of x.
 * @param y Current result of y.
 * @param x_temp Temporary value of x.
 * @param y_temp Temporary value of y.
 */
func recursiveExtendedEuclides(a int64,
	b int64,
	x int64,
	y int64,
	x_temp int64,
	y_temp int64) dioph_res {
	var result dioph_res = dioph_res{x, y, 0}
	if b != 0 {
		var div_result int64 = a / b
		result = recursiveExtendedEuclides(b, a%b, x_temp, y_temp, x-div_result*x_temp, y-div_result*y_temp)
	}
	return result
}

/**
 * This function recursively finds the result of a diophantine equation of the following form:
 * ax + by = c.
 *
 * @param a Value a in equation.
 * @param b Value b in equation.
 * @param c Value c in equation.
 * @return Structure holding result x and y of equation and error status.
 *         If error status == 1 - two zeros for a and b were given and c is != 0.
 *         If error status == 2 - there is no integral result available.
 */
func diophRecursive(a int64, b int64, c int64) dioph_res {
	var result dioph_res = dioph_res{0, 0, 0}
	var reversed bool = false
	var a_p uint64
	var b_p uint64
	if a < 0 {
		a_p = (uint64)(a * -1)
	} else {
		a_p = (uint64)(a)
	}
	if b < 0 {
		b_p = (uint64)(b * -1)
	} else {
		b_p = (uint64)(b)
	}
	var d uint64 = gcm(a_p, b_p)
	if d == 0 { // a and b == 0
		if c != 0 {
			result.error_status = 1
		}
	} else if c%(int64)(d) != 0 { // no result available
		result.error_status = 2
	} else {
		if a < b {
			var p int64 = a
			a = b
			b = p
			reversed = true
		}
		var x int64 = 1
		var y int64 = 0
		if b != 0 {
			var x_temp int64 = 0
			var y_temp int64 = 1
			result = recursiveExtendedEuclides(a, b, x, y, x_temp, y_temp)
		}
		if reversed {
			var tmp int64 = result.x
			result.x = result.y
			result.y = tmp
		}
		var s int64 = c / (int64)(d)
		result.x *= s
		result.y *= s
	}
	return result
}
