package main

func test() func() *[]int {
	var (
		local1 *int
		local2 *int
		local3 *int
		local4 *int
		local5 *int
		local6 *int
		local7 *int
		local8 *int
		local9 *int
	)

	_ = local1
	_ = local2
	_ = local3
	_ = local4
	_ = local5
	_ = local6
	_ = local7
	_ = local8
	_ = local9

	var shared *[]int

	var ret = func() *[]int {
		return shared
	}

	return ret
}

func main() {
	for i := 0; i < 1000000; i++ {
		test()()
	}
}
