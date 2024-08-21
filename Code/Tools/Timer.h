#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>


namespace sf
{
	class Timer
	{
		sf::Clock clock;
		sf::Time duration;
		sf::Time elapsedTime;
		bool isRunning = false;

		void Update();
	public:

		Timer(sf::Time duration = sf::seconds(1));

		bool SetDuration(sf::Time& newDuration);

		sf::Time GetRemainingTime();
		sf::Time GetElapsedTime();

		void Start();
		void Stop();
		void Reset();

		bool IsExpired();
	};
}
