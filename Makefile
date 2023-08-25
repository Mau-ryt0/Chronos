all: before assets build clean

sb: before assets build clean sbx

bgb: before assets build clean bgbx

emuli: before assets build clean emulix

before:
	rm -rf *.o *.gbc & clear

assets:
	png2asset Assets/lizzie_spr.png -c src/Sprites/lizzie_spr.c -spr8x16 -sw 16 -sh 16 -noflip -keep_duplicate_tiles
	png2asset Assets/TestMap.png -c src/Maps/TestMap.c -map -noflip -use_map_attributes
	clear

build:
# 	lcc -Wm-yc -Wm-ys -o logic.o ./src/main.c ./src/funcs.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c
# 	lcc -Wm-yc -Wm-ys -o graphics.o ./src/Maps/TestMap.c ./src/Tiles/Tiles.c ./src/Sprites/lizzie_spr.c
# 	lcc -Wm-yn"Chronos" -Wm-yc -Wm-ys -o main.gbc logic.o graphics.o
	lcc -Wm-yn"Chronos" -Wm-yc -Wm-ys -o main.gbc ./src/main.c ./src/funcs.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c ./src/Maps/TestMap.c ./src/Tiles/Tiles.c ./src/Sprites/lizzie_spr.c


sbx:
	sameboy main.gbc 

bgbx:
	wine /usr/local/BGB/bgb.exe main.gbc

emulix:
	emulicious main.gbc

clean:
	rm compile_files.txt -rf *.o
