package main

func AddToSlice(s []int) {
	for i := 0; i < len(s); i++ {
		s[i] += 2
	}
}
