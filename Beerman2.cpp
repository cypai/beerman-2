// Beerman2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
#include <conio.h>
#include <time.h>
#include "Enemies.h"
#define NEUTRAL 0
#define FIRE 1
#define WATER 2
#define EARTH 3
#define AIR 4
#define GRASS 5
#define LIGHTNING 6
using namespace std;

int battle_init(int inventory[],Beerman& beerman,Enemy enemy,int lvl,int ai_lvl,bool run,bool get_xp=1);
bool battle_beerman_seq(Beerman& beerman,Enemy& enemy,int beerman_status[],int enemy_status[],const bool can_run,int inventory[],int& hold,int objects[]);
void battle_enemy_seq(Beerman& beerman,Enemy& enemy,int beerman_status[],int enemy_status[],int objects[],int ai_lvl);
int battle_inventory_list(int menu_numbers[],int inventory[],int& j,int hold);
int perform_effects(Enemy& enemy,int effects_array[],int perform);
void perform_field(Beerman& beerman,Enemy& enemy,int beerman_status[],int enemy_status[],int perform);
Attack* check_combo(Beerman& beerman,int& hold,int objects[],int att,int thrw,int use,int drop,int effects_array[]);
Attack* throw_item(Beerman& beerman,int& hold,int objects[],int inventory[],int effects_array[],int& back);
Attack* use_item(Beerman& beerman,int& hold,int objects[],int inventory[],int effects_array[],int& back);
Attack* drop_item(Beerman& beerman,int& hold,int objects[],int inventory[],int effects_array[],int& back);
void check_battle_objects(const int& hold,const int objects[]);
void field_damage_manipulate(int at_element,int& damage,int effects_array[]);
void effect_text(Enemy& target,const int& effect);
int menu(int num_options, ... );
void pause();
void bar(int inventory[],Beerman& beerman,Enemy barfighter);
void gym(int inventory[],Beerman& beerman,Enemy punchingbag,Enemy gymmember,Enemy gymboxer,Enemy gymchampion,Enemy pikachu);
void playground(int inventory[],Beerman& beerman,Enemy boy,Enemy girl,Enemy policeman);
void shop(int inventory[],int& show_combo_tutorial);
int dungeon(string area,int size_x,int size_y,int start_x,int start_y,int end_x,int end_y,int& x,int& y);
void blackout(int inventory[],Beerman& beerman);
void show_inventory(int inventory[]);
string get_inventory_name(int inventory[],int number);
int save(Beerman beerman,const int inventory[],int mission_number,string mission_string,int area,int show_combo_tutorial,const int high_score[]);
void lost_woods_description(const int& x,const int& y);
void neo_hq_description(const int& x,const int& y,int& mission_number,string& mission);
void chapter_1_init(int& mission_number,string& mission);
void chapter_2_init(int& mission_number,string& mission,int& area);
void beer_council(int& mission_number,string& mission);
void apartment(int inventory[],Beerman& beerman,Enemy mudkipz,Enemy policeman,int& mission_number);
int city_hall(int inventory[],Beerman& beerman,Enemy carrie_nation,Enemy sir_elliot,int& mission_number,string& mission);
void publius_lyrics();
void chorus();
void shop_full(int inventory[]);
extern int randint(int,int);

int main()
{
	srand(time(NULL));
	cout<<"Beer Man II: The Return"<<endl;
	cout<<"-----------------------\n(C) Cheng-Yu Pai 2011"<<endl;
	cout<<"Loading...\n"<<flush;
	//Set up general variables
	string mission="Mission: Get the Thief.";
	int mission_number=0;
	int choice,area=0;
	int inventory[12],high_score[6];
	for (int i=0;i<12;i++)
		inventory[i]=0;
	for (int i=0;i<6;i++)
		high_score[i]=0;
	high_score[1]=3;
	high_score[3]=3;
	high_score[5]=3;
	inventory[0]=20;
	//Set up attacks
	//Template: name("Name",ELEMENT,Type,Power,Effect,Accuracy,Effect_Accuracy,MP,BAC);
	Attack punch("Punch",NEUTRAL,0,10,-1,100,100,0,0);
	Attack flail("Flail",NEUTRAL,0,17,-1,70,100,0,.1);
	Attack drunken_fist("Drunken Fist",NEUTRAL,0,25,-1,60,100,0,.15);
	Attack kick("Kick",NEUTRAL,0,10,-1,100,100,0,0);
	Attack poop("Poop",NEUTRAL,0,5,3,80,50,2,0);
	Attack false_evolve("False Evolve",NEUTRAL,1,0,3,80,100,3,0);
	Attack night_stick("Night Stick",NEUTRAL,0,17,-1,100,100,0,0);
	Attack pistol("Pistol",NEUTRAL,0,40,-1,90,100,8,0);
	Attack shotgun("Shotgun",NEUTRAL,0,40,-1,95,100,0,0);
	Attack erase("Erase",NEUTRAL,0,50,-1,85,100,4,0);
	Attack manipulate("Manipulate",NEUTRAL,1,0,3,100,100,3,0);
	Attack tackle("Tackle",NEUTRAL,0,25,-1,100,100,0,0);
	Attack quick_attack("Quick Attack",NEUTRAL,0,21,-1,100,100,0,0);
	Attack beer_missile("Beer Missile",NEUTRAL,0,50,-1,85,100,7,.2);
	Attack beginner_magic("Beginner's Magic",NEUTRAL,1,12,-1,100,100,1,0);
	Attack advanced_magic("Advanced Magic",NEUTRAL,1,40,-1,100,100,7,0);
	Attack purge("Purge",NEUTRAL,1,20,0,80,100,0,0);
	Attack knife("Knife",NEUTRAL,0,13,-1,100,100,0,0);
	Attack karate_chop("Karate Chop",NEUTRAL,0,25,-1,90,100,3,0);
	Attack poison_dart("Poison Dart",NEUTRAL,0,12,0,90,70,2,0);
	Attack spoil("Spoil",NEUTRAL,1,6,0,90,90,3,0);
	Attack swine_flu("Swine Flu Virus",NEUTRAL,1,8,0,90,70,2,0);
	Attack acid("Acid",NEUTRAL,1,12,0,90,75,2,0);
	Attack uppercut("Uppercut",NEUTRAL,0,30,-1,100,100,5,0);
	Attack beer_throw("Beer Throw",NEUTRAL,0,17,-1,100,100,0,0);
	Attack explosion("Explosion",NEUTRAL,0,100,21,100,100,17,0);
	Attack time_bomb("Time Bomb",NEUTRAL,0,0,27,100,100,4,.1);
	Attack war_dance("War Dance",NEUTRAL,1,0,24,100,100,5,.25);
	Attack en_guard("En Guard",NEUTRAL,1,0,25,100,100,8,0);
	Attack chaos_effect("Chaos Effect",NEUTRAL,1,0,26,100,100,5,0);
	Attack immolation_field("Immolation Field",FIRE,1,0,1,100,100,8,0);
	Attack deletion_field("Deletion Field",NEUTRAL,1,0,2,100,100,8,0);
	Attack slow("Slow",NEUTRAL,1,0,8,100,100,5,0);
	Attack growth("Growth",NEUTRAL,1,0,9,100,100,5,0);
	Attack acid_rain("Acid Rain",NEUTRAL,1,2,28,100,100,3,.1);
	Attack thunderstorm("Thunderstorm",LIGHTNING,1,0,10,100,100,10,.15);
	Attack taser("Taser",LIGHTNING,0,7,5,90,60,1,0);
	Attack spark("Spark",LIGHTNING,1,15,5,100,35,3,0);
	Attack lightning("Lightning",LIGHTNING,1,40,-1,100,100,10,0);
	Attack thunder("Thunder",LIGHTNING,1,42,5,85,30,13,0);
	Attack volt_tackle("Volt Tackle",LIGHTNING,0,55,5,100,10,15,0);
	Attack bonfire("Bonfire",FIRE,1,0,14,100,100,10,.15);
	Attack fire_punch("Fire Punch",FIRE,0,30,-1,100,100,7,.05);
	Attack falcon_punch("Falcon Punch",FIRE,0,60,-1,80,100,15,.2);
	Attack ember("Ember",FIRE,1,15,6,100,35,3,0);
	Attack fire_spin("Fire Spin",FIRE,1,30,6,100,10,7,.1);
	Attack flamethrower("Flamethrower",FIRE,1,50,6,95,70,12,.15);
	Attack solar_flare("Solar Flare",FIRE,1,57,6,85,30,12,0);
	Attack sandstorm("Sandstorm",EARTH,1,2,11,100,100,10,.15);
	Attack sand_attack("Sand Attack",EARTH,0,15,4,100,80,3,0);
	Attack rollout("Rollout",EARTH,0,12,-1,90,100,0,0);
	Attack rock_throw("Rock Throw",EARTH,0,17,-1,95,100,2,0);
	Attack rock_slide("Rock Slide",EARTH,0,7,20,95,100,6,.05);
	Attack meteor_smash("Meteor Smash",EARTH,0,40,-1,95,100,10,.1);
	Attack glass_shards("Glass Shards",EARTH,1,8,19,100,100,7,.1);
	Attack earthquake("Earthquake",EARTH,1,55,-1,100,100,12,0);
	Attack iron_tail("Iron Tail",EARTH,0,43,-1,75,100,8,0);
	Attack flood("Flood",WATER,1,5,13,100,100,11,.2);
	Attack water_bomb("Water Bomb",WATER,1,15,7,100,100,4,0);
	Attack water_blast("Water Blast",WATER,1,27,7,100,100,8,.05);
	Attack tsunami("Tsunami",WATER,1,34,7,100,100,13,.2);
	Attack tornado("Tornado",AIR,1,5,12,100,100,10,.2);
	Attack flying_strike("Flying Strike",AIR,0,17,-1,100,100,3,0);
	Attack aerial_ace("Aerial Ace",AIR,0,37,-1,100,100,6,.1);
	Attack gust("Gust",AIR,1,10,17,90,100,4,0);
	Attack wind_slash("Wind Slash",AIR,1,20,-1,100,100,3,0);
	Attack cyclone("Cyclone",AIR,1,33,-1,100,100,9,.2);
	Attack corrosive_fumes("Corrosive Fumes",AIR,1,30,0,100,80,8,.15);
	Attack overgrowth("Overgrowth",GRASS,1,0,15,100,100,9,.2);
	Attack seed_attack("Seed Attack",GRASS,0,20,-1,100,100,2,0);
	Attack bullet_seed("Bullet Seed",GRASS,0,6,19,100,100,5,.1);
	Attack solarbeam("Solarbeam",GRASS,1,38,-1,100,100,10,0);
	Attack animate_plants("Animate Plants",GRASS,1,0,22,100,100,4,.15);
	Attack leech_seed("Leech Seed",GRASS,1,0,23,100,100,5,.15);
	Attack milk_drink("Milk Drink",NEUTRAL,1,15,16,100,100,7,0);
	Attack recover("Recover",NEUTRAL,1,15,16,100,100,7,.1);
	Attack s_potion("S Potion",NEUTRAL,1,17,16,100,100,10,.15);
	Attack restore("Restore",NEUTRAL,1,5,18,100,100,0,0);
	Attack restore_2("Restore II",NEUTRAL,1,8,18,100,100,0,0);
	Attack stampede("Stampede",NEUTRAL,0,6,19,100,100,5,0);
	Attack fury_swipes("Fury Swipes",NEUTRAL,0,3,19,100,100,2,0);
	Attack neutralize("Neutralize",NEUTRAL,1,0,29,100,100,6,0);
	//Set up enemy stats: 
	//Enemy(string Name,int Element,int atk,int def,int matk,int mdef,int spd,int hp,int mp,int xp,int money,int ev);
	Enemy cow("Cow",NEUTRAL,1,2,1,1,1,20,2,10,2,1);
	cow.set_growth(1,2,1,1,1,10,2,1);
	cow.set_attack(kick,1,0);
	cow.set_attack(poop,3,1);
	cow.set_attack(stampede,7,2);
	cow.set_attack(milk_drink,8,3);
	cow.set_attack(swine_flu,15,4);
	cow.set_attack(iron_tail,17,5);
	cow.set_attack(neutralize,26,6);
	Enemy seagull("Seagull",AIR,1,0,1,1,3,13,3,11,5,4);
	seagull.set_growth(1,1,1,1,2,7,2,1);
	seagull.set_attack(flail,1,0);
	seagull.set_attack(water_bomb,3,1);
	seagull.set_attack(poop,3,2);
	seagull.set_attack(flying_strike,7,2);
	seagull.set_attack(gust,10,3);
	seagull.set_attack(water_blast,10,1);
	seagull.set_attack(aerial_ace,12,2);
	seagull.set_attack(tornado,16,4);
	seagull.set_attack(cyclone,23,5);
	seagull.set_attack(neutralize,27,6);
	Enemy boy("Little Boy",NEUTRAL,2,1,0,1,1,20,2,7,3,0);
	boy.set_growth(1,1,0,0,1,5,2,1);
	boy.set_attack(punch,1,0);
	Enemy girl("Little Girl",NEUTRAL,1,1,1,1,1,17,4,7,3,2);
	girl.set_growth(1,1,1,1,1,5,3,1);
	girl.set_attack(kick,1,0);
	girl.set_attack(beginner_magic,1,1);
	Enemy policeman("Policeman",NEUTRAL,2,2,1,2,2,20,5,12,5,1);
	policeman.set_growth(1,1,1,1,1,12,2,3);
	policeman.set_attack(punch,1,0);
	policeman.set_attack(night_stick,1,1);
	policeman.set_attack(taser,1,2);
	policeman.set_attack(pistol,10,3);
	policeman.set_attack(night_stick,7,0);
	policeman.set_attack(gust,7,1);
	policeman.set_attack(meteor_smash,15,1);
	policeman.set_attack(shotgun,20,1);
	policeman.set_attack(manipulate,20,3);
	policeman.set_attack(flamethrower,23,4);
	policeman.set_attack(en_guard,26,5);
	policeman.set_attack(neutralize,28,6);
	Enemy cow_boy("Cow Boy",NEUTRAL,2,2,1,1,3,35,5,25,9,1);
	cow_boy.set_growth(1,1,1,1,1,10,3,3);
	cow_boy.set_attack(knife,1,0);
	cow_boy.set_attack(beginner_magic,1,1);
	cow_boy.set_attack(stampede,1,2);
	cow_boy.set_attack(milk_drink,1,3);
	cow_boy.set_attack(shotgun,30,0);
	cow_boy.set_attack(advanced_magic,30,1);
	cow_boy.set_attack(gust,30,4);
	cow_boy.set_attack(neutralize,30,5);
	Enemy arnold("Arnold Schwarzenegger",NEUTRAL,6,4,1,1,2,35,5,25,9,0);
	arnold.set_growth(1,1,1,1,1,15,3,3);
	arnold.set_attack(night_stick,1,0);
	arnold.set_attack(pistol,1,1);
	arnold.set_attack(flying_strike,1,2);
	arnold.set_attack(fire_punch,1,3);
	arnold.set_attack(shotgun,30,0);
	arnold.set_attack(war_dance,30,1);
	arnold.set_attack(aerial_ace,30,2);
	arnold.set_attack(falcon_punch,30,3);
	arnold.set_attack(gust,30,4);
	arnold.set_attack(neutralize,30,5);
	Enemy fire_man("Fire Man",FIRE,6,5,14,17,6,42,6,25,9,3);
	fire_man.set_growth(1,1,1,1,1,20,3,3);
	fire_man.set_attack(restore,1,0);
	fire_man.set_attack(falcon_punch,1,1);
	fire_man.set_attack(water_blast,1,2);
	fire_man.set_attack(solar_flare,1,3);
	fire_man.set_attack(solarbeam,1,4);
	fire_man.set_attack(immolation_field,1,5);
	fire_man.set_attack(bonfire,1,6);
	fire_man.set_attack(restore_2,30,0);
	Enemy salieri("Antonio Salieri",NEUTRAL,6,4,6,4,12,35,5,25,9,2);
	salieri.set_growth(1,1,1,2,0,20,3,3);
	salieri.set_attack(night_stick,1,0);
	salieri.set_attack(pistol,1,1);
	salieri.set_attack(poison_dart,1,2);
	salieri.set_attack(recover,1,3);
	salieri.set_attack(immolation_field,1,4);
	salieri.set_attack(shotgun,30,0);
	salieri.set_attack(en_guard,30,1);
	salieri.set_attack(corrosive_fumes,30,2);
	salieri.set_attack(deletion_field,30,4);
	salieri.set_attack(gust,30,5);
	salieri.set_attack(neutralize,30,6);
	Enemy lyman_beecher("Zombie Lyman Beecher",NEUTRAL,6,8,21,18,7,35,5,25,9,3);
	lyman_beecher.set_growth(1,1,1,1,1,23,3,3);
	lyman_beecher.set_attack(restore_2,1,0);
	lyman_beecher.set_attack(pistol,1,1);
	lyman_beecher.set_attack(thunder,1,2);
	lyman_beecher.set_attack(recover,1,3);
	lyman_beecher.set_attack(thunderstorm,1,4);
	lyman_beecher.set_attack(growth,1,5);
	lyman_beecher.set_attack(tsunami,1,6);
	lyman_beecher.set_attack(shotgun,30,1);
	Enemy carrie_nation("Lich Carrie Nation",NEUTRAL,20,10,6,16,3,35,5,25,9,1);
	carrie_nation.set_growth(2,1,1,1,1,23,3,3);
	carrie_nation.set_attack(restore_2,1,0);
	carrie_nation.set_attack(pistol,1,1);
	carrie_nation.set_attack(war_dance,1,2);
	carrie_nation.set_attack(recover,1,3);
	carrie_nation.set_attack(falcon_punch,1,4);
	carrie_nation.set_attack(gust,1,5);
	carrie_nation.set_attack(slow,1,6);
	Enemy elliot("Sir Elliot",NEUTRAL,21,10,15,20,6,35,5,25,9,2);
	elliot.set_growth(2,1,1,1,1,27,3,3);
	elliot.set_attack(shotgun,1,0);
	elliot.set_attack(meteor_smash,1,1);
	elliot.set_attack(war_dance,1,2);
	elliot.set_attack(thunder,1,3);
	elliot.set_attack(gust,1,4);
	elliot.set_attack(chaos_effect,1,5);
	elliot.set_attack(time_bomb,1,6);
	Enemy eraser("The Eraser",NEUTRAL,8,16,18,13,6,100,5,25,9,3);
	eraser.set_growth(1,1,1,1,1,28,3,5);
	eraser.set_attack(restore_2,1,0);
	eraser.set_attack(deletion_field,1,1);
	eraser.set_attack(milk_drink,1,2);
	eraser.set_attack(erase,1,3);
	eraser.set_attack(en_guard,1,4);
	eraser.set_attack(solar_flare,1,5);
	eraser.set_attack(solarbeam,1,6);
	Enemy mecha("Giant Mecha",LIGHTNING,17,17,17,17,10,100,5,25,9,1);
	mecha.set_growth(2,1,1,1,1,28,3,5);
	mecha.set_attack(shotgun,1,0);
	mecha.set_attack(thunder,1,1);
	mecha.set_attack(falcon_punch,1,2);
	mecha.set_attack(meteor_smash,1,3);
	mecha.set_attack(solarbeam,1,4);
	mecha.set_attack(chaos_effect,1,5);
	mecha.set_attack(time_bomb,1,6);
	Enemy milk_man("Milk Man",NEUTRAL,5,8,10,8,8,20,3,25,9,0);
	milk_man.set_growth(2,1,1,1,1,20,3,5);
	milk_man.set_attack(shotgun,1,0);
	milk_man.set_attack(manipulate,1,1);
	milk_man.set_attack(milk_drink,1,2);
	milk_man.set_attack(neutralize,1,3);
	milk_man.set_attack(spoil,1,4);
	milk_man.set_attack(deletion_field,1,5);
	milk_man.set_attack(slow,1,6);
	Enemy mudkipz("Mudkipz",WATER,7,10,6,10,6,100,5,25,9,1);
	mudkipz.set_growth(1,1,1,1,1,31,3,3);
	mudkipz.set_attack(tackle,1,0);
	mudkipz.set_attack(s_potion,1,1);
	mudkipz.set_attack(swine_flu,1,2);
	mudkipz.set_attack(false_evolve,1,3);
	Enemy pikachu("Ash's Pikachu",LIGHTNING,13,5,13,5,15,10,7,23,9,4);
	pikachu.set_growth(1,1,1,1,1,19,3,2);
	pikachu.set_attack(quick_attack,1,0);
	pikachu.set_attack(volt_tackle,1,1);
	pikachu.set_attack(iron_tail,1,2);
	pikachu.set_attack(thunder,1,3);
	Enemy lawyer("Lawyer",NEUTRAL,3,3,6,5,5,20,3,14,9,0);	//Lawyer needs more balanced attacks growth
	lawyer.set_growth(2,1,1,1,1,12,3,6);
	lawyer.set_attack(restore,1,0);
	lawyer.set_attack(manipulate,1,1);
	lawyer.set_attack(slow,1,2);
	lawyer.set_attack(recover,1,3);
	lawyer.set_attack(chaos_effect,1,4);
	lawyer.set_attack(pistol,1,5);
	lawyer.set_attack(time_bomb,15,6);
	lawyer.set_attack(neutralize,30,1);
	Enemy thief("Thief",NEUTRAL,1,1,0,1,4,20,2,12,10,4);
	thief.set_growth(1,1,0,1,2,10,2,4);
	thief.set_attack(punch,1,0);
	thief.set_attack(knife,3,1);
	thief.set_attack(karate_chop,7,2);
	thief.set_attack(poison_dart,7,3);
	thief.set_attack(sand_attack,12,4);
	thief.set_attack(pistol,13,1);
	thief.set_attack(taser,17,5);
	thief.set_attack(manipulate,24,6);
	Enemy water_mage("Water Mage",WATER,0,1,5,4,2,20,20,12,10,3);
	water_mage.set_growth(0,1,2,2,1,10,5,3);
	water_mage.set_attack(knife,1,0);
	water_mage.set_attack(water_bomb,1,1);
	water_mage.set_attack(water_blast,8,1);
	water_mage.set_attack(flood,8,2);
	water_mage.set_attack(tsunami,13,1);
	water_mage.set_attack(restore,13,0);
	water_mage.set_attack(lightning,15,3);
	water_mage.set_attack(growth,17,4);
	water_mage.set_attack(thunderstorm,17,2);
	water_mage.set_attack(recover,30,5);
	water_mage.set_attack(neutralize,30,6);
	Enemy mage("Mage",NEUTRAL,1,1,4,3,1,20,20,12,10,2);
	mage.set_growth(1,1,2,2,1,10,5,3);
	mage.set_attack(punch,1,0);
	mage.set_attack(ember,1,1);
	mage.set_attack(knife,5,0);
	mage.set_attack(seed_attack,6,1);
	mage.set_attack(wind_slash,6,2);
	mage.set_attack(water_bomb,6,3);
	mage.set_attack(gust,10,4);
	mage.set_attack(spark,10,5);
	mage.set_attack(water_blast,12,3);
	mage.set_attack(flamethrower,17,1);
	mage.set_attack(lightning,17,5);
	mage.set_attack(earthquake,17,6);
	Enemy punching_bag("Punching Bag",NEUTRAL,1,2,0,1,3,15,0,8,4,0);
	punching_bag.set_growth(1,0,0,0,0,15,0,2);
	punching_bag.set_attack(punch,1,0);
	Enemy gym_member("Gym Member",NEUTRAL,2,1,1,1,2,20,5,11,5,1);
	gym_member.set_growth(1,1,1,1,1,10,2,3);
	gym_member.set_attack(punch,1,0);
	gym_member.set_attack(karate_chop,5,1);
	Enemy boxer("Boxer",NEUTRAL,2,2,1,1,3,20,5,13,7,1);
	boxer.set_growth(1,1,1,1,1,10,2,4);
	boxer.set_attack(punch,1,0);
	boxer.set_attack(karate_chop,5,1);
	boxer.set_attack(uppercut,9,2);
	boxer.set_attack(en_guard,13,3);
	boxer.set_attack(falcon_punch,15,4);
	Enemy gym_champion("Gym Champion",NEUTRAL,3,3,3,3,2,30,15,15,15,3);
	gym_champion.set_growth(2,2,2,2,1,13,4,5);
	gym_champion.set_attack(restore,1,0);
	gym_champion.set_attack(falcon_punch,1,1);
	gym_champion.set_attack(tsunami,1,2);
	gym_champion.set_attack(lightning,1,3);
	gym_champion.set_attack(immolation_field,1,4);
	gym_champion.set_attack(flood,1,4);
	Enemy bar_fighter("Bar Fighter",NEUTRAL,7,10,0,2,1,30,10,13,10,1);
	bar_fighter.set_growth(2,1,1,1,1,10,5,4);
	bar_fighter.set_attack(punch,1,0);
	bar_fighter.set_attack(uppercut,1,1);
	bar_fighter.set_attack(war_dance,18,2);
	bar_fighter.set_attack(en_guard,18,3);
	Enemy tree("Tree",GRASS,1,1,3,3,1,50,5,10,9,0);
	tree.set_growth(1,1,2,2,1,13,4,0);
	tree.set_attack(fury_swipes,1,0);
	tree.set_attack(seed_attack,1,1);
	tree.set_attack(bullet_seed,8,1);
	tree.set_attack(overgrowth,10,2);
	tree.set_attack(growth,10,3);
	tree.set_attack(leech_seed,13,4);
	tree.set_attack(solarbeam,15,5);
	tree.set_attack(animate_plants,18,6);
	Enemy green_mage("Green Mage",GRASS,0,1,5,4,2,20,20,12,10,3);
	green_mage.set_growth(1,1,2,2,1,12,5,3);
	green_mage.set_attack(knife,1,0);
	green_mage.set_attack(seed_attack,1,1);
	green_mage.set_attack(bullet_seed,8,1);
	green_mage.set_attack(overgrowth,8,2);
	green_mage.set_attack(recover,10,3);
	green_mage.set_attack(water_blast,12,4);
	green_mage.set_attack(growth,15,5);
	green_mage.set_attack(solarbeam,15,1);
	green_mage.set_attack(restore,18,0);
	green_mage.set_attack(animate_plants,18,6);
	green_mage.set_attack(leech_seed,20,5);
	Enemy centaur("Centaur",EARTH,4,4,2,2,6,23,5,12,10,2);
	centaur.set_growth(2,1,1,1,1,11,3,2);
	centaur.set_attack(kick,1,0);
	centaur.set_attack(stampede,5,1);
	centaur.set_attack(rock_throw,5,2);
	centaur.set_attack(spark,5,3);
	centaur.set_attack(lightning,10,3);
	centaur.set_attack(rock_slide,13,2);
	centaur.set_attack(thunderstorm,15,4);
	centaur.set_attack(growth,17,5);
	centaur.set_attack(gust,24,6);
	Enemy boulder("Boulder",EARTH,4,10,1,2,1,40,2,11,3,2);
	boulder.set_growth(2,2,0,1,1,17,2,0);
	boulder.set_attack(rollout,1,0);
	boulder.set_attack(sand_attack,1,1);
	boulder.set_attack(sandstorm,10,2);
	boulder.set_attack(glass_shards,10,3);
	boulder.set_attack(earthquake,15,3);
	boulder.set_attack(meteor_smash,17,4);
	Enemy gnome("Gnome",EARTH,4,4,4,2,6,13,5,10,10,2);
	gnome.set_growth(1,1,1,1,1,11,3,2);
	gnome.set_attack(knife,1,0);
	gnome.set_attack(sand_attack,1,1);
	gnome.set_attack(rock_slide,8,2);
	gnome.set_attack(glass_shards,10,3);
	gnome.set_attack(spark,12,4);
	gnome.set_attack(earthquake,17,3);
	gnome.set_attack(meteor_smash,18,2);
	gnome.set_attack(gust,23,5);
	Enemy air_elemental("Air Elemental",AIR,2,2,5,5,16,20,10,13,7,4);
	air_elemental.set_growth(1,1,1,1,1,8,5,2);
	air_elemental.set_attack(punch,1,0);
	air_elemental.set_attack(wind_slash,1,1);
	air_elemental.set_attack(flying_strike,5,2);
	air_elemental.set_attack(gust,8,3);
	air_elemental.set_attack(cyclone,15,1);
	air_elemental.set_attack(aerial_ace,17,2);
	air_elemental.set_attack(sand_attack,17,4);
	air_elemental.set_attack(tornado,20,5);
	air_elemental.set_attack(corrosive_fumes,26,6);
	Enemy lava_golem("Lava Golem",FIRE,5,5,2,2,2,23,10,11,7,1);
	lava_golem.set_growth(2,2,1,1,1,9,4,2);
	lava_golem.set_attack(punch,1,0);
	lava_golem.set_attack(ember,1,1);
	lava_golem.set_attack(fire_punch,7,2);
	lava_golem.set_attack(meteor_smash,12,3);
	lava_golem.set_attack(bonfire,15,3);
	lava_golem.set_attack(restore,15,0);
	lava_golem.set_attack(flamethrower,15,1);
	lava_golem.set_attack(rock_slide,17,4);
	lava_golem.set_attack(falcon_punch,20,2);
	lava_golem.set_attack(immolation_field,20,5);
	lava_golem.set_attack(earthquake,22,4);
	Enemy phoenix("Phoenix",FIRE,3,3,5,5,2,18,10,13,4,3);
	phoenix.set_growth(2,2,2,2,1,8,4,2);
	phoenix.set_attack(flail,1,0);
	phoenix.set_attack(ember,1,1);
	phoenix.set_attack(fire_punch,7,2);
	phoenix.set_attack(gust,10,2);
	phoenix.set_attack(bonfire,15,3);
	phoenix.set_attack(flamethrower,15,1);
	phoenix.set_attack(aerial_ace,15,4);
	phoenix.set_attack(immolation_field,17,5);
	phoenix.set_attack(solar_flare,20,2);
	phoenix.set_attack(solarbeam,20,6);
	Beerman beerman;
	beerman.set_attack(punch,1,0);
	beerman.set_attack(flail,1,1);
	beerman.set_attack(drunken_fist,1,2);
	beerman.set_attack(purge,1,3);
	beerman.set_attacks_b(beer_throw);
	beerman.set_attacks_b(ember);
	beerman.set_attacks_b(rock_throw);
	beerman.set_attacks_b(acid);
	beerman.set_attacks_b(slow);
	beerman.set_attacks_b(growth);
	beerman.set_attacks_b(water_bomb);
	beerman.set_attacks_b(wind_slash);
	beerman.set_attacks_b(flying_strike);
	beerman.set_attacks_b(seed_attack);
	beerman.set_attacks_b(spark);
	beerman.set_attacks_b(lightning);
	beerman.set_attacks_b(bonfire);
	beerman.set_attacks_b(fire_punch);
	beerman.set_attacks_b(falcon_punch);
	beerman.set_attacks_b(fire_spin);
	beerman.set_attacks_b(flamethrower);
	beerman.set_attacks_b(flood);
	beerman.set_attacks_b(water_blast);
	beerman.set_attacks_b(tsunami);
	beerman.set_attacks_b(sandstorm);
	beerman.set_attacks_b(sand_attack);
	beerman.set_attacks_b(rock_slide);
	beerman.set_attacks_b(meteor_smash);
	beerman.set_attacks_b(glass_shards);
	beerman.set_attacks_b(tornado);
	beerman.set_attacks_b(aerial_ace);
	beerman.set_attacks_b(corrosive_fumes);
	beerman.set_attacks_b(cyclone);
	beerman.set_attacks_b(overgrowth);
	beerman.set_attacks_b(bullet_seed);
	beerman.set_attacks_b(leech_seed);
	beerman.set_attacks_b(animate_plants);
	beerman.set_attacks_b(recover);
	beerman.set_attacks_b(thunderstorm);
	beerman.set_attacks_b(explosion);
	beerman.set_attacks_b(acid_rain);
	beerman.set_attacks_b(war_dance);
	beerman.set_attacks_b(beer_missile);
	beerman.set_attacks_b(time_bomb);
	int show_combo_tutorial=1;
	//Start game
	cout<<"<<<Press enter to begin the game>>>\n";
	pause();
	{
		int choice=0;
		do{
			choice=menu(2,"New Game","Load Game");
		} while (choice<1 || choice>2);
		if (choice==2)
		{
			//Load save file
			ifstream in_file;
			in_file.open("save.dat",ios::in);
			if (in_file.fail())
			{
				cerr<<"Error opening save file. Aborting program...";
				pause();
				exit(10);
			}
			in_file>>beerman;
			in_file>>mission_number;
			for (int i=0;i<12;i++)
				in_file>>inventory[i];
			in_file>>area;
			in_file>>show_combo_tutorial;
			for (int i=0;i<6;i++)
				in_file>>high_score[i];
			in_file.ignore();
			getline(in_file,mission);
			in_file.close();
			cout<<"Game loaded.\n";
			pause();
			if (mission_number==18){
				system("CLS");
				cout<<"Congratulations! You finished Beer Man II: The Return!\n"
					<<"Now you can go fight in the Arena in Grass Town to test your skills!\n"
					<<"You can also do a rematch with the Milk Man, if you wish.\n";
				pause();
			}
		}
		if (choice==1)
			chapter_1_init(mission_number,mission);
	}
	while (1)
	{
		if (area==0)	//If in Austria
		{
			if (mission_number==0)
			{
				cout<<"Beer Man: Get back here, you wallet stealing scoundrel!";
				pause();
				int win=0;
				while (!win){
					win=battle_init(inventory,beerman,thief,2,0,0);
					if (!win)
					{
						cout<<"Beer Man: Dang, this guy is tough! Let's try again.";
						beerman.change_hp(-beerman.change_hp(0)+beerman.hp_max());
						pause();
					}
				}
				cout<<"Thief: We may have lost this round, Beer Man, but we will prevail over you!\n";
				pause();
				cout<<"Beer Man: Wow I fail. I really must have been lazy. Also, I'm sober.\nThat is bad.\n"
					<<"I need to go to get some beer and some training at the local gym.\n";
				mission="Mission: Train until you reach Level 5.";
				mission_number++;
				pause();
				cout<<mission<<endl;
				pause();
				cout<<"...\n";
				pause();
				cout<<"Beer Man: By the way, who was that guy? It looked like he knew me...\n";
				pause();
			}
			do
			{
				system("CLS");
				//Austria
				if (beerman.get_lvl()>4 && mission_number==1)
				{
					cout<<"Beer Man: Alright, I think I'm prepared now to go outside.\n";
					pause();
					mission="Mission: Search for information outside.";
					cout<<mission;
					pause();
					mission_number=2;
				}
				cout<<"Austria\n-------"<<endl;
				choice=menu(7,"Go to the Town","Go outside","Check stats","Check Mission","Encyclopedia","Save","Quit");
				switch (choice)
				{
				case 1:
					area=1;
					break;
				case 2:
					if (mission_number==1)
					{
						cout<<"Beer Man: Hey, hey, I might be stupid but I'm not so dumb as to\ngo out as weak as I am right now. Get me to level 5 before\nexploring, alright?";
						pause();
						break;
					}
					area=2;
					break;
				case 3:
					beerman.display_stats();
					cout<<"\n\nMoney: "<<inventory[0];
					pause();
					system("CLS");
					show_inventory(inventory);
					break;
				case 4:
					cout<<mission;
					pause();
					break;
				case 5:
					beerman.encyclopedia();
					pause();
					break;
				case 6:
					save(beerman,inventory,mission_number,mission,0,show_combo_tutorial,high_score);
					break;
				case 7:
					{
					// Create save file
					save(beerman,inventory,mission_number,mission,0,show_combo_tutorial,high_score);
					exit(1);
					break;
					}
				}
				system("CLS");
			} while (choice>2);
		}
		if (area==1)	//If in Austrian Town
		{
			do
			{
				//Austrian Town
				cout<<"Austrian Town\n-------------"<<endl;
				choice=menu(7,"Bar","Gym","Inn","NPC","Playground","Shop","Back");
				system("CLS");
				switch (choice)
				{
				case 1:
					bar(inventory,beerman,bar_fighter);
					break;
				case 2:
					gym(inventory,beerman,punching_bag,gym_member,boxer,gym_champion,pikachu);
					break;
				case 3:
					cout<<"The Sleeping Dog Inn: Welcome! You may sleep here for only $2, but\nyour BAC will drop to 0.00.\n";
					choice=menu(2,"Sleep: $2","Back");
					if (choice==1 && inventory[0]>1)
					{
						cout<<"Beer Man: Something tells me that this was not a good idea.\n";
						pause();
						inventory[0]-=2;
						beerman.change_hp(beerman.hp_max());
						beerman.change_bac(-beerman.change_bac(0));
						cout<<"Beer Man: ugh... headache... need... beer...\n";
						pause();
						cout<<"Inn Owner: We sell the original Hair of the Dog Remedy for hangovers\nfor just $1! Want some?\n";
						choice=menu(2,"Sure","...I'll just go to the bar");
						if (choice==1){
							if (inventory[0]>0){
								inventory[0]--;
								cout<<"Beer Man received a small brown hair.\n";
								pause();
								cout<<"Beer Man: ...Did I just get ripped off?\n";
							}else
								cout<<"You don't have any money!\n";
							pause();
						}
					}
					break;
				case 4:
					if (mission_number<3){
						cout<<"NPC: You're exploring the area? Well let me give you some quick advice.\n"
							<<"The Alps and the Bohemian Forest used to be great tourist spots, but recently\n"
							<<"have turned extremely dangerous. I'd suggest you avoid those areas until you\n"
							<<"can handle it.";}
					else{
						int n=randint(1,12);
						if (n==1)
							cout<<"Drunk Guy: Hey, evr wundered why yer combos dun always work? Well that's\n"
								<<"cuz yer not drunk enuf to think of the idea, that's why!\nAlways stay as drunk as possible!\n"
								<<"Jus make shur you dun drink too much, cuz you could black out.\n";
						if (n==2)
							cout<<"NPC: Be careful on the Alps. It's a long journey up and down.\n";
						if (n==3)
							cout<<"NPC: Field Effects can severely change the state of battle. For example,\nOvergrowth "
								<<"heals all GRASS types each round and increases GRASS type damage\nby 50%.\n";
						if (n==4)
							cout<<"Scientist: Lightning always strikes the tallest object in the area.\n"
								<<"Therefore, since you are pretty tall, using Batteries will likely result\n"
								<<"in you getting struck.\n";
						if (n==5)
							cout<<"NPC: The element of the attack and the enemy must always be considered.\n"
								<<"Supereffetive moves do 2x the damage, and ineffective moves do 1/2 damage.\n";
						if (n==6)
							cout<<"NPC: Learn to utilize combos correctly, and sometimes you will be able to 1-hit KO the opponent!\n";
						if (n==7)
							cout<<"Cryptic Old Man: Rocks, Acids, and Electric Fans are pretty useful items.\n";
						if (n==8)
							cout<<"Drunkard: Don't like the taste of water? Spit it out!\n";
						if (n==9)
							cout<<"Cryptic Old Man: Flailing your arms around in certain environments\ncan create interesting effects.\n";
						if (n==10)
							cout<<"Fighter: Know your element. It can allow or disallow you from using\ncertain combos.";
						if (n==11)
							cout<<"NPC: Many attacks that the enemies use you can use as well.\n";
						if (n==12)
							cout<<"NPC: The Gym is a good place to look for new combos. Keep your BAC\n"
								<<"high as well, preferably above .2, to make sure you're not missing any!\n";
					}
					pause();
					break;
				case 5:
					playground(inventory,beerman,boy,girl,policeman);
					break;
				case 6:
					shop(inventory,show_combo_tutorial);
					break;
				case 7:
					area=0;
					break;
				}
				system("CLS");
			} while (choice>2 && choice!=7);
		}
		if (area==2)	//Outside Austria
		{
			do
			{
				cout<<"Austrian Wilderness\n-------------------"<<endl;
				choice=menu(5,"Danube River","Bohemian Forest","The Alps","Airport","Return to civilization");
				system("CLS");
				int x=0,y=0,win=1,area2=0,forward=1,leave;
				switch (choice)
				{
				case 1:
					area2=1;
					do{
						if (area2==1)
						{
							if (forward){x=0;y=0;}
							if (!forward){x=2;y=2;}
							do
							{
								int number=randint(0,2);
								leave=dungeon("Danube River",2,2,0,0,2,2,x,y);
								if (number==2 && leave!=-1){
									cout<<"You see nothing interesting. Just a bunch of cows, seagulls... and no beer.\n";
									pause();
								}
								if (!number && leave)
								{
									int number2=randint(0,3);
									switch (number2)
									{
									case 0:
										win=battle_init(inventory,beerman,mage,randint(3,5),0,1);
										break;
									case 1:
										win=battle_init(inventory,beerman,thief,randint(3,4),0,1);
										break;
									case 2:
										win=battle_init(inventory,beerman,cow,randint(3,5),0,1);
										break;
									case 3:
										win=battle_init(inventory,beerman,seagull,randint(3,5),0,1);
										break;
									}
								}
								if (!win)
									break;
								number=randint(0,2);
								if (!number)
								{
									cout<<"There is a small rock here. Pick it up?\n";
									if (menu(2,"Yes","No")==1)
									{
										inventory[4]++;
										cout<<"DANANANAAAA!!!\n";
										pause();
										cout<<"Beer Man: I got a rock!\n";
										pause();
									}
								}
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1)
								area2=0;
							if (leave==0)
								area2=2;
							if (leave==0 && mission_number==2)
							{
								cout<<"Whilst walking further along the Danube River, Beer Man spotted someone\nsurrounded by cows.\n";
								pause();
								cout<<"Beer Man: You look rather familiar...\n";
								pause();
								cout<<"Cow Boy: ...\n";
								pause();
								cout<<"Beer Man: Wait, you look like that one guy back in the URF, the Milk Man!\nThat must mean that you hate beer! GRAAAHHH!";
								pause();
								win=battle_init(inventory,beerman,cow_boy,5,1,0);
								if (!win)
									break;
								cout<<"Cow Boy: Ugh... how did you... You will never find the Neo-temperance HQ!\n";
								pause();
								cout<<"Beer Man: The Neo-temperance HQ...! Can't let that thing exist!\nThis looks like a job for Beerman!\n";
								pause();
								mission_number=3;
								mission="Mission: Look for the Neo-temperance HQ.";
								cout<<mission;
								pause();
								area2=2;
							}
							if (!win)
								break;
							forward=leave+1;
						}
						if (area2==2)
						{
							if (forward){x=1;y=0;}
							if (!forward){x=2;y=2;}
							do
							{
								leave=dungeon("Inner River",2,2,1,0,2,2,x,y);
								int number=randint(0,5);
								if (leave){
									switch (number)
									{
									case 0:
										win=battle_init(inventory,beerman,mage,randint(4,7),0,1);
										break;
									case 1:
										win=battle_init(inventory,beerman,thief,randint(4,6),0,1);
										break;
									case 2:
										win=battle_init(inventory,beerman,cow,randint(5,7),0,1);
										break;
									case 3:
										win=battle_init(inventory,beerman,seagull,randint(4,7),0,1);
										break;
									default:
										break;
									}
								}
								if (!win)
									break;
								number=randint(0,2);
								if (!number)
								{
									cout<<"There is a small rock here. Pick it up?\n";
									if (menu(2,"Yes","No")==1)
									{
										inventory[4]++;
										cout<<"DANANANAAAA!!!\n";
										pause();
										cout<<"Beer Man: I got a rock!\n";
										pause();
									}
								}
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1){
								area2=1;}
							if (leave==0 && mission_number==3){
								cout<<"Soon, a medium-sized building appears.\n";
								pause();
								cout<<"Beer Man: Aha! I win!\n";
								pause();
								cout<<"Beer Man: Wait, who is that coming out?\n";
								pause();
								cout<<"Beer Man: Is it a bird?\n";
								pause();
								cout<<"Beer Man: A plane?\n";
								pause();
								cout<<"Beer Man: No, it\'s Arnold Schwarzenegger!\n";
								pause();
								cout<<"Beer Man: Wait, what? That\'s not right. Whoa, he\'s carrying important-looking\nfiles and diagrams and stuff. Time to go beat him up.\n";
								pause();
								cout<<"Beer Man: Hey, wait a sec, he\'s not supposed to go into that\nspiffy-looking sports car!\n";
								pause();
								cout<<"Beer Man: Wait, how did I miss that? Wait, what? Wait, I gotta stop saying that, huh?\n";
								pause();
								cout<<"The sports car revs up and leaves Beer Man in the dust at 500 mph.\n";
								pause();
								cout<<"Beer Man: Looks like he\'s heading into the Forest.\n";
								pause();
								mission_number=4;
								mission="Mission: Get the files from Arnold Schwarzenegger.";
								cout<<mission<<endl;
								pause();
								cout<<"Beer Man: But first, let\'s try that door.\n";
								pause();
							}
							if (leave==0 && mission_number>5){
								cout<<"Beer Man enters the HQ Building. Inside is a simple, large, square room with\ngray walls, desks, papers, and used water bottles everywhere.\nIn the center of the room is a computer.\n";
								pause();
								if (mission_number==6){
									cout<<"Beer Man: Huh? There's noone here.\n";
									pause();
									cout<<"Beer Man: I must of scared them all away with my uber powers! WOOO! *hic*\n";
									pause();
								}
								area2=3;
							}
							forward=leave+1;
							if (leave==0 && mission_number<6){
								cout<<"Beer Man: ...? The door\'s locked. Guess I\'ll have to go back.\n";
								pause();
								forward=0;
							}
						}
						if (area2==3)
						{
							if (forward){x=2;y=0;}
							do
							{
								leave=dungeon("Neo-temperance HQ",4,4,2,0,5,5,x,y);	//There is no exit
								neo_hq_description(x,y,mission_number,mission);
								int number=randint(0,2);
								if (!number)
								{
									cout<<"There is a Water Bottle here. Pick it up?\n";
									if (menu(2,"Yes","No")==1)
									{
										inventory[8]++;
										cout<<"Beer Man obtained a Water Bottle!\n...It looks like it was used.\n";
										pause();
									}
								}
								if (leave==-1)
									area2=2;
								forward=leave+1;
							} while (leave>0);
						}
					} while (area2>0);
					break;
				case 2:
					area2=1;
					do{
						if (area2==1)
						{
							if (forward){x=0;y=0;}
							if (!forward){x=4;y=2;}
							do
							{
								leave=dungeon("Bohemian Forest",4,4,0,0,4,2,x,y);
								int number=randint(0,2);
								if (!number && leave)
								{
									int number2=randint(0,2);
									switch (number2)
									{
									case 0:
										win=battle_init(inventory,beerman,mage,randint(7,9),0,1);
										break;
									case 1:
										win=battle_init(inventory,beerman,thief,randint(6,8),0,1);
										break;
									case 2:
										win=battle_init(inventory,beerman,tree,randint(7,10),0,1);
										break;
									}
								}
								if (!win)
									break;
								number=randint(0,2);
								if (!number)
								{
									cout<<"There is a small seed here. Pick it up?\n";
									if (menu(2,"Yes","No")==1)
									{
										inventory[10]++;
										cout<<"DANANANAAAA!!! Beer Man obtained the seed!\n";
										pause();
									}
								}
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1)
								area2=0;
							if (leave==0)
								area2=2;
							if (leave==0 && mission_number==4)
							{
								cout<<"Beer Man: Ugh... Stupid forest is so BIG! Where is that guy, anyway?\n";
								pause();
								cout<<"Beer Man: ... hey there\'s the sports car. He must be close.\n";
								pause();
								area2=2;
							}
							forward=leave+1;
						}
						if (area2==2)
						{
							if (forward){x=0;y=1;}
							if (!forward){x=4;y=3;}
							do
							{
								lost_woods_description(x,y);
								leave=dungeon("Lost Woods",5,5,0,1,4,3,x,y);
								int number=randint(0,7);
								switch (number)
								{
								case 0:
									win=battle_init(inventory,beerman,mage,randint(9,12),1,1);
									break;
								case 1:
									win=battle_init(inventory,beerman,tree,randint(10,12),1,1);
									break;
								case 2:
									win=battle_init(inventory,beerman,centaur,randint(7,10),1,1);
									break;
								case 3:
									win=battle_init(inventory,beerman,water_mage,randint(9,12),1,1);
									break;
								case 4:
									win=battle_init(inventory,beerman,green_mage,randint(9,12),1,1);
									break;
								default:
									break;
								}
								if (!win)
									break;
								number=randint(0,3);
								if (!number)
								{
									cout<<"There is a small seed here. Pick it up?\n";
									if (menu(2,"Yes","No")==1)
									{
										inventory[10]++;
										cout<<"DANANANAAAA!!! Beer Man obtained the seed!\n";
										pause();
									}
								}
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1){
								area2=1;}
							if (leave==0 && mission_number==4){
								cout<<"Beer Man walks into a clearing.\n";
								pause();
								cout<<"Beer Man: There you are! Hand over the... uh... important-looking paper things.\nAnd maybe the car keys too.\n";
								pause();
								cout<<"Arnold: ...So you are the one they call Beer Man. Let\'s see how\nwell a drunken idiot can do against the Terminator.\n";
								pause();
								win=battle_init(inventory,beerman,arnold,11,2,0);
								if (!win)
									break;
								cout<<"Arnold: Ugh... how... could such a fumbling joke of a human beat\nme? The Terminator...!\n";
								pause();
								cout<<"Beer Man: Wasn\'t able to terminate me, old sport? I\'ll just take\nthese now...\n";
								pause();
								cout<<"Beer Man obtained the blueprints!\n";
								pause();
								cout<<"Beer Man: I think they\'re trying to revive some guy named Antonio\nSalieri into a lich. Somehow. Maybe I\'m supposed to stop this?\n";
								pause();
								mission_number=5;
								mission="Mission: Stop the necromancers on the Alps from reviving Antonio Salieri.";
								cout<<mission<<endl;
								pause();
								leave=-1;
							}
							forward=leave+1;
						}
					} while (area2>0);
					break;
				case 3:
					area2=1;
					do{
						if (area2==1)
						{
							if (forward){x=0;y=0;}
							if (!forward){x=0;y=10;}
							do
							{
								leave=dungeon("The Alps",0,10,0,0,0,10,x,y);
								int number=randint(0,4);
								if (number<2 && leave)
								{
									int number2=randint(0,3);
									switch (number2)
									{
									case 0:
										win=battle_init(inventory,beerman,boulder,randint(floor(x*.25)+11,floor(x*.25)+14),0,1);
										break;
									case 1:
										win=battle_init(inventory,beerman,gnome,randint(floor(x*.25)+10,floor(x*.25)+12),1,1);
										break;
									case 2:
										win=battle_init(inventory,beerman,lava_golem,randint(floor(x*.25)+10,floor(x*.25)+12),1,1);
										break;
									case 3:
										win=battle_init(inventory,beerman,centaur,randint(floor(x*.25)+10,floor(x*.25)+13),1,1);
										break;
									}
								}
								if (!win)
									break;
								number=randint(0,4);
								if (!number)
								{
									cout<<"There is a small rock here. Pick it up?\n";
									if (menu(2,"Yes","No")==1)
									{
										inventory[4]++;
										cout<<"DANANANAAAA!!!\n";
										pause();
										cout<<"Beer Man: I got a rock!\n";
										pause();
									}
								}
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1)
								area2=0;
							if (leave==0)
								area2=2;
							if (leave==0 && mission_number==5)
							{
								cout<<"Beer Man: *Pant...pant...pant*\n";
								pause();
								cout<<"Beer Man: Tall Tall Mountain! *hic*\n...I'm tired.";
								pause();
								area2=2;
							}
							forward=leave+1;
						}
						if (area2==2)
						{
							if (forward){x=0;y=0;}
							if (!forward){x=0;y=3;}
							do
							{
								leave=dungeon("Peak",0,3,0,0,0,3,x,y);
								int number=randint(0,7);
								switch (number)
								{
								case 0:
									win=battle_init(inventory,beerman,lava_golem,randint(12,15),1,1);
									break;
								case 1:
									win=battle_init(inventory,beerman,air_elemental,randint(12,14),1,1);
									break;
								case 2:
									win=battle_init(inventory,beerman,centaur,randint(12,15),1,1);
									break;
								case 3:
									win=battle_init(inventory,beerman,gnome,randint(13,15),1,1);
									break;
								case 4:
									win=battle_init(inventory,beerman,mage,randint(13,16),1,1);
									break;
								default:
									break;
								}
								if (!win)
									break;
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1){
								area2=1;}
							if (leave==0 && mission_number==5){
								cout<<"Near the mountain's peak, Beer Man notices a strange laboratory.\n";
								pause();
								cout<<"Beer Man: Ooohh what's in here?\n";
								pause();
								cout<<"*tweet**tweet**tweet*!\n";
								pause();
								cout<<"Guards: Keep him away from Salieri! He's not yet finished the\nsoul-binding process!\n";
								pause();
								cout<<"Beer Man: ...wuzz going on?\n";
								pause();
								win=battle_init(inventory,beerman,policeman,12,1,0);
								if (!win)
									break;
								cout<<"While Beer Man was fighting the guards, several others managed to block the\nentrance with a gigantic boulder.\n";
								pause();
								win=battle_init(inventory,beerman,boulder,17,1,0);
								if (!win)
									break;
								cout<<"Beer Man: ...HA! That's all? I've faced harder rocks than that! *hic*\n";
								pause();
								cout<<"Salieri: I AM REVIVED!!!!!111\nDEATH TO ALL WHO STAND AGAINST THE TEMPERANCE MOVEMENT!\n";
								pause();
								win=battle_init(inventory,beerman,salieri,17,2,0);
								if (!win)
									break;
								cout<<"Beer Man: That was the worst marathon battle I ever had... EVER!\n";
								pause();
								cout<<"Beer Man: Hey, there's a key to the Neo-Temperance HQ here!\n";
								pause();
								cout<<"DANANANAAAA!!!! Looks like Beer Man found a key!\n";
								pause();
								cout<<"Beer Man: Woooo! I gots the key!\nToo bad it\'s not the one to the sports car.\n";
								pause();
								mission_number=6;
								mission="Mission: Remove the Neo-Temperance movement from the face of the earth.";
								cout<<mission<<endl;
								pause();
								leave=-1;
							}
							forward=leave+1;
						}
					} while (area2>0);
					break;
				case 4:
					if (mission_number<7){
					cout<<"Beer Man: Hey, I\'m not finished with Austria yet!";
					pause();}
					else
					{
						cout<<"The airplane fare is $20.\n";
						if (mission_number>7){
							if (inventory[0]>=20){
								int choice;
								choice=menu(3,"Libeerty City","Grass Town","Cancel");
								if (choice==1){
									area=3;
									inventory[0]-=20;
									cout<<"Beer Man flew to Libeerty City.\n";}
								if (choice==2){
									area=6;
									inventory[0]-=20;
									cout<<"Beer Man flew to Grass Town.\n";}
								if (choice>2 || choice<1)
									break;
							}
							else
								cout<<"Unfortunately, you're broke.\n";
							pause();
						}
						if (mission_number==7)
							chapter_2_init(mission_number,mission,area);
					}
					break;
				case 5:
					area=0;
					break;
				default:
					break;
				}
				if (!win){
					blackout(inventory,beerman);
					win=1;}
				system("CLS");
			} while (choice<5 && area==2);
		}
		if (area==3)	//If in Libeerty City
		{
			do
			{
				system("CLS");
				//Libeerty City
				cout<<"Libeerty City\n-------------\n";
				choice=menu(7,"Go downtown","Go outside","Check stats","Check Mission","Encyclopedia","Save","Quit");
				switch (choice)
				{
				case 1:
					area=4;
					break;
				case 2:
					area=5;
					break;
				case 3:
					beerman.display_stats();
					cout<<"\n\nMoney: "<<inventory[0];
					pause();
					system("CLS");
					show_inventory(inventory);
					break;
				case 4:
					cout<<mission;
					pause();
					break;
				case 5:
					beerman.encyclopedia();
					pause();
					break;
				case 6:
					save(beerman,inventory,mission_number,mission,3,show_combo_tutorial,high_score);
					break;
				case 7:
					save(beerman,inventory,mission_number,mission,3,show_combo_tutorial,high_score);
					exit(1);
					break;
				}
				system("CLS");
			} while (choice>2);
		}
		if (area==4)	//If in Libeerty City downtown
		{
			do
			{
				//Libeerty City downtown
				cout<<"Libeerty City Downtown\n----------------------"<<endl;
				choice=menu(8,"Bar","Gym","Inn","NPC","City Hall","Shop","Apartments","Back");
				system("CLS");
				switch (choice)
				{
				case 1:
					bar(inventory,beerman,bar_fighter);
					break;
				case 2:
					gym(inventory,beerman,punching_bag,gym_member,boxer,gym_champion,pikachu);
					break;
				case 3:
					cout<<"The Sleeping Dog Inn: Welcome! You may sleep here for only $2, but\nyour BAC will drop to 0.00.\n";
					choice=menu(2,"Sleep: $2","Back");
					if (choice==1 && inventory[0]>1)
					{
						cout<<"Beer Man: Something tells me that this was not a good idea.\n";
						pause();
						inventory[0]-=2;
						beerman.change_hp(beerman.hp_max());
						beerman.change_bac(-beerman.change_bac(0));
						cout<<"Beer Man: ugh... headache... need... beer...\n";
						pause();
						cout<<"Inn Owner: We sell the original Hair of the Dog Remedy for hangovers\nfor just $1! Want some?\n";
						choice=menu(2,"Sure","...I'll just go to the bar");
						if (choice==1){
							if (inventory[0]>0){
								inventory[0]--;
								cout<<"Beer Man received a small brown hair.\n";
								pause();
								cout<<"Beer Man: ...Did I just get ripped off?\n";
							}else
								cout<<"You don't have any money!\n";
							pause();
						}
					}
					break;
				case 4:
					{
						int i=randint(1,11);
						if (i==1){
							if (mission_number<=13)	//MISSION NUMBER WHATEVER IT IS AT START OF CH 3
								cout<<"NPC: Remember, Beer Man, that you must always report back\nto the Beer Council to receive your next mission!\n";
							else
								cout<<"NPC: I guess telling the government of your progress was\nnot such a great idea.\n";
						}
						if (i==2)
							cout<<"Drunkard: Plants like getting drunk too! See? *holds up dead plant*\n";
						if (i==3)
							cout<<"Pyro: Flamethrowers are hard to come by these days... Maybe we\nshould just improvise one. Could work.\n";
						if (i==4)
							cout<<"Big Bulky Slow Guy: Stupid air elementals! Tornado makes them too fast!\n";
						if (i==5)
							cout<<"Weather Man: Dang it! People using Acid Rain are going to drive me\nout of business!\n";
						if (i==6)
							cout<<"RPG Player: Improvised Weapons give you an Attack bonus!\n";
						if (i==7)
							cout<<"NPC: Hey, I wonder if Beer can be propelled as a missile.\n";
						if (i==8)
							cout<<"Pyro: Remember, you need to fan the flame to make a bonfire!\n";
						if (i==9)
							cout<<"Tavern Owner: Beer can help mitigate status effects!\n";
						if (i==10)
							cout<<"Mage: Thunderstorms are only useful in long, extended battles.\nBut then they destroy everything, unless the opponent is EARTH type.\n";
						if (i==11)
							cout<<"Swimmer: I love flailing around in the water! Splash Attack!\n";
					pause();
					}
					break;
				case 5:
					if (city_hall(inventory,beerman,carrie_nation,elliot,mission_number,mission)){
						int area2=1,forward=1,x=0,y=0,win=1,leave;
						do{
							if (area2==1)
							{
								if (forward){x=1;y=0;}
								if (!forward){x=1;y=10;}
								do
								{
									leave=dungeon("The Government Hall",2,7,1,0,1,7,x,y);
									int number=randint(0,4);
									if (number<2 && leave)
									{
										int number2=randint(0,2);
										switch (number2)
										{
										case 0:
											win=battle_init(inventory,beerman,policeman,randint(27,30),2,1);
											break;
										case 1:
											win=battle_init(inventory,beerman,lawyer,randint(27,30),2,1);
											break;
										case 2:
											win=battle_init(inventory,beerman,gym_champion,randint(27,30),2,1);
											break;
										}
									}
									if (!win)
										break;
								} while (leave>0);
								if (!win)
									break;
								if (leave==-1)
									area2=0;
								if (leave==0)
									area2=2;
								if (leave==0 && mission_number==14)
								{
									cout<<"Beer Man: Ahead should be the Meeting Room... Elliot should be there.\n";
									pause();
									cout<<"As Beer Man enters, he sees two people discussing things in low whispers.\n"
										<<"One of them them notices Beer Man, whispers something to the other, and\ndisappears. "
										<<"The other swivels his chair around.\n";
									pause();
									cout<<"Sir Elliot: Well, well, well. Now look who we have here! So glad for you to\n"
										<<"join me again, Beer Man! Would you like some water?\n";
									pause();
									cout<<"Beer Man: No way! You are going down, you water-drinking traitor!\n";
									pause();
									win=battle_init(inventory,beerman,elliot,30,3,0);
									if (!win){
										cout<<"Sir Elliot: You fool. Our mega-weapon is already complete, ready to be\n"
											<<"unleashed on all the world. You are nothing, powerless to stop us! Now,\n"
											<<"if you'll excuse me, I'll continue my discussion with the boss.\n";
										pause();
										break;
									}
									cout<<"Sir Elliot: *pant* ...well good job. But even if you defeated me, you cannot\n"
										<<"win against all of us! You will never succeed!\n";
									pause();
									cout<<"Beer Man: ...yeah right.\n";
									pause();
									mission_number=15;
									area2=2;
								}
								forward=leave+1;
							}
							if (area2==2)
							{
								if (mission_number==15){
									cout<<"Beer Man: Hmm...my beer senses are tingling. Better be prepared.\n";
									pause();
								}
								if (forward){x=0;y=0;}
								if (!forward){x=0;y=3;}
								do
								{
									leave=dungeon("The Meeting Room",0,3,0,0,0,3,x,y);
								} while (leave>0);
								if (leave==-1){
									area2=1;}
								if (leave==0 && mission_number>=15){
									if (mission_number==16)
									{
										cout<<"As Beer Man enters the Oval Office, The Eraser looks up.\n";
										pause();
										cout<<"The Eraser: You're back.\n";
										pause();
										cout<<"Beer Man: And more powerful than ever before! Die you!\n";
										pause();
									}
									if (mission_number==15){
										cout<<"Beer Man enters the Oval Office. Inside is a shadowy figure.\n";
										pause();
										cout<<"???: ...Beer Man. Do you remember when we last fought?\n";
										pause();
										cout<<"Beer Man: ...who are you?\n";
										pause();
										cout<<"???: Surprising. Well, you were always the stupid one, only doing anything\n"
											<<"of note accidentally without you actually trying. I implore you, guess.\n";
										pause();
										cout<<"Beer Man: !!!\n";
										pause();
										cout<<"Beer Man: You're...the Eraser!\n";
										pause();
										cout<<"The Eraser: That's right. You defeated me last time only because I was not\n"
											<<"well informed or prepared. This time, however, with the City Beer Council\n"
											<<"giving me much information on your abilities, and with the rest of the plans\n"
											<<"already in motion, your precious beer alcoholism is doomed to die.\n";
										pause();
										cout<<"Beer Man: No. You just suck at doing stuff.\n";
										pause();
										mission_number=16;
									}
									if (mission_number<17){
										win=battle_init(inventory,beerman,eraser,31,3,0);
										if (!win)
											break;
									}
									if (mission_number==18){
										cout<<"As Beer Man reenters the Oval Office, the Milk Man reappears!\n";
										pause();
										cout<<"The Milk Man: MWA HA HA! You have not defeated me, and you never will!\n";
										pause();
										cout<<"The mecha reappears, newly restored and ready to fight.\n";
										pause();
									}
									if (mission_number==17){
										cout<<"The Milk Man: ...Huh? You're not dead? Well, let's try this again.\n";
										pause();
										cout<<"The mecha reappears, newly restored and ready to fight.\n";
										pause();
									}
									if (mission_number==16){
										cout<<"The Eraser: ...\n";
										pause();
										cout<<"Beer Man: That's right! Stay down!\n";
										pause();
										cout<<"*clap*";
										pause();
										cout<<"*clap*";
										pause();
										cout<<"*clap*\n";
										pause();
										cout<<"Another shadowy figure appears.\n";
										pause();
										cout<<"???: Congratulations, Beer Man.\n";
										pause();
										cout<<"Beer Man: Who?\n";
										pause();
										cout<<"???: Heh. Let's jog your memory, shall we? The last time we fought, I was\n"
											<<"a mere casualty. A thing forgotten to lie on the side of the street as you"
											<<"continued your journey. It is I...";
										pause();
										cout<<"THE MILK MAN!\n";
										pause();
										cout<<"Beer Man: WHAAAAAAAAAAAAAT!\n";
										pause();
										cout<<"The Milk Man: That's right, Beer Man. That puny insect is now the puppeteer\n"
											<<"behind the scenes, pulling the strings of the government to destroy you and\n"
											<<"that disgusting liquid you call beer! And now, in this final battle, you\n"
											<<"SHALL be destroyed, and beer SHALL be eradicated, and I WILL RULE THE WORLD!\n";
										pause();
										cout<<"Beer Man: You are a dead man.\n";
										pause();
										cout<<"The Milk Man: Heh. Well try your best... against this super mecha!\n";
										pause();
										mission_number=17;
										mission="Mission: Destroy the Milk Man.";
									}
									win=battle_init(inventory,beerman,mecha,32,3,0);
									if (!win)
										break;
									cout<<"The mecha shorts itself, forcing the Milk Man to come fight Beer Man\n"
										<<"without the aid of his fancy machinery.\n";
									pause();
									win=battle_init(inventory,beerman,milk_man,32,3,0);
									if (!win)
										break;
									cout<<"The Milk Man: NOOOOOOOOOOOOOOO!\n";
									pause();
									cout<<"As the Milk Man falls down, defeated, Beer Man starts breakdancing in\ncelebration.\n";
									pause();
									cout<<"*clap*";
									pause();
									cout<<"*clap*";
									pause();
									cout<<"*clap*\n";
									pause();
									cout<<"Beer Man: Oh God please no.\n";
									pause();
									cout<<"Random NPC Mob: Hoooray!!!! Yay for Beer Man!!!\n";
									pause();
									cout<<"Beer Man: Oh never mind, this is awesome!\n";
									pause();
									cout<<"Beer Man went on to become Libeerty City's mayor again, and reinstated the\nformer "
										<<"glory of the Beer Council. With the full routing of the Temperance\nMovement, finally "
										<<"Beer Man can relax and drink beer in peace. For now.\n";
									pause();
									cout<<"THE END\n";
									mission_number=18;
									mission="Mission Accomplished! You may rematch the Milk Man or try the Arena!";
									save(beerman,inventory,mission_number,mission,3,show_combo_tutorial,high_score);
									pause();
									exit(2);
								}
								forward=leave+1;
							}
						} while (area2>0);
						if (!win){
							blackout(inventory,beerman);
							win=1;
						}
					}
					break;
				case 6:
					shop(inventory,show_combo_tutorial);
					break;
				case 7:
					apartment(inventory,beerman,mudkipz,policeman,mission_number);
					break;
				case 8:
					area=3;
					break;
				}
				system("CLS");
			} while (choice>2 && choice!=8);
		}
		if (area==5)	//Outside Libeerty City
		{
			do
			{
				cout<<"Outside Libeerty City\n---------------------"<<endl;
				choice=menu(5,"Neutral Grounds","The Volcano","Former Temperance HQ","Airport","Return to civilization");
				system("CLS");
				int x=0,y=0,win=1,area2=0,forward=1,leave;
				switch (choice)
				{
				case 1:
					area2=1;
					do{
						if (area2==1)
						{
							if (forward){x=0;y=0;}
							if (!forward){x=6;y=6;}
							do
							{
								int number=randint(0,2);
								leave=dungeon("Neutral Grounds",5,5,0,0,6,6,x,y);
								if (!number && leave)
								{
									int number2=randint(0,3);
									switch (number2)
									{
									case 0:
										win=battle_init(inventory,beerman,centaur,randint(16,18),1,1);
										break;
									case 1:
										win=battle_init(inventory,beerman,air_elemental,randint(16,18),1,1);
										break;
									case 2:
										win=battle_init(inventory,beerman,cow,randint(16,18),0,1);
										break;
									case 3:
										win=battle_init(inventory,beerman,seagull,randint(16,18),1,1);
										break;
									}
								}
								if (!win)
									break;
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1)
								area2=0;
						}
					} while (area2>0);
					break;
				case 2:
					area2=1;
					do{
						if (area2==1)
						{
							if (forward){x=1;y=0;}
							if (!forward){x=1;y=5;}
							do
							{
								leave=dungeon("The Volcano",2,5,1,0,1,5,x,y);
								int number=randint(0,2);
								if (!number && leave)
								{
									int number2=randint(0,3);
									switch (number2)
									{
									case 0:
										win=battle_init(inventory,beerman,phoenix,randint(17,20),2,1);
										break;
									case 1:
										win=battle_init(inventory,beerman,gnome,randint(18,21),1,1);
										break;
									case 2:
										win=battle_init(inventory,beerman,boulder,randint(18,22),0,1);
										break;
									case 3:
										win=battle_init(inventory,beerman,lava_golem,randint(17,20),1,1);
										break;
									}
								}
								if (!win)
									break;
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1)
								area2=0;
							if (leave==0)
								area2=2;
							if (leave==0 && mission_number==8)
							{
								cout<<"Beer Man: *pant**pant**pant*\n";
								pause();
								cout<<"Beer Man: So...freaking...hot... I can feel the alcohol evaporating already!\n";
								pause();
								cout<<"Beer Man: If the Fire Man isn't here I'm going to be really angry!\n";
								pause();
								area2=2;
							}
							forward=leave+1;
						}
						if (area2==2)
						{
							if (forward){x=2;y=0;}
							if (!forward){x=2;y=4;}
							do
							{
								leave=dungeon("Magma Chamber",4,4,2,0,2,4,x,y);
								int number=randint(0,7);
								switch (number)
								{
								case 0:
									win=battle_init(inventory,beerman,phoenix,randint(19,21),2,1);
									break;
								case 1:
									win=battle_init(inventory,beerman,lava_golem,randint(19,22),1,1);
									break;
								case 2:
									win=battle_init(inventory,beerman,gnome,randint(20,25),1,1);
									break;
								case 3:
									win=battle_init(inventory,beerman,air_elemental,randint(18,21),1,1);
									break;
								default:
									break;
								}
								if (!win)
									break;
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1){
								area2=1;}
							if (leave==0 && mission_number==8){
								cout<<"Beer Man walks to the former desk of Fire Man. There is a note on it.\n";
								pause();
								cout<<"Note on desk: Dear Beer Man,\n"
									<<"If you thought that you would find me in such an obvious location...\n"
									<<"------------\n|You IDIOT!|\n------------\nNo one would be so stupid as to hide in such a place! Especially me!\n"
									<<"Seriously, good luck.\n\nSincerely,\nFire Man\n";
								pause();
								cout<<"Beer Man: *twitch*\n";
								pause();
								cout<<"Beer Man: *twitch*\n";
								pause();
								cout<<"Beer Man: *twitch*\n";
								pause();
								cout<<"Beer Man: RAAAAAAAAAAAAGE!!!\n";
								pause();
								cout<<"In his rage Beer Man began to run around screaming bloody revenge.\nAlong the way he accidentally tripped over a trapdoor,\nrevealing someone inside.\n";
								pause();
								cout<<"Fire Man: /!\\"<<endl;
								pause();
								cout<<"Beer Man: ...wut\n";
								pause();
								cout<<"Fire Man: Nooooo! How were you able to find me, you scoundrel?\n";
								pause();
								win=battle_init(inventory,beerman,fire_man,20,3,0);
								if (!win)
									break;
								cout<<"Fire Man: No...not again...!\n";
								pause();
								cout<<"Beer Man: Mission Accomplished. Another victory... for Beer Man.\n";
								pause();
								cout<<"Beer Man obtained the blueprints!\n";
								pause();
								mission_number=9;
								mission="Mission: Check with the Beer Council for your next mission.";
								cout<<"Beer Man: Let's go back to the Beer Council. They'll give me the\nnext mission.\n";
								pause();
								leave=-1;
							}
							forward=leave+1;
						}
					} while (area2>0);
					break;
				case 3:
					area2=1;
					do{
						if (area2==1)
						{
							if (forward){x=0;y=0;}
							if (!forward){x=5;y=5;}
							do
							{
								leave=dungeon("Former Temperance HQ",2,2,0,0,5,5,x,y);
								int number=randint(0,4);
								if (number<2 && leave && !(x==1 && y==1 && mission_number==9))
								{
									int number2=randint(0,4);
									switch (number2)
									{
									case 0:
										win=battle_init(inventory,beerman,policeman,randint(22,24),1,1);
										break;
									case 1:
										win=battle_init(inventory,beerman,mage,randint(22,24),1,1);
										break;
									case 2:
										win=battle_init(inventory,beerman,thief,randint(22,24),1,1);
										break;
									case 3:
										win=battle_init(inventory,beerman,green_mage,randint(22,24),1,1);
										break;
									case 4:
										win=battle_init(inventory,beerman,water_mage,randint(22,24),1,1);
										break;
									}
								}
								if (x==1 && y==1 && mission_number==9){
									cout<<"Beer Man notices a familiar sight...\n";
									pause();
									cout<<"Beer Man: YOU!!!\n";
									pause();
									cout<<"Lyman Beecher: Me.\n";
									pause();
									cout<<"Beer Man: You were dead!\n";
									pause();
									cout<<"Lyman Beecher: Well, I'm a zombie now. Is this surprising?\n";
									pause();
									win=battle_init(inventory,beerman,lyman_beecher,23,3,0);
									if (!win)
										break;
									cout<<"Beer Man: No bodyguard to hide behind this time, huh?\nYou die now.\n";
									pause();
									cout<<"Lyman Beecher: ...No matter. We have already won!\n";
									pause();
									mission_number=10;
									mission="Mission: Check with the Beer Council for your next mission.";
								}
								if (!win)
									break;
							} while (leave>0);
							if (!win)
								break;
							if (leave==-1)
								area2=0;
							if (leave==0)
								area2=2;
							forward=leave+1;
						}
					} while (area2>0);
					break;
				case 4:
					cout<<"The airplane fare is $20.\n";
					if (mission_number>7){
						if (inventory[0]>=20){
							int choice;
							choice=menu(3,"Austria","Grass Town","Cancel");
							if (choice==1){
								area=0;
								inventory[0]-=20;
								cout<<"Beer Man flew to Austria.\n";}
							if (choice==2){
								area=6;
								inventory[0]-=20;
								cout<<"Beer Man flew to Grass Town.\n";}
							if (choice>2 || choice<1)
								break;
						}
						else
							cout<<"Unfortunately, you're broke.\n";
					}
					pause();
					break;
				case 5:
					area=3;
					break;
				default:
					break;
				}
				if (!win){
					blackout(inventory,beerman);
					win=1;}
				system("CLS");
			} while (choice<5 && area==5);
		}
		if (area==6)	//If in Grass Town
		{
			do
			{
				system("CLS");
				//Grass Town
				cout<<"Grass Town\n-------------\n";
				choice=menu(7,"Go downtown","Visit the Arena","Check stats","Check Mission","Encyclopedia","Save","Quit");
				switch (choice)
				{
				case 1:
					area=7;
					break;
				case 2:
					if (mission_number==18)
						area=8;
					else{
						cout<<"The Arena is not yet open. Please come back later.\n";
						pause();
					}
					break;
				case 3:
					beerman.display_stats();
					cout<<"\n\nMoney: "<<inventory[0];
					pause();
					system("CLS");
					show_inventory(inventory);
					break;
				case 4:
					cout<<mission;
					pause();
					break;
				case 5:
					beerman.encyclopedia();
					pause();
					break;
				case 6:
					save(beerman,inventory,mission_number,mission,6,show_combo_tutorial,high_score);
					break;
				case 7:
					save(beerman,inventory,mission_number,mission,6,show_combo_tutorial,high_score);
					exit(1);
					break;
				}
				system("CLS");
			} while (choice>2 || (choice==2 && mission_number!=18));
		}
		if (area==7)	//If in Grass Town downtown
		{
			do
			{
				//Grass Town downtown
				cout<<"Grass Town Downtown\n-------------------"<<endl;
				choice=menu(7,"Bar","Gym","Inn","NPC","Shop","Airport","Back");
				system("CLS");
				switch (choice)
				{
				case 1:
					bar(inventory,beerman,bar_fighter);
					break;
				case 2:
					gym(inventory,beerman,punching_bag,gym_member,boxer,gym_champion,pikachu);
					break;
				case 3:
					cout<<"The Sleeping Dog Inn: Welcome! You may sleep here for only $2, but\nyour BAC will drop to 0.00.\n";
					choice=menu(2,"Sleep: $2","Back");
					if (choice==1 && inventory[0]>1)
					{
						cout<<"Beer Man: Something tells me that this was not a good idea.\n";
						pause();
						inventory[0]-=2;
						beerman.change_hp(beerman.hp_max());
						beerman.change_bac(-beerman.change_bac(0));
						cout<<"Beer Man: ugh... headache... need... beer...\n";
						pause();
						cout<<"Inn Owner: We sell the original Hair of the Dog Remedy for\nhangovers for just $1! Want some?\n";
						choice=menu(2,"Sure","...I'll just go to the bar");
						if (choice==1){
							if (inventory[0]>0){
								inventory[0]--;
								cout<<"Beer Man received a small brown hair.\n";
								pause();
								cout<<"Beer Man: ...Did I just get ripped off?\n";
							}else
								cout<<"You don't have any money!\n";
							pause();
						}
					}
					break;
				case 4:
					{
						int n=randint(1,11);
						if (n==1)
							cout<<"TI Scientist: Lab safety rules are very important. We take our lab workers'\n"
								<<"safety very seriously, and strive to make research as painful... I mean\n"
								<<"painless as possible.\n";
						if (n==2)
							cout<<"NPC: I think beer can burn easily, right? Be careful so that it doesn't\n"
								<<"start flaring up... it can hurt people!\n";
						if (n==3)
							cout<<"Scientist: The fumes from acids can seriously damage you. Be careful while\nworking with acids.\n";
						if (n==4)
							cout<<"NPC: Sometimes, just punching the enemy works better than using a combo. Make\n"
								<<"sure that your combo is worth it if you are going to use it! For example,\n"
								<<"weather or field effects will not be worth the trouble in short battles.\n";
						if (n==5)
							cout<<"NPC: Knowing how to recover your health efficiently is key in the Arena.\n"
								<<"But always make sure that your BAC stays under .40.\n";
						if (n==6){
							cout<<"NPC: You might love beer, but water is very healthy, you know! Maybe you\n"
								<<"should learn better drinking habits.\n";
							pause();
							cout<<"Beer Man: NEVER!\n";
						}
						if (n==7)
							cout<<"TI Engineer: You know, beer might make a good time bomb... We can add that\n"
								<<"in our current food-based weaponry, it might be a new hit!\n";
						if (n==8)
							cout<<"TI Scientist: Thunderstorms consist of electricity and a rain cloud.\n";
						if (n==9)
							cout<<"Farmer Joe: Steroids are very useful for growing ammo... I\nmean fruits and vegetables.\n";
						if (n==10)
							cout<<"NPC: I've heard only NEUTRAL people can raise attack and\nonly EARTH can decrease the opponent's damage...\n";
						if (n==11)
							cout<<"Fighter: Slowing the opponent down is always a good idea.\n";
					}
					pause();
					break;
				case 5:
					shop_full(inventory);
					break;
				case 6:
					cout<<"The airplane fare is $20.\n";
					if (mission_number>7){
						if (inventory[0]>=20){
							int choice;
							choice=menu(3,"Austria","Libeerty City","Cancel");
							if (choice==1){
								area=0;
								inventory[0]-=20;
								cout<<"Beer Man flew to Austria.\n";}
							if (choice==2){
								area=3;
								inventory[0]-=20;
								cout<<"Beer Man flew to Libeerty City.\n";}
							if (choice>2 || choice<1)
								break;
						}
						else
							cout<<"Unfortunately, you're broke.\n";
					}
					pause();
					break;
				case 7:
					area=6;
					break;
				}
				system("CLS");
			} while (choice>2 && choice<6);
		}
		if (area==8)	//ARENA
		{
			int mode=0,inventory_copy[12],beerman_level=beerman.get_lvl();
			Enemy *endurance[18],*boss_rush[10];
			for (int i=0;i<12;i++)
				inventory_copy[i]=inventory[i];
			endurance[0]=&tree;
			endurance[1]=&seagull;
			endurance[2]=&tree;
			endurance[3]=&boulder;
			endurance[4]=&thief;
			endurance[5]=&gnome;
			endurance[6]=&lava_golem;
			endurance[7]=&mage;
			endurance[8]=&green_mage;
			endurance[9]=&water_mage;
			endurance[10]=&policeman;
			endurance[11]=&bar_fighter;
			endurance[12]=&boxer;
			endurance[13]=&lawyer;
			endurance[14]=&centaur;
			endurance[15]=&air_elemental;
			endurance[16]=&phoenix;
			endurance[17]=&gym_champion;
			boss_rush[0]=&cow_boy;
			boss_rush[1]=&arnold;
			boss_rush[2]=&salieri;
			boss_rush[3]=&fire_man;
			boss_rush[4]=&lyman_beecher;
			boss_rush[5]=&carrie_nation;
			boss_rush[6]=&elliot;
			boss_rush[7]=&eraser;
			boss_rush[8]=&mecha;
			boss_rush[9]=&milk_man;
			beerman.scale_to_30();
			do
			{
				system("CLS");
				cout<<"The Arena\n---------\n";
				int recover=0,win=1;
				choice=menu(5,"Start a Challenge","Help","Check stats","Encyclopedia","Back");
				switch (choice)
				{
				case 1:
					{
						int fights=0;
						float original_bac=beerman.change_bac(0);
						recover=0;
						mode=menu(6,"Endurance","Infinite Random Endurance","Random Rush","Boss Rush","Single Boss Battle","Back");
						if (mode==1){
							fights=18;
							recover=3;
							for (int i=1;i<12;i++)
								inventory[i]=40;
						}
						if (mode==2){
							fights=-1;
							for (int i=1;i<12;i++)
								inventory[i]=15;
						}
						if (mode==3){
							fights=8;
							recover=1;
							for (int i=1;i<12;i++)
								inventory[i]=20;
						}
						if (mode==4){
							fights=10;
							recover=3;
							for (int i=1;i<12;i++)
								inventory[i]=35;
						}
						if (mode==5)
							fights=1;
						if (mode==6)
							fights=0;
						beerman.change_bac(-1);
						beerman.change_bac(.2);
						int i;
						for (i=0;i!=fights;i++)
						{
							if (mode!=5){
								system("CLS");
								cout<<"Round: "<<i+1;
							}
							if (mode!=2 && mode!=6 && mode!=5)
								cout<<"/"<<fights<<endl;
							if (mode!=5)
								pause();
							if (mode==1)
								win=battle_init(inventory,beerman,*endurance[i],30,3,0,0);
							if (mode==2)
								win=battle_init(inventory,beerman,*endurance[randint(0,17)],30,3,0,0);
							if (mode==3 && i!=7)
								win=battle_init(inventory,beerman,*endurance[randint(0,17)],30,3,0,0);
							if (mode==3 && i==7)
								win=battle_init(inventory,beerman,*boss_rush[randint(0,9)],30,3,0,0);
							if (mode==4)
								win=battle_init(inventory,beerman,*boss_rush[i],30,3,0,0);
							if (mode==5){
								cout<<"0: Cancel\n";
								for (int j=0;j<10;j++)
									cout<<j+1<<": "<<boss_rush[j]->get_name()<<endl;	
								bool fail;
								int select;
								do{
									cin>>select;
									fail=cin.fail();
									if (fail)
									{
										cin.clear();
										cin.ignore();
									}else{
										if (select<1 || select>10){
											mode=6;
											break;
										}
									}
								} while (fail);
								if (mode!=6)
									win=battle_init(inventory,beerman,*boss_rush[select-1],30,3,0,0);
							}
							if (!win || mode==6)
								break;
							if (recover>0 && i+1<fights){
								int select;
								cout<<"Would you like to use a Recover? Recovers left: "<<recover<<"\n";
								do{
									select=menu(2,"Yes","No");
								} while (select<1 || select>2);
								if (select==1){
									recover--;
									beerman.change_hp(beerman.hp_max());
								}
							}
						}
						if (win && mode!=6)
							cout<<"You win!\n";
						if (!win)
							cout<<"You lose.\n";
						if (mode!=6)
							pause();
						if (mode==1){
							if (win){
								high_score[0]=18;
								if (3-recover<high_score[1])
									high_score[1]=3-recover;
							}
							if (!win && i>high_score[0]){
								high_score[0]=i;
								high_score[1]=3-recover;
							}
							if (!win && i==high_score[0] && 3-recover<high_score[1])
								high_score[1]=3-recover;
						}
						if (mode==2){
							if (i>high_score[2])
								high_score[2]=i;
						}
						if (mode==3 && win){
							if (2-recover<high_score[3])
								high_score[3]=2-recover;
						}
						if (mode==4){
							if (win){
								high_score[0]=10;
								if (3-recover<high_score[1])
									high_score[1]=3-recover;
							}
							if (!win && i>high_score[0]){
								high_score[0]=i;
								high_score[1]=3-recover;
							}
							if (!win && i==high_score[0] && 3-recover<high_score[1])
								high_score[1]=3-recover;
						}
						//Reset HP and BAC
						beerman.change_hp(beerman.hp_max());
						beerman.change_bac(-1);
						beerman.change_bac(original_bac);
						for (int i=1;i<12;i++)	//Reset inventory except for money
							inventory[i]=inventory_copy[i];
					}
					break;
				case 2:
					system("CLS");
					cout<<"Arena Information\n-----------------\n"
						<<"In the Arena, you may take part in any one of the 4 Challenges provided.\n"
						<<"While in the Arena, you do not gain any Experience, nor do you gain Effort\n"
						<<"Values, but you do get paid for each fight you win. In each Challenge you\n"
						<<"are provided with a finite amount of Recovers, which you may use after a fight\n"
						<<"to restore your HP to its maximum value. In addition, in all modes except the\n"
						<<"Single Boss Battle you will be given a finite set of items for use in the\n"
						<<"Arena. Your inventory will be returned to you after the Challenge is finished.\n\n"
						<<"In the Arena, both the enemies and Beer Man will have a maximum experience\n"
						<<"level of 30. However, Beer Man's level will not scale up if his current \n"
						<<"level is under 30. Upon exiting the Arena, Beer Man will regain his levels.\n\n"
						<<"Beer Man will start all Challenges with a BAC of .2. BAC will be restored after\n"
						<<"exiting the Arena.\n";
					pause();
					system("CLS");
					cout<<"Arena Information\n-----------------\n";
					cout<<"Endurance: Fight through 18 different rounds of enemies. You get 3 Recovers\n"
						<<"and 40 of each item.\n"
						<<"High Score: "<<high_score[0]<<" Fights Won, "<<high_score[1]<<" Recovers used\n\n"
						<<"Infinite Random Endurance: Fight endlessly until you fall! No Recovers, but\n"
						<<"you do get 15 of each item.\n"
						<<"High Score: "<<high_score[2]<<" Fights Won\n\n"
						<<"Random Rush: 8 Random fights, with a last boss. You get 1 Recover and 20 of\n"
						<<"each item.\n";
					if (high_score[3]<3)
						cout<<"High Score: "<<high_score[3]<<" Recovers used\n\n";
					else
						cout<<"High Score: Not yet complete\n\n";
					cout<<"Boss Rush: Fight through all 10 storyline bosses in a row! You get 3 Recovers\n"
						<<"and 35 of each item.\n"
						<<"High Score: "<<high_score[4]<<" Fights Won, "<<high_score[5]<<" Recovers used\n\n"
						<<"Single Boss Battle: Choose a single storyline boss to fight. You will use your\n"
						<<"own items in the inventory. This mode has no recorded High Score.";
					pause();
					break;
				case 3:
					beerman.display_stats();
					cout<<"\n\nMoney: "<<inventory[0];
					pause();
					system("CLS");
					show_inventory(inventory);
					break;
				case 4:
					beerman.encyclopedia();
					pause();
					break;
				case 5:
					while (beerman.get_lvl()<beerman_level)
						beerman.grow_stats();
					area=6;
					break;
				}
				system("CLS");
			} while (choice!=5);
		}
	}
	return 0;
}
int battle_init(int inventory[],Beerman& beerman,Enemy enemy,int lvl,int ai_lvl,const bool can_run,bool get_xp)	//By using the copy constructor we will not affect the base stats
{
	signed int beerman_status[21],enemy_status[21],round=1,beerman_resid=0,enemy_resid=0;	//Resids are for movement per round calculation
	for (int i=0;i<21;i++){
		beerman_status[i]=0;
		enemy_status[i]=0;
	}
	bool run=0;
	float calc=0;	//For speed calculations and comparisons
	/*
	Hold items: Match Active, Rock, Sand, Water, Seed
	Permanent Ground items: Sandbox, Fan
	Temporary Ground items: Beer, Rock, Acid, Steroids, Battery, Seed
	*/
	int hold=0,objects[8];
	for (int i=0;i<8;i++)
		objects[i]=0;
	for (int i=1;i<lvl;i++)
		enemy.grow_stats();
	enemy.set_attacks_at_level();
	beerman.set_attacks_at_level();
	cout<<"<<<BATTLE START!>>>\nLv "<<beerman.get_lvl()<<" Beer Man VS Lv "<<enemy.get_lvl()<<" "<<enemy.get_name();
	pause();
	system("CLS");
	while (beerman.change_hp(0)>0 && enemy.change_hp(0)>0)
	{
		//Movement per round calculation for beerman
		calc=float(9+beerman.spd()+beerman_resid+(beerman.elem()==AIR && beerman_status[12]>0)*20)/15;
		if (beerman_status[9]>0)
			calc+=.4;
		if (beerman_status[8]>0)
			calc*=.75;
		if (beerman_status[7]>0)
			calc*=.9;
		if (beerman_status[5]>0)
			calc*=.8;
		while (calc>=1)
		{
			int paralyze=randint(0,4)*(beerman_status[5]>0);
			//Do stuff
			run=0;
			if (paralyze<4)
				run=battle_beerman_seq(beerman,enemy,beerman_status,enemy_status,can_run,inventory,hold,objects);
			else
				cout<<"Beer Man is paralyzed and cannot move!\n";
			if (run)
				break;
			if (beerman.change_bac(0)>=.4 || beerman.change_hp(0)<1)
				break;
			if (enemy.change_hp(0)<=0)
				break;
			calc--;
		}
		if (run)
			break;
		beerman_resid=int(calc*6);
		if (beerman.change_bac(0)>=.4 || beerman.change_hp(0)<1)
		{
			beerman.change_hp(-beerman.hp_max());	//Lose the battle
			break;
		}
		if (enemy.change_hp(0)<=0)
			break;
		//Movement per round calculation for enemy
		calc=float(9+enemy.spd()+enemy_resid+(enemy.elem()==AIR && enemy_status[12]>0)*20)/15;
		if (enemy_status[9]>0)
			calc+=.4;
		if (enemy_status[8]>0)
			calc*=.75;
		if (enemy_status[7]>0)
			calc*=.9;
		if (enemy_status[5]>0)
			calc*=.8;
		while (calc>=1)
		{
			//Do stuff
			int paralyze=randint(0,4)*(enemy_status[5]>0);
			if (paralyze<4)
				battle_enemy_seq(beerman,enemy,beerman_status,enemy_status,objects,ai_lvl);
			else
				cout<<enemy.get_name()<<" is paralyzed and cannot move!\n";
			//Damage=0 is an effect attack, no text
			calc--;
			pause();
		}
		enemy_resid=int(calc*6);
		if (beerman.change_hp(0)<1)
			break;
		//Special effects go here, perform_effects returns Leech Seed HP recovery value
		enemy.change_hp(perform_effects(beerman,beerman_status,1));
		beerman.change_bac(-(beerman_status[1]>0)*.01-(beerman_status[2]>0)*.02-(beerman_status[6]>0)*.005);
		beerman.change_hp(perform_effects(enemy,enemy_status,1));
		if (beerman_status[11]>0 && objects[1]>0){	//Fan keeps Sandstorm going on indefinitely
			cout<<"The fan keeps the Sandstorm active.\n";
			beerman_status[11]++;
		}
		perform_field(beerman,enemy,beerman_status,enemy_status,1);
		//Next round
		round++;
		//Decrease status counters
		for (int i=1;i<18;i++){	//Ignores poison counter, poison is permanent unless Good Beered x5, ignores drunken plants counter/atk/def
			if (beerman_status[i]>0 && i!=16) beerman_status[i]--;
			if (enemy_status[i]>0 && i!=16) enemy_status[i]--;
		}
		if (beerman_status[15]<1){	//Removes all drunken plants when Overgrowth does not exist
			beerman_status[16]=0;
			enemy_status[16]=0;
		}
		if (beerman_status[20]>0){	//Time Bomb code
			beerman_status[20]--;
			cout<<"Beer Man's Time Bomb's timer decreases to "<<beerman_status[20]<<".\n";
			if (beerman_status[20]==0)	//Explode!
			{
				int damage,effect;
				Attack *atk_ptr=new Attack("Explosion",NEUTRAL,0,35,-1,100,100,1,0);
				damage=atk_ptr->attack(enemy,beerman,effect,1);
				cout<<"Time Bomb used Explosion! Beer Man takes damage!\nDMG: "<<damage<<endl;
				beerman.change_hp(-damage);
				delete atk_ptr;
			}
			pause();
		}
		if (enemy_status[20]>0){	//Time Bomb code
			enemy_status[20]--;
			cout<<enemy.get_name()<<"\'s Time Bomb's timer decreases to "<<enemy_status[20]<<".\n";
			if (enemy_status[20]==0)	//Explode!
			{
				int damage,effect;
				Attack *atk_ptr=new Attack("Explosion",NEUTRAL,0,35,-1,100,100,1,0);
				damage=atk_ptr->attack(beerman,enemy,effect,1);
				cout<<"Time Bomb used Explosion! "<<enemy.get_name()<<" takes damage!\nDMG: "<<damage<<endl;
				enemy.change_hp(-damage);
				delete atk_ptr;
			}
			pause();
		}
		beerman.change_bac(-.01);
		enemy.change_mp(1);
	}
	if (beerman.change_hp(0)>0 && !run)
	{
		cout<<"You win!\n";
		pause();
		if (get_xp){
			cout<<"Beer Man gained "<<enemy.get_xp()*enemy.get_lvl()<<" EXP!";
			beerman.get_exp(enemy.get_xp()*enemy.get_lvl());
			pause();
			if (beerman.change_ev(enemy.get_EV(),1)==1)
				pause();
		}
		int moolah=enemy.get_money()+randint(0,int(enemy.get_lvl()/2));
		cout<<"Beer Man gained $"<<moolah<<"!";
		inventory[0]+=moolah;
	}
	if (beerman.change_hp(0)<=0)
	{
		cout<<"You lose...";
		beerman.change_hp(-beerman.change_hp(0));
	}
	if (!run) pause();
	system("CLS");
	return (beerman.change_hp(0)>0);
}
bool battle_beerman_seq(Beerman& beerman,Enemy& enemy,int beerman_status[],int enemy_status[],bool run,int inventory[],int& hold,int objects[])
{
	system("CLS");
	cout<<"LV "<<beerman.get_lvl()<<" Beer Man: "<<beerman.change_hp(0)<<"/"<<beerman.hp_max()<<"   BAC: "<<beerman.change_bac(0)<<endl;
	cout<<"LV "<<enemy.get_lvl()<<" "<<enemy.get_name()<<": "<<enemy.change_hp(0)<<"/"<<enemy.hp_max()<<"   MP: "<<enemy.change_mp(0)<<"\n";
	int choice=0,effect=-1,damage=0;
	do{
		Attack *at=0;
		cout<<endl;
		choice=menu(6,"Attack","Throw","Use","Drop","Check Status","Run");
		if (choice==5)
		{
			beerman.display_stats();
			pause();
			cout<<"\nSTATUS\n------\n";
			perform_effects(beerman,beerman_status,0);
			perform_effects(enemy,enemy_status,0);
			perform_field(beerman,enemy,beerman_status,enemy_status,0);
			check_battle_objects(hold,objects);
			system("CLS");
			cout<<"LV "<<beerman.get_lvl()<<" Beer Man: "<<beerman.change_hp(0)<<"/"<<beerman.hp_max()<<"   BAC: "<<beerman.change_bac(0)<<endl;
			cout<<"LV "<<enemy.get_lvl()<<" "<<enemy.get_name()<<": "<<enemy.change_hp(0)<<"/"<<enemy.hp_max()<<"   MP: "<<enemy.change_mp(0)<<"\n";
		}
		if (choice==1)
		{
			int choice2=menu(5,"Punch","Flail","Drunken Fist","Purge","Back");
			switch (choice2)
			{
			case 1:
				at=check_combo(beerman,hold,objects,1,0,0,0,beerman_status);
				if (at==0)
					at=beerman.get_attack(0);
				damage=at->attack(beerman,enemy,effect,1);
				cout<<"Beer Man used "<<at->get_name()<<"!\n";
				break;
			case 2:
				if (beerman.change_bac(0)<.1)
				{
					cout<<"You're not drunk enough!";
					choice=5;
					break;
				}
				at=check_combo(beerman,hold,objects,2,0,0,0,beerman_status);
				if (at==0)
					at=beerman.get_attack(1);
				damage=at->attack(beerman,enemy,effect,1);
				cout<<"Beer Man used "<<at->get_name()<<"!\n";
				break;
			case 3:
				if (beerman.change_bac(0)<.15)
				{
					cout<<"You're not drunk enough!";
					choice=5;
					break;
				}
				at=check_combo(beerman,hold,objects,3,0,0,0,beerman_status);
				if (at==0)
					at=beerman.get_attack(2);
				damage=at->attack(beerman,enemy,effect,1);
				cout<<"Beer Man used "<<at->get_name()<<"!\n";
				break;
			case 4:
				if (beerman.change_bac(0)==0)
				{
					cout<<"There is nothing to purge!";
					choice=5;
					break;
				}
				at=check_combo(beerman,hold,objects,4,0,0,0,beerman_status);
				if (at==0)
				{
					int half=0;
					if (beerman.change_bac(0)>.1){
						cout<<"How much BAC would you like to Purge?\n";
						if (beerman.change_bac(0)<.2)
							half=menu(2,"All BAC",".10 BAC");
						if (beerman.change_bac(0)>=.2)
							half=menu(3,"All BAC",".10 BAC",".20 BAC");
					}
					at=beerman.get_attack(3);
					if (half==1 || beerman.change_bac(0)<.1){
						damage=at->attack(beerman,enemy,effect,1)+ceil(beerman.change_bac(0)*100);
						beerman.change_bac(-.4);
					}
					if (half==3){
						damage=at->attack(beerman,enemy,effect,1)+20;
						beerman.change_bac(-.2);
					}
					if (half==2){
						damage=at->attack(beerman,enemy,effect,1)+10;
						beerman.change_bac(-.1);
					}
				}
				else{damage=at->attack(beerman,enemy,effect,1);}
				cout<<"Beer Man used "<<at->get_name()<<"!\n";
				break;
			case 5:
				choice=5;
				break;
			default:
				choice=5;
				break;
			}
		}
		if (choice==2)
		{
			int back=0;
			at=throw_item(beerman,hold,objects,inventory,beerman_status,back);
			if (back)
				choice=5;
			else{
				damage=at->attack(beerman,enemy,effect,1);
				cout<<"Beer Man used "<<at->get_name()<<"!\n";
				if (at->get_name()=="Growth")
					cout<<enemy.get_name()<<" grew larger!\n";
			}
		}
		if (choice==3)
		{
			int back=0;
			at=use_item(beerman,hold,objects,inventory,beerman_status,back);
			if (back)
				choice=5;
			else{
				if (at!=0){
					damage=at->attack(beerman,enemy,effect,1);
					cout<<"Beer Man used "<<at->get_name()<<"!\n";
					if (at->get_name()=="Acid Rain"){
						cout<<"The weather reverted to normal.\n";
						for (int i=10;i<16;i++)
						{
							beerman_status[i]=0;
							enemy_status[i]=0;
						}
					}
					if (at->get_name()=="Lightning")
					{
						int m=0;	//Beer Man gets struck unless enemy is large
						if ((beerman_status[9]<1 && enemy_status[9]<1) || (beerman_status[9]>0 && enemy_status[9]>0))
						{
							if (m)
								damage=at->attack(beerman,enemy,effect,1);
							else
								damage=at->attack(enemy,beerman,effect,1);
						}
						if (beerman_status[9]>0 && enemy_status[9]<1)
						{
							m=0;
							damage=at->attack(enemy,beerman,effect,1);
						}
						if (beerman_status[9]<1 && enemy_status[9]>0)
						{
							m=1;
							damage=at->attack(beerman,enemy,effect,1);
						}
						if (m){
							if (enemy_status[7]>0)
								damage*=1.5;
							cout<<enemy.get_name()<<" is struck by lightning!\nDMG: "<<damage<<endl;
							enemy.change_hp(-damage);}
						else{
							if (beerman_status[7]>0)
								damage*=1.5;
							cout<<"Beer Man is struck by lightning!\nDMG: "<<damage<<endl;
							beerman.change_hp(-damage);}
						damage=0;
						effect=-1;
					}
				}
			}
		}
		if (choice==4)
		{
			int back=0;
			at=drop_item(beerman,hold,objects,inventory,beerman_status,back);
			if (back)
				choice=5;
			else{
				if (at!=0){
					damage=at->attack(beerman,enemy,effect,1);
					if (at->get_name()!="Explosion")
						cout<<"Beer Man used "<<at->get_name()<<"!\n";
					if (at->get_name()=="Overgrowth" && objects[5]>0){
						cout<<"The Steroids increased the plants' growth!\n";
						beerman_status[15]+=5;
						enemy_status[15]+=5;
						objects[5]--;
					}
				}
			}
		}
		if (choice==6)
		{
			if (run)
			{
				int lvl_diff=beerman.get_lvl()-enemy.get_lvl(),n=randint(1,100);
				if (lvl_diff<0)
					lvl_diff=0;
				if (n+lvl_diff*10>59){	//Probability of escape: 60% + 10% each Beer Man level above the enemy
					cout<<"Got away safely.";
					pause();
					return 1;
				}else{
					cout<<"Beer Man tripped over his own feet and was unable to escape!\n";
					pause();
					return 0;
				}
			}
			else
			{
				cout<<"Can't run!\n";
				choice=5;
			}
		}
		int temp_damage=0;
		if (damage>0)
		{
			int att=1;
			if (beerman_status[3]>0 && effect!=21)
			{
				int n=randint(0,3);
				if (!n)
					att=0;
			}
			if (att)
			{
				if (effect!=16)
				{
					int multiple_times=1,number_times=0;
					if (effect==19)
						multiple_times=randint(2,5);
					if (effect==20)
						multiple_times=objects[3]+2;
					for (int i=0;i<multiple_times;i++)
					{
						temp_damage=damage+ceil(beerman.change_bac(0)*10);
						int hit_blind=randint(0,4)*(beerman_status[4]>0);
						if (hit_blind<4 && beerman_status[11]>0 && beerman.elem()!=EARTH)
							hit_blind=randint(-13,6);	//85% Accuracy in Sandstorm
						if (objects[4]>0 && at->get_type()==1){
							cout<<"The Acid Beaker slightly powered up Beer Man's special attack!\n";
							temp_damage=floor(temp_damage*1.25);
						}
						if (hold==4 && at->get_type()==0){
							cout<<"The held Rock slightly powered up Beer Man's physical attack!\n";
							temp_damage=floor(temp_damage*1.15);
						}
						field_damage_manipulate(at->elem(),temp_damage,beerman_status);
						temp_damage+=int(floor(temp_damage*(beerman_status[9]>0)*.2)-floor(temp_damage*(enemy_status[9]>0)*.2));	//Growth
						if (at->get_type()==0){
							if (beerman_status[18]>=0)
								temp_damage+=int(floor(temp_damage*.5*beerman_status[18])-floor(temp_damage*.5*enemy_status[19]));	//Stat boosts
							else
								temp_damage+=int(floor(temp_damage*pow(.8,-beerman_status[18]))-floor(temp_damage*.5*enemy_status[19]));
						}
						if (multiple_times>1)
							temp_damage+=randint(-2,1);
						if (temp_damage<1)
							temp_damage=1;
						if (hit_blind<4 || effect==21){
							cout<<"DMG: "<<temp_damage<<endl;
							enemy.change_hp(-temp_damage);
							if (effect==21){
								cout<<"Beer Man's DMG: "<<temp_damage<<endl;
								beerman.change_hp(-temp_damage);
							}
							number_times++;
						}
						else
							cout<<"Beer Man missed!\n";
					}
					if (effect==19 || effect==20)
						cout<<"Hit "<<number_times<<" times!\n";
					if (effect==20){
						if (number_times>2)
							cout<<"Beer Man's rock wall was used in the attack and no longer exists.\n";
						objects[3]=0;
					}
					if (at->get_name()=="Acid" && enemy_status[19]>0){
						enemy_status[19]=0;
						cout<<"The Acid neutralized "<<enemy.get_name()<<"'s Defense!\n";
					}
				}
				else
				{
					cout<<"Healed: "<<damage;
					beerman.change_hp(damage);
				}
			}
			else
			{
				cout<<"Beer Man hit himself!\nDMG: "<<beerman.atk()<<endl;
				beerman.change_hp(-beerman.atk());
			}
		}
		if (damage<0 && choice!=5)
		{
			cout<<"Beer Man missed!\n";
		}
		if (effect>-1 && effect<9 && damage>-1)
			effect_text(enemy,effect);
		if (effect>-1 && effect<3 && damage>-1)
			enemy_status[effect]=100;
		if (effect>2 && effect<7 && damage>-1)
			enemy_status[effect]+=7;
		if (effect>6 && effect<10 && damage>-1)
			enemy_status[effect]+=5;
		if (effect>9 && effect<16){
			for (int i=10;i<16;i++){
				beerman_status[i]=0;
				enemy_status[i]=0;
			}
			beerman_status[effect]=8;
			enemy_status[effect]=8;
		}
		if (effect==22){
			if (beerman_status[15]>0){
				beerman_status[16]=1;
				cout<<"The plants become drunk and start to move erratically!\n";
			}else{cout<<"But there were no plants...\n";}
		}
		if (effect==23){
			enemy_status[17]+=10;
			cout<<enemy.get_name()<<" was seeded!\n";
		}
		if (effect==24){
			if (beerman_status[18]<6){
				beerman_status[18]++;
				cout<<"Beer Man's incomprehensible war dance raises his Attack!\n";
			}else{cout<<"But Beer Man's Attack cannot rise any higher!\n";}
		}
		if (effect==27)
			enemy_status[20]=3;
		if (effect==28){
			for (int i=10;i<16;i++){
				beerman_status[i]=0;
				enemy_status[i]=0;
			}
			beerman_status[1]=0;
			beerman_status[2]=0;
			cout<<"All field conditions disappeared!\n";
		}
		effect=-1;
		if (choice<1 || choice>6)
			choice=5;
		//if damage<0 attack missed
	} while (choice==5);
	pause();
	return 0;
}
void battle_enemy_seq(Beerman& beerman,Enemy& enemy,int beerman_status[],int enemy_status[],int objects[],int ai_lvl)
{
	int damage=0,effect=-1,choice=0,move_chosen=1;
	Attack *at=0;
	int n=randint(1,10);	//Randomly decide to use Status [1,2], Attack [3,5], Most Effective Move [6,8], or random [9,10]
	do{
		//AI (lvls 0-2)
		int weather_atk=-1,current_weather=-1,lowest_mp=100,lowest_mp_number=0,war_dance=-1,gust=-1,recover=-1,growth=-1,neutralize=-1;
		int other_index=-1,other[7],other_status[7],number_status=0;
		float other_effective[7];
		for (int i=0;i<7;i++){
			other[i]=0;
			other_status[i]=0;
			other_effective[i]=0;
		}
		for (int i=0;i<=enemy.get_max_attack_number();i++){	//Retreive the different attacks and assign them
			if (enemy.get_attack(i)->get_mp_req()<lowest_mp && enemy.get_attack(i)->get_mp_req()!=0)
				lowest_mp_number=i;
			if (enemy.get_attack(i)->get_effect()>9 && enemy.get_attack(i)->get_effect()<16){
				weather_atk=i;
				continue;
			}
			if (enemy.get_attack(i)->get_effect()==29){
				neutralize=i;
				continue;
			}
			if (enemy.get_attack(i)->get_effect()==24){
				war_dance=i;
				continue;
			}
			if (enemy.get_attack(i)->get_effect()==17){
				gust=i;
				continue;
			}
			if (enemy.get_attack(i)->get_effect()==16){
				recover=i;
				continue;
			}
			if (enemy.get_attack(i)->get_effect()==9){
				growth=i;
				continue;
			}
			//All other attacks are general: other lists index of attack, other_effective shows effectiveness, other_status records status effect
			other_index++;
			other[other_index]=i;
			if (enemy.get_attack(i)->get_type()==0)
				other_effective[other_index]=enemy.get_attack(i)->get_effective(beerman)*enemy.atk()*float(1+enemy_status[18]/2)/beerman.def()*float(enemy.get_attack(i)->get_power());
			else
				other_effective[other_index]=enemy.get_attack(i)->get_effective(beerman)*enemy.matk()/beerman.mdef()*float(enemy.get_attack(i)->get_power());
			if (enemy.get_attack(i)->get_effect()==19 || enemy.get_attack(i)->get_effect()==20)
				other_effective[other_index]*=4;
			other_status[other_index]=0;
			if ((enemy.get_attack(i)->get_effect()>-1 && enemy.get_attack(i)->get_effect()<9) || (enemy.get_attack(i)->get_effect()>=22 && enemy.get_attack(i)->get_effect()<28)){
				other_status[other_index]=1;
				number_status++;
			}
		}
		int number_objects=0,most_effective_index=0,number_status_eff=0;
		//Retreive number of status conditions
		for (int i=0;i<9;i++){
			if (enemy_status[i]>0)
				number_status_eff++;
		}
		if (enemy_status[17]>0)
			number_status_eff++;
		for (int i=0;i<8;i++){
			if (objects[i]>0)
				number_objects++;}	//Retrieve number of objects on ground
		for (int i=0;i<6;i++){
			if (beerman_status[i+10]>0)
				current_weather=i+10;	//Retreive current weather
		}
		for (int i=0;i<7;i++){
			if (other_effective[i]>other_effective[most_effective_index])
				most_effective_index=i;	//Retreive most effective attack
		}
		//Priority List: War Dance, Weather, Growth (if thunderstorm), Blow away items (>2), Recover (hp low), random(Status, Attack), Backup Move
		//AI Attack Selection List (from least priority to highest priority)
		//First step: at=0 to go to random selection if nothing else applies
		//AI Levels: 0: Almost random, 1: Priority List, 2: Most Effective Start, 3: More Status, 4: No random attack (mostly)
		if (n<3+(ai_lvl>2) && number_status>0 && ai_lvl>2 && beerman.change_hp(0)<int(beerman.hp_max()*.2))	//AI 3+: Attack at low hp
			n=8;
		if (n<3+(ai_lvl>2) && number_status>0 && ai_lvl!=0){	//Select a Status attack
			bool fail;
			int a=0;
			do{
				fail=0;
				a=randint(0,other_index);
				if (!other_status[a])
					fail=1;
				else{
					int status_available=(beerman_status[20]>0)+(beerman_status[17]>0)+(beerman_status[1]>0)+(beerman_status[2]>0);
					if (enemy.get_attack(a)->get_effect()==27 && beerman_status[20]>0)	//No Time Bomb if already there is a time bomb
						fail=1;
					if (enemy.get_attack(a)->get_effect()==22 && beerman_status[15]<1)	//No Animate Plants if there is no Overgrowth
						fail=1;
					if (enemy.get_attack(a)->get_effect()==23 && beerman_status[17]>0)	//No Leech Seed if already there
						fail=1;
					if (enemy.get_attack(a)->get_effect()==1 && beerman_status[1]>0)	//No Immolation Field if already there
						fail=1;
					if (enemy.get_attack(a)->get_effect()==2 && beerman_status[2]>0)	//No Deletion Field if already there
						fail=1;
					if (fail==1 && number_status==1)
						break;
				}
			} while (fail);
			if (fail){
				if (enemy.get_attack(a)->get_mp_req()<=enemy.change_mp(0))	//if mp_req too high go to random selection
					at=enemy.get_attack(a);
			}
		}
		if (n<4 && ai_lvl==4 && at!=0){	//AI 4: Attack at low hp
			if (at->get_effect()!=26){
				if (beerman_status[at->get_effect()]>0)
					n=8;
			}
		}
		if (n>2+(ai_lvl>2) && n<8-ai_lvl && ai_lvl!=0){	//Select a damage-inducing attack
			bool fail;
			int a=0;
			do{
				fail=0;
				a=randint(0,other_index);
				if (other_status[a])
					fail=1;
			} while (fail);
			if (enemy.get_attack(a)->get_mp_req()<=enemy.change_mp(0))	//if mp_req too high go to random selection
				at=enemy.get_attack(a);
		}
		if (((n>7-ai_lvl && n<9) || (number_status>0 && n<3)) && enemy.get_attack(most_effective_index)->get_mp_req()<=enemy.change_mp(0) && ai_lvl!=0)
			at=enemy.get_attack(other[most_effective_index]);
		//Priority List is skipped if AI level is 0
		//n>8 at=0 to go to random selection if nothing else applies
		if (ai_lvl!=0){
			if (neutralize>-1 && number_status_eff>2 && enemy.get_attack(neutralize)->get_mp_req()<=enemy.change_mp(0))
				at=enemy.get_attack(neutralize);
			if (recover>-1 && enemy.change_hp(0)<int(enemy.hp_max()*.2) && enemy.get_attack(recover)->get_mp_req()<=enemy.change_mp(0) && beerman.change_hp(0)>int(beerman.hp_max()*.1))
				at=enemy.get_attack(recover);
			if (number_objects>randint(2,3) && gust>-1 && enemy.get_attack(gust)->get_mp_req()<=enemy.change_mp(0))
				at=enemy.get_attack(gust);
			if (growth>-1 && beerman_status[10]>0 && beerman_status[9]<1 && enemy.get_attack(growth)->get_mp_req()<=enemy.change_mp(0))
				at=enemy.get_attack(growth);
			if (current_weather<0 && weather_atk!=-1 && enemy.get_attack(weather_atk)->get_mp_req()<=enemy.change_mp(0))
				at=enemy.get_attack(weather_atk);
			if (war_dance>-1 && enemy_status[18]<2 && enemy.get_attack(war_dance)->get_mp_req()<=enemy.change_mp(0))
				at=enemy.get_attack(war_dance);
		}
		//If no AI available, go random selection: Starts here
		if (at==0)
		{
			choice=randint(0,enemy.get_max_attack_number());
			at=enemy.get_attack(choice);
			move_chosen=1;
			if (at->get_mp_req()==0 && enemy.change_mp(0)>enemy.get_attack(lowest_mp_number)->get_mp_req())
				at=enemy.get_attack(lowest_mp_number);
			if (enemy.change_mp(0)<enemy.get_attack(lowest_mp_number)->get_mp_req())
				at=enemy.get_attack(0);
			if (at->get_name()=="Gust"){
				if (number_objects==0)
					move_chosen=0;
			}
			if (at->get_effect()>9 && at->get_effect()<16 && current_weather!=-1)
				move_chosen=0;
			if (at->get_mp_req()>enemy.change_mp(0))
				move_chosen=0;
			if (at->get_effect()==16 && enemy.change_hp(0)>enemy.hp_max()/1.5)
				move_chosen=0;
			if (at->get_effect()==27 && beerman_status[20]>0)	//No Time Bomb if already there is a time bomb
				move_chosen=0;
			if (at->get_effect()==22 && beerman_status[15]<1)	//No Animate Plants if there is no Overgrowth
				move_chosen=0;
			if (at->get_effect()==23 && beerman_status[17]>0)	//No Leech Seed if already there
				move_chosen=0;
			if (at->get_effect()==1 && beerman_status[1]>0)	//No Immolation Field if already there
				move_chosen=0;
			if (at->get_effect()==2 && beerman_status[2]>0)	//No Deletion Field if already there
				move_chosen=0;
			if (at->get_effect()==29 && number_status_eff<2)	//No Neutralize if less than 2 status
				move_chosen=0;
			if (move_chosen==0)
				at=0;
		}
		else
			move_chosen=1;
	} while (!move_chosen);
	enemy.change_mp(-at->get_mp_req());
	cout<<enemy.get_name()<<" used "<<at->get_name()<<"!\n";
	if ((enemy.elem()==GRASS || enemy.elem()==EARTH) && at->get_name()=="Growth" && beerman_status[10]<1){	//Cast Growth on self only if element is GRASS/EARTH
		damage=at->attack(beerman,enemy,effect,1);
		cout<<enemy.get_name()<<" grew larger!\n";
		enemy_status[9]=5;
		effect=-1;
	}
	else{
		damage=at->attack(enemy,beerman,effect,1);
		if (at->get_name()=="Growth")
			cout<<"Beer Man grew larger!\n";
	}
	if (at->get_name()=="War Hawk")
		cout<<"A War Hawk was summoned!\n";
	if (at->get_name()=="Acid Rain"){
		cout<<"The weather reverted to normal.\n";
		for (int i=10;i<16;i++)
		{
			beerman_status[i]=0;
			enemy_status[i]=0;
		}
	}
	if (at->get_name()=="Lightning")
	{
		int m=0;
		if ((beerman_status[9]<1 && enemy_status[9]<1) || (beerman_status[9]>0 && enemy_status[9]>0))
		{
			if (m)
				damage=at->attack(beerman,enemy,effect,1);
			else
				damage=at->attack(enemy,beerman,effect,1);
		}
		if (beerman_status[9]>0 && enemy_status[9]<1)
		{
			m=0;
			damage=at->attack(enemy,beerman,effect,1);
		}
		if (beerman_status[9]<1 && enemy_status[9]>0)
		{
			m=1;
			damage=at->attack(beerman,enemy,effect,1);
		}
		if (m){
			if (enemy_status[7]>0)
				damage*=1.5;
			cout<<enemy.get_name()<<" is struck by lightning!\nDMG: "<<damage<<endl;
			enemy.change_hp(-damage);}
		else{
			if (beerman_status[7]>0)
				damage*=1.5;
			cout<<"Beer Man is struck by lightning!\nDMG: "<<damage<<endl;
			beerman.change_hp(-damage);}
		damage=0;
		effect=-1;
	}
	if (damage>0)
	{
		if (effect!=16 && effect!=18)
		{
			int att=1;
			if (enemy_status[3]>0)
			{
				int n=randint(0,3);
				if (!n)
					att=0;
			}
			if (att)
			{
				int multiple_times=1,number_times=0;
				if (effect==19 || effect==20)
					multiple_times=randint(2,5);
				for (int i=0;i<multiple_times;i++)
				{
					int temp_damage=damage,hit_blind=randint(0,4)*(enemy_status[4]>0);
					if (hit_blind<4 && beerman_status[11]>0 && enemy.elem()!=EARTH)
						hit_blind=randint(-13,6);	//85% Accuracy in Sandstorm
					field_damage_manipulate(at->elem(),temp_damage,enemy_status);
					temp_damage+=int(floor(temp_damage*(enemy_status[9]>0)*.2)-floor(temp_damage*(beerman_status[9]>0)*.2));	//Growth
					if (at->get_type()==0)
						temp_damage+=int(floor(temp_damage*.5*enemy_status[18])-floor(temp_damage*.5*beerman_status[19]));	//Stat boosts
					if (at->get_type()==0 && beerman.elem()==EARTH)
						temp_damage=int(floor(damage*pow(.85,objects[3])));
					if (at->get_type()==1 && beerman.elem()==EARTH)
						temp_damage=int(floor(damage*pow(.9,objects[3])));
					if (multiple_times>1)
						temp_damage+=randint(-2,1);
					if (temp_damage<1)
						temp_damage=1;
					if (hit_blind<4){
						cout<<"DMG: "<<temp_damage<<endl;
						beerman.change_hp(-temp_damage);
						number_times++;
					}
					else{
						damage=-100;	//-100 is miss by blindness
						cout<<enemy.get_name()<<" missed!\n";
					}
				}
				if (effect==19 ||effect==20)
					cout<<"Hit "<<number_times<<" times!";
			}
			else
			{
				damage=0;
				cout<<enemy.get_name()<<" hit itself!\nDMG: "<<enemy.atk()<<endl;
				enemy.change_hp(-enemy.atk());
			}
		}
		if (effect==16)
		{
			cout<<"Healed: "<<damage;
			enemy.change_hp(damage);
		}
		if (effect==18)
		{
			cout<<"Mana Restored: "<<damage;
			enemy.change_mp(damage);
		}
	}
	if (at->get_name()=="Volt Tackle" || at->get_name()=="Resign"){
		int d=floor(enemy.hp_max()*.08);
		if (d>25)
			d=25;
		enemy.change_hp(-d);
		cout<<enemy.get_name()<<" took recoil damage: "<<d<<"\n";
	}
	if (at->get_name()=="Separation of Powers"){
		if (beerman_status[18]>-6){
			beerman_status[18]--;
			cout<<"Beer Man's Attack fell!\n";
		}else{cout<<"But Beer Man's Attack cannot fall any lower!\n";}
	}
	if (effect==26 && damage>-1){		//Chaos effect
		effect=randint(2,9);
		if (effect==9)
			effect=0;
	}
	if (effect>-1 && effect<9 && damage>-1)
		effect_text(beerman,effect);
	if (effect>-1 && effect<3 && damage>-1)
		beerman_status[effect]=100;
	if (effect>2 && effect<7 && damage>-1)
		beerman_status[effect]+=7;
	if (effect>6 && effect<10 && damage>-1)
		beerman_status[effect]+=5;
	if (effect>9 && effect<16){
		for (int i=10;i<16;i++){
			beerman_status[i]=0;
			enemy_status[i]=0;
		}
		beerman_status[effect]=8;
		enemy_status[effect]=8;
	}
	if (effect==17){
		cout<<"All ground objects were blown away by the attack!\n";
		for (int i=0;i<8;i++)
			objects[i]=0;
	}
	if (effect==22){
		if (enemy_status[15]>0){
			enemy_status[16]=1;
			cout<<"The plants start to move!\n";
		}else{cout<<"But there were no plants to animate...\n";}
	}
	if (effect==23){
		beerman_status[17]+=10;
		cout<<"Beer Man was seeded!\n";
	}
	if (effect==24){
		if (enemy_status[18]<6){
			enemy_status[18]++;
			cout<<enemy.get_name()<<"'s Attack rises!\n";
		}else{cout<<"But "<<enemy.get_name()<<"'s Attack cannot rise any higher!\n";}
	}
	if (effect==25){
		if (enemy_status[19]<6){
			enemy_status[19]++;
			cout<<enemy.get_name()<<"'s Defense rises!\n";
		}else{cout<<"But "<<enemy.get_name()<<"'s Defense cannot rise any higher!\n";}
	}
	if (effect==27)
		beerman_status[20]=3;
	if (effect==29){
		for (int i=0;i<9;i++)
			enemy_status[i]=0;
		enemy_status[17]=0;
		cout<<enemy.get_name()<<" purified itself from status conditions!\n";
	}
	if (damage<0 && damage!=-100)	//-100 is the miss by blindness
	{
		cout<<enemy.get_name()<<" missed!"<<endl;
	}
	return;
}
int battle_inventory_list(int menu_numbers[],int inventory[],int& j,int hold)	//j is the outside counting variable
{
	//hold: 0: does not check held item (throw), +: does not allow holding new items (use), -: allows dropping held item (drop)
	int choice3=0;
	cout<<"0: Back\n";
	for (int i=1;i<12;i++)
	{
		if (inventory[i]>0 && (hold<1 || (hold>0 && i!=3 && i!=4 && i!=6 && i!=8 && i!=10)))
		{
			menu_numbers[j]=i;
			cout<<j<<": "<<get_inventory_name(inventory,i)<<" ("<<inventory[i]<<")\n";
			j++;
		}
	}
	if (hold==-1)
		cout<<j<<": Get rid of the held item\n";
	bool fail;
	do{
		cin>>choice3;
		fail=cin.fail();
		if (fail){
			cin.clear();
			cin.ignore();
		}
	} while (fail);
	if ((choice3>=j && hold!=-1) || (choice3>j && hold==-1) || (choice3<1))
		return -1;
	return choice3;
}
Attack* throw_item(Beerman& beerman,int& hold,int objects[],int inventory[],int effects_array[],int& back)
{
	cout<<"Throw what?\n";
	int menu_numbers[12],j=1,choice2=battle_inventory_list(menu_numbers,inventory,j,0);
	if (choice2==-1){
		back=1;
		return 0;}
	Attack* combo=0;
	if (choice2>0 && choice2<j){
		inventory[menu_numbers[choice2]]--;
		switch (menu_numbers[choice2])
		{
		case 1:	//Go to case 2
		case 2:
			combo=check_combo(beerman,hold,objects,0,1,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Beer Throw");
			return combo;
			break;
		case 3:
			combo=check_combo(beerman,hold,objects,0,3,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Ember");
			return combo;
			break;
		case 4:
			combo=check_combo(beerman,hold,objects,0,4,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Rock Throw");
			return combo;
			break;
		case 5:
			combo=check_combo(beerman,hold,objects,0,5,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Acid");
			return combo;
			break;
		case 6:
			combo=check_combo(beerman,hold,objects,0,6,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Slow");
			return combo;
			break;
		case 7:
			combo=check_combo(beerman,hold,objects,0,7,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Growth");
			return combo;
			break;
		case 8:
			combo=check_combo(beerman,hold,objects,0,8,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Water Bomb");
			return combo;
			break;
		case 9:
			combo=check_combo(beerman,hold,objects,0,9,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Wind Slash");
			return combo;
			break;
		case 10:
			combo=check_combo(beerman,hold,objects,0,10,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Seed Attack");
			return combo;
			break;
		case 11:
			combo=check_combo(beerman,hold,objects,0,11,0,0,effects_array);
			if (combo==0)
				return beerman.get_attack2("Spark");
			return combo;
			break;
		}
	}
	return 0;
}
Attack* use_item(Beerman& beerman,int& hold,int objects[],int inventory[],int effects_array[],int& back)
{
	cout<<"Use what?\n";
	int menu_numbers[12],j=1,choice2=battle_inventory_list(menu_numbers,inventory,j,hold);
	if (choice2==-1){
		back=1;
		return 0;}
	Attack* combo=0;
	if (choice2>0 && choice2<j){
		inventory[menu_numbers[choice2]]--;
		switch (menu_numbers[choice2])
		{
		case 1:
			cout<<"Beer Man drank beer.";
			beerman.change_hp(ceil(beerman.hp_max()*.5));
			beerman.change_bac(.05);
			break;
		case 2:
			cout<<"Beer Man drank good beer.";
			beerman.change_hp(ceil(beerman.hp_max()*.8));
			beerman.change_bac(.07);
			break;
		case 3:
			hold=3;
			cout<<"Beer Man lit a Match.\n";
			break;
		case 4:
			hold=4;
			cout<<"Beer Man is now holding a Rock.\n";
			break;
		case 5:
			cout<<"Beer Man did some Acid. Beer Man is confused!\n";
			effects_array[3]+=5;
			break;
		case 6:
			hold=6;
			cout<<"Beer Man is now holding some Sand.\n";
			break;
		case 7:
			cout<<"Beer Man took some Steroids. Beer Man grew larger!\n";
			effects_array[9]=5;
			break;
		case 8:
			hold=8;
			combo=check_combo(beerman,hold,objects,0,0,8,0,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man poured some Water into his mouth. Disgusting!\n";
			break;
		case 9:
			combo=check_combo(beerman,hold,objects,0,0,9,0,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man used the Electric Fan to fly up in the air!\n";
			return beerman.get_attack2("Flying Strike");
			break;
		case 10:
			cout<<"Beer Man is now holding a Seed.\n";
			hold=10;
			break;
		case 11:
			cout<<"Beer Man activated a Battery.\n";
			return beerman.get_attack2("Lightning");
			break;
		}
	}
	//No attack
	return 0;
}
Attack* drop_item(Beerman& beerman,int& hold,int objects[],int inventory[],int effects_array[],int& back)
{
	cout<<"Drop what?\n";
	int menu_numbers[12],j=1;
	int choice2=battle_inventory_list(menu_numbers,inventory,j,(hold>0)-2);
	if (choice2==-1){
		back=1;
		return 0;}
	if (choice2==j && hold>0){
		if (hold!=8)
			cout<<"Beer Man let go of his "<<get_inventory_name(inventory,hold)<<".\n";
		else
			cout<<"Beer Man spat out the Water.\n";
		hold=0;}
	Attack* combo=0;
	if (choice2>0 && choice2<j){
		inventory[menu_numbers[choice2]]--;
		switch (menu_numbers[choice2])
		{
		case 1:
			combo=check_combo(beerman,hold,objects,0,0,0,1,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man dropped a Beer on the ground.\n";
			objects[2]++;
			break;
		case 2:
			cout<<"Beer Man dropped a Good Beer on the ground.\n";
			objects[2]++;
			break;
		case 3:
			combo=check_combo(beerman,hold,objects,0,0,0,3,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man lit a match and dropped it on the ground. Nothing happened.\n";
			break;
		case 4:
			cout<<"Beer Man dropped a Rock on the ground.\n";
			objects[3]++;
			if (beerman.elem()==EARTH)
				cout<<"Beer Man begins to use the Rock to build a fort.\n";
			break;
		case 5:
			combo=check_combo(beerman,hold,objects,0,0,0,5,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man dropped a beaker of Acid on the ground.\n";
			objects[4]++;
			break;
		case 6:
			combo=check_combo(beerman,hold,objects,0,0,0,6,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man dropped a Sandbox on the ground.\n";
			objects[0]=1;
			break;
		case 7:
			cout<<"Beer Man dropped some Steroids on the ground.\n";
			objects[5]++;
			break;
		case 8:
			combo=check_combo(beerman,hold,objects,0,0,0,8,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man poured some water on the ground. Nothing happened.\n";
			break;
		case 9:
			combo=check_combo(beerman,hold,objects,0,0,0,9,effects_array);
			if (combo!=0)
				return combo;
			cout<<"Beer Man dropped an Electric Fan on the ground.\n";
			objects[1]++;
			break;
		case 10:
			cout<<"Beer Man dropped a Seed on the ground.\n";
			objects[7]++;
			break;
		case 11:
			cout<<"Beer Man dropped a Battery on the ground.\n";
			objects[6]++;
			break;
		}
	}
	//No attack
	return 0;
}
Attack* check_combo(Beerman& beerman,int& hold,int objects[],int att,int thrw,int use,int drop,int effects_array[])
{
	Attack* atk_list[10];
	int atk_number=0,lose_hold[10],obj_number[10];
	for (int i=0;i<8;i++){
		lose_hold[i]=0;
		obj_number[i]=0;
	}
	if (hold==3 && (att==1 || att==3)){
		atk_list[atk_number]=beerman.get_attack2("Fire Punch");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==FIRE && hold==3 && att==3){
		atk_list[atk_number]=beerman.get_attack2("Falcon Punch");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (hold==8 && att==4){
		atk_list[atk_number]=beerman.get_attack2("Water Blast");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==WATER && hold==8 && att==4){
		atk_list[atk_number]=beerman.get_attack2("Flood");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==WATER && effects_array[13]>0 && att==2){
		atk_list[atk_number]=beerman.get_attack2("Tsunami");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==EARTH && thrw==4){
		atk_list[atk_number]=beerman.get_attack2("Rock Slide");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==AIR && objects[1]>0 && att==2){
		atk_list[atk_number]=beerman.get_attack2("Tornado");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==AIR && objects[1]>0 && att==2 && effects_array[12]>0){
		atk_list[atk_number]=beerman.get_attack2("Cyclone");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[7]>0 && drop==8){
		atk_list[atk_number]=beerman.get_attack2("Overgrowth");
		obj_number[atk_number]=7;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==GRASS && use==8){
		atk_list[atk_number]=beerman.get_attack2("Recover");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if ((att==1 || att==3) && hold==6){
		atk_list[atk_number]=beerman.get_attack2("Sand Attack");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (use==9 && hold==4){
		atk_list[atk_number]=beerman.get_attack2("Meteor Smash");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (thrw==5 && objects[1]>0){
		atk_list[atk_number]=beerman.get_attack2("Corrosive Fumes");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[1]>0 && use==9){
		atk_list[atk_number]=beerman.get_attack2("Aerial Ace");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if ((objects[2]>0 && objects[1]>0 && drop==3) || (use==9 && objects[2]>0 && hold==3)){
		atk_list[atk_number]=beerman.get_attack2("Flamethrower");
		obj_number[atk_number]=2;
		if (use==9)
			lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (hold==3 && att==2){
		atk_list[atk_number]=beerman.get_attack2("Fire Spin");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[7]>0 && use==9){
		atk_list[atk_number]=beerman.get_attack2("Bullet Seed");
		obj_number[atk_number]=7;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[7]>0 && objects[1]>0 && drop==3){
		atk_list[atk_number]=beerman.get_attack2("Bonfire");
		obj_number[atk_number]=8;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[0]>0 && drop==3){
		atk_list[atk_number]=beerman.get_attack2("Glass Shards");
		obj_number[atk_number]=0;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if ((objects[0]>0 && use==9) || (objects[1]>0 && drop==6) || (objects[0]>0 && drop==9)){
		atk_list[atk_number]=beerman.get_attack2("Sandstorm");
		if ((objects[0]>0 && use==9) || (objects[0]>0 && drop==9))
			obj_number[atk_number]=0;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[1]>0 && objects[6]>0 && drop==8){
		atk_list[atk_number]=beerman.get_attack2("Thunderstorm");
		obj_number[atk_number]=6;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[4]>0 && drop==8){	//Explosion only occurs when water is dropped onto acid (bad chemistry)
		cout<<"The Water comes in contact with the Acid.\nThe Acid Beaker used Explosion!\nWow, did they not teach you basic chemistry?\n";
		objects[4]--;
		return beerman.get_attack2("Explosion");}	//Explosion gets top priority! No choice in the matter.
	if ((objects[4]>0 && use==9) || (drop==5 && objects[1]>0)){
		atk_list[atk_number]=beerman.get_attack2("Acid Rain");
		obj_number[atk_number]=4;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (effects_array[15]>0 && (drop==1 || drop==2)){
		atk_list[atk_number]=beerman.get_attack2("Animate Plants");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (hold==10 && (att==1 || att==3)){
		atk_list[atk_number]=beerman.get_attack2("Leech Seed");
		lose_hold[atk_number]=1;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (beerman.elem()==NEUTRAL && att==2){
		atk_list[atk_number]=beerman.get_attack2("War Dance");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[1]>0 && (thrw==2 || thrw==1)){
		atk_list[atk_number]=beerman.get_attack2("Beer Missile");
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (objects[2]>0 && drop==5){
		atk_list[atk_number]=beerman.get_attack2("Time Bomb");
		obj_number[atk_number]=2;
		if (atk_list[atk_number]->get_bac_req()<=beerman.change_bac(0))
			atk_number++;}
	if (atk_number==0)
		return 0;
	//Menu for choosing combo attack
	cout<<"0: Original Selection\n";
	for (int i=0;i<atk_number;i++)
		cout<<i+1<<": "<<atk_list[i]->get_name()<<"\n";
	bool fail;
	int choice=0;
	do{
		cin>>choice;
		fail=cin.fail();
		if (fail)
		{
			cin.clear();
			cin.ignore();
		}
	} while (fail);
	if (choice<1 || choice>atk_number)
		return 0;
	if (obj_number[choice-1]==8){
		objects[5]--;
		objects[7]--;}
	else
		objects[obj_number[choice-1]]--;
	if (lose_hold[choice-1]>0)
		hold=0;
	return atk_list[choice-1];
}
int perform_effects(Enemy& enemy,int effects_array[],int perform)
{
	//Returns leech seed HP value, otherwise 0
	int total_effects=0;
	for (int i=0;i<10;i++)
	{
		if (effects_array[i]>0) 
			total_effects++;
	}
	if (effects_array[17]>0)
		total_effects++;
	if (total_effects==0)
		return 0;
	if (effects_array[0]>0)
	{
		int dmg=0;
		if (perform){
			if (int(enemy.hp_max()*.06)>20)
				dmg=-20;
			else
				dmg=-int(enemy.hp_max()*.06);
		}
		enemy.change_hp(dmg);
		cout<<enemy.get_name()<<" is poisoned!\n";
		if (perform)
			cout<<"DMG: "<<-dmg<<endl;
	}
	if (effects_array[1]>0)
	{
		cout<<enemy.get_name()<<" is within an Immolation Field!\n";
		if (perform){
			enemy.change_hp(-10);
			cout<<"DMG: 10"<<endl;
		}
	}
	if (effects_array[2]>0)
	{
		cout<<enemy.get_name()<<" is within a Deletion Field!\n";
		if (perform){
			enemy.change_hp(-25);
			cout<<"DMG: 25"<<endl;
		}
	}
	if (effects_array[3]>0)
		cout<<enemy.get_name()<<" is confused!"<<endl;
	if (effects_array[4]>0)
		cout<<enemy.get_name()<<" is blind!"<<endl;
	if (effects_array[5]>0)
		cout<<enemy.get_name()<<" is paralyzed!"<<endl;
	if (effects_array[6]>0)
	{
		int dmg=0;
		cout<<enemy.get_name()<<" is burned!\n";
		if (perform){
			if (int(enemy.hp_max()*.08)>25)
				dmg=-25;
			else
				dmg=-int(enemy.hp_max()*.08);
			enemy.change_hp(dmg);
			cout<<"DMG: "<<-dmg<<endl;
			dmg=enemy.change_mp(0)-enemy.change_mp(-int(ceil(enemy.mp_max()*.05)));
			if (dmg>0)
				cout<<enemy.get_name()<<" lost "<<dmg<<" MP!\n";
		}
	}
	if (effects_array[7]>0)
		cout<<enemy.get_name()<<" is drenched!"<<endl;
	if (effects_array[8]>0)
		cout<<enemy.get_name()<<" is slow!"<<endl;
	if (effects_array[9]>0)
		cout<<enemy.get_name()<<" is large!"<<endl;
	int seed_hp=0;
	if (effects_array[17]>0){
		if (perform){
			seed_hp=floor(enemy.hp_max()*.08);
			if (seed_hp>20)
				seed_hp=20;
			enemy.change_hp(-seed_hp);
			cout<<enemy.get_name()<<"'s life was leeched!\nLeeched: "<<seed_hp<<endl;
		}else{cout<<enemy.get_name()<<" is seeded!"<<endl;}
	}
	pause();
	return seed_hp;
}
void perform_field(Beerman& beerman,Enemy& enemy,int beerman_status[],int enemy_status[],int perform)
{
	int field_exists=0;
	for (int i=10;i<=15;i++){
		if (beerman_status[i]>0)
			field_exists=1;
	}
	if ((beerman_status[20]>0 || enemy_status[20]>0) && !perform)
		field_exists=1;
	if (!field_exists)
		return;
	cout<<endl;
	if (beerman_status[10]>0)
	{
		if (perform)
		{
			cout<<"The thunderstorm continues.\n";
			int n=randint(0,4);
			if (n)
			{
				Attack *a;
				int effect=-1,acc=1,damage=0,m=randint(0,1);
				a=beerman.get_attack2("Lightning",0);
				if ((beerman_status[9]<1 && enemy_status[9]<1) || (beerman_status[9]>0 && enemy_status[9]>0))
				{
					if (m)
						damage=a->attack(beerman,enemy,effect,acc);
					else
						damage=a->attack(enemy,beerman,effect,acc);
				}
				if (beerman_status[9]>0 && enemy_status[9]<1)
				{
					m=0;
					damage=a->attack(enemy,beerman,effect,acc);
				}
				if (beerman_status[9]<1 && enemy_status[9]>0)
				{
					m=1;
					damage=a->attack(beerman,enemy,effect,acc);
				}
				damage=int(damage*.75);
				if (m){
					if (enemy_status[7]>0)
						damage*=1.5;
					cout<<enemy.get_name()<<" is struck by lightning!\nDMG: "<<damage<<endl;
					enemy.change_hp(-damage);}
				else{
					if (beerman_status[7]>0)
						damage*=1.5;
					cout<<"Beer Man is struck by lightning!\nDMG: "<<damage<<endl;
					beerman.change_hp(-damage);}
			}
		}
		else
			cout<<"There is a thunderstorm.\n";
	}
	if (beerman_status[11]>0)
	{
		if (perform)
		{
			cout<<"The sandstorm continues to blow.\n";
			if (beerman.elem()!=EARTH){
				cout<<"Beer Man is buffeted by the sandstorm!\nDMG: 5\n";
				beerman.change_hp(-5);
			}
			if (enemy.elem()!=EARTH){
				cout<<enemy.get_name()<<" is buffeted by the sandstorm!\nDMG: 5\n";
				enemy.change_hp(-5);
			}
		}else{cout<<"A sandstorm is blowing.\n";}
	}
	if (beerman_status[12]>0)
	{
		if (perform)
		{
			cout<<"The tornado continues to blow.\n";
			if (beerman.elem()!=AIR){
				cout<<"Beer Man is launched into the air by the tornado!\nDMG: 12\n";
				beerman.change_hp(-12);
			}
			if (enemy.elem()!=AIR){
				cout<<enemy.get_name()<<" is launched into the air by the tornado!\nDMG: 12\n";
				enemy.change_hp(-12);
			}
		}else{cout<<"A tornado is blowing.\n";}
	}
	if (beerman_status[13]>0)
		cout<<"The ground is flooded.\n";
	if (beerman_status[14]>0)
		cout<<"A large fire is blazing.\n";
	if (beerman_status[15]>0){
		cout<<"There are plants all over the ground.\n";
		if (perform){
			if (beerman.elem()==GRASS){
				cout<<"Beer Man regains 7 HP!\n";
				beerman.change_hp(7);
			}
			if (enemy.elem()==GRASS){
				cout<<enemy.get_name()<<" regains 7 HP!\n";
				enemy.change_hp(7);
			}
		}
		if (beerman_status[16]){
			if (perform){
				int damage,effect;
				cout<<"The drunken plants ooze with alcohol. Beer Man regains "<<floor(beerman.hp_max()*.08)<<" HP!\n";
				beerman.change_hp(int(floor(beerman.hp_max()*.08)));
				Attack *atk_ptr=new Attack("Vine Whip",GRASS,1,6,-1,100,100,1,0);
				damage=atk_ptr->attack(beerman,enemy,effect,1);
				cout<<"The drunken plants use Vine Whip!\nDMG: "<<damage<<endl;
				enemy.change_hp(-damage);
				delete atk_ptr;
			}else{cout<<"Some of the plants are drunk.\n";}
		}
		if (enemy_status[16]){
			if (perform){
				int damage,effect;
				Attack *atk_ptr=new Attack("Vine Whip",GRASS,1,6,-1,100,100,1,0);
				damage=atk_ptr->attack(enemy,beerman,effect,1);
				cout<<"The animated plants use Vine Whip!\nDMG: "<<damage<<endl;
				beerman.change_hp(-damage);
				delete atk_ptr;
			}else{cout<<"Some of the plants are animated.\n";}
		}
	}
	if (!perform)
	{
		if (beerman_status[20]>0){
			cout<<"A Time Bomb near Beer Man is at T minus "<<beerman_status[20]<<" rounds.\n";
		}
		if (enemy_status[20]>0){
			cout<<"A Time Bomb near "<<enemy.get_name()<<" is at T minus "<<enemy_status[20]<<" rounds.\n";
		}
	}
	pause();
}
void check_battle_objects(const int& hold,const int objects[])
{
	switch (hold)
	{
	case 3:
		cout<<"Beer Man is holding a lit Match.\n";
		break;
	case 4:
		cout<<"Beer Man is holding a Rock.\n";
		break;
	case 6:
		cout<<"Beer Man is holding some Sand.\n";
		break;
	case 8:
		cout<<"Beer Man is holding Water in his mouth.\n";
		break;
	case 10:
		cout<<"Beer Man is holding a Seed.\n";
		break;
	default:
		cout<<"Beer Man is not holding anything.\n";
		break;
	}
	if (objects[0]>0)
		cout<<"A Sandbox is on the ground.\n";
	if (objects[1]>0)
		cout<<"An Electric Fan is on the ground.\n";
	if (objects[2]>0)
		cout<<objects[2]<<" Beer(s) are on the ground\n";
	if (objects[3]>0)
		cout<<objects[3]<<" Rock(s) are on the ground.\n";
	if (objects[4]>0)
		cout<<objects[4]<<" Acid Beaker(s) are on the ground\n";
	if (objects[5]>0)
		cout<<objects[5]<<" Steroids(s) are on the ground.\n";
	if (objects[6]>0)
		cout<<objects[6]<<" Battery(s) are on the ground\n";
	if (objects[7]>0)
		cout<<objects[7]<<" Seed(s) are on the ground.\n";
	pause();
	return;
}
void field_damage_manipulate(int at_element,int& damage,int effects_array[])
{
	if (effects_array[11]>0 && at_element==EARTH)
		damage=int(floor(damage*1.5));
	if (effects_array[12]>0 && at_element==AIR)
		damage=int(floor(damage*1.5));
	if (effects_array[13]>0 && at_element==WATER)
		damage=int(floor(damage*1.5));
	if (effects_array[14]>0 && at_element==FIRE)
		damage=int(damage*1.8);
	if (effects_array[15]>0 && at_element==GRASS)
		damage=int(floor(damage*1.7));
}
void effect_text(Enemy& target,const int& effect)
{
	if (effect<0 || effect>9)
		return;
	cout<<target.get_name();
	switch (effect)
	{
	case 0:
		cout<<" becomes poisoned!\n";
		break;
	case 1:
		cout<<" becomes surrounded by an Immolation Field!\n";
		break;
	case 2:
		cout<<" becomes surrounded by a Deletion Field!\n";
		break;
	case 3:
		cout<<" becomes confused!\n";
		break;
	case 4:
		cout<<" becomes blind!\n";
		break;
	case 5:
		cout<<" becomes paralyzed!\n";
		break;
	case 6:
		cout<<" gets burned!\n";
		break;
	case 7:
		cout<<" becomes drenched!\n";
		break;
	case 8:
		cout<<" becomes slow!\n";
		break;
	case 9:
		cout<<" grows larger!\n";
		break;
	}
	return;
}
int menu(int num_options, ... )
{
	//Variable arguments that display each individual item as a menu option
	int select=0;
	va_list arguments;
	va_start(arguments,num_options);
	for (int k=1; k<=num_options; k++){
		cout<<k<<": "<<va_arg(arguments,char*)<<endl;
	}
	va_end(arguments);
	bool fail;
	do{
		cin>>select;
		fail=cin.fail();
		if (fail)
		{
			cin.clear();
			cin.ignore();
		}
	} while (fail);
	return select;
}
void pause()
{
	while (1){
		if (_kbhit())
			break;
	}
	_getch();
	cout<<endl;
}
void bar(int inventory[],Beerman& beerman,Enemy barfighter)
{
	int choice=0;
	do{
		system("CLS");
		cout<<"The Bar\n-------\n";
		choice=menu(5,"Get a Drink: Price differs","Beer: $7","Good Beer: 15$","Solicit","Back");
		switch (choice)
		{
		case 1:
			{
				cout<<"A normal beer is $5. Special drinks are $10. Which one would you like?\n";
				int choice2=menu(8,"Beer","Hydrogen Beer","Diluted Beer","Dirty Beer","Carbonated Beer","Organic Beer","Neutral Beer","None");
				if (choice2==8)
					break;
				if (choice2==1)
				{
					if (inventory[0]>=5)
					{
						inventory[0]-=5;
						beerman.change_hp(int(beerman.hp_max()/2));
						cout<<"Beer Man: Ahhh.... That hit the spot!";
						pause();
						if (beerman.change_bac(.05)>.4)
							blackout(inventory,beerman);
					}
					else
					{
						cout<<"Bartender: You ain't got the money, bub.";
						pause();
					}
				}
				if (choice2>1)
				{
					if (inventory[0]>=10)
					{
						inventory[0]-=10;
						beerman.change_hp(int(beerman.hp_max()/2));
						beerman.change_element(choice2-1);
						if (choice2==7)
							beerman.change_element(NEUTRAL);
						cout<<"Beer Man: Whoooooa. What is this stuff?";
						pause();
						cout<<"Bartender: It's our specialty beer. It can change your elemental types.";
						pause();
						if (beerman.change_bac(.05)>.4)
							blackout(inventory,beerman);
					}
					else
					{
						cout<<"Bartender: You ain't got the money, bub.";
						pause();
					}
				}
			}
			break;
		case 2:
			if (inventory[0]>=7)
			{
				inventory[0]-=7;
				inventory[1]++;
				cout<<"You bought 1 Beer!";
			}
			else
			{
				cout<<"You don't have enough money for that!";
			}
			pause();
			break;
		case 3:
			if (inventory[0]>=15)
			{
				inventory[0]-=15;
				inventory[2]++;
				cout<<"You bought 1 Good Beer!";
			}
			else
			{
				cout<<"You don't have enough money for that!";
			}
			pause();
			break;
		case 4:
			{
				int number=randint(1,20);
				if (number>10 && number<17)
					cout<<"He responds by punching you in the face.";
				if (number>10 && number>16)
					cout<<"A big, burly man comes up and cracks his knuckles. Oh crap.";
				if (number>10)
				{
					pause();
					if (!battle_init(inventory,beerman,barfighter,number,1,1))
						blackout(inventory,beerman);
				}
				else
				{
					number=randint(1,5);
					inventory[0]+=number;
					cout<<"Man: Whatever.\nHe hands you some money. Obtained $"<<number<<"!";
					pause();
				}
			}
			break;
		case 5:
			break;
		}
	} while (choice!=5);
}
void gym(int inventory[],Beerman& beerman,Enemy punchingbag,Enemy gymmember,Enemy gymboxer,Enemy gymchampion,Enemy pikachu)
{
	int choice=0,win=1;
	do{
		win=1;
		system("CLS");
		cout<<"The Gym\n-------\n";
		choice=menu(6,"Newbies Training Room: Levels 1-5","Intermediate Fighters: Levels 6-10","Fighters' Ring: Levels 11-15","Heavyweights' Room: Levels 16-20","Off limits","Back");
		switch (choice)
		{
		case 1:
			win=battle_init(inventory,beerman,punchingbag,randint(1,5),0,1);
			break;
		case 2:
			win=battle_init(inventory,beerman,gymmember,randint(6,10),1,1);
			break;
		case 3:
			win=battle_init(inventory,beerman,gymboxer,randint(11,15),1,1);
			break;
		case 4:
			win=battle_init(inventory,beerman,gymchampion,randint(16,20),2,1);
			break;
		case 5:
			cout<<"Beer Man: So what's in this room of the Gym?\n";
			pause();
			cout<<"???: Oh, there's the leader!\n";
			pause();
			cout<<"Beer Man: Huh?\n";
			pause();
			cout<<"Ash Ketchum: I'm Ash Ketchum! I challenge you to a Pokemon battle so that\n"
				<<"I can win all of the gym badges! Go Pikachu!\n";
			pause();
			cout<<"Beer Man: ...um... Go Beer Man!\n";
			pause();
			win=battle_init(inventory,beerman,pikachu,30,2,2);
			if (win)
			{
				cout<<"And Ash lost yet again, because he has no battling skills.\n";
				pause();
				cout<<"Ash Ketchum: I'll be back, and stronger than ever before!\n";
				pause();
				cout<<"Beer Man: ...Yeah. Right.\n";
				pause();
			}
			break;
		case 6:
			break;
		}
		if (!win)
			blackout(inventory,beerman);
	} while (choice!=6);
}
void playground(int inventory[],Beerman& beerman,Enemy boy,Enemy girl,Enemy policeman)
{
	int choice=0,watching=randint(0,2),timer=-1,win=1;
	do{
		timer+=1;
		if (timer>=2)
		{
			timer=0;
			watching=randint(0,2);
		}
		system("CLS");
		cout<<"The Playground\n--------------\n";
		choice=menu(4,"Steal that Sandbox","Look around","Act suspicious","Leave");
		switch (choice)
		{
		case 1:
			{
				cout<<"Yeah! Let's do this!\n";
				pause();
				int r=randint(0,2);
				if (!watching && r)
				{
					cout<<"Beer Man somehow managed to pry the Sandbox out of the ground and steal it\nwithout being seen. Hooray for teaching family values!\n";
					pause();
					cout<<"Beer Man obtained 1 Sandbox!";
					pause();
					inventory[6]++;
					break;
				}
				if (!watching && !r)
				{
					cout<<"Beer Man: I get the feeling that somebody is watching me...";
					pause();
				}
				int i=randint(0,1);
				string kidname;
				(watching==1) ? kidname="Little Boy" : kidname="Little Girl";
				if (i)
					cout<<kidname<<": Hey mister, what are you doing?";
				if (!i)
					cout<<kidname<<": HEY! I'm playing in the sandbox right now!";
				pause();
				if (!watching && !r)
					cout<<"Beer Man: ****! I knew it!";
				else
					cout<<"Beer Man: I must has the Sandbox! You can't stop me!";
				pause();
				if (watching==1)
				{
					r=1;
					win=battle_init(inventory,beerman,boy,randint(2,4),0,0);
				}
				if (watching==2 || !r)
					win=battle_init(inventory,beerman,girl,randint(2,4),0,0);
				if (!win)
				{
					cout<<"Beer Man: Ugh, how humiliating... to be beaten by a "<<kidname<<"!";
					pause();
					break;
				}
				i=randint(0,3);
				if (i)
				{
					cout<<"*tweet**tweet**tweet*!!!!";
					pause();
					cout<<"Policeman: Hey you! No assaulting children!";
					pause();
					win=battle_init(inventory,beerman,policeman,randint(5,7),1,0);
					if (!win)
					{
						cout<<"Beer Man: Noo...! So... close...!";
						pause();
						break;
					}
					cout<<"Beer Man: Cool. Now, to steal that Sandbox...";
					pause();
					inventory[6]++;
					cout<<"Beer Man obtained 1 Sandbox!";
					pause();
					break;
				}
				if (!win)
					break;
				cout<<"...";
				pause();
				cout<<"Beer Man: Wow, I got away with beating up little kids! Yay!";
				pause();
				cout<<"Beer Man: Now, to steal that Sandbox...";
				pause();
				inventory[6]++;
				cout<<"Beer Man obtained 1 Sandbox!";
				pause();
				break;
			}
		case 2:
			{
				int i=randint(0,4);

				if (!i)
				{
					cout<<"Policeman: You look suspicious. What are you doing?";
					pause();
					cout<<"Beer Man: Uh...";
					pause();
					cout<<"Policeman: Sir, I'm afraid I must remove you from these premises immediately.";
					pause();
					win=battle_init(inventory,beerman,policeman,randint(7,10),1,1);
					if (!win)
						break;
					cout<<"Beer Man: Whew, that was a close one.";
					pause();
					break;
				}
				switch (watching)
				{
				case 0:
					cout<<"No one's watching... probably.";
					break;
				case 1:
					cout<<"A little boy is staring at you intently.";
					break;
				case 2:
					cout<<"A little girl is watching you carefully.";
					break;
				}
				pause();
				break;
			}
		case 3:
			cout<<"Policeman: You look suspicious. What are you doing?";
			pause();
			cout<<"Beer Man: *shifty eyes*";
			pause();
			cout<<"Policeman: Sir, I'm afraid I must remove you from these premises immediately.";
			pause();
			win=battle_init(inventory,beerman,policeman,randint(5,7),1,1);
			break;
		case 4:
			break;
		}
		if (!win)
		{
			inventory[0]=int(inventory[0]*.7);
			cout<<"You black out...\n";
			pause();
			cout<<"...???\n";
			pause();
			cout<<"You regain consciousness.\n";
			pause();
			cout<<"Police: Hello there. You are here in jail for questionable behavior\n"
				<<"at a playground. More specifically, attempting or appearing to attempt\n"
				<<"to assault children. We will let you go for 30% of your current holdings.";
			pause();
			cout<<"Beer Man: ...\n";
			pause();
			cout<<"You handed them your money. You have $"<<inventory[0]<<" left.\n";
			pause();
			beerman.change_hp(beerman.hp_max());
			win=1;
		}
	} while (choice!=4);
	return;
}
void shop(int inventory[],int& show_combo_tutorial)
{
	system("CLS");
	int have_money,choice;
	cout<<"General Store\n-------------\nWelcome to Surgeon General's General Store, the store with all things\nharmful and harmless. What would you like?\n\n";
	if (show_combo_tutorial)
	{
		pause();
		cout<<"Surgeon General: Ah, it's your first time here. Well, you are probably\nwondering "
			<<"why you would need to buy so many random and innocuous items. They're\nuseless, right? "
			<<"WRONG! You'll never make it in the crazy world out there by\nyourself, no matter "
			<<"who you are. That's why we have items!\n";
		pause();
		cout<<"Beer Man: Huh. Really. I think that all I need is beer.\n";
		pause();
		cout<<"Surgeon General: That's where you're wrong, my friend. Normal attacks won't\nwork on those "
			<<"insanely hard enemies out there. That's where Combo Attacks come\nin handy! By placing and "
			<<"using certain items in certain ways, you can create\nnew attacks! Here's a freebie:\n"
			<<"Holding a Match and Punching will allow you to use Fire Punch.\n";
		pause();
		cout<<"Beer Man: Oooooohhh. Me likey!\n";
		pause();
		cout<<"Surgeon General: Note that sometimes your elemental affinity also comes into\nplay. Also "
			<<"remember that your BAC can cause certain combos to work or not.\nChoose your items wisely, "
			<<"and you will come out on top! Now go buy some items!\n*sneaky grin*\n";
		pause();
		show_combo_tutorial=0;
	}
	do
	{
		have_money=0;
		cout<<"Beer Man has $"<<inventory[0]<<".\n\n";
		choice=menu(7,"Match - $5","Water Bottle - $8","Acid - $12","Steroids - $15","Battery - $17","Electric Fan - $20","Back");
		switch (choice)
		{
		case 1:
			if (inventory[0]>=5){
				inventory[0]-=5;
				inventory[3]++;
				cout<<"Bought a Match.\n";
				have_money=1;
			}
			break;
		case 2:
			if (inventory[0]>=8){
				inventory[0]-=8;
				inventory[8]++;
				cout<<"Bought a Water Bottle.\n";
				have_money=1;
			}
			break;
		case 3:
			if (inventory[0]>=12){
				inventory[0]-=12;
				inventory[5]++;
				cout<<"Bought an Acid Bottle.\n";
				have_money=1;
			}
			break;
		case 4:
			if (inventory[0]>=15){
				inventory[0]-=15;
				inventory[7]++;
				cout<<"Bought a Steroid.\n";
				have_money=1;
			}
			break;
		case 5:
			if (inventory[0]>=17){
				inventory[0]-=17;
				inventory[11]++;
				cout<<"Bought a Battery.\n";
				have_money=1;
			}
			break;
		case 6:
			if (inventory[0]>=20){
				inventory[0]-=20;
				inventory[9]++;
				cout<<"Bought an Electric Fan.\n";
				have_money=1;
			}
			break;
		case 7:
			break;
		default:
			choice=0;
			break;
		}
		if (choice<7 && choice>0 && !have_money)
			cout<<"You don't have enough money!\n";
		if (choice!=7)
			pause();
	} while (choice!=7);
	return;
}
int dungeon(string area,int size_x,int size_y,int start_x,int start_y,int end_x,int end_y,int& x,int& y)
{
	int choice2=0;
	string movement="";
	while (choice2==0){
		system("CLS");
		cout<<area<<": ("<<x<<","<<y<<")\n";
		if (x==start_x && y==start_y)
			choice2=menu(5,"North","South","East","West","Back");
		else
			choice2=menu(5,"North","South","East","West","Stay in place");
		switch (choice2)
		{
		case 1:
			y++;
			movement="Moved North.";
			break;
		case 2:
			y--;
			movement="Moved South.";
			break;
		case 3:
			x++;
			movement="Moved East.";
			break;
		case 4:
			x--;
			movement="Moved West.";
			break;
		case 5:
			if (x==start_x && y==start_y)
				movement="Moving Back.";
			else
				movement="Staying here.";
			break;
		}
		if (y<0 || y>size_y || x<0 || x>size_x)
		{
			if (y<0)
				y=0;
			if (x<0)
				x=0;
			if (y>size_y)
				y=size_y;
			if (x>size_x)
				x=size_x;
			cout<<"Cannot move in that direction!";
			choice2=0;
		}
		else
			cout<<movement;
		pause();
	}
	if (x==start_x && y==start_y)
		return -1;
	if (x==end_x && y==end_y)
		return 0;
	return 1;
}
void blackout(int inventory[],Beerman& beerman)
{
	inventory[0]=int(inventory[0]*.8);
	cout<<"You black out...\n";
	pause();
	cout<<"...???\n";
	pause();
	cout<<"You regain consciousness.\n";
	pause();
	cout<<"You were robbed! You have $"<<inventory[0]<<" left.\n";
	pause();
	beerman.change_hp(beerman.hp_max());
	if (beerman.change_bac(0)>=.4)
	{
		beerman.change_bac(-beerman.change_bac(0));
		beerman.change_bac(.39);
	}
}
void show_inventory(int inventory[])
{
	cout<<"Inventory\n---------\n\n";
	for (int i=1;i<12;i++)
	{
		if (inventory[i]>0)
			cout<<get_inventory_name(inventory,i)<<": "<<inventory[i]<<endl;
	}
	pause();
}
string get_inventory_name(int inventory[],int number)
{
	switch (number)
	{
	case 0:
		return "Money";
		break;
	case 1:
		return "Beer";
		break;
	case 2:
		return "Good Beer";
		break;
	case 3:
		return "Match";
		break;
	case 4:
		return "Rock";
		break;
	case 5:
		return "Acid";
		break;
	case 6:
		return "Sandbox";
		break;
	case 7:
		return "Steroids";
		break;
	case 8:
		return "Water Bottle";
		break;
	case 9:
		return "Electric Fan";
		break;
	case 10:
		return "Seed";
		break;
	case 11:
		return "Battery";
		break;
	default:
		return "Error: No item name";
		break;
	}
}
int save(Beerman beerman,const int inventory[],int mission_number,string mission_string,int area,int show_combo_tutorial,const int high_score[])
{
	cout<<"Saving game... Please do not close the program.\n";
	ofstream out_file("save.dat",ios::trunc);
	if (out_file.bad())
	{
		cerr<<"Error with opening/creating save.dat\n";
		return 0;
	}
	out_file<<beerman;
	out_file<<mission_number<<endl;
	for (int i=0;i<12;i++)
		out_file<<inventory[i]<<endl;
	out_file<<area<<endl;
	out_file<<show_combo_tutorial<<endl;
	for (int i=0;i<6;i++)
		out_file<<high_score[i]<<endl;
	out_file<<mission_string<<endl;
	out_file.close();
	cout<<"Game saved.\n";
	pause();
	return 1;
}
void lost_woods_description(const int& x,const int& y)
{
	int x_prox=abs(x-4),y_prox=abs(y-4),n=randint(0,1);
	if (x_prox<=1 && y_prox<=1 && (x_prox!=0 && y_prox!=0)){
		cout<<"You see less trees.\n";
		pause();
	}
	else{
		if (n && (x_prox!=0 && y_prox!=0)){
			cout<<"You see trees.\n";
			pause();
		}
	}
	if (x_prox==0 && y_prox==0){
		cout<<"You are in a clearing.\n";
		pause();
	}
}
void neo_hq_description(const int& x,const int& y,int& mission_number,string& mission)
{
	if (x==0 || x==4 || y==0 || y==4){
		cout<<"You are at the wall of the large HQ room.\n";
		pause();
	}
	if (x==2 && y==2){
		cout<<"You see here a computer.\n";
		pause();
		cout<<"Beer Man examines the screen for beer-related products.\nInstead, he finds a message:\n";
		pause();
		cout<<"To the Most Esteemed and Gracious Sir Elliot,\n\n"
			<<"After witnessing your great advances with the Neo-Temperance Movement in\n"
			<<"Austria, the Temperance Movement in the United Radistates of Feesica\n"
			<<"would like to cordially invite you to join us in a meeting to discuss\n"
			<<"a world revival of beer-destruction. Please arrive promptly at the\n"
			<<"Temperance HQ in Libeerty City February 18, 2011.\n\n"
			<<"Thank You,\nThe Temperance Movement of the URF\n";
		pause();
		cout<<"Beer Man: ****!";
		pause();
		mission="Mission: Return to Libeerty City as inconspicuously as possible.";
		mission_number=7;
		cout<<mission;
		pause();
	}
}
void chapter_1_init(int& mission_number,string& mission)
{
	cout<<"March 15, 2011: Libeerty City, URF"<<endl;
	pause();
	cout<<"City Council: Hello, Mayor Beer Man. We have some news for you."<<endl;
	pause();
	cout<<"Beer Man: (drunk) huuuuuhh? what is it? *hic*"<<endl;
	pause();
	cout<<"City Council: You're fired. You're so lazy and incompetant\nthat you are a "
		<<"disgrace to the city. In fact, you're going to be\nexiled to Austria. We have appointed "
		<<"a new mayor, Bier Mann in your place.\nSee you later. Or not."<<endl;
	pause();
	cout<<"Beer Man: ...wait whut happened?";
	pause();
	system("CLS");
	cout<<"CHAPTER 1: AUSTRIA\n"
		<<"------------------"<<endl;
	pause();
	cout<<"Austria, the home of great artists, musicians, and history. What\n"
		<<"a wonderful place to be in. But Beer Man is thinking of something else..."<<endl;
	pause();
	cout<<"Beer Man: Wow. I just got booted. How can I get my position back?\n";
	pause();
	cout<<"*sneak sneak sneak*\n";
	pause();
	cout<<"*snatch*\n";
	pause();
	cout<<"Beer Man: Wait a second, that guy just stole my wallet! Come back here!\n";
	pause();
	cout<<mission;
	pause();
	system("CLS");
}
void chapter_2_init(int& mission_number,string& mission,int& area)
{
	cout<<"Whilst at the Austrian Airport Beer Man notices some Libeerty City Councilmen.\n";
	pause();
	cout<<"Beer Man: Waaaaazup.\n";
	pause();
	cout<<"Mission Failed.\nGAME OVER\n";
	pause();
	cout<<"City Council: Beer Man! It's an outrage! Bier Mann has disappeared and the\nformer Temperance Movement has returned in full scale!\n"
		<<"We need you to return to your former position as mayor of Libeerty City\nto stop the Temperance Movement! We apologize for your exile\n"
		<<"and will fully compensate you for your airplane tickets back.\n";
	pause();
	cout<<"Beer Man thusly took a free airplane ride back to Libeerty City.\n";
	area=3;
	pause();
	system("CLS");
	cout<<"CHAPTER 2: THE RETURN\n"
		<<"---------------------\n";
	pause();
	cout<<"Beer Man and the City Council sat down for a meeting at the City Hall.\n";
	pause();
	cout<<"City Council: So Beer Man. Again, we are so terribly sorry about\nall of this. Now, about your duties...\n";
	pause();
	cout<<"Beer Man: I don't care for legal stuff! I just want to beat people up!\n";
	pause();
	cout<<"City Council: *facepalm* Fine. We will reinstate the Beer Council for you.\nCome back to City Hall for your latest mission.\n"
		<<"Your first mission is to eliminate the Fire Man.\n";
	pause();
	cout<<"Beer Man: ...Heh. Just like Beer Man I all over again.\n";
	pause();
	mission="Mission: Defeat the Fire Man.";
	mission_number=8;
	cout<<mission;
	pause();
}
void beer_council(int& mission_number,string& mission)
{
	switch (mission_number)
	{
	case 8:
		cout<<"Beer Council: Your first target is Fire Man. You might remember him\nfrom Beer Man I. Eliminate him.\n";
		pause();
		break;
	case 9:
		cout<<"Beer Council: Alright, your next target is the late Lyman Beecher.\n"
			<<"Apparently the Temperance Movement revived him as a zombie.\nShould be pretty easy.\n";
		pause();
		mission="Mission: Remove Lyman Beecher.";
		break;
	case 10:
		cout<<"Beer Council: For the last few days, a Carrie Nation has been\n"
			<<"defacing city property with anti-beer slogans. It is your job to take\nher out. But be careful, we also have reports "
			<<"of her being a lich.\nIn that case it may be impossible to take her out before removing\n"
			<<"her phylactery. Find her soul, destroy it, then destroy Carrie Nation!\n";
		pause();
		cout<<"Beer Council: As for the location of her soul, it may be prudent to\nsearch the apartment complex. Unfortunately, we do not\n"
			<<"know which room she is staying in, but here is her card:\n"
			<<"--------------------\nCarrie Nation\nPhone: 800-XOWATER\nRoom: H2O.\nLong Live Temperance!\n--------------------\n";
		pause();
		mission="Mission: Destroy Carrie Nation's phylactery.";
		break;
	case 11:
		cout<<"Beer Council: So did you destroy the phylactery?\n";
		pause();
		cout<<"Beer Man: I threw it in the trash can!\n";
		pause();
		cout<<"Beer Council: YOU IDIOT! A trash can won't destroy a phylactery!\nGo get it again and properly destroy it.";
		pause();
		mission="Mission: Properly destroy Carrie Nation's phylactery.";
		break;
	case 12:
		cout<<"Beer Council: So did you actually destroy the phylactery this time?\n";
		pause();
		cout<<"Beer Man: I threw it in the fireplace!\n";
		pause();
		cout<<"Beer Council: That's much better. Wait a sec, was the fireplace on?\n";
		pause();
		cout<<"Beer Man: Of course! Who do you think I am?\n";
		pause();
		cout<<"Beer Council: A numbskull? Anyway, go ahead and destroy Carrie Nation.\n"
			<<"Her current location is unknown, so go find her yourself.\n";
		pause();
		mission_number=13;
		mission="Mission: Remove Carrie Nation.";
		break;
	case 13:
		cout<<"Beer Council: Go remove Carrie Nation. She was last seen\n downtown somewhere.\n";
		pause();
		break;
	default:
		cout<<"The Beer Council cannot be trusted anymore. The government has\nbeen infiltrated by traitors to Beer!\n";
		pause();
		break;
	}
	return;
}
void apartment(int inventory[],Beerman& beerman,Enemy mudkipz,Enemy policeman,int& mission_number)
{
	system("CLS");
	cout<<"The Apartment\n-------------\nThe Apartment. It has a lot of unusual tenants...\n"
		<<"And for some reason, you hear what sounds like a bunch of zombies rapping.\n"
		<<"You also see a sign: \nTaking All Challengers! Come to Room 42!\n";
	pause();
	int choice=0,win=1;
	bool fail=0;
	do{
		win=1;
		cout<<"Which room would you like to visit? Rooms available: 1-499, 0 to return\n";
		do{
			fail=0;
			cin>>choice;
			fail=cin.fail();
			if (fail){
				cin.clear();
				cin.ignore();
			}
		} while (fail);
		switch (choice)
		{
		case 0:
			break;
		case 42:
			//Okeymon trainer
			cout<<"???: Aha! A challenger!\n";
			pause();
			cout<<"Beer Man: Sure.\n";
			pause();
			cout<<"Okeymon Trainer: I am the Okeymon Trainer! I challenge you to an\nOkeymon Battle! Go Mudkipz!\n";
			pause();
			cout<<"Beer Man: Go... Beer Man!\n";
			pause();
			win=battle_init(inventory,beerman,mudkipz,30,3,0);
			cout<<"Okeymon Trainer: Come back anytime!\n";
			pause();
			break;
		case 101:
			{
				cout<<"As Beer Man opens the door to Room 101, the sound of zombies rapping\nincreases in volume. Suddenly...\n";
				pause();
				cout<<"Zombie 1: Yo, wassup, fool?\n";
				pause();
				cout<<"Zombie 2: We the Publius!\n";
				pause();
				cout<<"Zombie 3: Would you like to hear our rap, fool?\n";
				pause();
				cout<<"Beer Man: Uhhh...\n";
				pause();
				cout<<"Alexander Hamilton: Our names are A-Ham, J-Mad, and Jo Jay, and this\n"
					<<"is our song!\n";
				pause();
				cout<<"John Jay: 1, 2, 3, 4!\n";
				pause();
				publius_lyrics();
				system("CLS");
				cout<<"Beer Man: ...ugh...o my gawd... ugh...\n";
				pause();
				cout<<"Beer Man: ...the legal stuff... laws... government... GAHHHH! DIE YOU ZOMBIES!!!\n";
				pause();
				Attack *atk_ptr1,*atk_ptr2,*atk_ptr3,*atk_ptr4;
				atk_ptr1=new Attack("Rimshot",NEUTRAL,0,30,-1,90,100,0,0);
				atk_ptr2=new Attack("Judgment",NEUTRAL,1,42,-1,90,100,9,0);
				atk_ptr3=new Attack("Resign",NEUTRAL,1,55,-1,100,100,8,0);
				atk_ptr4=new Attack("Negotiate Treaty",NEUTRAL,1,0,25,70,100,0,0);
				Enemy *enemy_ptr=new Enemy("John Jay",NEUTRAL,5,7,6,6,6,40,7,25,3,2);
				enemy_ptr->set_growth(1,1,2,1,1,27,3,3);
				enemy_ptr->set_attack(*atk_ptr1,1,0);
				enemy_ptr->set_attack(*atk_ptr2,1,1);
				enemy_ptr->set_attack(*atk_ptr3,1,2);
				enemy_ptr->set_attack(*atk_ptr4,1,3);
				win=battle_init(inventory,beerman,*enemy_ptr,25,3,0);
				delete atk_ptr1;
				delete atk_ptr2;
				delete atk_ptr3;
				delete atk_ptr4;
				delete enemy_ptr;
				if (!win)
					break;
				atk_ptr1=new Attack("Power Chord",NEUTRAL,1,30,-1,90,100,0,0);
				atk_ptr2=new Attack("Separation of Powers",NEUTRAL,1,0,-1,100,100,8,0);
				atk_ptr3=new Attack("War Hawk",NEUTRAL,0,55,-1,100,100,7,0);
				atk_ptr4=new Attack("Revise Constitution",NEUTRAL,1,16,16,100,100,7,0);
				enemy_ptr=new Enemy("James Madison",NEUTRAL,5,7,7,7,6,40,7,25,3,2);
				enemy_ptr->set_growth(1,1,2,1,1,27,3,3);
				enemy_ptr->set_attack(*atk_ptr1,1,0);
				enemy_ptr->set_attack(*atk_ptr2,1,1);
				enemy_ptr->set_attack(*atk_ptr3,1,2);
				enemy_ptr->set_attack(*atk_ptr4,1,3);
				win=battle_init(inventory,beerman,*enemy_ptr,25,3,0);
				delete atk_ptr1;
				delete atk_ptr2;
				delete atk_ptr3;
				delete atk_ptr4;
				delete enemy_ptr;
				if (!win)
					break;
				atk_ptr1=new Attack("Duelling Pistol",NEUTRAL,0,32,-1,90,100,0,0);
				atk_ptr2=new Attack("Rap",NEUTRAL,1,30,-1,100,100,0,0);
				atk_ptr3=new Attack("Feedback",NEUTRAL,0,10,19,85,100,5,0);
				atk_ptr4=new Attack("National Bank",NEUTRAL,1,0,25,100,100,9,0);
				enemy_ptr=new Enemy("Alexander Hamilton",NEUTRAL,7,7,7,5,6,42,7,25,3,2);
				enemy_ptr->set_growth(2,1,1,1,1,27,3,3);
				enemy_ptr->set_attack(*atk_ptr1,1,0);
				enemy_ptr->set_attack(*atk_ptr2,1,1);
				enemy_ptr->set_attack(*atk_ptr3,1,2);
				enemy_ptr->set_attack(*atk_ptr4,1,3);
				win=battle_init(inventory,beerman,*enemy_ptr,25,3,0);
				delete atk_ptr1;
				delete atk_ptr2;
				delete atk_ptr3;
				delete atk_ptr4;
				delete enemy_ptr;
				if (!win)
					break;
				cout<<"Beer Man: ...gasp...gasp...gasp...\n";
				pause();
				cout<<"Beer Man: YEAH! No more legal lawyer law stuff!! Wooo!\n";
				pause();
				cout<<"Beer Man exits the room, satisfied with his good deed.\n";
				pause();
				cout<<"Zombies: ...we'll be back...\n";
				pause();
			}
			break;
		case 314:
			cout<<"As Beer Man opens the door to Room 314, he suddenly gets blinded\nby heavenly light!\n";
			pause();
			cout<<"Beer Man: O my gawd my precious eyes!\n";
			pause();
			cout<<"Charlie Pai: Wassup. I made this entire world.\n";
			pause();
			cout<<"Beer Man: HOLY ****! Uhh... time to make a quick exit.\n";
			pause();
			break;
		case 426:	//Room H2O
			if (mission_number!=11 && mission_number!=10)
			{
				cout<<"Beer Man opens the door.\n";
				pause();
				cout<<"There is nothing of interest inside.\n";
				pause();
				break;
			}
			if (mission_number==11){
				cout<<"Beer Man opens the door. This time he throws the phylactery into a fire.\n";
				pause();
				cout<<"Beer Man: That should do it.\n";
				pause();
				mission_number=12;
			}
			if (mission_number==10){
				cout<<"Beer Man opens the door.\n";
				pause();
				cout<<"Beer Man: Hmmm...\n";
				pause();
				cout<<"Beer Man searches the room and accidentally breaks a large, expensive vase.\n";
				pause();
				cout<<"Beer Man: Whoops. Um. Is that a phylactery I spy? Yes it is! I am awesome!\n";
				pause();
				cout<<"Beer Man quickly disposes of it in the trash can.\n";
				pause();
				cout<<"Beer Man: That should do it!";
				pause();
				mission_number=11;
			}
			break;
		default:
			if (choice>0 && choice<500)
			{
				int n=randint(0,1);
				cout<<"Beer Man opens the door.\n";
				pause();
				if (n==0){
					cout<<"There is nothing of interest inside.\n";
					pause();
				}
				if (n==1){
					cout<<"Woman: *screams* Intruder! Police! Police! *calls 911*\n";
					pause();
					win=battle_init(inventory,beerman,policeman,randint(23,27),1,0);
					if (win){
						cout<<"Beer Man makes a hasty retreat.\n";
						pause();
					}
					else{
						inventory[0]=int(inventory[0]*.7);
						cout<<"You black out...\n";
						pause();
						cout<<"...???\n";
						pause();
						cout<<"You regain consciousness.\n";
						pause();
						cout<<"Police: Hello there. You are here in jail for questionable behavior\n"
							<<"at an apartment. More specifically, trespassing upon private property\n"
							<<"with apparent motive to rob. We will let you go for 30% of your current holdings.";
						pause();
						cout<<"Beer Man: ...\n";
						pause();
						cout<<"You handed them your money. You have $"<<inventory[0]<<" left.\n";
						pause();
						beerman.change_hp(beerman.hp_max());
						win=1;
					}
				}
			}else{
				cout<<"There is no room "<<choice<<"!\n";
				pause();
			}
			break;
		}
		if (!win){
			blackout(inventory,beerman);
			win=1;
		}
	} while (choice!=0);
}
int city_hall(int inventory[],Beerman& beerman,Enemy carrie_nation,Enemy sir_elliot,int& mission_number,string& mission)
{
	//Returns 1 if Beer Man goes into the government offices.
	int win=1,choice=5;
	do{
		system("CLS");
		cout<<"City Hall\n---------\n";
		if (mission_number==13)
			cout<<"You hear some spraying noises somewhere.\n";
		choice=menu(4,"Government Offices","Beer Council","Back Door","Back");
		switch (choice){
		case 1:
			if (mission_number<14){
				cout<<"Beer Man: Why would I want to go in there? There are stupid, nasty,\nscheming lawyers and government officials there.\n";
				pause();
			}else{
				cout<<"Beer Man: Screw planning, it's time to finish this! LEEEEROOOOOOY-\n";
				pause();
				return 1;
			}
			break;
		case 2:
			beer_council(mission_number,mission);
			break;
		case 3:
			if (mission_number==13){
				cout<<"As Beer Man exits into the alley, he spies a woman painting graffiti\non the City Hall's walls.\n";
				pause();
				cout<<"Beer Man: ...? Who are you?\n";
				pause();
				cout<<"Beer Man: Wait... you're Carrie Nation! Time to die!\n";
				pause();
				cout<<"Carrie Nation: Ha ha ha ha ha! You seriously think you can defeat me?\nThe immortal? Well, try if you want.\n";
				pause();
				win=battle_init(inventory,beerman,carrie_nation,25,3,0);
				if (!win)
					break;
				cout<<"Carrie Nation: No... no! This cannot be! I am a lich! I am invincible!!\n";
				pause();
				cout<<"Carrie Nation: NOOOOOOOOOOOOOOO-\n";
				pause();
				cout<<"???: What's this noise you're making, Carrie? Is something going on?\nWhat, is your graffiti ruined or something?\n";
				pause();
				cout<<"Beer Man: Who's this? Come out with your hands up!\n";
				pause();
				system("CLS");
				cout<<"CHAPTER 3: THE CONSPIRACY\n"
					<<"-------------------------\n";
				pause();
				cout<<"A man dressed in a fancy suit and tie and a top hat appears.\n";
				pause();
				cout<<"Beer Man: !!! You're... Bier Mann! What are you doing here?!\n";
				pause();
				cout<<"Sir Elliot: My name is Sir Elliot. You might know me as the leader\nof the Neo-Temperance Society in Austria. Honestly,\n"
					<<"your city is really gullible. Me? BIER MANN? HA! Your so-called\nBeer Society was powerless when I came into power.\n"
					<<"And now, nearly all of the Temperance Movement's plans are\ncomplete, and YOU ARE POWERLESS TO STOP US! MWA HA HA!\n";
				pause();
				cout<<"Beer Man: You traitor! Die!\n";
				pause();
				mission_number=14;
				mission="Mission: Infiltrate the Libeerty City Government for glory!";
				win=battle_init(inventory,beerman,sir_elliot,27,3,0);
				if (!win){
					cout<<"Sir Elliot: That's right, Beer Man. You are nothing.\n";
					pause();
					cout<<"Sir Elliot struts away, leaving Beer Man lying on the ground with a hangover.\n";
					pause();
					blackout(inventory,beerman);
					win=1;
					cout<<"Beer Man: Ugh... The government has turned traitor against beer!\nI must stop this!\n";
					pause();
				}else{
					cout<<"Sir Elliot: ...Surprising. Well, next time you won't be as lucky.\n";
					pause();
					cout<<"Sir Elliot struts away into City Hall.\n";
					pause();
					cout<<"Beer Man: ...So even the government has lost itself to Temperance!\n";
					pause();
				}
				cout<<mission;
				pause();
			}else{
				cout<<"There's nobody here. Not even that Crack Pot that Beer Man used\nto talk with.\n";
				pause();
			}
			break;
		default:
			break;
		}
		if (!win)
			blackout(inventory,beerman);
		win=1;
	} while (choice!=4);
	return 0;
}
void publius_lyrics()
{
	system("CLS");
	cout<<"We Are Publius\n--------------\n";
	chorus();
	cout<<"'Sup homes my name is Alexander Hamilton\nA-Ham for short, my foes are on the run\nGot my man John Jay layin' down the beat\nAnd James Madison'll get ya on your feet\n";
	pause();
	cout<<"I'm here to represent Fed Seventy-Eight\nBut all our Federalist Papers are totally great\nIf you look in your pocket and pull out a 10\nMy face is gonna be on it, and I'll say this again\n";
	pause();
	chorus();
	cout<<"The name's John Jay\nAnd I'm here to say\nWe thought the Articles were\nTOTALLY LAME\n";
	pause();
	cout<<"So we tellin' you\nTo ratify\nConstitution is the best, you\nCAN'T DENY\n";
	pause();
	chorus();
	cout<<"J-Mad's in the house, right over here\nI'm the fourth president, to make it crystal clear\nBeat down Anti-Feds with paper 51\nTakes down all their points like a muh-sheen gun\n";
	pause();
	cout<<"So you gonna ask us, what's our beef with you?\nDrinkin' beer all the time is real uncool\nWe're gonna beat you, loosen yo construction\nTill all of your organs no longer function\n";
	pause();
	chorus();
	cout<<"YEUH!!!!\n";
	pause();
	return;
}
void chorus()
{
	cout<<"Yeah we Publius\nThe three of us\nLike a Cerberus\nThe Federalists\n";
	pause();
	cout<<"Yeah we Publius\nThe three of us\nLike a Cerberus\nThe Federalists\n";
	pause();
}
void shop_full(int inventory[])
{
	system("CLS");
	int have_money,choice;
	cout<<"General Store\n-------------\nWelcome to Surgeon General's General Store, the store with all things\nharmful and harmless. What would you like?\n\n";
	do
	{
		have_money=0;
		cout<<"Beer Man has $"<<inventory[0]<<".\n\n";
		choice=menu(10,"Match - $5","Rock - $5","Water Bottle - $8","Seed - $8","Acid - $12","Steroids - $15","Sandbox - $15","Battery - $17","Electric Fan - $20","Back");
		switch (choice)
		{
		case 1:
			if (inventory[0]>=5){
				inventory[0]-=5;
				inventory[3]++;
				cout<<"Bought a Match.\n";
				have_money=1;
			}
			break;
		case 2:
			if (inventory[0]>=5){
				inventory[0]-=5;
				inventory[4]++;
				cout<<"Bought a Rock.\n";
				have_money=1;
			}
			break;
		case 3:
			if (inventory[0]>=8){
				inventory[0]-=8;
				inventory[8]++;
				cout<<"Bought a Water Bottle.\n";
				have_money=1;
			}
			break;
		case 4:
			if (inventory[0]>=8){
				inventory[0]-=8;
				inventory[10]++;
				cout<<"Bought a Seed.\n";
				have_money=1;
			}
			break;
		case 5:
			if (inventory[0]>=12){
				inventory[0]-=12;
				inventory[5]++;
				cout<<"Bought an Acid Bottle.\n";
				have_money=1;
			}
			break;
		case 6:
			if (inventory[0]>=15){
				inventory[0]-=15;
				inventory[7]++;
				cout<<"Bought a Steroid.\n";
				have_money=1;
			}
			break;
		case 7:
			if (inventory[0]>=15){
				inventory[0]-=15;
				inventory[6]++;
				cout<<"Bought a Sandbox.\n";
				have_money=1;
			}
			break;
		case 8:
			if (inventory[0]>=17){
				inventory[0]-=17;
				inventory[11]++;
				cout<<"Bought a Battery.\n";
				have_money=1;
			}
			break;
		case 9:
			if (inventory[0]>=20){
				inventory[0]-=20;
				inventory[9]++;
				cout<<"Bought an Electric Fan.\n";
				have_money=1;
			}
			break;
		case 10:
			break;
		default:
			choice=0;
			break;
		}
		if (choice<10 && choice>0 && !have_money)
			cout<<"You don't have enough money!\n";
		if (choice!=10)
			pause();
	} while (choice!=10);
	return;
}