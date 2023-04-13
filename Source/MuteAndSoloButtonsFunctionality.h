#pragma once

class MuteAndSoloButtonsFunctionality
{
public:

	int closeSoloGroup[6] = { 4, 8, 9, 13, 14, 18 };
	int OHSoloGroup[4] = { 5, 10, 15, 19 };
	int roomSoloGroup[4] = { 6, 11, 16, 20 };
	int bleedSoloGroup[4] = { 7, 12, 17, 21 };

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
			// solo clicked, remember the state of mute buttons before solo and mute them (except for the one with the same index, and the ones from the same group)
			else if (soloButtons[soloButtonId]->getToggleState() && i != soloButtonId)
			{
				muteStateBeforeFirstSolo[i] = muteButtons[i]->getToggleState();
				muteButtons[i]->setToggleState(true, true);
				muteButtons[i]->setEnabled(false);
			}
		}

		//unmuteMainGroupButtons(soloButtons, muteButtons, soloButtonId);

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
		
		//unmuteMainGroupButtons(soloButtons, muteButtons, soloButtonId);
	}

	void unmuteButtonsWhenSolo(std::vector<juce::ToggleButton*> muteButtons, bool muteStateBeforeFirstSolo[4])
	{
		for (int i = 0; i < muteButtons.size(); i++)
		{
			muteButtons[i]->setEnabled(true);
			muteButtons[i]->setToggleState(muteStateBeforeFirstSolo[i], true);
		}
	}

	//void unmuteMainGroupButtons(std::vector<juce::ToggleButton*> soloButtons, std::vector<juce::ToggleButton*> muteButtons, int soloButtonId)
	//{
	//	// unmute the main close mute button if the pressed solo button was one of the close solo buttons
	//	for (int j = 0; j < 6; j++)
	//	{
	//		if (soloButtonId == closeSoloGroup[j])
	//		{
	//			muteButtons[0]->setEnabled(true);
	//			muteButtons[0]->setToggleState(false, true);
	//			muteButtons[0]->setEnabled(false);
	//		}
	//	}
	//	// unmute the main mute buttons if the solo button was one of the solo group buttons
	//	for (int j = 0; j < 4; j++)
	//	{
	//		if (OHSoloGroup[j] = soloButtonId)
	//		{
	//			muteButtons[1]->setEnabled(true);
	//			muteButtons[1]->setToggleState(false, true);
	//			muteButtons[1]->setEnabled(false);
	//		}
	//		else if (roomSoloGroup[j] = soloButtonId)
	//		{
	//			muteButtons[2]->setEnabled(true);
	//			muteButtons[2]->setToggleState(false, true);
	//			muteButtons[2]->setEnabled(false);
	//		}
	//		else if (bleedSoloGroup[j] = soloButtonId)
	//		{
	//			muteButtons[3]->setEnabled(true);
	//			muteButtons[3]->setToggleState(false, true);
	//			muteButtons[3]->setEnabled(false);
	//		}
	//	}
	//}
};
