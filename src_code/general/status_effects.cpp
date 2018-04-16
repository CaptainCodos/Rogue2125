#include "status_effects.h"

StatusEffect::StatusEffect(int ID)
{
	m_id = ID;

	m_energyDmg = 0.0f;
	m_tickDmg = 0.0f;
	m_fuelAdd = 0.0f;

	m_dmgType = 0;

	m_stacks = 1;

	m_delete = false;
	m_trigger = false;

	m_speedMod = 0.5f;

	m_time = 1.0f;

	switch (m_id)
	{
	case 0:
		m_energyDmg = 0.0f;
		m_tickDmg = 0.0f;
		m_fuelAdd = 0.0f;

		m_speedMod = 0.5f;
		break;
	case 1:
		m_energyDmg = -1.0f;
		m_tickDmg = 1.0f;
		m_dmgType = 2;
		m_speedMod = 0.5f;
		break;
	case 2:
		m_tickDmg = 2.0f;
		m_dmgType = 3;
		m_speedMod = 0.6f;
		break;
	case 3:
		m_energyDmg = 2.0f;
		m_tickDmg = 2.0f;
		m_fuelAdd = 1.0f;
		m_dmgType = 3;
		m_speedMod = 0.6f;
		break;
	case 4:
		m_tickDmg = 1.0f;
		m_dmgType = 1;
		m_speedMod = 0.3f;
		break;
	}

}

bool StatusEffect::ToBeDeleted() { return m_delete; }
bool StatusEffect::IsTriggering() { return m_trigger; }
int StatusEffect::GetEffectID() { return m_id; }
float StatusEffect::GetSpeedMod() { return m_speedMod; }
int StatusEffect::GetDmgType() { return m_dmgType; }

void StatusEffect::AddStack() { m_stacks++; }
int StatusEffect::GetStacks() { return m_stacks; }

void StatusEffect::update(double dt)
{
	if (m_stacks <= 0)
	{
		m_delete = true;
		m_trigger = false;
	}
	else
	{
		if (m_time <= 0.0f)
		{
			m_stacks--;
			m_trigger = true;

			m_time = 1.0f;
		}
		else
		{
			m_time -= dt;
			m_trigger = false;
		}
	}
}

void StatusEffect::DeliverEffect(float &hp, float maxEn, float &en, float &fuel)
{
	m_trigger = false;

	switch (m_id)
	{
	case 1:
		en -= m_energyDmg;

		if (en > maxEn)
		{
			en = maxEn;
			hp -= m_tickDmg;
		}
		break;
	case 2:
		hp -= m_tickDmg;
		break;
	case 3:
		hp -= m_tickDmg;
		en -= m_energyDmg;
		fuel += m_fuelAdd;
		break;
	case 4:
		hp -= m_tickDmg;
		break;
	}
}
