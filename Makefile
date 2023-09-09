all: before assets build clean

sb: before assets build clean sbx

bgb: before assets build clean bgbx

emuli: before assets build clean emulix

before:
	rm -rf *.o *.gbc & clear

assets:
	png2asset Assets/lizzie_spr.png -c src/Sprites/lizzie_spr.c -spr8x16 -sw 16 -sh 16 -noflip -keep_duplicate_tiles -tiles_only
	png2asset Assets/Heart.png -c src/Sprites/Heart.c -spr8x8 -tiles_only
	png2asset Assets/TestMap.png -c src/Maps/TestMap.c -map -source_tileset Assets/MapTiles.png -noflip -use_map_attributes
	png2asset Assets/MapTiles.png -c src/Tiles/MapTiles.c -map -tiles_only -noflip -no_palettes
	png2asset Assets/Font.png -c src/UI/Font.c -map -tiles_only -noflip -no_palettes -keep_duplicated_tiles
	png2asset Assets/Dialog.png -c src/Maps/Dialog.c -map -source_tileset Assets/DialogTiles.png -noflip -use_map_attributes
	png2asset Assets/DialogTiles.png -c src/Tiles/DialogTiles.c -tiles_only -map -noflip
	clear

build:
# 	lcc -Wm-yc -Wm-ys -o logic.o ./src/main.c ./src/funcs.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c
# 	lcc -Wm-yc -Wm-ys -o graphics.o ./src/Maps/TestMap.c ./src/Tiles/Tiles.c ./src/Sprites/lizzie_spr.c
# 	lcc -Wm-yn"Chronos" -Wm-yc -Wm-ys -o main.gbc logic.o graphics.o
	lcc -Wl-lsrc/inc/hUGEDriver.lib -Wm-yn"Chronos" -Wm-yc -Wm-ys -o main.gbc ./src/main.c ./src/funcs.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c ./src/Maps/TestMap.c ./src/Tiles/MapTiles.c ./src/UI/Font.c ./src/Maps/Dialog.c ./src/Tiles/DialogTiles.c ./src/Sprites/Heart.c ./src/Sprites/lizzie_spr.c ./src/Ost/Menuet.c


sbx:
	sameboy main.gbc 

bgbx:
	wine /usr/local/BGB/bgb.exe main.gbc

emulix:
	emulicious main.gbc

clean:
	rm compile_files.txt -rf *.o
