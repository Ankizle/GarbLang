package main

import (
	"fmt"
	"os/exec"
)

var testers = []string{"loopalloc", "closurealloc"}
var builders = map[string]func(string){
	"c": func(name string) {
		cmd := exec.Command("gcc", "c/"+name+".c", "-o", "c/"+name+".bin")
		cmd.Run()
	},
	"garb": func(name string) {

		//compile to cc
		cmd1 := exec.Command("./garblang.bin", "garb/"+name+".garb")
		cmd1.Run()

		//move the cc file into the garb
		cmd2 := exec.Command("mv", "out.cc", "garb/out.cc")
		cmd2.Run()

		//compile the cc file in the garb/
		cmd3 := exec.Command("g++", "garb/out.cc", "-o", "garb/"+name+".bin")
		cmd3.Run()
	},
	"go": func(name string) {
		cmd := exec.Command("go", "build", "-o", "go/"+name+".bin", "go/"+name+".go")
		cmd.Run()
	},
}

func main() {

	for _, v := range builders {
		for _, vv := range testers {
			v(vv)
		}
	}

	for _, v := range testers {
		fmt.Println("TESTING", v+": ")
		fmt.Println("------------------------------------------------------------------------")

		for k := range builders {
			fmt.Println("LANGUAGE", k+": ")
			fmt.Println("-----------------------------")
			out, _ := exec.Command("time", "-f", "real %e\nuser %U\nsys %S", k+"/"+v+".bin").CombinedOutput()
			fmt.Print(string(out))

			fmt.Println("-----------------------------")
		}
		fmt.Println("------------------------------------------------------------------------")
	}
}
