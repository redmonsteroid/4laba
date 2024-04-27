package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

func findld(arr []int) []int {
	currentLength := 1
	maxLength := 1
	startIndex := 0
	maxStartIndex := 0
	prev := arr[0]

	for index, num := range arr {
		if index > 0 {
			if num < prev {
				currentLength++
			} else {
				if currentLength > maxLength {
					maxLength = currentLength
					maxStartIndex = startIndex
				}
				currentLength = 1
				startIndex = index
			}
		}
		prev = num
	}

	if currentLength > maxLength {
		maxLength = currentLength
		maxStartIndex = startIndex
	}

	result := make([]int, maxLength)
	copy(result, arr[maxStartIndex:maxStartIndex+maxLength])
	return result
}

func thirdVector(arr []int) []int {
	sum := 0
	for _, n := range arr {
		sum += n
	}
	avg := float64(sum) / float64(len(arr))

	var result []int
	for _, n := range arr {
		if float64(n) < avg {
			result = append(result, n)
		}
	}
	return result
}

func fourthVector(arr []int) []int {
	first, second := arr[0], arr[1]
	result := append([]int{}, arr[2:]...)
	result = append(result, first, second)
	return result
}

func fifth1(arr []int) []int {
	result := make([]int, len(arr))
	copy(result, arr)
	sort.Sort(sort.Reverse(sort.IntSlice(result)))
	return result
}

func fifth2(arr []int) []int {
	digitCount := make([]int, 10)

	for _, num := range arr {
		temp := num
		for temp > 0 {
			digit := temp % 10
			digitCount[digit]++
			temp /= 10
		}
	}

	return digitCount
}

func main() {
	rand.Seed(time.Now().UnixNano())

	var randomVector []int
	n := 10

	// Заполняем срез случайными значениями от 150 до 350
	for i := 0; i < n; i++ {
		randomVector = append(randomVector, rand.Intn(201)+150) // [150, 350]
	}

	taskVector := findld(randomVector)
	fmt.Println("Original Random Vector:", randomVector)
	fmt.Println("Result of findld:", taskVector)

	randomVector = nil
	// Заполняем срез случайными значениями ASCII (от 31 до 123)
	for i := 0; i < n; i++ {
		randomVector = append(randomVector, rand.Intn(93)+31) // ASCII range (31-123)
	}

	fmt.Println("Random ASCII Vector:")
	for _, num := range randomVector {
		character := rune(num) // Преобразуем int в Unicode символ
		fmt.Printf("%c ", character)
	}
	fmt.Println()

	taskVector = fourthVector(randomVector)
	for _, num := range taskVector {
		character := rune(num) // Преобразуем int в Unicode символ
		fmt.Printf("%c ", character)
	}
	fmt.Println()
	randomVector = nil
	// Заполняем срез случайными значениями от 100 до 900
	for i := 0; i < n; i++ {
		randomVector = append(randomVector, rand.Intn(801)+100) // [100, 900]
	}

	taskVector = fifth1(randomVector)
	fmt.Println("Result of fifth1 (sorted descending):", taskVector)

	taskVector = fifth2(randomVector)
	fmt.Println("Result of fifth2 (digit count):", taskVector)
}
