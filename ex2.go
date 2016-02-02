

package main

import (
 	. "fmt"
	"runtime"
	"time"
)

var i int

func routine1(c chan int){
	c <- i
    	for j := 0; j < 1000000; j++ {
		i := <-c
		i++
		c <- i
	}
}
func routine2(c chan int){
	c <- i
    	for j := 0; j < 1000000; j++ {
		i := <-c
		i--
		c <- i
	}
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	c := make(chan int, 2)
	go routine1(c)
	go routine2(c)
	x, y := <-c, <-c
	i = x + y
	time.Sleep(100*time.Millisecond)
	Println(i, x, y)
}
