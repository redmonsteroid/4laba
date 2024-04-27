package main

import (
	"fmt"
)

func main() {
	var rand []int
	var xi int // number for rand
	var repeat int
	firstAppear := false

	fmt.Println("Enter x0, A, B, C")
	var x0, A, B, C int
	fmt.Scanln(&x0, &A, &B, &C)

	if !(0 <= A && A <= C) || !(0 <= B && B <= C) || !(0 <= x0 && x0 < C) {
		fmt.Println("error")
		return
	}

	rand = append(rand, x0)
	for i := 0; i < 9; i++ {
		xi = (A*rand[i] + B) % C
		rand = append(rand, xi)
		if x0 == xi && len(rand) > 1 && !firstAppear {
			repeat = i + 2 // +2 because index starts from 0 and value is added on the next iteration
			firstAppear = true
		}
	}

	for _, n := range rand {
		fmt.Print(n, " ")
	}
	fmt.Println()
	fmt.Println(repeat)
}
