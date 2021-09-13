#include"MAP.h"
#include"CHARACTER.h"

CHARACTER::~CHARACTER(){}
void CHARACTER::init(){}
void CHARACTER::update(){}
void CHARACTER::draw(){}

//“–‚½‚è”»’è—p
float CHARACTER::cTop()	   { return Pos.y + OffsetTop;    }
float CHARACTER::cBottom() { return Pos.y + OffsetBottom; }
float CHARACTER::cLeft()   { return Pos.x + OffsetLeft;   }
float CHARACTER::cRight()  { return Pos.x + OffsetRight;  }
VECTOR2 CHARACTER::cLeftTop()	 { return VECTOR2(Pos.x + OffsetLeft,  Pos.y + OffsetTop);    }
VECTOR2 CHARACTER::cLeftBottom() { return VECTOR2(Pos.x + OffsetLeft,  Pos.y + OffsetBottom); }
VECTOR2 CHARACTER::cRightTop()	 { return VECTOR2(Pos.x + OffsetRight, Pos.y + OffsetTop);    }
VECTOR2 CHARACTER::cRightBottom(){ return VECTOR2(Pos.x + OffsetRight, Pos.y + OffsetBottom); }
VECTOR2 CHARACTER::cTopLeft()	 { return VECTOR2(Pos.x + OffsetLeft,  Pos.y + OffsetTop);    }
VECTOR2 CHARACTER::cTopRight()	 { return VECTOR2(Pos.x + OffsetRight, Pos.y + OffsetTop);	  }
VECTOR2 CHARACTER::cBottomLeft() { return VECTOR2(Pos.x + OffsetLeft,  Pos.y + OffsetBottom); }
VECTOR2 CHARACTER::cBottomRight(){ return VECTOR2(Pos.x + OffsetRight, Pos.y + OffsetBottom); }