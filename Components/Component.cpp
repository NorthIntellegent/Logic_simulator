#include "Component.h"
#include <iostream>
Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
	m_ID = -1; // Default ID
	m_Selected = false;
}

Component::Component()
{
	m_ID = -1;
	m_Selected = false;
}

Component::~Component()
{}

void Component::SetLabel(string label)
{
	m_Label = label;
}

string Component::GetLabel()
{
	return m_Label;
}

void Component::SetID(int id)
{
	m_ID = id;
}

int Component::GetID()
{
	return m_ID;
}

bool Component::Inside(int x, int y)
{
	cout << "  Inside Check: " << x << "," << y << " vs Rect: " << m_GfxInfo.x1 << "," << m_GfxInfo.y1 << " - " << m_GfxInfo.x2 << "," << m_GfxInfo.y2 << endl;
	if(x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 && y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)
		return true;
	return false;
}

void Component::SetSelected(bool s)
{
	m_Selected = s;
}

bool Component::IsSelected() const
{
	return m_Selected;
}

