~~~ C++ PATTERNS ~~~

~ Design Patterns: https://en.wikipedia.org/wiki/Design_Patterns
	- Also called the "Gang of Four" design patterns
	- A subset of the software design patterns list (https://en.wikipedia.org/wiki/Software_design_pattern)
	- Others added later: extension interface, dependency injection, type-object
	- Other design patterns include SOLID, DRY and GRASP

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
	- flyweight: share data between objects, and generate vacant data when requested, so the client can access data in a centralised manner
	- proxy: store an object inside a wrapper of a common interface, which maintains an ulterior objective as the client indirectly accesses functionality

~ Behavioural Patterns:
	- chain of responsibiliity
	- command
	- mediator
	- observer
	- interpreter
	- state
	- strategy
	- template method
	- visitor
	- iterator
	- memento
	- null object