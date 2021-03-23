package main

func test() func() *[]int {

	shared := make([]int, 100)

	for k := range shared {
		shared[k] = 1
	}

	var ret = func() *[]int {
		return &shared
	}

	return ret
}

func main() {
	for i := 0; i < 100000; i++ {
		test()()
	}
}
