#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Enemies.h"
#define NEUTRAL 0
#define FIRE 1
#define WATER 2
#define EARTH 3
#define AIR 4
#define GRASS 5
#define LIGHTNING 6

int randint(int a, int b)
{
	return (rand()%(b-a+1)+a);
}
float round(float& number, int decimal_pts)
{
	number=floor(number*pow(10.0,decimal_pts)+.5)/pow(10.0,decimal_pts);
	return number;
}
Attack::Attack(string Name,int Element,int Type,int Power,signed int Effect,int Accuracy,int Ef_Accuracy,int MP_req,float BAC_req)
{
	name=Name;
	element=Element;
	type=Type;
	power=Power;
	effect=Effect;
	accuracy=Accuracy;
	ef_accuracy=Ef_Accuracy;
	mp_req=MP_req;
	bac_req=BAC_req;
}
int Attack::attack(Enemy& attacker,Enemy& enemy,int& Effect,const float& Acc)
{
	//Determine elemental weakness/resistance multiplier
	float elem_multiplier=1;
	if (this->element==enemy.elem())
		elem_multiplier=.5;
	if (this->element==FIRE && (enemy.elem()==AIR || enemy.elem()==GRASS))
		elem_multiplier=2;
	if (this->element==WATER && (enemy.elem()==FIRE || enemy.elem()==EARTH))
		elem_multiplier=2;
	if (this->element==EARTH && (enemy.elem()==FIRE || enemy.elem()==LIGHTNING))
		elem_multiplier=2;
	if (this->element==AIR && (enemy.elem()==EARTH || enemy.elem()==GRASS))
		elem_multiplier=2;
	if (this->element==GRASS && (enemy.elem()==WATER || enemy.elem()==EARTH))
		elem_multiplier=2;
	if (this->element==FIRE && enemy.elem()==WATER)
		elem_multiplier=.5;
	if (this->element==WATER && enemy.elem()==GRASS)
		elem_multiplier=.5;
	if (this->element==EARTH && enemy.elem()==GRASS)
		elem_multiplier=.5;
	if (this->element==AIR && enemy.elem()==FIRE)
		elem_multiplier=.5;
	if (this->element==GRASS && enemy.elem()==FIRE)
		elem_multiplier=.5;
	if (this->element==LIGHTNING){
		if (enemy.elem()==EARTH)
			elem_multiplier=.5;
		if (enemy.elem()==GRASS)
			elem_multiplier=.5;
		if (enemy.elem()==WATER || enemy.elem()==AIR)
			elem_multiplier=2;
	}
	if (this->element==NEUTRAL || enemy.elem()==NEUTRAL)
		elem_multiplier=1;
	//Accuracy formula
	int acc=accuracy;
	acc+=(int)(bac_req>0)*100*Beerman::bac;
	//Check if the attack hits
	int hit=(randint(1,100)<=int(Acc*acc));
	//Determine amount of damage dealt
	float damage;
	damage=int(float(attacker.atk()+10)/float(enemy.def()+10)*power*elem_multiplier*!type)+randint(attacker.get_lvl()/10+3,attacker.get_lvl()/3+3);
	damage+=int(float(attacker.matk()+10)/float(enemy.mdef()+10)*power*elem_multiplier*type);
	if (this->element==attacker.elem() && attacker.elem()!=NEUTRAL)
		damage=int(damage*1.2);
	if (effect==16)
		damage=(attacker.def()+attacker.mdef())*2;
	if (damage<1)
		damage=1;
	if (power==0) damage=0;
	if (!hit) damage=-1;	//If missed, turn damage negative (applies to special attacks as well)
	int ef_rand=randint(1,100);
	if (ef_rand<=ef_accuracy)
		Effect=effect;
	return (int)damage;
}
float Attack::get_effective(Enemy& enemy)
{
	float elem_multiplier=1;
	if (this->element==enemy.elem())
		elem_multiplier=.5;
	if (this->element==FIRE && (enemy.elem()==AIR || enemy.elem()==GRASS))
		elem_multiplier=2;
	if (this->element==WATER && (enemy.elem()==FIRE || enemy.elem()==EARTH))
		elem_multiplier=2;
	if (this->element==EARTH && (enemy.elem()==FIRE || enemy.elem()==LIGHTNING))
		elem_multiplier=2;
	if (this->element==AIR && (enemy.elem()==EARTH || enemy.elem()==GRASS))
		elem_multiplier=2;
	if (this->element==GRASS && (enemy.elem()==WATER || enemy.elem()==EARTH))
		elem_multiplier=2;
	if (this->element==FIRE && enemy.elem()==WATER)
		elem_multiplier=.5;
	if (this->element==WATER && enemy.elem()==GRASS)
		elem_multiplier=.5;
	if (this->element==EARTH && enemy.elem()==GRASS)
		elem_multiplier=.5;
	if (this->element==AIR && enemy.elem()==FIRE)
		elem_multiplier=.5;
	if (this->element==GRASS && enemy.elem()==FIRE)
		elem_multiplier=.5;
	if (this->element==LIGHTNING){
		if (enemy.elem()==EARTH)
			elem_multiplier=.5;
		if (enemy.elem()==GRASS)
			elem_multiplier=.5;
		if (enemy.elem()==WATER || enemy.elem()==AIR)
			elem_multiplier=2;
	}
	if (this->element==NEUTRAL || enemy.elem()==NEUTRAL)
		elem_multiplier=1;
	return elem_multiplier;
}
Enemy::Enemy(string Name,int Element,int atk,int def,int matk,int mdef,int spd,int hp,int mp,int xp,int money,int ev)
{
	name=Name;
	element=Element;
	ATK=atk+3;
	DEF=def+3;
	MATK=matk+3;
	MDEF=mdef+3;
	SPD=spd;
	HP=hp;
	MP=mp;
	this->hp=HP;
	this->mp=MP;
	lvl=1;
	acc=100;
	XP=xp;
	MONEY=money;
	attack_number=0;
	EV=ev;
	for(int i=0;i<15;i++)
	{
		attack_level[i]=0;
		attack_location[i]=0;
		attack_list[i]=NULL;
	}
}
void Enemy::set_growth(int atk,int def,int matk,int mdef,int spd,int hp,int mp,int money)
{
	gATK=atk;
	gDEF=def;
	gMATK=matk;
	gMDEF=mdef;
	gSPD=spd;
	gHP=hp;
	gMP=mp;
	gMONEY=money;
}
void Enemy::set_attack(Attack& att,int level,int location)
{
	int number=0;
	for(int i=0;i<15;i++)
	{
		if (attack_list[i]==NULL)
		{
			number=i;
			break;
		}
	}
	attack_level[number]=level;
	attack_location[number]=location;
	attack_list[number]=&att;
}
void Enemy::set_attacks_at_level()
{
	int level=this->lvl,temp_atk_level[7];
	for(int i=0;i<7;i++)
		temp_atk_level[i]=0;
	for(int i=0;i<15;i++)
	{
		if (attack_level[i]<=level && attack_level[i]>=temp_atk_level[attack_location[i]])
		{
			attacks[attack_location[i]]=attack_list[i];
			temp_atk_level[attack_location[i]]=attack_level[i];
			if (attack_number<attack_location[i])
				attack_number=attack_location[i];
		}
	}
}
int Enemy::get_max_attack_number()
{
	return attack_number;
}
Attack* Enemy::get_attack(int numb)
{
	return (attacks[numb]);
}
void Enemy::grow_stats()
{
	ATK+=gATK;
	DEF+=gDEF;
	MATK+=gMATK;
	MDEF+=gMDEF;
	SPD+=gSPD;
	HP+=gHP;
	MP+=gMP;
	hp=HP;
	mp=MP;
	MONEY+=gMONEY;
	lvl++;
}
float Beerman::bac=0;
int Beerman::exp=0;
Beerman::Beerman() : Enemy("Beer Man",NEUTRAL,2,2,1,1,1,29,0,0,0,0)
{
	set_growth(1,1,1,1,1,13,0,0);
	level_up();
	level_up();
	for (int i=0;i<5;i++)
		evs[i]=0;
	for (int i=0;i<40;i++){
		attack_list2[i]=NULL;
		used_combo[i]=0;
	}
}
float Beerman::change_bac(float a)
{
	bac+=a;
	round(bac,3);
	if (bac<0) bac=0;
	return bac;
}
void Beerman::level_up()
{
	grow_stats();
}
void Beerman::display_stats()
{
	system("CLS");
	string str_element;
	switch (element)
	{
	case NEUTRAL:
		str_element="Neutral";
		break;
	case FIRE:
		str_element="Fire";
		break;
	case WATER:
		str_element="Water";
		break;
	case EARTH:
		str_element="Earth";
		break;
	case AIR:
		str_element="Air";
		break;
	case GRASS:
		str_element="Grass";
		break;
	case LIGHTNING:
		str_element="Lightning";
		break;
	}
	cout<<"Beerman\n-------\nLevel: "<<lvl<<"\nEXP: "<<Beerman::exp<<"/"<<lvl*30+floor(3*pow(double(lvl-3),2))<<"\n\n"
		<<"HP: "<<hp<<"/"<<HP<<"\nBAC: "<<Beerman::bac<<"\n\n"
		<<str_element<<"\nATK: "<<ATK<<"\nDEF: "<<DEF<<"\nMATK: "<<MATK<<"\nMDEF: "<<MDEF<<"\nSPD: "<<SPD;
}
int Beerman::get_exp(int xp)
{
	Beerman::exp+=xp;
	if (Beerman::exp>=lvl*30)
	{
		for (;exp>=lvl*30+floor(3*pow(double(lvl-3),2));exp-=(lvl-1)*30+floor(3*pow(double(lvl-4),2)))
		{
			level_up();
			cout<<"\nBeerman leveled up! Beerman is now level "<<this->get_lvl()<<"!";
		}
	}
	return Beerman::exp;
}
int Beerman::change_ev(int ev,int amount)
{
	evs[ev]+=amount;
	if (evs[ev]>=7)
	{
		evs[ev]-=7;
		switch (ev)
		{
		case 0:
			ATK++;
			cout<<"Beerman feels that his arms are stronger!";
			break;
		case 1:
			DEF++;
			cout<<"Beerman feels more capable of taking hits!";
			break;
		case 2:
			MATK++;
			cout<<"Beerman feels an increase in inner focus!";
			break;
		case 3:
			MDEF++;
			cout<<"Beerman feels more capable in taking magical hits!";
			break;
		case 4:
			SPD++;
			cout<<"Beerman feels more agile!";
			break;
		}
		return 1;
	}
	return 0;
}
void Beerman::set_attacks_b(Attack& att)
{
	for (int i=0;i<40;i++)
	{
		if (attack_list2[i]==0)
		{
			attack_list2[i]=&att;
			break;
		}
	}
	return;
}
Attack* Beerman::get_attack2(string att_name,bool discover_combo)
{
	for (int i=0;i<40;i++)
	{
		if (attack_list2[i]->get_name()==att_name)
		{
			if (discover_combo && attack_list2[i]->bac_req<=Beerman::bac)
				used_combo[i]=1;
			return attack_list2[i];
		}
	}
	return 0;
}
void Beerman::encyclopedia()
{
	int total=0;
	system("CLS");
	cout<<"Encyclopedia\n------------\n";
	for (int i=0;i<40;i++)
	{
		if (used_combo[i])
		{
			total++;
			cout<<attack_list2[i]->get_name()<<": "<<attack_list2[i]->get_bac_req();
			if (attack_list2[i]->get_type()==0)
				cout<<" (P)\n";
			else
				cout<<" (M)\n";
			if (attack_list2[i]->get_name()=="Fire Punch")
				cout<<" -> Hold Match, Punch/Drunken Fist\n";
			if (attack_list2[i]->get_name()=="Falcon Punch")
				cout<<" -> FIRE, Hold Match, Drunken Fist\n";
			if (attack_list2[i]->get_name()=="Water Blast")
				cout<<" -> Hold Water, Purge\n";
			if (attack_list2[i]->get_name()=="Flood")
				cout<<" -> WATER, Hold Water, Purge\n";
			if (attack_list2[i]->get_name()=="Tsunami")
				cout<<" -> WATER, Flood, Flail\n";
			if (attack_list2[i]->get_name()=="Rock Slide")
				cout<<" -> EARTH, Throw Rock\n";
			if (attack_list2[i]->get_name()=="Tornado")
				cout<<" -> AIR, Fan on ground, Flail\n";
			if (attack_list2[i]->get_name()=="Cyclone")
				cout<<" -> AIR, Fan on ground, Tornado, Flail\n";
			if (attack_list2[i]->get_name()=="Overgrowth")
				cout<<" -> Seed on ground, Drop Water Bottle\n";
			if (attack_list2[i]->get_name()=="Recover")
				cout<<" -> GRASS, Put Water in Mouth\n";
			if (attack_list2[i]->get_name()=="Sand Attack")
				cout<<" -> Hold Sand, Punch/Drunken Fist\n";
			if (attack_list2[i]->get_name()=="Meteor Smash")
				cout<<" -> Hold Rock, Flying Strike\n";
			if (attack_list2[i]->get_name()=="Corrosive Fumes")
				cout<<" -> Fan on ground, Throw Acid\n";
			if (attack_list2[i]->get_name()=="Aerial Ace")
				cout<<" -> Fan on ground, Flying Strike\n";
			if (attack_list2[i]->get_name()=="Fire Spin")
				cout<<" -> Hold Match, Flail\n";
			if (attack_list2[i]->get_name()=="Flamethrower")
				cout<<" -> Beer on ground, Fan on ground, Drop Match\n -> Beer on ground, Hold Match, Use Fan\n";
			if (attack_list2[i]->get_name()=="Bullet Seed")
				cout<<" -> Seed on ground, Use Fan\n";
			if (attack_list2[i]->get_name()=="Bonfire")
				cout<<" -> Seed on ground, Fan on ground, Drop Match\n";
			if (attack_list2[i]->get_name()=="Glass Shards")
				cout<<" -> Sandbox on ground, Drop Match\n";
			if (attack_list2[i]->get_name()=="Sandstorm")
				cout<<" -> Sandbox on ground, Use Fan\n -> Sandbox on ground, Drop Fan\n -> Fan on ground, Drop Sandbox\n";
			if (attack_list2[i]->get_name()=="Thunderstorm")
				cout<<" -> Fan on ground, Battery on ground, Drop Water Bottle\n";
			if (attack_list2[i]->get_name()=="Explosion")
				cout<<" -> Acid on ground, Drop Water Bottle\n";
			if (attack_list2[i]->get_name()=="Acid Rain")
				cout<<" -> Acid on ground, Use Fan\n -> Fan on ground, Drop Acid\n";
			if (attack_list2[i]->get_name()=="Animate Plants")
				cout<<" -> Overgrowth, Drop Beer\n";
			if (attack_list2[i]->get_name()=="Leech Seed")
				cout<<" -> Hold Seed, Punch/Drunken Fist\n";
			if (attack_list2[i]->get_name()=="War Dance")
				cout<<" -> NEUTRAL, Flail\n";
			if (attack_list2[i]->get_name()=="Beer Missile")
				cout<<" -> Fan on ground, Throw Beer\n";
			if (attack_list2[i]->get_name()=="Time Bomb")
				cout<<" -> Beer on ground, Drop Acid\n";
		}
	}
	cout<<"\nCombos Discovered: "<<total<<"/40\n";
	return;
}
void Beerman::scale_to_30()
{
	while (lvl>30){
		ATK-=gATK;
		DEF-=gDEF;
		MATK-=gMATK;
		MDEF-=gMDEF;
		SPD-=gSPD;
		HP-=gHP;
		MP-=gMP;
		hp=HP;
		mp=MP;
		MONEY-=gMONEY;
		lvl--;
	}
	return;
}
ostream& operator << (ostream& out_file,const Beerman& beerman)
{
	out_file<<beerman.lvl<<endl;
	out_file<<beerman.exp<<endl;
	out_file<<beerman.ATK<<endl;
	out_file<<beerman.DEF<<endl;
	out_file<<beerman.MATK<<endl;
	out_file<<beerman.MDEF<<endl;
	out_file<<beerman.SPD<<endl;
	out_file<<beerman.HP<<endl;
	out_file<<beerman.hp<<endl;
	out_file<<beerman.bac<<endl;
	for (int i=0;i<5;i++)
		out_file<<beerman.evs[i]<<endl;
	out_file<<beerman.element<<endl;
	for (int i=0;i<40;i++)
		out_file<<beerman.used_combo[i]<<endl;
	return out_file;
}
istream& operator >> (istream& in_file,Beerman& beerman)
{
	in_file>>beerman.lvl;
	in_file>>beerman.exp;
	in_file>>beerman.ATK;
	in_file>>beerman.DEF;
	in_file>>beerman.MATK;
	in_file>>beerman.MDEF;
	in_file>>beerman.SPD;
	in_file>>beerman.HP;
	in_file>>beerman.hp;
	in_file>>beerman.bac;
	for (int i=0;i<5;i++)
		in_file>>beerman.evs[i];
	in_file>>beerman.element;
	for (int i=0;i<40;i++)
		in_file>>beerman.used_combo[i];
	return in_file;
}