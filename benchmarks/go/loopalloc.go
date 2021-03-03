package main

func main() {
	var a []int
	_ = a

	for i := 0; i < 1000000; i++ {
		a = append(a, 0)
	}

}
