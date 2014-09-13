/* ConversationPanel.h
Copyright (c) 2014 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#ifndef CONVERSATION_PANEL_H_
#define CONVERSATION_PANEL_H_

#include "Panel.h"

#include "WrappedText.h"

#include <functional>
#include <list>
#include <map>
#include <string>
#include <vector>

class Conversation;
class PlayerInfo;
class System;



// User interface panel that displays a conversation, allowing you to make choices,
// and then can be closed once the conversation ends.
class ConversationPanel : public Panel {
public:
	ConversationPanel(PlayerInfo &player, const Conversation &conversation, const System *system = nullptr);
	
template <class T>
	void SetCallback(T *t, void (T::*fun)(int));
	
	// Draw this panel.
	virtual void Draw() const;
	
	
protected:
	// Only override the ones you need; the default action is to return false.
	virtual bool KeyDown(SDL_Keycode key, Uint16 mod);
	virtual bool Click(int x, int y);
	virtual bool Drag(int dx, int dy);
	
	
private:
	void Goto(int index);
	std::string Substitute(const std::string &source) const;
	
	
private:
	class ClickZone {
	public:
		ClickZone(const Point &topLeft, const Point &size);
		
		bool Contains(const Point &point);
		
	private:
		Point topLeft;
		Point size;
	};
	
	
private:
	PlayerInfo &player;
	
	const Conversation &conversation;
	int node;
	std::function<void(int)> callback = nullptr;
	
	int scroll;
	
	WrappedText wrap;
	std::list<WrappedText> text;
	std::list<WrappedText> choices;
	int choice;
	
	std::string firstName;
	std::string lastName;
	std::map<std::string, std::string> subs;
	
	mutable std::vector<ClickZone> zones;
	
	const System *system;
};



template <class T>
void ConversationPanel::SetCallback(T *t, void (T::*fun)(int))
{
	callback = std::bind(fun, t, std::placeholders::_1);
}



#endif
