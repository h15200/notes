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
