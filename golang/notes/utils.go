package main

import (
	"fmt"
)

// illustrates the idea of slices being reference types
func AddToSlice(s []int) {
	for i := 0; i < len(s); i++ {
		s[i] += 2
	}
}

// fmt verbs that I always forget

func FormatByteWithD(b []byte) {
	fmt.Printf("\nbyte type as %%d is: %d\n", b)
	fmt.Println("It prints the int32 val")
}

func FormatByteWithC(b []byte) {
	fmt.Printf("\nbyte type as %%c is: %c\n", b)
	fmt.Println("it prints the visual representation of the char")
}

func FormatByteWithQ(b []byte) {
	fmt.Printf("\nbyte type as %%q is: %q\n", b)
	fmt.Println("It adds quotes")
}
func FormatRuneWithD(r rune) {
	fmt.Printf("\nRune type as %%d is: %d\n", r)
	fmt.Println("It prints the int32 val")
}

func FormatRuneWithC(r rune) {
	fmt.Printf("\nRune type as %%c is: %c\n", r)
	fmt.Println("it prints the visual representation of the char")
}

func FormatRuneWithQ(r rune) {
	fmt.Printf("\nRune type as %%q is: %q\n", r)
	fmt.Println("It adds quotes around the rune")
}

// everything in go is passed by value, but slices are a head which points
// to subsets of a backing array
func BadSlicePop(s []int) {
	s = s[:len(s)-1]
	// this doesn't do anything because the head is the same
	// s[0] = 123 WOULD change the slice
}

func RemoveIndex(s []int, i int) []int {
	// returning a new slice
	// [1,2,3,4,5], where we remove index 2
	// take [3,4,5] as destination, and [4,5] as source and copy -> [4,5,4], then pop
	copy(s[i:], s[i+1:])
	s = s[:len(s)-1]
	return s

}
