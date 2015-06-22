/*
 * L1Downscaling.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#include "L1Downscaling.h"

#include <options/Options.h>

namespace na62 {

std::vector<std::string> L1Downscaling::algorithmTitles_;
std::atomic<int>* L1Downscaling::eventCountersByAlgoID_;
std::vector<uint> L1Downscaling::downscaleFactors_;

void L1Downscaling::initialize() {
	for (auto& algoTitle : algorithmTitles_) {
		downscaleFactors_.push_back(Options::GetInt((char*) algoTitle.c_str()));
	}
	eventCountersByAlgoID_ = new std::atomic<int>(downscaleFactors_.size());
}

uint L1Downscaling::getNumberOfRegisteredAlgorithms(){
	return algorithmTitles_.size();
}
uint L1Downscaling::registerAlgorithm(std::string algorithmTitle) {
	// Check if the algo has already been registered
	if (std::find(algorithmTitles_.begin(), algorithmTitles_.end(),
			algorithmTitle) != algorithmTitles_.end()) {
		std::cerr << "Tried to register algorithm '" << algorithmTitle
				<< "' twice!" << std::endl;
		exit(1);
	}

	algorithmTitle = "algodownscaling_" + algorithmTitle;
	Options::addOption(algorithmTitle, 1,
			"Autogenerated option for a downscaling factor of a specific L1 algorithm");

	algorithmTitles_.push_back(algorithmTitle);
	return algorithmTitles_.size() - 1;
}

} /* namespace na62 */
