package main

import (
	"fmt"
	"math/rand"
)

func main() {
//	fmt.Println("hello, world!")
  // an array is a non-dynamic array 
	//myArr := [3]int{3,4,5}
	// slices are dynamic arrays
	//var mySlice []string
	//fmt.Println(myArr)
	//mySlice = append(mySlice, "hello")
	//mySlice = append(mySlice, "world")
	//mySlice = append(mySlice, "in Go")
	//for _, v := range mySlice {
	//	fmt.Println(v)
//	}
//	num := 4
	//fmt.Printf("%v, %T\n",num, num )
	//myR := 'a'
	//myS := "a"
	//fmt.Printf("%T, %T\n", myR, myS)
  defer fmt.Println("Generated!")

  if rand.Intn(100) > 50 {
    fmt.Println( "Returning!")
  }

  fmt.Println("waiting...")

  if rand.Intn(100) < 50 {
    fmt.Println( "Returning later!")
  }
}