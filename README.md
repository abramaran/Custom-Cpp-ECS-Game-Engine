# Custom-Cpp-ECS-Game-Engine
Custom C++ engine I wrote using Entity Component System architecture for our game [Go!Go!! Robot Brawl](https://tako-ko.itch.io/gogo-robot-brawl). I was in charge of developing the ECS engine, and then along with several other people we implemented the systems and components for this specific game.

Below is an overview of the core classes and concepts of this engine:

## Entity

They are equivalent to actors or gameObjects in this engine. They are formed by one unique identifier and a collection of components.

## IComponent

Components store data grouped by meaning, such as position, velocity, 3d mesh... And are each linked to one entity only.

## Systems

Systems process components to carry out their purpose, such as updating physics or updating animations, among many other uses. They iterate the Component vector of a type, check that the same entity has the required components, and modify the values of the components.

## Events

Fire-and-forget components that are fired by one system and processed by another, and destroyed after being processed. For example, there is an event for when a player gets stunned, or when the animation needs to change.

## Tags

Empty components that serve an identifying purpose but do not store values. They are a convenient way of filtering entities.

## GameManager

The main class of the engine. It performs the update loop, creates the game window, controls the general flow of the game, and changes between states.

## GameStorage

Stores the vectors of entities, components and events.

## EntityManager

Factory functions to create and initialize entities.

## ComponentManager

Template functions to add and delete components.

## StateMapping

Maps each game state with its update functions and key bindings.
