CFLAGS		+= -I./sources/app/fishing_diary_game
CPPFLAGS	+= -I./sources/app/fishing_diary_game

VPATH += sources/app/fishing_diary_game

#CPP game source files 
SOURCES_CPP += sources/app/fishing_diary_game/fd_game_gun.cpp
SOURCES_CPP += sources/app/fishing_diary_game/fd_game_bullet.cpp
SOURCES_CPP += sources/app/fishing_diary_game/fd_game_fish.cpp