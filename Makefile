mac:
	g++ -std=c++17 -o snake snake.cpp `fltk-config --cxxflags --ldflags` -lfltk_images -framework AudioToolbox
linux:
	g++ -o snake snake.cpp `fltk-config --cxxflags --ldflags --use-images` -lasound

clean:
	rm snake