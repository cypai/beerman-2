/*
Enemies.h
Defines the variables for all enemy characters
*/

#include <string>
#define NEUTRAL 0
#define FIRE 1
#define WATER 2
#define EARTH 3
#define AIR 4
#define GRASS 5
#define LIGHTNING 6
using namespace std;

class Attack;
class Enemy
{
public:
	Enemy(string Name,int Element,int atk,int def,int matk,int mdef,int spd,int hp,int mp,int xp,int money,int ev);
	void set_growth(int atk,int def,int matk,int mdef,int spd,int hp,int mp,int money);
	void set_attack(Attack& att,int level,int location);
	void grow_stats();
	int get_EV(){return EV;}
	string get_name(){return name;}
	int change_hp(int amount){hp+=amount;if (hp>HP) hp=HP;return hp;}	//Can be used to return current hp value by setting amount to 0
	int change_mp(int amount){mp+=amount;if (mp>MP) mp=MP;if (mp<0) mp=0;return mp;}	//Can be used to return current mp value by setting amount to 0
	int atk(){return ATK;}
	int def(){return DEF;}
	int matk(){return MATK;}
	int mdef(){return MDEF;}
	int spd(){return SPD;}
	int hp_max(){return HP;}
	int mp_max(){return MP;}
	int get_xp(){return XP;}
	int get_money(){return MONEY;}
	int elem(){return element;}
	int attack_amount(){return attack_number;}
	int get_lvl(){return lvl;}
	Attack* get_attack(int numb);
	int get_max_attack_number();
	void set_attacks_at_level();
protected:
	string name;
	int element;
	int ATK,DEF,MATK,MDEF,SPD,HP,MP,XP,MONEY;
	int gATK,gDEF,gMATK,gMDEF,gSPD,gHP,gMP,gMONEY;
	int EV;
	int hp,mp,lvl,acc;
	int attack_level[15],attack_location[15],attack_number;
	Attack *attack_list[15],*attacks[7];

	friend class Attack;
};
class Attack
{
public:
	Attack(string Name,int Element,int Type,int Power,signed int Effect,int Accuracy,int Ef_Accuracy,int MP_req,float BAC_req);
	int attack(Enemy& attacker,Enemy& enemy,int& Effect,const float& Acc);	//Returns damage (-1 if miss), changes Effect to effect number
	//This method ensures that status effect code can manipulate the damage
	//argument acc is the accuracy modifier
	string get_name(){return name;}
	int get_mp_req(){return mp_req;}
	float get_bac_req(){return bac_req;}
	signed int get_effect(){return effect;}
	int get_type(){return type;}
	int elem(){return element;}
	float get_effective(Enemy& enemy);
	int get_power(){return power;}

private:
	string name;
	int element;
	int type;	//0: Physical, 1: Magical
	int power;
	signed int effect;
	int accuracy;	//Out of 100
	int ef_accuracy;	//Out of 100
	int mp_req;
	float bac_req;

	friend class Enemy;
	friend class Beerman;
};
class Beerman : public Enemy
{
public:
	Beerman();
	void level_up();
	float change_bac(float a);
	void change_element(int elem){element=elem;}
	void display_stats();
	int get_exp(int xp);
	int change_ev(int ev,int amount);
	void set_attacks_b(Attack& att);
	Attack* get_attack2(string att_name,bool discover_combo=1);
	void encyclopedia();
	void scale_to_30();

protected:
	static int exp;
	static float bac;
	int evs[5];
	Attack *attack_list2[40];
	bool used_combo[40];
	friend ostream& operator << (ostream& out_file,const Beerman& beerman);
	friend istream& operator >> (istream& in_file,Beerman& beerman);

	friend class Attack;
};