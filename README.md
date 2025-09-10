# MJSDL

SDL3 + RAII + a couple of toys.

C++14 minimum required.

[toc]

## What?

`mjsdl` is simply a SDL3 wrapper for RAII safety in C++, with a couple of
small kindnesses thrown in for shiggles. It does not, nor should it, replace all
of the SDL library with wrappers, only the types where it makes sense.

The goal is to have as small a surface as possible, that can be used with
minimal changes to working code. It will not get you out of reading the SDL
documentation, doing error checking, or anything else.

Being inline header-only code, you will find that with even minimal
optimisations enabled all of the `mjsdl` code vanishes in the generated output
when using the simplest drop in replacement style.

## How?

Many of the SDL types have a cycle of Create/Destroy or Acquire/Release
functions. These are replaced by C++ move-only classes taking care of this with
RAII.

All classes have:
* Default constructors that begin the object uninitialised.
* A constructor that takes the exact arguments of the SDL creation function.
* Constructors that take the SDL type (and others needed for destruction) are
supplied to interface with other libraries or existing code.
* `get()` to access the underlying SDL type.
* `is_valid()` to test the underlying type isn't null.
* `release()` to give up ownership of the SDL type, it must then be deleted manually or by other code.

They may optionally have:
* Additional constructors to cheat a little, such as avoiding \*CreateInfo objects with only two fields.
* Helper methods, say if an item is really only used to do a couple of things. And example is `mjsdl::GPUTransferBuffer` has `map()` and `unmap()` methods.

### Implimentation Details

All construtors have an optional guard object. Check that out at [#Guards](#Guards). It's
zero-cost and does nothing by default, you can simply ignore this feature and
continue error checking however you like, if at all, It's your code.

Sometimes SDL types are created and destroyed via another item (`SDL_GPUBUffer`
takes `SDL_GPUDevice` at creation and destruction for example). Since in these
cases the item is always used at creation and destruction, `mjsdl` classes
simply hold on to it in a non-owning pointer until destruction. You need to do
nothing, and it costs only a few bytes.

Classes always have a `get()` and a `is_valid()` method, to get the internal
SDL type and to test if it is nullptr. I have decided it is better to be
explicit rather than rely on overloading operators to do the same things, such
as `std::optional` does - it's clearer and we aren't paying by the letter.

If a method returns memory that needsd to be freed by SDL_free it will be
wrapped up in a `std::unique_ptr` with a custom deleter.

Yesm it's a lot of boilerplate. You may notice a generator directory, most
classes are generated using a python script and a template. This makes
additions and modifications trivial. Don't worry, the git repo always comes
with files pre-generated, you don't need to generate anything unless you wish
to make changes.

### Huh? (example)

#### SDL.

```cpp

```

## Guards

Every constructor can take a guard object in case of errors. (Not the default
or sdl pointer stealing ones, they don't do jack and don't have errors,
probably...)

## Why?

1. Remembering to destroy a pile of items in the reverse order they were
   created in and when errors and exceptions occur is a pain in the ass. We can
   use RAII, move semantics, C compatability, type safety, and more to solve these
   issues - may as well use them in as non-intrusive a way as possible.
2. Error checking is a dick for C libraries, taking away the burden with
   dependency injected templated guard objects with overloaded operators sounds
   like a nightmare but it's really simple in practice, low effort, and zero-cost
   by default with the noop guard.
