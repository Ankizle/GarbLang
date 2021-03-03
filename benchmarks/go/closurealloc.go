package main

func test() func() *[]int {

	shared := []int{}
	shared = append(shared, 0)

	var ret = func() *[]int {
		return &shared
	}

	return ret
}

func main() {
	for i := 0; i < 1000000; i++ {
		test()()
	}
}
