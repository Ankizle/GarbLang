package main

import (
	"os/exec"
	"strconv"
	"strings"

	"github.com/360EntSecGroup-Skylar/excelize"
)

var testers = []string{"loopalloc", "closurealloc", "manyrefs"}
var langOrder = []string{"c", "garb", "go"}
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

	out := excelize.NewFile()

	for _, v := range builders {
		for _, vv := range testers {
			v(vv)
		}
	}

	for _, v := range testers {

		_ = out.NewSheet(v)

		for i, k := range langOrder {

			startcol := i * (len(langOrder) + 1) //+1 to add a space between each lang

			out.SetCellValue(v, string(startcol+65)+"1", k)
			out.SetCellValue(v, string(startcol+65)+"2", "real")
			out.SetCellValue(v, string(startcol+66)+"2", "user")
			out.SetCellValue(v, string(startcol+67)+"2", "sys")

			for t := 0; t < 1000; t++ {
				stdout, _ := exec.Command("time", "-f", "%e %U %S", k+"/"+v+".bin").CombinedOutput()
				splitted := strings.Split(strings.TrimSpace(string(stdout)), " ")

				real, _ := strconv.ParseFloat(splitted[0], 64)
				user, _ := strconv.ParseFloat(splitted[1], 64)
				sys, _ := strconv.ParseFloat(splitted[2], 64)

				out.SetCellValue(v, string(startcol+65)+strconv.Itoa(t+3), int(real*1000))
				out.SetCellValue(v, string(startcol+66)+strconv.Itoa(t+3), int(user*1000))
				out.SetCellValue(v, string(startcol+67)+strconv.Itoa(t+3), int(sys*1000))
			}

		}

	}

	out.SaveAs("data.xlsx")
}
