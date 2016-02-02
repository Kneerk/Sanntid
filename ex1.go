package main

import (
 	. "fmt"
	"runtime"
	"time"
)


func routine1()  (i int){
    	for j := 0; j < 1000000; j++ {
		i++
	}
	return 
}
func routine2()  (i int){
    	for j := 0; j < 1000000; j++ {
		i--
	}
	return 
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	i := 0
	go routine1()
	go routine2()
	time.Sleep(100*time.Millisecond)
	
	Println(i)
}
