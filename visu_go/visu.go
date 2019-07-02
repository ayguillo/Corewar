package main

import (
	"fmt"
	"os"
	"time"
	"bufio"
	"strings"

	"github.com/veandco/go-sdl2/sdl"
	"github.com/veandco/go-sdl2/ttf"
)

func scan(mem, infos chan string) {
	var stdin string
	var dur time.Duration
	var err error

	in:= bufio.NewReader(os.Stdin)
	if dur, err = time.ParseDuration("3s"); err != nil {
		panic(err)
	}
	for {
	stdin, err = in.ReadString(';')
	mem <- stdin
	stdin, err = in.ReadString(';')
	infos <- stdin
	time.Sleep(dur)
	}
}

func printInfos(stdin string, surface *sdl.Surface, window *sdl.Window) {
	var solid *sdl.Surface
	var err error
	var font *ttf.Font

	if len(stdin) == 0 {
		return
	}
	if font, err = ttf.OpenFont("visu_go/Rubik-Regular.ttf", 25); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
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
	lines := strings.Split(stdin, "\n")
	surface.FillRect(&background, 0xff000000)
	for key := range lines {
		if len(lines[key]) != 0 {
			if solid, err = font.RenderUTF8Solid(lines[key], sdl.Color{255,255,255,255}); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			if err = solid.Blit(nil, surface, &line); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
		}
		line.Y += 50
	}
	window.UpdateSurface()
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
	for key:= 0; key + 2 < len(stdin); key += 2 {
		switch stdin[key]{
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
			fmt.Println(key)
		}
		if key + 2 < len(stdin) && key % 2 == 0 {
			if solid, err = font.RenderUTF8Solid(stdin[key : key + 2], color); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			if err = solid.Blit(nil, surface, &arena); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
			arena.X += 30
			if arena.X + arena.W > background.X + background.W {
				arena.X = 60
				arena.Y += 20
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

	mem := make(chan string, 200)
	infos := make(chan string, 200)
	if err = sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}
	defer sdl.Quit()

	if err = ttf.Init(); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to initialize TTF: %s\n", err)
		panic(err)
	}
	defer ttf.Quit()

	if font, err = ttf.OpenFont("visu_go/ArcadeClassic.ttf", 25); err != nil {
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
	surface.FillRect(nil, 0xff404040)

	rect := sdl.Rect{
		X: 0,
		Y: 0,
		W: 800,
		H: 800,
	}

	surface.FillRect(&rect, 0xffff0000)

	go scan(mem, infos)
	running := true
	
	for running {
		select {
		case stdin = <-mem:
			printArena(stdin, surface, font, window)
			break
		case stdin = <-infos:
			printInfos(stdin, surface, window)
			break;
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
						surface.FillRect(nil, 0xff404040)
						surface.FillRect(&rect, 0xffff0000)
						printArena(stdin, surface, font, window)
					}
					if test.State == sdl.PRESSED && test.Keysym.Sym == sdl.K_LEFT {
						rect.X -= 10
						surface.FillRect(nil, 0xff404040)
						surface.FillRect(&rect, 0xffff0000)
						printArena(stdin, surface, font, window)
					}
					break
				}
			}
		}
	}
}
