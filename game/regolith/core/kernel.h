#pragma once

#include <vector>

namespace core {

	// A system that acts on entities. 
	// Generally, this will act on a subset of entities using World::each().
	//
	// Systems often will respond to events by subclassing EventSubscriber. 
	// You may use configure() to subscribe to events, but remember to unsubscribe in unconfigure().
	class System {
		public:
			virtual ~System() {}

			// Called when this system is added.
			virtual void startup(){}

			// Called when this system is being removed.
			virtual void shutdown(){}

			// Called when tick() is called. 
			virtual void tick() {}		
	};

	class Kernel final {
	public:


		static void run() {

		}

		template<typename ...Components>
		static void newEntity() {

		}


	private:
		
	};


}