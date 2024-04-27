package main

import (
	"fmt"
	"math/rand"
	"time"
)

func eyeForAnEye(roundNumber int, selfChoices, enemyChoices []bool) bool {
	if roundNumber == 0 {
		return true
	} else {
		return enemyChoices[roundNumber-1]
	}
}

func spy(roundNumber int, selfChoices, enemyChoices []bool) bool {
	if roundNumber == 0 {
		return true
	} else {
		event := rand.Intn(10) // 10% chance of not cooperating
		if event == 0 {
			return false
		}
		return selfChoices[roundNumber-1] // otherwise, same as "eye for an eye"
	}
}

func random(roundNumber int, selfChoices, enemyChoices []bool) bool {
	return rand.Intn(2) == 0
}

func logic(first, second bool, firstPlayer, secondPlayer *int) {
	if first == second && first == false {
		*firstPlayer += 4
		*secondPlayer += 4
	}
	if first == second && first == true {
		*firstPlayer += 24
		*secondPlayer += 24
	}
	if first == true && second == false {
		*firstPlayer += 0
		*secondPlayer += 20
	}
	if first == false && second == true {
		*firstPlayer += 20
		*secondPlayer += 0
	}
}

func resultTable(firstPlayer, secondPlayer int) {
	if firstPlayer > secondPlayer {
		fmt.Printf("%d %d\nfirst player wins\n", firstPlayer, secondPlayer)
	} else if firstPlayer < secondPlayer {
		fmt.Printf("%d %d\nsecond player wins\n", firstPlayer, secondPlayer)
	} else {
		fmt.Printf("%d %d\ndraw\n", firstPlayer, secondPlayer)
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())
	amountOfRounds := rand.Intn(101) + 100
	var firstStrateg, secondStrateg []bool
	var firstPlayer, secondPlayer int

	fmt.Println("eyes for an eye vs spy")
	for roundNumber := 0; roundNumber < amountOfRounds; roundNumber++ {
		firstStrateg = append(firstStrateg, eyeForAnEye(roundNumber, firstStrateg, secondStrateg))
		secondStrateg = append(secondStrateg, spy(roundNumber, secondStrateg, firstStrateg))
		logic(firstStrateg[len(firstStrateg)-1], secondStrateg[len(secondStrateg)-1], &firstPlayer, &secondPlayer)
	}
	resultTable(firstPlayer, secondPlayer)
	firstStrateg, secondStrateg = nil, nil
	firstPlayer, secondPlayer = 0, 0

	fmt.Println("eyes for an eye vs random")
	for roundNumber := 0; roundNumber < amountOfRounds; roundNumber++ {
		firstStrateg = append(firstStrateg, eyeForAnEye(roundNumber, firstStrateg, secondStrateg))
		secondStrateg = append(secondStrateg, random(roundNumber, firstStrateg, secondStrateg))
		logic(firstStrateg[len(firstStrateg)-1], secondStrateg[len(secondStrateg)-1], &firstPlayer, &secondPlayer)
	}
	resultTable(firstPlayer, secondPlayer)
	firstStrateg, secondStrateg = nil, nil
	firstPlayer, secondPlayer = 0, 0

	fmt.Println("spy vs random")
	for roundNumber := 0; roundNumber < amountOfRounds; roundNumber++ {
		firstStrateg = append(firstStrateg, spy(roundNumber, firstStrateg, secondStrateg))
		secondStrateg = append(secondStrateg, random(roundNumber, firstStrateg, secondStrateg))
		logic(firstStrateg[len(firstStrateg)-1], secondStrateg[len(secondStrateg)-1], &firstPlayer, &secondPlayer)
	}
	resultTable(firstPlayer, secondPlayer)
}
