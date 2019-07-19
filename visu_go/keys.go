package main

import (
	"time"

	"github.com/veandco/go-sdl2/sdl"
)

func handleKeys(chDur chan time.Duration, dur *time.Duration, stop *bool) bool {
	for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
		switch test := event.(type) {
		case *sdl.QuitEvent:
			println("Quit")
			return false
		case *sdl.KeyboardEvent:
			if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_ESCAPE {
				println("Quit")
				return false
			}
			if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_EQUALS {
				if (*dur) > 1000000 {
					*dur /= 2
					chDur <- *dur
				} else {
					*dur = 1000000
				}
				*stop = false

			}
			if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_MINUS {
				if (*dur).Seconds() < 1.0 {
					*dur *= 2
					chDur <- *dur
				} else {
					*dur = time.Second * 2
				}
				*stop = false
			}
			if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_SPACE {
				if *stop == false {
					*stop = true
					chDur <- 0
				} else {
					*stop = false
					chDur <- *dur
				}
			}
		}
	}
	return true
}