#pragma once
#include <random>
#include <map>
#include <string>
#include <vector> 
#include <list>

class RandomGenerator
{
public:
	static int random(const int min, const int max);
	static double random(const double min, const double max);

	template <typename T>
	static const T &randomFromVector(const std::vector<T> &vect) {
		if (vect.size() > 0) {
			int rand = random(0, vect.size() - 1);
			return vect[rand];
		}
		return -1;
	}

	template<typename T>
	static const T &randomFromList(const std::list<T> &list) {
		if (list.size() > 0) {
			int rand = random(0, list.size() - 1);
			auto it = list.begin();
			std::advance(it, rand);
			return *it;
		}

		return nullptr;
	}

	template<typename A, typename B>
	static const std::pair<A, B> &randomFromMap(const std::map<A, B> &map) {
		if (map.size() > 0) {
			int rand = random(0, map.size() - 1);
			auto it = map.begin();
			std::advance(it, rand);
			return *it;
		}
	}

	static const int chance(std::initializer_list<int> chances) {

		// calculate total and generate random
		int total = 0, start = 0, i = 0;
		for (auto chance : chances) total += chance;
		int rand = RandomGenerator::random(0, total - 1);

		// determine wich item has 'won'
		for (auto chance : chances) {
			// catch for filtering 0 values
			if (chance > 0) {
				if (rand >= start && rand < start + chance) {
					return i;
				}
				start += chance;
			}
			i++;
		}

		// default: 0 wins
		return 0;
	}

	static const int chance(std::initializer_list<double> chances) {

		// calculate total and generate random
		double total = 0, start = 0, i = 0;
		for (auto chance : chances) total += chance;
		double rand = RandomGenerator::random(0.0, total - 1);

		// determine wich item has 'won'
		for (auto chance : chances) {
			// catch for filtering 0 values
			if (chance > 0.0) {
				if (rand >= start && rand < start + chance) {
					return i;
				}
				start += chance;
			}
			i++;
		}

		// default: 0 wins
		return 0;
	}

private:
	RandomGenerator();
	virtual ~RandomGenerator();
	std::uniform_int_distribution<int> &getOrCreateDist(const int min, const int max);
	std::uniform_real_distribution<double> &RandomGenerator::getOrCreateDist(const double min, const double max);
	static RandomGenerator &instance();
	
	std::random_device _dev;
	std::default_random_engine _dre;
	std::map<std::string, std::uniform_int_distribution<int>*> _distMap;
	std::map<std::string, std::uniform_real_distribution<double>*>_disDouble;
};

