//Academic Integrity statement Ty Abbott ty937650 - “I Ty Abbott ty937650 affirm that this
//program is entirely my own work and that I have neither developed my code together with any
//another person, nor copied any code from any other person, nor permitted my code to be copied
//or otherwise used by any other person, nor have I copied, modified, or otherwise used programs
//created by others. I acknowledge that any violation of the above terms will be treated as academic
//dishonesty.”

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

// each process has this info stored about it
type process struct {
	name                                           string
	arrival, burst, start, finish, wait, burstleft, turnaround int
	running, arrived                               bool
}

// method: 0 = fcfs 1 = sfj 2 = rr
// processcount: number of processes
// runfor: number of time units
// quantum: -1 = non-rr > 0 = rr
type info struct {
	method, processcount, runfor, quantum int
}

func main() {
	input := os.Args[1]
	output := os.Args[2]
	specs, processes := readInput(input, output)
	switch specs.method {
	case 0:
		fcfs(specs, processes, output)
	case 1:
		sjf(specs, processes, output)
	case 2:
		rr(specs, processes, output)
	default:
		fmt.Println("uh-oh")
	}

}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func contains(s [150]int, e int) bool {
	for _, a := range s {
		if a == e {
			return true
		}
	}
	return false
}

func swap(processes [150]process, a int, b int){
	temp := processes[a]
	processes[a] = processes[b]
	processes[b] = temp
}

func quicksort(processes [150]process, l int, r int){
	if l >= r {
		return
	}
	
	pivot := processes[r].arrival
	count := l
	
	for i:= l; i <= r; i++ {
		if processes[i].arrival <= pivot {
			swap(processes, count, i)
			count++
		}
	}
	
	quicksort(processes, l, count-2); 
    quicksort(processes, count, r);
}

func quicksortburst(processes [150]process, l int, r int){
	if l >= r {
		return
	}
	
	pivot := processes[r].burst
	count := l
	
	for i:= l; i <= r; i++ {
		if processes[i].burst <= pivot {
			swap(processes, count, i)
			count++
		}
	}
	
	quicksortburst(processes, l, count-2); 
    quicksortburst(processes, count, r);
}

func readInput(input, output string) (info, [150]process) {
	// struct to store information on processes
	var specs info
	var processes [150]process

	// variables to help with reading input
	// var comment bool = false
	var cnt, keyword, previous int = 0, 0, 0
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
			// use a switch to determine which keyword we're reading
			switch keyword {
			case 1:
				specs.processcount, e = strconv.Atoi(word)
				keyword = 0
				previous = 1
			case 2:
				specs.runfor, e = strconv.Atoi(word)
				keyword = 0
				previous = 2
			case 3:
				// use a switch to check for the method
				switch word {
				case "fcfs":
					specs.method = 0
					keyword = 0
					specs.quantum = -1
				case "sjf":
					specs.method = 1
					keyword = 0
					specs.quantum = -1

				case "rr":
					specs.method = 2
					keyword = 0
				default:
					fmt.Println("Error reading runfor")
				}
				previous = 3
			case 4:
				specs.quantum, e = strconv.Atoi(word)
				keyword = 0
				previous = 4
			case 5:
				processes[cnt].name = word
				keyword = 0
				previous = 5
			case 6:
				processes[cnt].arrival, e = strconv.Atoi(word)
				keyword = 0
				previous = 6
			case 7:
				processes[cnt].burst, e = strconv.Atoi(word)
				processes[cnt].start = -1
				processes[cnt].finish = -1
				keyword = 0
				cnt++
				previous = 7
			default:
				keyword = 0
			}
			check(e)
		}
		// switch statement to check for keywords
		switch word {
		case "processcount":
			if previous == 0 {
				keyword = 1
			} else {
				keyword = 0
			}
		case "runfor":
			if previous == 1 {
				keyword = 2
			} else {
				keyword = 0
			}
		case "use":
			if previous == 2 {
				keyword = 3
			} else {
				keyword = 0
			}
		case "quantum":
			if previous == 3 {
				keyword = 4
			} else {
				keyword = 0
			}
		case "name":
			if previous == 9 {
				keyword = 5
			} else {
				keyword = 0
			}
		case "arrival":
			if previous == 5 {
				keyword = 6
			} else {
				keyword = 0
			}
		case "burst":
			if previous == 6 {
				keyword = 7
			} else {
				keyword = 0
			}
		case "#":
			keyword = 8
			// comment = true
		case "process":
			previous = 9
			keyword = 0
		default:
			keyword = 0
		}
	}
	return specs, processes
}
func rr(specs info, processes [150]process, output string) {
	quicksort(processes, 0, specs.processcount-1)
	var queue []process
	flag := 0
	trackquantum := 0
	
	// create file to write to
	file, err := os.Create(output)
	check(err)
	defer file.Close()
	
	quantum := specs.quantum
	fmt.Fprintf(file, "Using Round-Robin\nQuantum %3d\n\n", quantum)

	for i := 0; i <= specs.runfor; i++ {
		for j := 0; j < specs.processcount; j++ {
		
			if processes[j].arrival == i {
				
				fmt.Fprintf(file, "Time %3d : %s arrived\n", i, processes[j].name)
				queue = append(queue, processes[j])

			}
			
		}
		
		if flag == 0 && len(queue) > 0{
			fmt.Fprintf(file, "Time %3d : %s selected (burst %3d)\n", i, queue[0].name, queue[0].burst)
			// Process currently running
			flag = 1
		}

		
		// when quantum has been reached, but still has burst
		if len(queue) > 0 && trackquantum == quantum && queue[0].burst != 0 {
			// set the flag to 0 to show that the next process can be selected
			flag = 0
			
			// not done with burst, append the current one to the end
			queue = append(queue, queue[0])
			
			// dequeue the current first one
			queue = queue[1:]
			

			
			fmt.Fprintf(file, "Time %3d : %s selected (burst %3d)\n", i, queue[0].name, queue[0].burst)			
			flag = 1
			
			trackquantum = 0
			
		} else if len(queue) > 0 && queue[0].burst == 0 {
			fmt.Fprintf(file, "Time %3d : %s finished\n", i, queue[0].name)
			
			for k := 0; k < len(processes); k++ {
				if processes[k].name == queue[0].name {
					processes[k].turnaround = i - processes[k].arrival
					processes[k].wait = processes[k].turnaround - processes[k].burst
				}
			}
			flag = 0
			queue = queue[1:]
			if len(queue) > 0 {
				
				fmt.Fprintf(file, "Time %3d : %s selected (burst %3d)\n", i, queue[0].name, queue[0].burst)
				flag = 1
			} else if len(queue) == 0 {
				flag = 2
			} else {
				flag = 1
			}
			
			// reset quantum 
			trackquantum = 0
			
		} 
		
		if len(queue) > 0 {
			queue[0].burst--
		}
		
		trackquantum++
		
		if flag == 2 {
			if i == specs.runfor {
				
				fmt.Fprintf(file, "Finished at time %3d\n\n", i)
				
			} else {
				fmt.Fprintf(file, "Time %3d : Idle\n", i)
			}
		}
	}
	
	for i := 0; i < specs.processcount; i++ {
		fmt.Fprintf(file, "%s wait %3d turnaround %3d\n", processes[i].name, processes[i].wait, processes[i].turnaround)	
	}
}
func sjf(specs info, processes [150]process, output string) {
	var count, time int = 0, 0
	ready := false

	// create file to write to
	file, err := os.Create(output)
	check(err)
	defer file.Close()

	fmt.Fprintf(file, "  %d processes\nUsing preemptive Shortest Job First\n", specs.processcount)

	for i := 0; i < specs.processcount; i++ {
		processes[i].wait = 0
		processes[i].burstleft = processes[i].burst
		processes[i].running = false
		processes[i].arrived = false
	}

	for time < specs.runfor {
		p := processes[count]

		// check for arrivals
		for i := 0; i < specs.processcount; i++ {
			if processes[i].arrival == time {
				fmt.Fprintf(file, "Time %3d : %s arrived\n", time, processes[i].name)
				processes[i].arrived = true
			}
		}

		// check for finished
		if p.burstleft == 0 {
			fmt.Fprintf(file, "Time %3d : %s finished\n", time, p.name)
			p.finish = time
			p.running = false
		}

		// check if there are processes ready to be run
		for i := 0; i < specs.processcount; i++ {
			if processes[i].arrived && processes[i].burstleft != 0 {
				ready = true
			}
		}

		// check for selected
		min, spot := 99999, 0
		// loop to find the process with the lowest remaining burst
		for i := 0; i < specs.processcount; i++ {
			if processes[i].arrived && processes[i].burstleft > 0 {
				if processes[i].burstleft < min {
					min = processes[i].burstleft
					spot = i
				}
			}
		}
		// check if process with lowest reminaing burst is already running
		if processes[spot].running {
			// don't print anything
			time++
			processes[spot].burstleft--
			count = spot
		} else if ready {
			// switching the current running process
			// set all processes to not running
			for i := 0; i < specs.processcount; i++ {
				processes[i].running = false
			}
			// sets process with lowest remaining burst to running
			fmt.Fprintf(file, "Time %3d : %s selected (burst %3d)\n", time, processes[spot].name, processes[spot].burst)
			processes[spot].running = true
			processes[spot].burstleft--
			processes[spot].start = time
			count = spot
			time++
		} else {
			// idle
			fmt.Fprintf(file, "Time %3d : Idle\n", time)
			time++
		}

		// increment waits
		for i := 0; i < specs.processcount; i++ {
			if processes[i].arrived && processes[i].burstleft != 0 {
				processes[i].wait++
			}
		}
	}
	fmt.Fprintf(file, "Finished at time %3d\n\n", specs.runfor)
	for i := 0; i < specs.processcount; i++ {
		pr := processes[i]
		turnaround := pr.finish - pr.arrival
		fmt.Fprintf(file, "%s wait %3d turnaround %3d\n", pr.name, pr.wait, turnaround)
	}

}

func fcfs1(specs info, processes [150]process, output string) {
	quicksort(processes, 0, specs.processcount-1)
	var flag, printed1, printed2, count int = 0, 0, 0, 0
	var starttime int
		
	file, err := os.Create(output)
	check(err)
	defer file.Close()
		
	fmt.Fprintf(file, "Using First-Come First-Served\n")
		
	for i := 0; i <= specs.runfor; i++ {
		for j := 0; j < specs.processcount; j++ {
			// checks if anything has arrived
			if processes[j].arrival == i {
				fmt.Fprintf(file, "Time %3d : %s arrived\n", i, processes[j].name)
			}
			
			
			if flag != 2 && i != 0 && i - processes[count-1].burst == starttime {
				processes[count-1].turnaround = i - processes[count-1].arrival
				processes[count-1].wait = processes[count-1].turnaround - processes[count-1].burst
				
				if printed2 == 0 {
					
					fmt.Fprintf(file, "Time %3d : %s finished\n", i, processes[count-1].name)
					printed2 = 1
				}
				if count-1 == len(processes) - 1 {
					flag = 2
				}  else {
					flag = 0
				}
				
			} 
			
			if flag == 0 && count < specs.processcount {
				if processes[count].arrival > i {
					if printed1 == 0 {
						fmt.Fprintf(file, "Time %3d : Idle\n", i)
						printed1 = 1
					}
				} else {
					fmt.Fprintf(file, "Time %3d : %s selected (burst %3d)\n", i, processes[count].name, processes[count].burst)
					flag = 1
					count++
					starttime = i
				}
			} 
			
		}
		printed1 = 0
		printed2 = 0
		if flag == 2 && count >= specs.processcount {
			if i == specs.runfor {
				fmt.Fprintf(file, "Finished at time %3d\n\n", i)
			} else {
				fmt.Fprintf(file, "Time %3d : Idle\n", i)
			}
		}
		
		
	}
	for i := 0; i < specs.processcount; i++ {
		for j := 0; j < specs.processcount; j++ {	
				fmt.Fprintf(file, "%s wait %3d turnaround %3d\n", processes[i].name, processes[j].wait, processes[j].turnaround)
			}
		}
}

func fcfs(specs info, processes [150]process, output string) {
	var time, count int = 0, 0
	var ordered [150]int

	// populate queue with earliest arrivals first
	for i := 0; i < specs.processcount; i++ {
		min, spot := 999999, 0
		for j := 0; j < specs.processcount; j++ {
			if contains(ordered, j) && processes[j].arrival < min {
				min = processes[j].arrival
				spot = j
			}
		}
		ordered[i] = spot
	}
	count = 0
	fmt.Printf("%v", ordered)

	// create file to write to
	file, err := os.Create(output)
	check(err)
	defer file.Close()
	running := false

	fmt.Fprintf(file, "  %d processes\nUsing First-Come First-Served\n", specs.processcount)

	// go through processes and write to file
	for time < specs.runfor {
		// loop through all finished
		if count >= specs.processcount || processes[ordered[count]].finish == time {
			fmt.Fprintf(file, "Time %3d : %s finished\n", time, processes[ordered[count]].name)
			running = false
			count++
		}
		// loop through all arrived
		for i := 0; i < specs.processcount; i++ {
			if processes[ordered[count]].arrival == time {
				fmt.Fprintf(file, "Time %3d : %s arrived\n", time, processes[ordered[count]].name)
			}
		}

		// loop through all selected
		if running {
		} else if processes[ordered[count]].arrival <= time {
			running = true
			processes[ordered[count]].start = time
			processes[ordered[count]].finish = time + processes[ordered[count]].burst
			fmt.Fprintf(file, "Time %3d : %s selected (burst %3d)\n", time, processes[ordered[count]].name, processes[ordered[count]].burst)
		} else {
			fmt.Fprintf(file, "Time %3d : Idle\n", time)
		}
		time++
	}
	// writing to end of file
	fmt.Fprintf(file, "Finished at time %3d\n\n", specs.runfor)
	for i := 0; i < specs.processcount; i++ {
		pr := processes[i]
		wait := pr.start - pr.arrival
		turnaround := pr.finish - pr.arrival
		fmt.Fprintf(file, "%s wait %3d turnaround %3d\n", pr.name, wait, turnaround)
	}
}


