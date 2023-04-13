#ifndef MOVEDATABASE_H
#define MOVEDATABASE_H

#include <string>
#include <map>
#include <tuple>

#include "Move.h"

using namespace std;


map<string, tuple<int, int, int, Type, Category>> MoveData = {
	{ "PLACEHOLDER", {-1, -1, -1, NONE, STATUS} },
	{ "Pound", {40, 100, 35, NORMAL, PHYSICAL} },
	{ "Karate Chop", {50, 100, 25, FIGHTING, PHYSICAL} },
	{ "Double Slap", {15, 85, 10, NORMAL, PHYSICAL} },
	{ "Comet Punch", {18, 85, 15, NORMAL, PHYSICAL} },
	{ "Mega Punch", {80, 85, 20, NORMAL, PHYSICAL} },
	{ "Pay Day", {40, 100, 20, NORMAL, PHYSICAL} },
	{ "Fire Punch", {75, 100, 15, FIRE, PHYSICAL} },
	{ "Ice Punch", {75, 100, 15, ICE, PHYSICAL} },
	{ "Thunder Punch", {75, 100, 15, ELECTRIC, PHYSICAL} },
	{ "Scratch", {40, 100, 35, NORMAL, PHYSICAL} },
	{ "Vise Grip", {55, 100, 30, NORMAL, PHYSICAL} },
	{ "Guillotine", {0, 30, 5, NORMAL, PHYSICAL} },
	{ "Razor Wind", {80, 100, 10, NORMAL, SPECIAL} },
	{ "Swords Dance", {0, 0, 20, NORMAL, STATUS} },
	{ "Cut", {50, 95, 30, NORMAL, PHYSICAL} },
	{ "Gust", {40, 100, 35, FLYING, SPECIAL} },
	{ "Wing Attack", {60, 100, 35, FLYING, PHYSICAL} },
	{ "Whirlwind", {0, 0, 20, NORMAL, STATUS} },
	{ "Fly", {90, 95, 15, FLYING, PHYSICAL} },
	{ "Bind", {15, 85, 20, NORMAL, PHYSICAL} },
	{ "Slam", {80, 75, 20, NORMAL, PHYSICAL} },
	{ "Vine Whip", {45, 100, 25, GRASS, PHYSICAL} },
	{ "Stomp", {65, 100, 20, NORMAL, PHYSICAL} },
	{ "Double Kick", {30, 100, 30, FIGHTING, PHYSICAL} },
	{ "Mega Kick", {120, 75, 5, NORMAL, PHYSICAL} },
	{ "Jump Kick", {100, 95, 10, FIGHTING, PHYSICAL} },
	{ "Rolling Kick", {60, 85, 15, FIGHTING, PHYSICAL} },
	{ "Sand Attack", {0, 100, 15, GROUND, STATUS} },
	{ "Headbutt", {70, 100, 15, NORMAL, PHYSICAL} },
	{ "Horn Attack", {65, 100, 25, NORMAL, PHYSICAL} },
	{ "Fury Attack", {15, 85, 20, NORMAL, PHYSICAL} },
	{ "Horn Drill", {0, 30, 5, NORMAL, PHYSICAL} },
	{ "Tackle", {40, 100, 35, NORMAL, PHYSICAL} },
	{ "Body Slam", {85, 100, 15, NORMAL, PHYSICAL} },
	{ "Wrap", {15, 90, 20, NORMAL, PHYSICAL} },
	{ "Take Down", {90, 85, 20, NORMAL, PHYSICAL} },
	{ "Thrash", {120, 100, 10, NORMAL, PHYSICAL} },
	{ "Double-Edge", {120, 100, 15, NORMAL, PHYSICAL} },
	{ "Tail Whip", {0, 100, 30, NORMAL, STATUS} },
	{ "Poison Sting", {15, 100, 35, POISON, PHYSICAL} },
	{ "Twineedle", {25, 100, 20, BUG, PHYSICAL} },
	{ "Pin Missile", {25, 95, 20, BUG, PHYSICAL} },
	{ "Leer", {0, 100, 30, NORMAL, STATUS} },
	{ "Bite", {60, 100, 25, DARK, PHYSICAL} },
	{ "Growl", {0, 100, 40, NORMAL, STATUS} },
	{ "Roar", {0, 0, 20, NORMAL, STATUS} },
	{ "Sing", {0, 55, 15, NORMAL, STATUS} },
	{ "Supersonic", {0, 55, 20, NORMAL, STATUS} },
	{ "Sonic Boom", {0, 90, 20, NORMAL, SPECIAL} },
	{ "Disable", {0, 100, 20, NORMAL, STATUS} },
	{ "Acid", {40, 100, 30, POISON, SPECIAL} },
	{ "Ember", {40, 100, 25, FIRE, SPECIAL} },
	{ "Flamethrower", {90, 100, 15, FIRE, SPECIAL} },
	{ "Mist", {0, 0, 30, ICE, STATUS} },
	{ "Water Gun", {40, 100, 25, WATER, SPECIAL} },
	{ "Hydro Pump", {110, 80, 5, WATER, SPECIAL} },
	{ "Surf", {90, 100, 15, WATER, SPECIAL} },
	{ "Ice Beam", {90, 100, 10, ICE, SPECIAL} },
	{ "Blizzard", {110, 70, 5, ICE, SPECIAL} },
	{ "Psybeam", {65, 100, 20, PSYCHIC, SPECIAL} },
	{ "Bubble Beam", {65, 100, 20, WATER, SPECIAL} },
	{ "Aurora Beam", {65, 100, 20, ICE, SPECIAL} },
	{ "Hyper Beam", {150, 90, 5, NORMAL, SPECIAL} },
	{ "Peck", {35, 100, 35, FLYING, PHYSICAL} },
	{ "Drill Peck", {80, 100, 20, FLYING, PHYSICAL} },
	{ "Submission", {80, 80, 20, FIGHTING, PHYSICAL} },
	{ "Low Kick", {0, 100, 20, FIGHTING, PHYSICAL} },
	{ "Counter", {0, 100, 20, FIGHTING, PHYSICAL} },
	{ "Seismic Toss", {0, 100, 20, FIGHTING, PHYSICAL} },
	{ "Strength", {80, 100, 15, NORMAL, PHYSICAL} },
	{ "Absorb", {20, 100, 25, GRASS, SPECIAL} },
	{ "Mega Drain", {40, 100, 15, GRASS, SPECIAL} },
	{ "Leech Seed", {0, 90, 10, GRASS, STATUS} },
	{ "Growth", {0, 0, 20, NORMAL, STATUS} },
	{ "Razor Leaf", {55, 95, 25, GRASS, PHYSICAL} },
	{ "Solar Beam", {120, 100, 10, GRASS, SPECIAL} },
	{ "Poison Powder", {0, 75, 35, POISON, STATUS} },
	{ "Stun Spore", {0, 75, 30, GRASS, STATUS} },
	{ "Sleep Powder", {0, 75, 15, GRASS, STATUS} },
	{ "Petal Dance", {120, 100, 10, GRASS, SPECIAL} },
	{ "String Shot", {0, 95, 40, BUG, STATUS} },
	{ "Dragon Rage", {0, 100, 10, DRAGON, SPECIAL} },
	{ "Fire Spin", {35, 85, 15, FIRE, SPECIAL} },
	{ "Thunder Shock", {40, 100, 30, ELECTRIC, SPECIAL} },
	{ "Thunderbolt", {90, 100, 15, ELECTRIC, SPECIAL} },
	{ "Thunder Wave", {0, 90, 20, ELECTRIC, STATUS} },
	{ "Thunder", {110, 70, 10, ELECTRIC, SPECIAL} },
	{ "Rock Throw", {50, 90, 15, ROCK, PHYSICAL} },
	{ "Earthquake", {100, 100, 10, GROUND, PHYSICAL} },
	{ "Fissure", {0, 30, 5, GROUND, PHYSICAL} },
	{ "Dig", {80, 100, 10, GROUND, PHYSICAL} },
	{ "Toxic", {0, 90, 10, POISON, STATUS} },
	{ "Confusion", {50, 100, 25, PSYCHIC, SPECIAL} },
	{ "Psychic", {90, 100, 10, PSYCHIC, SPECIAL} },
	{ "Hypnosis", {0, 60, 20, PSYCHIC, STATUS} },
	{ "Meditate", {0, 0, 40, PSYCHIC, STATUS} },
	{ "Agility", {0, 0, 30, PSYCHIC, STATUS} },
	{ "Quick Attack", {40, 100, 30, NORMAL, PHYSICAL} },
	{ "Rage", {20, 100, 20, NORMAL, PHYSICAL} },
	{ "Teleport", {0, 0, 20, PSYCHIC, STATUS} },
	{ "Night Shade", {0, 100, 15, GHOST, SPECIAL} },
	{ "Mimic", {0, 0, 10, NORMAL, STATUS} },
	{ "Screech", {0, 85, 40, NORMAL, STATUS} },
	{ "Double Team", {0, 0, 15, NORMAL, STATUS} },
	{ "Recover", {0, 0, 5, NORMAL, STATUS} },
	{ "Harden", {0, 0, 30, NORMAL, STATUS} },
	{ "Minimize", {0, 0, 10, NORMAL, STATUS} },
	{ "Smokescreen", {0, 100, 20, NORMAL, STATUS} },
	{ "Confuse Ray", {0, 100, 10, GHOST, STATUS} },
	{ "Withdraw", {0, 0, 40, WATER, STATUS} },
	{ "Defense Curl", {0, 0, 40, NORMAL, STATUS} },
	{ "Barrier", {0, 0, 20, PSYCHIC, STATUS} },
	{ "Light Screen", {0, 0, 30, PSYCHIC, STATUS} },
	{ "Haze", {0, 0, 30, ICE, STATUS} },
	{ "Reflect", {0, 0, 20, PSYCHIC, STATUS} },
	{ "Focus Energy", {0, 0, 30, NORMAL, STATUS} },
	{ "Bide", {0, 0, 10, NORMAL, PHYSICAL} },
	{ "Metronome", {0, 0, 10, NORMAL, STATUS} },
	{ "Mirror Move", {0, 0, 20, FLYING, STATUS} },
	{ "Self-Destruct", {200, 100, 5, NORMAL, PHYSICAL} },
	{ "Egg Bomb", {100, 75, 10, NORMAL, PHYSICAL} },
	{ "Lick", {30, 100, 30, GHOST, PHYSICAL} },
	{ "Smog", {30, 70, 20, POISON, SPECIAL} },
	{ "Sludge", {65, 100, 20, POISON, SPECIAL} },
	{ "Bone Club", {65, 85, 20, GROUND, PHYSICAL} },
	{ "Fire Blast", {110, 85, 5, FIRE, SPECIAL} },
	{ "Waterfall", {80, 100, 15, WATER, PHYSICAL} },
	{ "Clamp", {35, 85, 15, WATER, PHYSICAL} },
	{ "Swift", {60, 0, 20, NORMAL, SPECIAL} },
	{ "Skull Bash", {130, 100, 10, NORMAL, PHYSICAL} },
	{ "Spike Cannon", {20, 100, 15, NORMAL, PHYSICAL} },
	{ "Constrict", {10, 100, 35, NORMAL, PHYSICAL} },
	{ "Amnesia", {0, 0, 20, PSYCHIC, STATUS} },
	{ "Kinesis", {0, 80, 15, PSYCHIC, STATUS} },
	{ "Soft-Boiled", {0, 0, 5, NORMAL, STATUS} },
	{ "High Jump Kick", {130, 90, 10, FIGHTING, PHYSICAL} },
	{ "Glare", {0, 100, 30, NORMAL, STATUS} },
	{ "Dream Eater", {100, 100, 15, PSYCHIC, SPECIAL} },
	{ "Poison Gas", {0, 90, 40, POISON, STATUS} },
	{ "Barrage", {15, 85, 20, NORMAL, PHYSICAL} },
	{ "Leech Life", {80, 100, 10, BUG, PHYSICAL} },
	{ "Lovely Kiss", {0, 75, 10, NORMAL, STATUS} },
	{ "Sky Attack", {140, 90, 5, FLYING, PHYSICAL} },
	{ "Transform", {0, 0, 10, NORMAL, STATUS} },
	{ "Bubble", {40, 100, 30, WATER, SPECIAL} },
	{ "Dizzy Punch", {70, 100, 10, NORMAL, PHYSICAL} },
	{ "Spore", {0, 100, 15, GRASS, STATUS} },
	{ "Flash", {0, 100, 20, NORMAL, STATUS} },
	{ "Psywave", {0, 100, 15, PSYCHIC, SPECIAL} },
	{ "Splash", {0, 0, 40, NORMAL, STATUS} },
	{ "Acid Armor", {0, 0, 20, POISON, STATUS} },
	{ "Crabhammer", {100, 90, 10, WATER, PHYSICAL} },
	{ "Explosion", {250, 100, 5, NORMAL, PHYSICAL} },
	{ "Fury Swipes", {18, 80, 15, NORMAL, PHYSICAL} },
	{ "Bonemerang", {50, 90, 10, GROUND, PHYSICAL} },
	{ "Rest", {0, 0, 5, PSYCHIC, STATUS} },
	{ "Rock Slide", {75, 90, 10, ROCK, PHYSICAL} },
	{ "Hyper Fang", {80, 90, 15, NORMAL, PHYSICAL} },
	{ "Sharpen", {0, 0, 30, NORMAL, STATUS} },
	{ "Conversion", {0, 0, 30, NORMAL, STATUS} },
	{ "Tri Attack", {80, 100, 10, NORMAL, SPECIAL} },
	{ "Super Fang", {0, 90, 10, NORMAL, PHYSICAL} },
	{ "Slash", {70, 100, 20, NORMAL, PHYSICAL} },
	{ "Substitute", {0, 0, 10, NORMAL, STATUS} },
	{ "Struggle", {50, 0, 1, NORMAL, PHYSICAL} },
	{ "Sketch", {0, 0, 1, NORMAL, STATUS} },
	{ "Triple Kick", {10, 90, 10, FIGHTING, PHYSICAL} },
	{ "Thief", {60, 100, 25, DARK, PHYSICAL} },
	{ "Spider Web", {0, 0, 10, BUG, STATUS} },
	{ "Mind Reader", {0, 0, 5, NORMAL, STATUS} },
	{ "Nightmare", {0, 100, 15, GHOST, STATUS} },
	{ "Flame Wheel", {60, 100, 25, FIRE, PHYSICAL} },
	{ "Snore", {50, 100, 15, NORMAL, SPECIAL} },
	{ "Curse", {0, 0, 10, GHOST, STATUS} },
	{ "Flail", {0, 100, 15, NORMAL, PHYSICAL} },
	{ "Conversion 2", {0, 0, 30, NORMAL, STATUS} },
	{ "Aeroblast", {100, 95, 5, FLYING, SPECIAL} },
	{ "Cotton Spore", {0, 100, 40, GRASS, STATUS} },
	{ "Reversal", {0, 100, 15, FIGHTING, PHYSICAL} },
	{ "Spite", {0, 100, 10, GHOST, STATUS} },
	{ "Powder Snow", {40, 100, 25, ICE, SPECIAL} },
	{ "Protect", {0, 0, 10, NORMAL, STATUS} },
	{ "Mach Punch", {40, 100, 30, FIGHTING, PHYSICAL} },
	{ "Scary Face", {0, 100, 10, NORMAL, STATUS} },
	{ "Feint Attack", {60, 0, 20, DARK, PHYSICAL} },
	{ "Sweet Kiss", {0, 75, 10, FAIRY, STATUS} },
	{ "Belly Drum", {0, 0, 10, NORMAL, STATUS} },
	{ "Sludge Bomb", {90, 100, 10, POISON, SPECIAL} },
	{ "Mud-Slap", {20, 100, 10, GROUND, SPECIAL} },
	{ "Octazooka", {65, 85, 10, WATER, SPECIAL} },
	{ "Spikes", {0, 0, 20, GROUND, STATUS} },
	{ "Zap Cannon", {120, 50, 5, ELECTRIC, SPECIAL} },
	{ "Foresight", {0, 0, 40, NORMAL, STATUS} },
	{ "Destiny Bond", {0, 0, 5, GHOST, STATUS} },
	{ "Perish Song", {0, 0, 5, NORMAL, STATUS} },
	{ "Icy Wind", {55, 95, 15, ICE, SPECIAL} },
	{ "Detect", {0, 0, 5, FIGHTING, STATUS} },
	{ "Bone Rush", {25, 90, 10, GROUND, PHYSICAL} },
	{ "Lock-On", {0, 0, 5, NORMAL, STATUS} },
	{ "Outrage", {120, 100, 10, DRAGON, PHYSICAL} },
	{ "Sandstorm", {0, 0, 10, ROCK, STATUS} },
	{ "Giga Drain", {75, 100, 10, GRASS, SPECIAL} },
	{ "Endure", {0, 0, 10, NORMAL, STATUS} },
	{ "Charm", {0, 100, 20, FAIRY, STATUS} },
	{ "Rollout", {30, 90, 20, ROCK, PHYSICAL} },
	{ "False Swipe", {40, 100, 40, NORMAL, PHYSICAL} },
	{ "Swagger", {0, 85, 15, NORMAL, STATUS} },
	{ "Milk Drink", {0, 0, 5, NORMAL, STATUS} },
	{ "Spark", {65, 100, 20, ELECTRIC, PHYSICAL} },
	{ "Fury Cutter", {40, 95, 20, BUG, PHYSICAL} },
	{ "Steel Wing", {70, 90, 25, STEEL, PHYSICAL} },
	{ "Mean Look", {0, 0, 5, NORMAL, STATUS} },
	{ "Attract", {0, 100, 15, NORMAL, STATUS} },
	{ "Sleep Talk", {0, 0, 10, NORMAL, STATUS} },
	{ "Heal Bell", {0, 0, 5, NORMAL, STATUS} },
	{ "Return", {0, 100, 20, NORMAL, PHYSICAL} },
	{ "Present", {0, 90, 15, NORMAL, PHYSICAL} },
	{ "Frustration", {0, 100, 20, NORMAL, PHYSICAL} },
	{ "Safeguard", {0, 0, 25, NORMAL, STATUS} },
	{ "Pain Split", {0, 0, 20, NORMAL, STATUS} },
	{ "Sacred Fire", {100, 95, 5, FIRE, PHYSICAL} },
	{ "Magnitude", {0, 100, 30, GROUND, PHYSICAL} },
	{ "Dynamic Punch", {100, 50, 5, FIGHTING, PHYSICAL} },
	{ "Megahorn", {120, 85, 10, BUG, PHYSICAL} },
	{ "Dragon Breath", {60, 100, 20, DRAGON, SPECIAL} },
	{ "Baton Pass", {0, 0, 40, NORMAL, STATUS} },
	{ "Encore", {0, 100, 5, NORMAL, STATUS} },
	{ "Pursuit", {40, 100, 20, DARK, PHYSICAL} },
	{ "Rapid Spin", {50, 100, 40, NORMAL, PHYSICAL} },
	{ "Sweet Scent", {0, 100, 20, NORMAL, STATUS} },
	{ "Iron Tail", {100, 75, 15, STEEL, PHYSICAL} },
	{ "Metal Claw", {50, 95, 35, STEEL, PHYSICAL} },
	{ "Vital Throw", {70, 0, 10, FIGHTING, PHYSICAL} },
	{ "Morning Sun", {0, 0, 5, NORMAL, STATUS} },
	{ "Synthesis", {0, 0, 5, GRASS, STATUS} },
	{ "Moonlight", {0, 0, 5, FAIRY, STATUS} },
	{ "Hidden Power", {60, 100, 15, NORMAL, SPECIAL} },
	{ "Cross Chop", {100, 80, 5, FIGHTING, PHYSICAL} },
	{ "Twister", {40, 100, 20, DRAGON, SPECIAL} },
	{ "Rain Dance", {0, 0, 5, WATER, STATUS} },
	{ "Sunny Day", {0, 0, 5, FIRE, STATUS} },
	{ "Crunch", {80, 100, 15, DARK, PHYSICAL} },
	{ "Mirror Coat", {0, 100, 20, PSYCHIC, SPECIAL} },
	{ "Psych Up", {0, 0, 10, NORMAL, STATUS} },
	{ "Extreme Speed", {80, 100, 5, NORMAL, PHYSICAL} },
	{ "Ancient Power", {60, 100, 5, ROCK, SPECIAL} },
	{ "Shadow Ball", {80, 100, 15, GHOST, SPECIAL} },
	{ "Future Sight", {120, 100, 10, PSYCHIC, SPECIAL} },
	{ "Rock Smash", {40, 100, 15, FIGHTING, PHYSICAL} },
	{ "Whirlpool", {35, 85, 15, WATER, SPECIAL} },
	{ "Beat Up", {0, 100, 10, DARK, PHYSICAL} }
};




#endif