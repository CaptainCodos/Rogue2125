#pragma once
#include "ecm.h"
#include "cmp_text.h"
#include "cmp_sprite.h"

class ButtonComponent : public Component {
public:
	explicit ButtonComponent(Entity* p, std::shared_ptr<TextComponent>, std::shared_ptr<ShapeComponent>);
	~ButtonComponent() = default;

	void update(double dt) override;
private:
	std::shared_ptr<TextComponent> _btnText;
	std::shared_ptr<ShapeComponent> _btnShape;
};