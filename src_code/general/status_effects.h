#pragma once

class StatusEffect
{
public:
	StatusEffect(int ID);
	~StatusEffect() = default;

	bool ToBeDeleted();
	bool IsTriggering();

	int GetEffectID();
	int GetDmgType();

	float GetSpeedMod();

	void update(double dt);
	void DeliverEffect(float &hp, float maxEn, float &en, float &fuel);

	void AddStack();
	int GetStacks();
protected:
	int m_id;

	int m_dmgType;

	int m_stacks;
	bool m_delete;
	bool m_trigger;
	float m_time;

	float m_tickDmg;
	float m_energyDmg;
	float m_fuelAdd;
	float m_speedMod;
};