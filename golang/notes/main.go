package main

// playground to test go syntax

import (
	"fmt"
)

// to run this, make sure to add files to dependencies like utils.go as args after go run
func main() {

	// mySlice := []int{1, 2, 3}
	// fmt.Printf("%#v\n", mySlice)
	// AddToSlice(mySlice)
	// fmt.Printf("New Slice %#v: \nSlices are a reference type, so passing in to a func without turning it into a pointer still mutates the original slice\n", mySlice)
	FormatByteWithD([]byte("H"))
	FormatByteWithC([]byte("H"))
	FormatByteWithQ([]byte("H"))

	// FormatRuneWithD('は')
	// FormatRuneWithC('は')
	// FormatRuneWithQ('は')

	s := []int{1, 2, 3, 4, 5}

	BadSlicePop(s)
	fmt.Printf("slice is the same: %#v\n", s)

	// good slice pop
	s = s[:len(s)-1]
	fmt.Printf("proper pop inline: %#v\n", s)

	new_s := RemoveIndex(s, 0)
	fmt.Printf("new s is: %#v\n", new_s)

	// still pointing to the same underlying array
	fmt.Printf("pointers to old: %p, pointers to new: %p\n", s, new_s)

}
