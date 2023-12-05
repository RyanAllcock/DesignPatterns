~~~ C++ PATTERNS ~~~

~ Design Patterns: https://en.wikipedia.org/wiki/Design_Patterns
	- Also called the "Gang of Four" design patterns
	- Formally represent common programming constructs, to enhance design consistency for object-oriented codebases
	- A subset of the software design patterns list (https://en.wikipedia.org/wiki/Software_design_pattern)
	- Others added later: extension interface, dependency injection, type-object, null object
	- Other design patterns/principles include SOLID, DRY, GRASP and IDEALS

~ Creational Patterns:
	- factory: builds object components called products using a factory
	- abstract factory: builds object products based on factory themes
	- builder: assembles objects from a list of components using a director, each built using the provided builder
	- prototype shallow copy: object instance used in multiple references
	- prototype deep copy: existing object instance cloning into separate references
	- singleton: one global object instance, able to be referenced from anywhere

~ Structural Patterns:
	- adapter: interfaces an outdated object by adapting new methods from it's original methods into a wrapper, so a client can straightforwardly use the object
	- decorator: wraps the methods of an object with additional & optional functionality
	- facade: object's methods opaquely operate on more complex internal objects, to abstract complex internal functionality
	- bridge: abstract object assigns each required task in a method to an abstract implementation reference, which handle their tasks independently
	- composite: call methods across a hierarchy of same-class objects, using composite objects to distribute calls across their listed connections
	- flyweight: store flyweights in factory, dynamically add new ones by key that aren't present, each concrete flyweight has overloaded operations by context
	- proxy: store an object inside a wrapper of a common interface, which maintains an ulterior objective as the client indirectly accesses functionality

~ Behavioural Patterns:
	- chain of responsibility: chain sub-operations on an object, using a sequence of loosely-coupled handlers which receive the object then pass it along
	- command: encapsulate operations on a referenced object using command objects, so a client can store commands to be executed on a retriever at any time
	- mediator: components/colleagues communicate events with each other indirectly, by notifying a central mediator which holds shared data and states
	- observer: subject notifies all attached observers of an event, by prompting each one to update using the subject's data
	- memento: originator object copies it's current state into a memento, which is added to and managed by a caretaker
	- state: context holds a state object, which handles the context's data and can be actively replaced by a different state internally
	- strategy: context holds a strategy object, which implements an algorithm for the context's operation, and can be replaced externally by other strategies
	- null object: interface extended by concrete subclasses, alongside a null subclass with empty operations for objects awaiting concrete assignment
	- iterator: aggregate object traversed through, using iterator object which locates and processes elements from the aggregate data in a sequence
	- interpreter: expression objects from sentences describe runtime tasks, possibly non-deterministic or context-reliant, interpreted using a language symbol ruleset
	- template method: abstract class implements template method of primitives describing overall operation, primitives are implemented by concrete classes
X	- visitor