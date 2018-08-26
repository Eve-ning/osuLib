#pragma once
#include <iostream>
#include <fstream>
#include "../../OsuException.h"
#include "SpriteCommand.h"

class SpriteObject
{
public:
	enum class LAYER {
		Foreground,
		Background,
		Fail,
		Pass
	};

	enum class ORIGIN {
		TopLeft,
		TopCentre,
		TopRight,
		CentreLeft,
		Centre,
		CentreRight,
		BottomLeft,
		BottomCentre,
		BottomRight
	};

	SpriteObject(const std::string &filePath, LAYER layer = LAYER::Foreground, int x = 320, int y = 240, ORIGIN origin = ORIGIN::TopLeft);
	~SpriteObject();

	std::vector<std::shared_ptr<SpriteCommand>> commands() const { return m_commands; }
	int x() const { return m_x; }
	int y() const { return m_y; }
	LAYER layer() const { return m_layer; }
	std::string layerAsString() const {
		switch (m_layer)
		{
		case SpriteObject::LAYER::Foreground:
			return "Foreground";
		case SpriteObject::LAYER::Background:
			return "Background";
		case SpriteObject::LAYER::Fail:
			return "Fail";
		case SpriteObject::LAYER::Pass:
			return "Pass";
		default:
			return "";
		}
	}
	std::string filePath() const { return m_filePath; }
	ORIGIN origin() const { return m_origin; }
	std::string originAsString() const {
		switch (m_origin)
		{
		case SpriteObject::ORIGIN::TopLeft:
			return "TopLeft";				 
		case SpriteObject::ORIGIN::TopCentre:								 
			return "TopCentre";
		case SpriteObject::ORIGIN::TopRight:
			return "TopRight";
		case SpriteObject::ORIGIN::CentreLeft:
			return "CentreLeft";
		case SpriteObject::ORIGIN::Centre:
			return "Centre";
		case SpriteObject::ORIGIN::CentreRight:
			return "CentreRight";
		case SpriteObject::ORIGIN::BottomLeft:
			return "BottomLeft";
		case SpriteObject::ORIGIN::BottomCentre:
			return "BottomCentre";
		case SpriteObject::ORIGIN::BottomRight:
			return "BottomRight";
		default:
			return "";
		}
	}

	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }
	void setLayer(LAYER layer) { m_layer = layer; }
	void setFilePath(std::string filePath) { m_filePath = filePath; }
	void setCommands(std::vector<std::shared_ptr<SpriteCommand>> commands) { m_commands = commands; }

	void addCommand(std::shared_ptr<SpriteCommand> command) { m_commands.push_back(command);}
	void addCommand(Command::Fade cmd){ m_commands.push_back(std::make_shared<Command::Fade>(cmd)); }
	void addCommand(Command::Move cmd){ m_commands.push_back(std::make_shared<Command::Move>(cmd)); }
	void addCommand(Command::Scale cmd){ m_commands.push_back(std::make_shared<Command::Scale>(cmd)); }
	void addCommand(Command::Rotate cmd){ m_commands.push_back(std::make_shared<Command::Rotate>(cmd)); }
	void addCommand(Command::Color cmd){ m_commands.push_back(std::make_shared<Command::Color>(cmd)); }

	void removeCommand() { m_commands.pop_back(); }
	std::shared_ptr<SpriteCommand> getCommand(int i) { return m_commands.at(i); }

	std::string toString() const {
		std::stringstream ss;
		ss << "Sprite," << layerAsString() << ","
			<< originAsString() << ","
			<< filePath() << ","
			<< boost::lexical_cast<std::string>(m_x) << "," <<
			boost::lexical_cast<std::string>(m_y);

		return ss.str();
	}
	std::vector<std::string> toStringList() const {
		std::vector<std::string> vs;

		vs.push_back(toString());
		for (auto command : m_commands) {
			vs.push_back(command->toString());
		}

		return vs;
	}

private:
	int m_x = 320;
	int m_y = 240;
	LAYER m_layer = LAYER::Foreground;
	std::string m_filePath = "";
	ORIGIN m_origin = ORIGIN::TopLeft;
	std::vector<std::shared_ptr<SpriteCommand>> m_commands = {};
};

