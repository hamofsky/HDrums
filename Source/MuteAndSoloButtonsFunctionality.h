#pragma once

class MuteAndSoloButtonsFunctionality
{
public:
	void soloStateChanged(int soloButtonId, std::vector<juce::ToggleButton*> soloButtons,
		std::vector<juce::ToggleButton*> muteButtons, bool muteStateBeforeFirstSolo[4], bool soloAlreadyEngaged)
	{
		// solo clicked for the first time
		if (soloButtons[soloButtonId]->getToggleState() && !soloAlreadyEngaged)
		{
			muteButtonsWhenSoloFirstTime(soloButtonId, soloButtons, muteButtons, muteStateBeforeFirstSolo);
			soloAlreadyEngaged = true;
			unsoloButtonsWhenSolo(soloButtonId, soloButtons);
		}
		// solo clicked for the n-th time
		else if (soloButtons[soloButtonId]->getToggleState() && soloAlreadyEngaged)
		{
			muteButtonsWhenSoloAgain(soloButtonId, soloButtons, muteButtons, muteStateBeforeFirstSolo);
			unsoloButtonsWhenSolo(soloButtonId, soloButtons);
		}
		// solo unclicked
		else if (!soloButtons[soloButtonId]->getToggleState())
		{
			unmuteButtonsWhenSolo(muteButtons, muteStateBeforeFirstSolo);
			soloAlreadyEngaged = false;
		}
	}

	void unsoloButtonsWhenSolo(int soloButtonId, std::vector<juce::ToggleButton*> soloButtons)
	{
		for (int i = 0; i < soloButtons.size(); i++)
		{
			if (i != soloButtonId)
			{
				soloButtons[i]->setToggleState(false, false);
			}
		}
	}

	void muteButtonsWhenSoloFirstTime(int soloButtonId, std::vector<juce::ToggleButton*> soloButtons,
		std::vector<juce::ToggleButton*> muteButtons, bool muteStateBeforeFirstSolo[4])
	{
		for (int i = 0; i < muteButtons.size(); i++)
		{
			// solo clicked, remember the state of a mute button with the same index and unmute it
			if (soloButtons[soloButtonId]->getToggleState() && i == soloButtonId)
			{
				muteStateBeforeFirstSolo[i] = muteButtons[i]->getToggleState();
				muteButtons[i]->setToggleState(false, true);
				muteButtons[i]->setEnabled(false);
			}
			// solo clicked, remember the state of mute buttons before solo and mute them (except for the one with the same index)
			else if (soloButtons[soloButtonId]->getToggleState() && i != soloButtonId)
			{
				muteStateBeforeFirstSolo[i] = muteButtons[i]->getToggleState();
				muteButtons[i]->setToggleState(true, true);
				muteButtons[i]->setEnabled(false);
			}
		}
	}

	void muteButtonsWhenSoloAgain(int soloButtonId, std::vector<juce::ToggleButton*> soloButtons,
		std::vector<juce::ToggleButton*> muteButtons, bool muteStateBeforeFirstSolo[4])
	{
		for (int i = 0; i < muteButtons.size(); i++)
		{
			// solo clicked, mute all buttons except for the one with the same index
			if (soloButtons[soloButtonId]->getToggleState() && i != soloButtonId)
			{
				muteButtons[i]->setToggleState(true, true);
				muteButtons[i]->setEnabled(false);
			}
			// solo clicked, unmute a button with the same index
			else if (soloButtons[soloButtonId]->getToggleState() && i == soloButtonId)
			{
				muteButtons[i]->setToggleState(false, true);
				muteButtons[i]->setEnabled(false);
			}
		}
	}

	void unmuteButtonsWhenSolo(std::vector<juce::ToggleButton*> muteButtons, bool muteStateBeforeFirstSolo[4])
	{
		for (int i = 0; i < muteButtons.size(); i++)
		{
			muteButtons[i]->setEnabled(true);
			muteButtons[i]->setToggleState(muteStateBeforeFirstSolo[i], true);
		}
	}
};
