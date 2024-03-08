#pragma once

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;

public:
	SpriteGo(const std::string& name = "");

	sf::FloatRect GetLocalBounds() override;
	sf::FloatRect GetGlobalBounds() override;


	void SetTexture(const std::string& textureId);
	void SetColor(int r, int g, int b);

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetRotation(float r) override;


	void SetOrigin(Origins newOrigin) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;

	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

};

