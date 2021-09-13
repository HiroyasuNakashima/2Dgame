#pragma once
class CONTAINER;
class WINDOW;
class MAP;
class PLAYER;

class OBJECT {
public:
	static void setContainer(CONTAINER* c);
	static void setWindow(WINDOW* w);
	static void setMap(MAP* m);
	static void setPlayer(PLAYER* p);
protected:
	static CONTAINER* C;
	static WINDOW* W;
	static MAP* Map;
	static PLAYER* Player;
};