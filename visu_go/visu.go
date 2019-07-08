package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
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
			close(chMem)
			close(chInfos)
			return
		}
		chMem <- stdin
		stdin, err = in.ReadString(';')
		if err != nil {
			close(chMem)
			close(chInfos)
			return
		}
		chInfos <- stdin
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
				time.Sleep(dur)
			}
		}
	}
}

func printInfos(stdin string, surface *sdl.Surface, font *ttf.Font, window *sdl.Window, color [5]sdl.Color, w, h int32) {
	var solid *sdl.Surface
	var err error
	var i int

	i = 0

	if len(stdin) == 0 {
		return
	}

	line := sdl.Rect{
		X: 2060 * w / 2560,
		Y: 60 * h / 1440,
		W: 500 * w / 2560,
		H: 20 * h / 1440,
	}

	background := sdl.Rect{
		X: 2050 * w / 2560,
		Y: 50 * h / 1440,
		W: 500 * w / 2560,
		H: 1350 * h / 1440,
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
		line.Y += 35 * h / 1440
	}
}

func printArena(stdin string, surface *sdl.Surface, font *ttf.Font, window *sdl.Window, color [5]sdl.Color, w, h int32) {
	var solid *sdl.Surface
	var err error
	var i int

	i = 0

	if len(stdin) == 0 {
		return
	}
	arena := sdl.Rect{
		X: 60 * w / 2560,
		Y: 60 * h / 1440,
		W: 20 * w / 2560,
		H: 20 * h / 1440,
	}
	background := sdl.Rect{
		X: 50 * w / 2560,
		Y: 50 * h / 1440,
		W: 1950 * w / 2560,
		H: 1350 * h / 1440,
	}
	surface.FillRect(&background, 0xff000000)
	for key := 0; key+2 < len(stdin); key += 2 {
		switch stdin[key] {
		case 'R':
			i = 1
		case 'Y':
			i = 4
		case 'P':
			i = 3
		case 'G':
			i = 2
		default:
			i = 0
		}
		if i != 0 {
			key += 2
		}
		if key+2 < len(stdin) && key%2 == 0 {
			if solid, err = font.RenderUTF8Solid(stdin[key:key+2], color[i]); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to render text: %s\n", err)
				panic(err)
			}
			defer solid.Free()
			if err = solid.Blit(nil, surface, &arena); err != nil {
				fmt.Fprintf(os.Stderr, "Failed to put text on window surface: %s\n", err)
				panic(err)
			}
			arena.X += 30 * w / 2560
			if arena.X+arena.W > background.X+background.W {
				arena.X = 60 * w / 2560
				arena.Y += 20 * h / 1440
			}
		}
	}
}

func update(chMem, chInfos chan string, fontMem, fontInfos *ttf.Font, tick chan bool, surface *sdl.Surface, window *sdl.Window, color [5]sdl.Color, w, h int32, loadingColor *uint32) {
	var infos, mem string

	loading := sdl.Rect{
		X: 0,
		Y: 0,
		W: 0,
		H: h,
	}

	select {
	case <-tick:
		select {
		case mem = <-chMem:
			infos = <-chInfos
			if len(infos) > 1 {
				surface.FillRect(nil, 0xff404040)
				split := strings.Split(infos, "\n")
				if len(split) >= 3 {
					cycles := strings.Split(split[2], " ")
					if len(cycles) == 5 {
						if cycle, err := strconv.Atoi(cycles[2]); err == nil {
							if cycleToDie, err := strconv.Atoi(cycles[4]); err == nil {
								loading.W = w * int32(cycle) / int32(cycleToDie)
								if loading.W != 0 {
									if (cycleToDie/510 != 0 && cycle%(cycleToDie/510) == 0 &&
										*loadingColor+uint32(0x00010000+0x00010000*(510/cycleToDie)) <= 0x00ff0000) ||
										(cycleToDie/510 == 0 && *loadingColor+uint32(0x00010000+0x00010000*(510/cycleToDie)) <= 0x00ff0000) {
										*loadingColor += uint32(0x00010000 + 0x00010000*(510/cycleToDie))
									} else if (cycleToDie/510 != 0 && cycle%(cycleToDie/510) == 0 && *loadingColor-uint32(0x00000100+0x00000100*(510/cycleToDie)) >= 0x00ff0000) ||
										(cycleToDie/510 == 0 && *loadingColor-uint32(0x00000100+0x00000100*(510/cycleToDie)) >= 0x00ff0000) {
										*loadingColor -= uint32(0x00000100 + 0x00000100*(510/cycleToDie))
									} else if (cycleToDie/510 != 0 && cycle%(cycleToDie/510) == 0) || cycleToDie/510 == 0 {
										*loadingColor |= 0x00ff0000
									}
									if cycle == 1 {
										*loadingColor = 0x0000ff00
									}
									surface.FillRect(&loading, *loadingColor)
								}
							}
						}
					}
				}
				printArena(mem, surface, fontMem, window, color, w, h)
				printInfos(infos, surface, fontInfos, window, color, w, h)
				window.UpdateSurface()
			}
		default:
			return
		}
	default:
		return
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

func main() {
	var window *sdl.Window
	var surface *sdl.Surface
	var err error
	var dur time.Duration
	var fontMem, fontInfos *ttf.Font
	var stop bool
	var color [5]sdl.Color
	var loadingColor uint32

	if err = sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}
	defer sdl.Quit()

	if err = ttf.Init(); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to initialize TTF: %s\n", err)
		panic(err)
	}
	defer ttf.Quit()

	window, err = sdl.CreateWindow("CoreWar", sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		0, 0, sdl.WINDOW_FULLSCREEN_DESKTOP)
	if err != nil {
		panic(err)
	}
	defer window.Destroy()

	w, h := window.GetSize()

	if fontMem, err = ttf.OpenFont("visu_go/ArcadeClassic.ttf", 25*int(h)/1440); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer fontMem.Close()

	if fontInfos, err = ttf.OpenFont("visu_go/Rubik-Regular.ttf", 25*int(h)/1440); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open font: %s\n", err)
		panic(err)
	}
	defer fontInfos.Close()

	surface, err = window.GetSurface()
	if err != nil {
		panic(err)
	}
	defer surface.Free()

	chMem := make(chan string, 2)
	chInfos := make(chan string, 2)
	chDur := make(chan time.Duration, 2)
	chTick := make(chan bool, 2)

	color[0] = sdl.Color{R: 255, G: 255, B: 255, A: 255}
	color[1] = sdl.Color{R: 255, G: 0, B: 0, A: 255}
	color[2] = sdl.Color{R: 0, G: 255, B: 0, A: 255}
	color[3] = sdl.Color{R: 128, G: 0, B: 255, A: 255}
	color[4] = sdl.Color{R: 255, G: 255, B: 0, A: 255}

	loadingColor = 0x0000ff00

	stop = true
	dur = 1 * time.Second
	chDur <- 0
	chTick <- true

	go scan(chMem, chInfos)
	go tick(chDur, chTick)

	for {
		if handleKeys(chDur, &dur, &stop) == false {
			return
		}
		update(chMem, chInfos, fontMem, fontInfos, chTick, surface, window, color, w, h, &loadingColor)
	}
}
