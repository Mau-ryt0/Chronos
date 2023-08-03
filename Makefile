all: before assets build

sameboy: before assets build clean exec

bgb: assets build clean bgbex

before:
	rm -rf *.o *.gbc & clear

assets:
	png2asset Assets/lizzie_spr.png -c src/Sprites/lizzie_spr.c -spr8x16 -keep_duplicate_tiles
	png2asset Assets/TestMap.png -c src/Maps/TestMap.c -map -noflip -use_map_attributes
	clear

build:
	lcc -Wm-yn"Chronos" -Wm-yc -Wm-ys -o main.gbc ./src/main.c ./src/lizzie.c ./src/camera.c ./src/setup.c ./src/Maps/TestMap.c ./src/Tiles/Tiles.c ./src/Sprites/lizzie_spr.c

exec:
	/snap/sameboy/1770/usr/bin/sameboy main.gbc

bgbex:
	wine /usr/local/BGB/bgb.exe main.gbc

clean:
	rm compile_files.txt -rf *.o & clear
