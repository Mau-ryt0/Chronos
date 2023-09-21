# Put your GBDK tools PATH.
LCC = lcc
P2A = png2asset

# Put your emulator PATH.
SBPATH = sameboy
BGBPATH = bgb
EMULIPATH = emulicious

# Yes, "Chronos" is actually a provisional title.
PROVTITLE = Chronos

# Game sources.
MAINSOURCE := ./src/main.c ./src/funcs.c ./src/lizzie.c ./src/camera.c ./src/gfx.c ./src/setup.c ./src/structs.c
TILESOURCE := ./src/Tiles/MapTiles.c ./src/Sprites/Glitters.c ./src/Sprites/lizzie_spr.c
MAPSOURCE := ./src/Maps/TestMap.c ./src/Maps/WaterSpring.c 
UISOURCE:= ./src/UI/Heart.c ./src/UI/Font.c ./src/Tiles/DialogTiles.c ./src/UI/Dialog.c
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
	$(P2A) Assets/lizzie_spr.png -c src/Sprites/lizzie_spr.c -spr8x16 -noflip -keep_duplicate_tiles -tiles_only
	$(P2A) Assets/Glitters.png -c src/Sprites/Glitters.c -spr8x8 -tiles_only

	$(P2A) Assets/TestMap.png -c src/Maps/TestMap.c -map -source_tileset Assets/MapTiles.png -noflip -use_map_attributes
	$(P2A) Assets/MapTiles.png -c src/Tiles/MapTiles.c -map -tiles_only -noflip -no_palettes
	$(P2A) Assets/WaterSpring.png -c src/Maps/WaterSpring.c -map -noflip -use_map_attributes

	$(P2A) Assets/Font.png -c src/UI/Font.c -map -tiles_only -noflip -no_palettes -keep_duplicated_tiles
	$(P2A) Assets/Heart.png -c src/UI/Heart.c -spr8x8 -tiles_only

	$(P2A) Assets/Dialog.png -c src/UI/Dialog.c -map -source_tileset Assets/DialogTiles.png -noflip -use_map_attributes
	$(P2A) Assets/DialogTiles.png -c src/Tiles/DialogTiles.c -tiles_only -map -noflip
	clear

build:
	$(LCC) -Wl-lsrc/inc/hUGEDriver.lib -Wm-yn"$(PROVTITLE)" -Wm-yc -Wm-ys -Wl-yt0x1B -Wl-j -Wm-ya4 -autobank -Wb-ext=.rel -Wb-v -o $(PROVTITLE).gbc $(MAINSOURCE) $(TILESOURCE) $(MAPSOURCE) $(UISOURCE) $(OSTSOURCE)
# 	$(LCC) -Wa-l -Wm-yc -Wm-ys -Wl-m -Wl-j -o logic.o $(MAINSOURCE)
# 	$(LCC) -Wa-l -Wm-yc -Wm-ys -Wl-m -Wl-j -o graphics.o $(TILESOURCE) $(MAPSOURCE)
# 	$(LCC) -Wa-l -Wm-yc -Wm-ys -Wl-m -Wl-j -o sound.o $(OSTSOURCE)
# 	$(LCC) -Wa-l -Wl-lsrc/inc/hUGEDriver.lib -Wm-yn"Chronos" -Wl-m -Wl-j -Wm-yc -Wm-ys -o main.gbc logic.o graphics.o sound.o

clean:
	rm -f *.o *.lst *.map *.gbc *.ihx *.sym *.cdb *.adb
