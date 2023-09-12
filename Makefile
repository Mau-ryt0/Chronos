# Put your GBDK tools PATH.
LCC = lcc
P2A = png2asset

# Put your emulator PATH.
SBPATH = sameboy
BGBPATH = wine /usr/local/BGB/bgb.exe
EMULIPATH = emulicious

# Yes, "Chronos" is actually a provisional title.
PROVTITLE = Chronos

# Game sources.
MAINSOURCE := ./src/main.c ./src/funcs.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c
TILESOURCE := ./src/Tiles/MapTiles.c ./src/UI/Font.c ./src/Tiles/DialogTiles.c ./src/Sprites/Heart.c ./src/Sprites/lizzie_spr.c
MAPSOURCE := ./src/Maps/TestMap.c ./src/Maps/WaterSpring.c ./src/Maps/Dialog.c
OSTSOURCE := ./src/Ost/Menuet.c ./src/Ost/Spring.c

# This just build the game.
all: clean assets build

# This just execute the game.
sbx:
	$(SBPATH) $(PROVTITLE).gbc

bgbx:
	$(BGBPATH) $(PROVTITLE).gbc

emulix:
	$(EMULIPATH) $(PROVTITLE).gbc

# This build and execute the game.
# syntax: make [emulator]
# example: make sb
sb: clean assets build sbx
bgb: clean assets build bgbx
emuli: clean assets build emulix

assets:
	$(P2A) Assets/lizzie_spr.png -c src/Sprites/lizzie_spr.c -spr8x16 -sw 16 -sh 16 -noflip -keep_duplicate_tiles -tiles_only
	$(P2A) Assets/Heart.png -c src/Sprites/Heart.c -spr8x8 -tiles_only

	$(P2A) Assets/TestMap.png -c src/Maps/TestMap.c -map -source_tileset Assets/MapTiles.png -noflip -use_map_attributes
	$(P2A) Assets/MapTiles.png -c src/Tiles/MapTiles.c -map -tiles_only -noflip -no_palettes
	$(P2A) Assets/WaterSpring.png -c src/Maps/WaterSpring.c -map -noflip -use_map_attributes

	$(P2A) Assets/Font.png -c src/UI/Font.c -map -tiles_only -noflip -no_palettes -keep_duplicated_tiles

	$(P2A) Assets/Dialog.png -c src/Maps/Dialog.c -map -source_tileset Assets/DialogTiles.png -noflip -use_map_attributes
	$(P2A) Assets/DialogTiles.png -c src/Tiles/DialogTiles.c -tiles_only -map -noflip
	clear

build:
# 	lcc -Wm-yc -Wm-ys -o logic.o ./src/main.c ./src/funcs.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c
# 	lcc -Wm-yc -Wm-ys -o graphics.o ./src/Maps/TestMap.c ./src/Tiles/Tiles.c ./src/Sprites/lizzie_spr.c
# 	lcc -Wm-yn"Chronos" -Wm-yc -Wm-ys -o main.gbc logic.o graphics.o
	$(LCC) -Wl-lsrc/inc/hUGEDriver.lib -Wm-yn"$(PROVTITLE)" -Wm-yc -Wm-ys -o $(PROVTITLE).gbc $(MAINSOURCE) $(TILESOURCE) $(MAPSOURCE) $(OSTSOURCE)

clean:
	rm -f *.o *.lst *.map *.gbc *.ihx *.sym *.cdb *.adb
