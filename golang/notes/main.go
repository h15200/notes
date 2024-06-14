package main

// playground to test go syntax

import (
	"fmt"
)

// to run this, make sure to add files to dependencies like utils.go as args after go run
func main() {
	mySlice := []int{1, 2, 3}
	fmt.Printf("%#v\n", mySlice)
	AddToSlice(mySlice)
	fmt.Printf("New Slice %#v: \nSlices are a reference type, so passing in to a func without turning it into a pointer still mutates the original slice\n", mySlice)

}
