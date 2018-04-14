#pragma once
#include "ecm.h"
#include "cmp_text.h"
#include "cmp_sprite.h"

class ButtonComponent : public Component {
public:
	explicit ButtonComponent(Entity* p, std::shared_ptr<TextComponent> text, std::shared_ptr<ShapeComponent> shape);
	~ButtonComponent() = default;

	void update(double dt) override;
	void render() override;
	bool clicked(double delay);
private:
	std::shared_ptr<TextComponent> _btnText;
	std::shared_ptr<ShapeComponent> _btnShape;
};