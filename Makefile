all: before assets build clean

sb: before assets build clean sbx

bgb: before assets build clean bgbx

before:
	rm -rf *.o *.gbc & clear

assets:
	png2asset Assets/lizzie_spr.png -c src/Sprites/lizzie_spr.c -spr8x16 -noflip -keep_duplicate_tiles
	png2asset Assets/TestMap.png -c src/Maps/TestMap.c -map -noflip -use_map_attributes
	clear

build:
	lcc -Wm-yn"Chronos" -Wm-yc -Wm-ys -o main.gbc ./src/main.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c ./src/Maps/TestMap.c ./src/Tiles/Tiles.c ./src/Sprites/lizzie_spr.c

sbx:
	/snap/sameboy/1770/usr/bin/sameboy main.gbc 

bgbx:
	wine /usr/local/BGB/bgb.exe main.gbc

clean:
	rm compile_files.txt -rf *.o
