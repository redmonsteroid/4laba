package main

import (
	"fmt"
	"math"
)

func f(x float64) float64 {
	return math.Cos(x+0.3) - x*x
}

func df(x float64) float64 {
	return -math.Sin(x+0.3) - 2*x // Производная функции f(x)
}

func g(x float64) float64 {
	return math.Sqrt(math.Cos(x + 0.3)) // Функция g(x) для метода простых итераций
}

func newtonMethod(x0, epsilon float64) float64 {
	x := x0
	iteration := 1
	fmt.Println("Newton's Method Iterations:")
	fmt.Println("Iteration", "x", "difference")
	fmt.Println("__________________________________________________")

	for {
		f_x := f(x)
		df_x := df(x)
		x = x - f_x/df_x // след значение x
		fmt.Printf("%d %20.10f %20.10f\n", iteration, x, math.Abs(-f_x/df_x))
		iteration++
		if math.Abs(f(x)) <= epsilon {
			break
		}
	}

	return x
}

func simpleIterationMethod(x0, epsilon float64) float64 {
	xn := x0
	var xn_plus_1 float64
	iteration := 0
	isRepeated := false
	var roots []float64

	fmt.Println("\nSimple Iteration Method Iterations:")
	fmt.Println("Iteration", "xn", "xn+1", "difference")
	fmt.Println("__________________________________________________")

	for {
		xn_plus_1 = g(xn)
		fmt.Printf("%d %20.10f %15.10f %15.10f\n", iteration, xn, xn_plus_1, math.Abs(xn_plus_1-xn))

		for _, root := range roots {
			if math.Abs(xn_plus_1-root) < epsilon {
				isRepeated = true // проверка на повтор корня
				break
			}
		}
		if !isRepeated {
			roots = append(roots, xn_plus_1)
		}
		xn = xn_plus_1
		iteration++

		if math.Abs(g(xn)-xn) <= epsilon || iteration >= 100 || isRepeated {
			break
		}
	}

	return xn
}

func halfDivisionMethod(a, b, epsilon float64) float64 {
	iteration := 1
	var midPoint float64

	fmt.Println("\nHalf Division Method:")
	fmt.Println("N", "a", "b", "b-a")
	fmt.Println("_______________________________________")

	if f(a)*f(b) >= 0 {
		fmt.Println("Интервал выбран неправильно. В данном сегменте нет корня.")
		return math.NaN()
	}

	for {
		midPoint = (a + b) / 2.0
		fmt.Printf("%d %10.10f %14.10f %14.10f\n", iteration, a, b, b-a)

		if f(midPoint) == 0.0 {
			return midPoint // Найден точный корень
		} else if f(a)*f(midPoint) < 0 {
			b = midPoint // Корень находится в левой половине отрезка
		} else {
			a = midPoint // Корень находится в правой половине отрезка
		}

		if math.Abs(b-a) <= epsilon {
			break
		}
		iteration++
	}
	return (a + b) / 2.0 // Возвращаем середину последнего интервала как приближенный корень
}

func main() {
	a := 0.0          // Начало интервала
	b := 1.0          // Конец интервала
	epsilon := 0.0001 // Точность

	fmt.Println("Ищем корень уравнения cos(x + 0.3) - x^2 = 0 с использованием различных методов:")

	newton := newtonMethod((a+b)/2, epsilon)
	fmt.Println("Найденный корень методом Ньютона: x =", newton)

	simpleIteration := simpleIterationMethod((a+b)/2, epsilon)
	fmt.Println("Найденный корень простым итерационным методом: x =", simpleIteration)

	halfDivision := halfDivisionMethod(a, b, epsilon)
	fmt.Println("Найденный корень методом половинного деления: x =", halfDivision)
}
