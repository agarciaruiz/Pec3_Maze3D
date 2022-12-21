#ifndef GLOBAL_H
#define GLOBAL_H

#define SCR_WIDTH 1020
#define SCR_HEIGHT 800

enum Screens { NONE, LOGO, TITLE, OPTIONS, GAMEPLAY, ENDING, LOADING };
enum PropType { LAVA, KEY, TURRET, BRIDGE };

typedef struct Prop {
	Model model;
	Vector3 position;
	float size;
	BoundingBox bb;
	PropType type;
	bool isEmpty;
}Prop;

#endif