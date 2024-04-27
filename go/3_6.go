package main

import (
	"fmt"
	"math"
	"math/rand"
)

func fillVectorWithRandom(vec []int) {
	for i := range vec {
		vec[i] = rand.Intn(100) + 1
	}
}

func countOccurrences(container []int, element int) int {
	count := 0
	for _, value := range container {
		if value == element {
			count++
		}
	}
	return count
}

func mean(container []int) float64 {
	var n float64
	for _, i := range container {
		n += float64(i)
	}
	return n / float64(len(container))
}

func variance(container []int) float64 {
	m := mean(container)
	var sumSqDiff float64
	for _, value := range container {
		sumSqDiff += (float64(value) - m) * (float64(value) - m)
	}
	return sumSqDiff / float64(len(container)-1)
}

func normalCDF(x float64) float64 {
	return (1.0 / 2.0) * (1.0 + math.Erf(x/math.Sqrt2))
}

func chiSquareTest(container []int) float64 {
	size := len(container)
	var chi2 float64
	meanVal := mean(container)
	stdDev := math.Sqrt(variance(container))

	for i := 1; i <= 100; i++ {
		expectedFreq := float64(size) * (normalCDF(float64(i-int(meanVal))/stdDev) - normalCDF(float64(i-1-int(meanVal))/stdDev))
		observedFreq := float64(countOccurrences(container, i))
		chi2 += math.Pow(observedFreq-expectedFreq, 2) / expectedFreq
	}

	return chi2
}

func chiPrint(vec []int, criticalValue float64) {
	chiSquareValue := chiSquareTest(vec)
	meanExpected := mean(vec)
	meanObserved := mean(vec)

	fmt.Println("Chi-Square P-value:", chiSquareValue)
	if chiSquareValue <= criticalValue {
		fmt.Println("Hypothesis of normal distribution is not rejected.")
	} else {
		fmt.Println("Hypothesis of normal distribution is rejected.")
	}
	fmt.Println("Expected mean:", meanExpected)
	fmt.Println("Observed mean:", meanObserved)
	fmt.Println()
}

func main() {
	vector50 := make([]int, 50)
	vector100 := make([]int, 100)
	vector1000 := make([]int, 1000)
	fillVectorWithRandom(vector50)
	fillVectorWithRandom(vector100)
	fillVectorWithRandom(vector1000)
	criticalValue := 124.342 // Critical chi-square value for 99 degrees of freedom and 0.05 significance level
	chiPrint(vector50, criticalValue)
	chiPrint(vector100, criticalValue)
	chiPrint(vector1000, criticalValue)
}
