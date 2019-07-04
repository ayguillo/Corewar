package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"time"

	"github.com/veandco/go-sdl2/sdl"
	"github.com/veandco/go-sdl2/ttf"
)

func scan(chMem, chInfos chan string) {
	var stdin string
	var err error

	in := bufio.NewReader(os.Stdin)
	for {
		stdin, err = in.ReadString(';')
		if err != nil {
			return
		}
		chMem <- stdin
		stdin, err = in.ReadString(';')
		if err != nil {
			return
		}
		chInfos <- stdin
	}
}

func printInfos(stdin string, surface *sdl.Surface, font *ttf.Font, window *sdl.Window) {
	var solid *sdl.Surface
	var err error
	var color [5]sdl.Color
	var i int

	color[0] = sdl.Color{255, 255, 255, 255}
	color[1] = sdl.Color{255, 0, 0, 255}
	color[2] = sdl.Color{0, 255, 0, 255}
	color[3] = sdl.Color{128, 0, 255, 255}
	color[4] = sdl.Color{255, 255, 0, 255}
	i = 0

	if len(stdin) == 0 {
		return
	}

	line := sdl.Rect{
		X: 2050,
		Y: 60,
		W: 500,
		H: 20,
	}

	background := sdl.Rect{
		X: 2050,
		Y: 50,
		W: 500,
		H: 1350,
	}

	stdin = stdin[:len(stdin)-1]
	lines := strings.Split(stdin, "\n")
	surface.FillRect(&background, 0xff000000)
	for key := range lines {
		if len(lines[key]) != 0 {
			if strings.Contains(lines[key], "---PLAYER[") && i < 4 {
				i++
			}
			if solid, err = font.RenderUTF8Solid(lines[key], color[i]); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			if err = solid.Blit(nil, surface, &line); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
		}
		line.Y += 35
	}
}

func printArena(stdin string, surface *sdl.Surface, font *ttf.Font, window *sdl.Window) {
	var solid *sdl.Surface
	var err error
	var color sdl.Color

	if len(stdin) == 0 {
		return
	}
	arena := sdl.Rect{
		X: 60,
		Y: 60,
		W: 20,
		H: 20,
	}
	background := sdl.Rect{
		X: 50,
		Y: 50,
		W: 1950,
		H: 1350,
	}
	surface.FillRect(&background, 0xff000000)
	for key := 0; key+2 < len(stdin); key += 2 {
		switch stdin[key] {
		case 'R':
			color = sdl.Color{255, 0, 0, 255}
			break
		case 'Y':
			color = sdl.Color{255, 255, 0, 255}
			break
		case 'P':
			color = sdl.Color{128, 0, 255, 255}
			break
		case 'G':
			color = sdl.Color{0, 255, 0, 255}
			break
		default:
			color = sdl.Color{255, 255, 255, 255}
			break
		}
		if color != (sdl.Color{255, 255, 255, 255}) {
			key += 2
		}
		if key+2 < len(stdin) && key%2 == 0 {
			if solid, err = font.RenderUTF8Solid(stdin[key:key+2], color); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			if err = solid.Blit(nil, surface, &arena); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
			arena.X += 30
			if arena.X+arena.W > background.X+background.W {
				arena.X = 60
				arena.Y += 20
			}
		}
	}
}

func update(chMem, chInfos chan string, fontMem, fontInfos *ttf.Font, tick chan bool, surface *sdl.Surface, window *sdl.Window) {
	var infos, mem string

	select {
	case <-tick:
		select {
		case mem = <-chMem:
			printArena(mem, surface, fontMem, window)
			infos = <-chInfos
			printInfos(infos, surface, fontInfos, window)
			window.UpdateSurface()
		default:
			return
		}
	default:
		return
	}
}

func tick(chDur chan time.Duration, chTick chan bool) {
	var dur time.Duration
	for {
		select {
		case dur = <-chDur:
		default:
			if dur != 0.0 {
				chTick <- true
			}
			time.Sleep(dur)
		}
	}
}

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
				*dur /= 2
				if dur.Nanoseconds() == 0.0 {
					(*dur)++
				}
				*stop = false
				chDur <- *dur
			}
			if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_MINUS {
				if (*dur).Seconds() < 1.0 {
					*dur *= 2
				}
				*stop = false
				chDur <- *dur
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

func main() {
	var window *sdl.Window
	var surface *sdl.Surface
	var err error
	var dur time.Duration
	var fontMem, fontInfos *ttf.Font
	var stop bool

	chMem := make(chan string, 200)
	chInfos := make(chan string, 200)
	chDur := make(chan time.Duration, 200)
	chTick := make(chan bool, 2)
	stop = true

	if err = sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}
	defer sdl.Quit()

	if err = ttf.Init(); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to initialize TTF: %s\n", err)
		panic(err)
	}
	defer ttf.Quit()

	if fontMem, err = ttf.OpenFont("visu_go/ArcadeClassic.ttf", 25); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer fontMem.Close()

	if fontInfos, err = ttf.OpenFont("visu_go/Rubik-Regular.ttf", 25); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer fontInfos.Close()
	window, err = sdl.CreateWindow("CoreWar", sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		800, 600, sdl.WINDOW_FULLSCREEN_DESKTOP)
	if err != nil {
		panic(err)
	}
	defer window.Destroy()

	surface, err = window.GetSurface()
	if err != nil {
		panic(err)
	}
	surface.FillRect(nil, 0xff404040)

	dur = 1 * time.Second
	chDur <- 0
	chTick <- true
	go scan(chMem, chInfos)
	go tick(chDur, chTick)
	for {
		if handleKeys(chDur, &dur, &stop) == false {
			return
		}
		update(chMem, chInfos, fontMem, fontInfos, chTick, surface, window)
	}
}
