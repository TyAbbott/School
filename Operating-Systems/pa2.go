// Academic Integrity statement Ty Abbott ty937650 - “I Ty Abbott ty937650 affirm that this
// program is entirely my own work and that I have neither developed my code together with any
// another person, nor copied any code from any other person, nor permitted my code to be copied
// or otherwise used by any other person, nor have I copied, modified, or otherwise used programs
// created by others. I acknowledge that any violation of the above terms will be treated as academic
// dishonesty.”

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

type info struct {
	types, upper, lower, init, size int
}
func main() {
	input := os.Args[1]
	specs, requests := readInput(input)
	check := checkabort(specs)
	if !check {
		requests, specs.size = checkerrors(requests, specs)
		switch specs.types {
			case 0:
				fmt.Printf("Seek algorithm: FCFS\n")
				printOutput(requests, specs)
				fcfs(requests, specs)
			case 1:
				fmt.Printf("Seek algorithm: SSTF\n")
				printOutput(requests, specs)
				sstf(requests, specs)
			case 2:
				fmt.Printf("Seek algorithm: LOOK\n")
				printOutput(requests, specs)
				look(requests, specs)
			case 3:
				fmt.Printf("Seek algorithm: C-LOOK\n")
				printOutput(requests, specs)
				clook(requests, specs)
			case 4:
				fmt.Printf("Seek algorithm: SCAN\n")
				printOutput(requests, specs)
				scan(requests, specs)
			case 5:
				fmt.Printf("Seek algorithm: C-SCAN\n")
				printOutput(requests, specs)
				cscan(requests, specs)
			default:
				fmt.Printf("Type undeclared")
		}
	} else {
		// do nothing
	}
}

// Checks errors
func check(e error) {
	if e != nil {
		panic(e)
	}
}

// Checks for aborts before running program
func checkabort(specs info) bool {
	check := false
	if specs.upper < specs.lower {
		fmt.Printf("ABORT(13):upper (%d) < lower (%d)\n", specs.upper, specs.lower)
		check = true
	} else if specs.init < specs.lower {
		fmt.Printf("ABORT(12):initial (%d) < lower (%d)\n", specs.init, specs.lower)
		check = true
	} else if specs.init > specs.upper {
		fmt.Printf("ABORT(11):initial (%d) > upper (%d)\n", specs.init, specs.upper)
		check = true
	} else {
		check = false
	}
	return check
}

// Checks for errors and removes requests causing the error
func checkerrors(requests [20]int, specs info) ([20]int, int) {
	newrequests := requests
	newsize := specs.size
	for j := 0; j < specs.size; j++ {
		if requests[j] > specs.upper || requests[j] < specs.lower {
			fmt.Printf("ERROR(15):Request out of bounds: req (%d) > upper (%d) or < lower (%d)\n", requests[j], specs.upper, specs.lower)
			for i := j; i < 19; i++ {
				newrequests[i] = requests[i+1]
			}
			newsize--
		}
	}
	return newrequests, newsize
}

// Reads input from file and populates int array and info struct
func readInput(input string) (info, [20]int) {
	// struct to store information and array to hold requests
	var specs info
	var requests [20]int
	
	// variables for reading input
	var count, keyword int = 0, 0
	var e error = nil
	// open and defer closing the file
	file, err := os.Open(input)
	check(err)
	defer file.Close()
	
	// setting up scanner to read file
	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanWords)
	
	// add each word in the file to a string array
	var words []string
	for scanner.Scan() {
		words = append(words, scanner.Text())
	}
	
	// loop through each word in the array
	for _, word := range words {
		// checking if we are right after a keyword
		if keyword != 0 {
			switch keyword {
			// use
			case 1 :
				switch word {
				case "fcfs":
					specs.types = 0
					keyword = 0
				case "sstf":
					specs.types = 1
					keyword = 0
				case "look":
					specs.types = 2
					keyword = 0
				case "c-look":
					specs.types = 3
					keyword = 0
				case "scan":
					specs.types = 4
					keyword = 0
				case "c-scan":
					specs.types = 5
					keyword = 0
				default:
					fmt.Println("Error reading use")
				}
			// lowerCYL
			case 2 :
				specs.lower, e = strconv.Atoi(word)
				keyword = 0
			// upperCYL
			case 3 :
				specs.upper, e = strconv.Atoi(word)
				keyword = 0
			// initCYL
			case 4 :
				specs.init, e = strconv.Atoi(word)
				keyword = 0
			// cylreq
			case 5 :
				requests[count], e = strconv.Atoi(word)
				count++
				keyword = 0
			default:
				fmt.Println("keyword not recognized")
			}
		}
		// look for keywords
		switch word {
		case "use":
			keyword = 1
		case "lowerCYL":
			keyword = 2
		case "upperCYL":
			keyword = 3
		case "initCYL":
			keyword = 4
		case "cylreq":
			keyword = 5
		case "#":
		default:
			keyword = 0
		}		
	}
	specs.size = count
	check(e)
	return specs, requests
}

// Prints output
func printOutput(requests [20]int, specs info) {
	fmt.Printf("\tLower cylinder: %5d\n", specs.lower)
	fmt.Printf("\tUpper cylinder: %5d\n", specs.upper)
	fmt.Printf("\tInit cylinder:  %5d\n", specs.init)
	fmt.Printf("\tCylinder requests:\n")
	for i := 0; i < specs.size; i++ {
		fmt.Printf("\t\tCylinder %5d\n", requests[i])
	}
}

// Simple bubble sort algorithm for sorting int arrays
func bubblesort(array [20]int, size int) ([20]int){
	for i := 0; i < size; i++ {
		for j := 0; j < (size-1-i); j++ {
			if array[j] > array[j+1] {
				array[j], array[j+1] = array[j+1], array[j]
			}
		}
	}
	return array
}

// Makes a negative number postive
func makepos(a int) (int) {
	if a < 0 {
		return (a-(2*a))
	} else {
		return a
	}
}

// First-Come First-Served
// Disk requests are fulfilled in the order of their arrival
func fcfs(requests [20]int, specs info) {
	// Start at init and go to first request
	var total, diff int = 0, 0
	total += makepos(requests[0]-specs.init)
	fmt.Printf("Servicing %5d\n", requests[0])
	// Loop through the rest of the requests
	for i := 1; i < specs.size; i++ {
		diff = makepos(requests[i-1]-requests[i])
		total += diff
		fmt.Printf("Servicing %5d\n", requests[i])
	}
	fmt.Printf("FCFS traversal count = %5d\n", total)
}

// Shortest Seek Time First
// Move the shortest distance at each switch
func sstf(requests [20]int, specs info) {
	var current, total, diff, min, spot int = 0, 0, 0, 99999, 0
	current = specs.init
	for j := 0; j < specs.size; j++ {
		for i := 0; i < specs.size; i++ {
			diff = makepos(requests[i]-current)
			if diff < min {
				min = diff
				spot = i
			}
		}
		total += min
		current = requests[spot]
		fmt.Printf("Servicing %5d\n", requests[spot])
		requests[spot] = 9999999
		min = 999999
	}
	fmt.Printf("SSTF traversal count = %5d\n", total)
}

// SCAN
// Works like an elevator, goes up until it reaches top then goes to bottom
func scan(requests [20]int, specs info) {
	sorted := bubblesort(requests, specs.size)
	var start, end, total, current int = specs.size-1, specs.size, 0, 0
	// find the starting location
	for i := 0; i < end; i++ {
		if sorted[i] > specs.init {
			start = i
			break
		}
	}
	current = specs.init
	// go from start to the "top"
	for j := start; j < end; j++ {
		total += makepos(sorted[j]-current)
		current = sorted[j]
		fmt.Printf("Servicing %5d\n", sorted[j])
		
	}
	if start != 0 {
		total += specs.upper-current
		current = specs.upper
		// go from "top" to the "bottom"
		for j := start-1; j >= 0; j-- {
			total += makepos(sorted[j]-current)
			current = sorted[j]
			fmt.Printf("Servicing %5d\n", sorted[j])
		}
	}
	fmt.Printf("SCAN traversal count = %5d\n", total)
}

// C-SCAN
// Works like scan, but when it gets to the "top", goes back to the "bottom"
func cscan(requests [20]int, specs info) {
	sorted := bubblesort(requests, specs.size)
	var start, end, total, current int = specs.size-1, specs.size, 0, 0
	// find the starting location
	for i := 0; i < end; i++ {
		if sorted[i] > specs.init {
			start = i
			break
		}
	}
	current = specs.init
	// go from start to the "top"
	for j := start; j < end; j++ {
		total += makepos(sorted[j]-current)
		current = sorted[j]
		fmt.Printf("Servicing %5d\n", sorted[j])
	}
	if start != 0 {
		total += specs.upper-current
		total += specs.upper
		current = 0
		// go from "bottom" to the "start"
		for j := 0; j < start; j++ {
			total += makepos(sorted[j]-current)
			current = sorted[j]
			fmt.Printf("Servicing %5d\n", sorted[j])
		}
	}
	fmt.Printf("C-SCAN traversal count = %5d\n", total)
}

// LOOK
// Same as scan but instead of going to "top" and "bottom" stops at last request
func look(requests [20]int, specs info) {
	sorted := bubblesort(requests, specs.size)
	var start, end, total, current int = specs.size-1, specs.size, 0, 0
	// find the starting location
	for i := 0; i < end; i++ {
		if sorted[i] > specs.init {
			start = i
			break
		}
	}
	current = specs.init
	// go from start to the last request
	for j := start; j < end; j++ {
		total += makepos(sorted[j]-current)
		current = sorted[j]
		fmt.Printf("Servicing %5d\n", sorted[j])
	}
	// go from "top" to the "bottom"
	for j := start-1; j >= 0; j-- {
		total += makepos(sorted[j]-current)
		current = sorted[j]
		fmt.Printf("Servicing %5d\n", sorted[j])
	}
	fmt.Printf("LOOK traversal count = %5d\n", total)
}

// C-LOOK
// Works like look, but when it gets to the "top", goes back to the "bottom"
func clook(requests [20]int, specs info) {
	sorted := bubblesort(requests, specs.size)
	var start, end, total, current int = specs.size-1, specs.size, 0, 0
	// find the starting location
	for i := 0; i < end; i++ {
		if sorted[i] > specs.init {
			start = i
			break
		}
	}
	current = specs.init
	// go from start to the "top"
	for j := start; j < end; j++ {
		total += makepos(sorted[j]-current)
		current = sorted[j]
		fmt.Printf("Servicing %5d\n", sorted[j])
	}
	// go from "bottom" to the "start"
	for j := 0; j < start; j++ {
		total += makepos(sorted[j]-current)
		current = sorted[j]
		fmt.Printf("Servicing %5d\n", sorted[j])
	}
	fmt.Printf("C-LOOK traversal count = %5d\n", total)
}