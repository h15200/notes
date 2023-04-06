package main

import (
	"fmt"
)

func main() {
	mySlice := []int{1,2,3}
	fmt.Println(mySlice)
	addToSlice(mySlice)
	fmt.Println(mySlice)


}

func addToSlice(slice []int) {
	for i := 0; i < len(slice); i++ {
		slice[i] += 2
	}
}