package main

import (
	"fmt"
	"os"
	"strings"
	"time"

	"github.com/veandco/go-sdl2/sdl"
	"github.com/veandco/go-sdl2/ttf"
)

func scan(ch chan string) {
	var stdin string
	var dur time.Duration
	var err error

	if dur, err = time.ParseDuration("3s"); err != nil {
		panic(err)
	}

	for {
		fmt.Scanf("%s\n", &stdin)
		stdin = strings.Trim(stdin, "\n")
		ch <- stdin
		time.Sleep(dur)
	}
}

func main() {
	var window *sdl.Window
	var font *ttf.Font
	var surface *sdl.Surface
	var solid *sdl.Surface
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

	if font, err = ttf.OpenFont("visu_go/ArcadeClassic.ttf", 32); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer font.Close()

	window, err = sdl.CreateWindow("test", sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		800, 600, sdl.WINDOW_FULLSCREEN_DESKTOP)
	if err != nil {
		panic(err)
	}
	defer window.Destroy()

	if solid, err = font.RenderUTF8Solid("test", sdl.Color{255, 255, 255, 255}); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
		panic(err)
	}
	defer solid.Free()

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

	arena := sdl.Rect{
		X: 100,
		Y: 100,
		W: 800,
		H: 800,
	}

	if err = solid.Blit(nil, surface, &arena); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
		panic(err)
	}

	window.UpdateSurface()

	running := true
	go scan(ch)
	for running {
		select {
		case stdin = <-ch:
			if solid, err = font.RenderUTF8Solid(stdin, sdl.Color{R: 255, G: 255, B: 255, A: 255}); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			surface.FillRect(nil, 0xff00ffff)
			surface.FillRect(&rect, 0xffff0000)
			if err = solid.Blit(nil, surface, &arena); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
			window.UpdateSurface()
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
						println("hey")
						running = false
					}
					if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_RIGHT {
						rect.X += 10
						surface.FillRect(nil, 0xff00ffff)
						surface.FillRect(&rect, 0xffff0000)
						if err = solid.Blit(nil, surface, &arena); err != nil {
							fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
							panic(err)
						}
						window.UpdateSurface()
					}
					if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_LEFT {
						rect.X -= 10
						surface.FillRect(nil, 0xff00ffff)
						surface.FillRect(&rect, 0xffff0000)
						if err = solid.Blit(nil, surface, &arena); err != nil {
							fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
							panic(err)
						}
						window.UpdateSurface()
					}
					break
				}
			}
		}
	}
}
