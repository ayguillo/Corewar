package main

import (
	"fmt"
	"os"
	"time"
	"bytes"
	"strings"

	"github.com/veandco/go-sdl2/sdl"
	"github.com/veandco/go-sdl2/ttf"
)

func scan(ch chan string) {
	var stdin string
	var buffer bytes.Buffer
	var dur time.Duration
	var err error

	if dur, err = time.ParseDuration("1s"); err != nil {
		panic(err)
	}
	for {
		for i := 0; i < 300; i++ {
		fmt.Scanf("%s", &stdin)
		buffer.WriteString(stdin)
		}
		ch <- (strings.Split(buffer.String(), ";"))[0]
		time.Sleep(dur)
	}
}

func printArena(stdin string, surface *sdl.Surface, font *ttf.Font, window *sdl.Window) {
	var solid *sdl.Surface
	var err error

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
		W: 2000,
		H: 1300,
	}
	fmt.Println(stdin)
	surface.FillRect(&background, 0xff000000)
	for key := range stdin {
		if key + 2 < len(stdin) {
		if solid, err = font.RenderUTF8Solid(stdin[key : key + 2], sdl.Color{255, 255, 255, 255}); err != nil {
			fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
			panic(err)
		}
		defer solid.Free()
		if err = solid.Blit(nil, surface, &arena); err != nil {
			fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
			panic(err)
		}
		arena.X += 20
		if arena.X + arena.W > background.X + background.W {
			arena.X = 60
			arena.Y += 15
		}
		}
	}
	window.UpdateSurface()
}

func main() {
	var window *sdl.Window
	var font *ttf.Font
	var surface *sdl.Surface
	var err error
	var stdin string

	ch := make(chan string, 200)
	if err = sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}
	defer sdl.Quit()

	if err = ttf.Init(); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to initialize TTF: %s\n", err)
		panic(err)
	}
	defer ttf.Quit()

	if font, err = ttf.OpenFont("visu_go/ArcadeClassic.ttf", 16); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer font.Close()

	window, err = sdl.CreateWindow("Corewar", sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		800, 600, sdl.WINDOW_FULLSCREEN_DESKTOP)
	if err != nil {
		panic(err)
	}
	defer window.Destroy()

	surface, err = window.GetSurface()
	if err != nil {
		panic(err)
	}
	surface.FillRect(nil, 0xff00ffff)

	rect := sdl.Rect{
		X: 0,
		Y: 0,
		W: 800,
		H: 800,
	}

	surface.FillRect(&rect, 0xffff0000)

	go scan(ch)
	running := true
	
	for running {
		select {
		case stdin = <-ch:
			surface.FillRect(nil, 0xff00ffff)
			surface.FillRect(&rect, 0xffff0000)
			printArena(stdin, surface, font, window)
			break
		default:
			for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
				switch test := event.(type) {
				case *sdl.QuitEvent:
					println("Quit")
					running = false
					break
				case *sdl.KeyboardEvent:
					if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_ESCAPE {
						println("Quit")
						running = false
					}
					if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_RIGHT {
						rect.X += 10
						surface.FillRect(nil, 0xff00ffff)
						surface.FillRect(&rect, 0xffff0000)
						printArena(stdin, surface, font, window)
					}
					if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_LEFT {
						rect.X -= 10
						surface.FillRect(nil, 0xff00ffff)
						surface.FillRect(&rect, 0xffff0000)
						printArena(stdin, surface, font, window)
					}
					break
				}
			}
		}
	}
}
