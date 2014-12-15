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

	static const int chance(std::initializer_list<int> chances) {

		// calculate total and generate random
		int total = 0, start = 0, i = 0;
		for (auto chance : chances) total += chance;
		int rand = RandomGenerator::random(0, total - 1);

		// determine wich item has 'won'
		for (auto chance : chances) {
			if (rand >= start && rand < start + chance) {
				return i;
			}
			start += chance;
			i++;
		}

		// default: 0 wins
		return 0;
	}

private:
	RandomGenerator();
	virtual ~RandomGenerator();
	std::uniform_int_distribution<int> &getOrCreateDist(const int min, const int max);
	static RandomGenerator &instance();
	
	std::random_device _dev;
	std::default_random_engine _dre;
	std::map<std::string, std::uniform_int_distribution<int>*> _distMap;
};

